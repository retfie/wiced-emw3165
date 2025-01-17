/*
 *
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 *
 * $Id: wlu.h 473249 2014-04-28 20:23:06Z fengwang $
 */

#ifndef _wlu_h_
#define _wlu_h_

#include "wlu_cmd.h"

extern const char *wlu_av0;

/* parse common option */
extern int wl_option(char ***pargv, char **pifname, int *phelp);
extern void wl_cmd_init(void);
extern void wlu_init(void);

/* print usage */
extern void wl_cmd_usage(FILE *fid, cmd_t *cmd);
extern void wl_usage(FILE *fid, cmd_t *port_cmds);
extern void wl_cmds_usage(FILE *fid, cmd_t *port_cmds);

/* print helpers */
extern void wl_printlasterror(void *wl);
extern void wl_printint(int val);

/* pretty print an SSID */
extern int wl_format_ssid(char* buf, uint8* ssid, int ssid_len);

/* pretty hex print a contiguous buffer */
extern void wl_hexdump(uchar *buf, uint nbytes);

/* check driver version */
extern int wl_check(void *wl);

/* wl functions used by the ndis wl. */
extern void dump_rateset(uint8 *rates, uint count);
extern uint freq2channel(uint freq);
extern int wl_ether_atoe(const char *a, struct ether_addr *n);
extern char *wl_ether_etoa(const struct ether_addr *n);
struct ipv4_addr;	/* forward declaration */
extern int wl_atoip(const char *a, struct ipv4_addr *n);
extern char *wl_iptoa(const struct ipv4_addr *n);
extern cmd_func_t wl_int;
extern cmd_func_t wl_varint;
extern void wl_dump_raw_ie(bcm_tlv_t *ie, uint len);
extern int wl_mk_ie_setbuf(const char *command, uint32 pktflag_ok, char **argv,
	vndr_ie_setbuf_t **buf, int *buf_len);
extern cmd_func_t wl_list_ie;

extern void wl_printlasterror(void *wl);
extern bool wc_cmd_check(const char *cmd);

#ifdef BCMINTERNAL
extern int wl_iov_names(void *wl, cmd_t *cmd, char **argv);
extern int wl_cmd_help(void *wl, cmd_t *cmd_in, char **argv);
#endif

/* functions for downloading firmware to a device via serial or other transport */
#ifdef SERDOWNLOAD
extern int dhd_init(void *dhd, cmd_t *cmd, char **argv);
extern int dhd_download(void *dhd, cmd_t *cmd, char **argv);
extern int hsic_download(void *dhd, cmd_t *cmd, char **argv);
extern int rwl_download(void *dhd, cmd_t *cmd, char **argv);
#endif /* SERDOWNLOAD */

#ifdef BCMDLL
#ifdef LOCAL
extern FILE *dll_fd;
#else
extern void * dll_fd_out;
extern void * dll_fd_in;
#endif
#undef printf
#undef fprintf
#define printf printf_to_fprintf	/* printf to stdout */
#define fprintf fprintf_to_fprintf	/* fprintf to stderr */
extern void fprintf_to_fprintf(FILE * stderror, const char *fmt, ...);
extern void printf_to_fprintf(const char *fmt, ...);
extern void raw_puts(const char *buf, void *dll_fd_out);
#define	fputs(buf, stdout) raw_puts(buf, dll_fd_out)
#endif /* BCMDLL */

extern int wlu_var_getbuf(void *wl, const char *iovar, void *param, int param_len, void **bufptr);
extern chanspec_t wl_chspec_from_driver(chanspec_t chanspec);
extern chanspec_t wl_chspec_to_driver(chanspec_t chanspec);
extern int wlu_var_getbuf_sm(void *wl, const char *iovar, void *param, int param_len,
	void **bufptr);
extern char* wl_rate_print(char *rate_buf, uint32 rspec);
extern int ARGCNT(char **argv);

#define RAM_SIZE_4325  0x60000
#define RAM_SIZE_4329  0x48000
#define RAM_SIZE_43291 0x60000
#define RAM_SIZE_4330_a1  0x3c000
#define RAM_SIZE_4330_b0  0x48000

/* useful macros */
#ifndef ARRAYSIZE
#define ARRAYSIZE(a)  (sizeof(a)/sizeof(a[0]))
#endif /* ARRAYSIZE */

/* buffer length needed for wl_format_ssid
 * 32 SSID chars, max of 4 chars for each SSID char "\xFF", plus NULL
 */
#define SSID_FMT_BUF_LEN (4*32+1)	/* Length for SSID format string */
#define USAGE_ERROR  -1     /* Error code for Usage */
#define IOCTL_ERROR  -2     /* Error code for Ioctl failure */
#define BAD_PARAM -3 /* Error code for bad params, but don't dump cmd_help */
#define CMD_DEPRECATED -4 /* Commands that are functionally deprecated or don't provide
			   * a useful value to a specific OS port of wl
			   */

/* integer output format */
#define INT_FMT_DEC	0	/* signed integer */
#define INT_FMT_UINT	1	/* unsigned integer */
#define INT_FMT_HEX	2	/* hexdecimal */

/* command line argument usage */
#define CMD_ERR	-1	/* Error for command */
#define CMD_OPT	0	/* a command line option */
#define CMD_WL	1	/* the start of a wl command */

#endif /* _wlu_h_ */
