/*
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                     Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

#define THREAD_COMMANDS \
    { (char*) "thread_list",    thread_list,        0, NULL, NULL, (char*) "",                  (char*) "[ThreadX only] Lists the current running threads"}, \
    { (char*) "thread_kill",    thread_kill,        0, NULL, NULL, (char*) "<thread id>",       (char*) "[ThreadX only] Kills the specified running thread"}, \
    { (char*) "thread_spawn",   thread_spawn,       0, NULL, NULL, (char*) "[priority] <cmds>", (char*) "[ThreadX only] Spawns a new thread for the specified command. Optionally run at a specific priority."},

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

int thread_list( int argc, char* argv[] );
int thread_kill( int argc, char* argv[] );
int thread_spawn( int argc, char* argv[] );

#ifdef __cplusplus
} /*extern "C" */
#endif
