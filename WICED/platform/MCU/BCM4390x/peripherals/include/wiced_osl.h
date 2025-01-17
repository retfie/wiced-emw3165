/*
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 *
 * WICED Run Time Environment OS Abstraction Layer.
 *
 */

#ifndef _wiced_osl_h_
#define _wiced_osl_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "RTOS/wwd_rtos_interface.h"
#include "wwd_assert.h"
#include "wwd_buffer_interface.h"

/* Define OSL assert via WICED assert */
#define ASSERT(b)               wiced_assert("peripherals", b)

/* Misc */

extern void osl_udelay(unsigned usec);

#define BUS_SWAP32(v)           (v)
#define OSL_DELAY(usec)         osl_udelay(usec)
#define OSL_ARCH_IS_COHERENT()  0
#define OSL_ACP_WAR_ENAB()      0

/* Register access macros */

#define compile_barrier()       __asm__ __volatile__ ("" : : : "memory") /* assume registers are Device memory, so have implicit CPU memory barriers */

#define wreg32(r, v)            ({*(volatile uint32 *)(r) = (uint32)(v); compile_barrier();})
#define rreg32(r)               (*(volatile uint32 *)(r))
#define wreg16(r, v)            ({*(volatile uint16 *)(r) = (uint16)(v); compile_barrier();})
#define rreg16(r)               (*(volatile uint16 *)(r))
#define wreg8(r, v)             ({*(volatile uint8 *)(r) = (uint8)(v); compile_barrier();})
#define rreg8(r)                (*(volatile uint8 *)(r))

#if defined (__GNUC__)
#define R_REG(osh, r)           (BCM_REFERENCE(osh), *((volatile typeof(r))(r)))
#define W_REG(osh, r, v)        ({BCM_REFERENCE(osh); *((volatile typeof(r))(r)) = (v); compile_barrier();})
#else
#define R_REG(osh, r) \
    (BCM_REFERENCE(osh), sizeof(*(r)) == sizeof(uint32_t) ? \
        rreg32(r) : (sizeof(*(r)) == sizeof(uint16_t) ? rreg16(r) : rreg8(r)))
#define W_REG(osh, r, v) \
    do { \
        BCM_REFERENCE(osh); \
        if (sizeof(*(r)) == sizeof(uint32)) { \
            wreg32(r, v); \
        } else if (sizeof(*(r)) == sizeof(uint16)) { \
            wreg16(r, v); \
        } else { \
            wreg8(r, v); \
        } \
    } while (0)
#endif

#define AND_REG(osh, r, v)      W_REG(osh, (r), R_REG(osh, r) & (v))
#define OR_REG(osh, r, v)       W_REG(osh, (r), R_REG(osh, r) | (v))

#define REG_MAP(pa, size)       ({BCM_REFERENCE(size); (void *)(pa);})
#define REG_UNMAP(va)           BCM_REFERENCE(va)

/* general purpose memory allocation */

extern void* osl_malloc_align(uint size, uint align_bits);
extern int osl_mfree(void *addr);

#define MALLOC(osh, size)                       ({BCM_REFERENCE(osh); malloc(size);})
#define MALLOC_ALIGN(osh, size, align_bits)     ({BCM_REFERENCE(osh); osl_malloc_align(size, align_bits);})
#define MFREE(osh, addr, size)                  ({BCM_REFERENCE(osh); BCM_REFERENCE(size); free(addr);})
#define MALLOCED(osh)                           ({BCM_REFERENCE(osh); 0;})
#define MALLOC_FAILED(osh)                      ({BCM_REFERENCE(osh); 0;})
#define MALLOC_DUMP(osh, b)                     ({BCM_REFERENCE(osh); BCM_REFERENCE(b);})

/* Prefetch */

static inline void bcm_prefetch_32B(const uint8 *addr, const int cachelines_32B)
{
    switch (cachelines_32B)
    {
        case 4:__asm__ __volatile__("pld\t%a0" :: "p"(addr + 96) : "cc");
        case 3:__asm__ __volatile__("pld\t%a0" :: "p"(addr + 64) : "cc");
        case 2:__asm__ __volatile__("pld\t%a0" :: "p"(addr + 32) : "cc");
        case 1:__asm__ __volatile__("pld\t%a0" :: "p"(addr +  0) : "cc");
        default: break;
    }
}

/* DMA memory allocation */

extern void* osl_dma_alloc_consistent(uint size, uint16 align_bits, uint *alloced, dmaaddr_t *descpa);
extern void osl_dma_free_consistent(void *va);

#define DMA_ALLOC_CONSISTENT(osh, size, align, alloced, pap, dmah) \
    ({ \
        BCM_REFERENCE(osh); \
        BCM_REFERENCE(dmah); \
        osl_dma_alloc_consistent(size, align, alloced, pap); \
    })
#define DMA_FREE_CONSISTENT(osh, va, size, pa, dmah) \
    ({ \
        BCM_REFERENCE(osh); \
        BCM_REFERENCE(size); \
        BCM_REFERENCE(pa); \
        BCM_REFERENCE(dmah); \
        osl_dma_free_consistent(va); \
    })

/* DMA memory mapping/unmapping */

extern dmaaddr_t osl_dma_map(void *va, uint size, int direction);

#define DMA_TX            1    /* TX direction for DMA map/unmap */
#define DMA_RX            2    /* RX direction for DMA map/unmap */

#define DMA_MAP(osh, va, size, direction, p, dmah) \
    ({ \
        BCM_REFERENCE(osh); \
        BCM_REFERENCE(p); \
        BCM_REFERENCE(dmah); \
        osl_dma_map(va, size, direction); \
    })
#define DMA_UNMAP(osh, pa, size, direction, p, dmah) \
    ({ \
        BCM_REFERENCE(osh); \
        BCM_REFERENCE(pa); \
        BCM_REFERENCE(size); \
        BCM_REFERENCE(direction); \
        BCM_REFERENCE(p); \
        BCM_REFERENCE(dmah); \
    })

/* Shared (dma-able) memory access macros */
#define R_SM(r)                         *(r)
#define W_SM(r, v)                      (*(r) = (v))
#define BZERO_SM(r, len)                memset((r), '\0', (len))

/* Packet primitives */

extern void* osl_pktget(void *osh, uint len, bool send);
extern void osl_pktfree(void *osh, void *p, bool send);

#define PKTGET(osh, len, send)          osl_pktget(osh, len, send)
#define PKTFREE(osh, p, send)           osl_pktfree(osh, p, send)
#define PKTDATA(osh, p)                 ({BCM_REFERENCE(osh); host_buffer_get_current_piece_data_pointer(p);})
#define PKTLEN(osh, p)                  ({BCM_REFERENCE(osh); host_buffer_get_current_piece_size(p);})
#define PKTSETLEN(osh, p, len)          ({BCM_REFERENCE(osh); host_buffer_set_size(p, len);})
#define PKTPULL(osh, p, bytes)          ({BCM_REFERENCE(osh); host_buffer_add_remove_at_front((wiced_buffer_t *)&p, bytes);})
#define PKTPUSH(osh, p, bytes)          PKTPULL(osh, p, -bytes)
#define PKTPRIO(p)                      ({BCM_REFERENCE(p); 0;})
#define PKTNEXT(osh, p)                 ({BCM_REFERENCE(osh); host_buffer_get_next_piece(p);})
#define PKTSETNEXT(osh, p, x)           ({BCM_REFERENCE(osh); BCM_REFERENCE(p); BCM_REFERENCE(x); ASSERT(0);})

#define bcopy(src, dst, len)            memcpy((dst), (src), (len))
#define bcmp(b1, b2, len)               memcmp((b1), (b2), (len))
#define bzero(b, len)                   memset((b), 0, (len))

/* Backplane Clocks */

extern uint32 osl_alp_clock(void);
extern uint32 osl_ht_clock(void);
extern uint32 osl_ilp_clock(void);
extern uint32 osl_backplane_clock(uint32 core_base);
extern void   osl_set_int_lpoclk(uint32 cpu_freq);
extern void   osl_set_ext_lpoclk(uint32 cpu_freq);

/* Core control */
extern void   osl_core_enable(uint coreid);
extern uint   osl_get_corerev(uint coreid);
extern void   osl_wrapper_disable(void *wrapper);
extern void   osl_wrapper_enable(void *wrapper);

/* OSH structure */
typedef struct wiced_osh
{
    int32_t pktget_add_remove;
    int32_t pktfree_add_remove;
} wiced_osh_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _wiced_osl_h_ */
