#
# Copyright 2015, Broadcom Corporation
# All Rights Reserved.
#
# This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
# the contents of this file may not be disclosed to third parties, copied
# or duplicated in any form, in whole or in part, without the prior
# written permission of Broadcom Corporation.
#

NAME := WICED_NetX_Interface

GLOBAL_INCLUDES := .

$(NAME)_SOURCES := wiced_network.c \
                   tcpip.c \
                   ../../wiced_network_common.c \
                   ../../wiced_tcpip_common.c

$(NAME)_COMPONENTS := daemons/DHCP_server \
                      utilities/linked_list

$(NAME)_CFLAGS  = $(COMPILER_SPECIFIC_PEDANTIC_CFLAGS)

$(NAME)_CHECK_HEADERS := wiced_network.h