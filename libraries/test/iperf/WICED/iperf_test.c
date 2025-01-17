/*
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#include "iperf.h"
#include <stdlib.h>
#include "wwd_debug.h"

extern int iperf     ( int argc, char* argv[] );

/*!
 ******************************************************************************
 * Call the iperf command for a number of iterations
 *
 * @return  0 for success, otherwise error
 */

int iperf_test( int argc, char* argv[] )
{
    int iterations = atoi(argv[1]);
    int a = 0;

    while ( a < iterations )
    {
        WPRINT_APP_INFO( ( "---------------------------------------------------------------- Iteration %d ---------------\n", a ) );
        iperf( argc - 2, &argv[2] );
        a++;
    }
    return 0;
}

