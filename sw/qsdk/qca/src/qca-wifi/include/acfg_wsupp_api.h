/*
 * Copyright (c) 2008-2010, Atheros Communications Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef ACFG_WSUPP_API_H
#define ACFG_WSUPP_API_H

#include <stddef.h>

#include "acfg_wsupp_types.h"

/**
 * This file defines module level APIs for supplicant
 * configuration. These APIs can be divided into categories as below:
 * 1. Create/Destroy supplicant context
 * 2. Add/Remove wireless interfaces manipulated by supplicant
 * 3. Configure WPA/WPA2/WPS for wireless interfaces
 * 4. Receive events generated by supplicant
 */

/**
 * @brief Initialize the security service context
 *        This routine create a context which provide security service
 *        The flags specifies how the security service is initialized:
 *        ACFG_WSUPP_INIT_RESTART: start/restart the security service
 *              the security service must be started at least once
 *              duplicated restart calls won't be harmful and
 *              for each restart all the configuration would be removed
 *        ACFG_WSUPP_INIT_CLEANUP: clean up all the configuration
 *              for the specified interface without restarting service
 * @param [in] ifname NULL=default, char string for interface name,
 *        [in] flags
 *
 * @return an opaque handle to the module, NULL on failure
 */
acfg_wsupp_hdl_t* acfg_wsupp_init(uint8_t *ifname, acfg_wsupp_init_flags_t flags);

/**
 * @brief Cleanup any module-level resources. \n
 *        Should be called once for each acfg_wsupp_init call.
 * @param [in] mctx opaque handle to the module
 */
void acfg_wsupp_uninit(acfg_wsupp_hdl_t *mctx);

/**
 * @brief Add a WLAN n/w interface for configuration
 * @param[in] mctx module context
 * @param[in] if_uctx user context for interface
 * @param[in] ifname WLAN interface name (e.g. ath0)
 *
 * @return status of operation
 */
uint32_t acfg_wsupp_if_add(acfg_wsupp_hdl_t *mctx,
        char *ifname);

/**
 *
 * @param[in] mctx module context
 * @param[in] ifname WLAN interface name
 *
 * @return status of operation
 */
uint32_t acfg_wsupp_if_remove(acfg_wsupp_hdl_t *mctx,
        char *ifname);


/**
 *
 * @brief Add a new network to an interface - it must later be configured
 * and enabled before use.
 * @param[in] mctx module context
 * @param[in] nw_uctx user context for network
 * @param[in] ifname interface name for the driver VAP
 * @param[out] network_id for the new network
 *
 * @return status of operation
 */
uint32_t acfg_wsupp_nw_create(acfg_wsupp_hdl_t *mctx,
        char *ifname,
        int *network_id);

/**
 * @brief disconnects, and removes a network
 * @param[in] mctx module context
 * @param[in] ifname interface name for the driver VAP
 * @param[out] network_id for the new network
 *
 * @return status of operation
 */
uint32_t acfg_wsupp_nw_delete(acfg_wsupp_hdl_t *mctx,
        char *ifname,
        int network_id);

/**
 * @brief sets an item number to the passed string.
 * once a network is enabled, some attributes may no longer be set.
 * @param[in] mctx module context
 * @param[in] network_id for the new network
 * @param[in] item number to be added
 * @param[in] in_string describing ssid, psk etc.
 *
 * @return status of operation
 */
uint32_t acfg_wsupp_nw_set(acfg_wsupp_hdl_t *mctx,
        int network_id,
        enum acfg_wsupp_nw_item item,
        char *in_string);

/**
 * @brief gets an item attribute of certain network id
 * @param[in] mctx module context
 * @param[in] network_id for the new network
 * @param[in] item number
 * @param[out] reply - optional returned string for command result
 * @param [in,out] reply_len - in max size reply, out actual reply size
 *
 * @return status of operation
 */
uint32_t acfg_wsupp_nw_get(acfg_wsupp_hdl_t *mctx,
        int network_id,
        enum acfg_wsupp_nw_item item,
        char *reply, size_t *reply_len);

/**
 * @brief Lists the configured networks, including stored information for
 * persistent groups.
 *
 * The identifier in this list is used with acfg_p2p_group_add and
 * acfg_p2p_invite to indicate which persistent group is to be reinvoked.
 *
 * @param [in] mctx opaque handle to the module
 * @param [out] reply - optional returned string for command result
 * @param [in,out] reply_len - in max size reply, out actual reply size
 *
 * @return  status of operation
 */
uint32_t acfg_wsupp_nw_list(acfg_wsupp_hdl_t *mctx,
        char *reply, size_t *reply_len);

/**
 * @brief Request a wps call to handle various security requests
 * @param [in] mctx opaque handle to the module
 * @param [in] wps which form of wps request
 * @param [in] params - optional string parameters
 * @param [out] reply - optional returned string for command result
 * @param [in,out] reply_len - in max size reply, out actual reply size
 *
 * @return  status of operation
 */
uint32_t acfg_wsupp_wps_req(acfg_wsupp_hdl_t *mctx, enum acfg_wsupp_wps_type wps,
        const char *params,
        char *reply, size_t *reply_len);

/**
 * @brief set some supplicant parameter at run time.
 * @param [in] mctx opaque handle to the module
 * @param [in] type to be set in supplicant
 * @param [in] val - optional integer value if type demands one
 * @param [in] str - optional string, if type demands one
 *
 * @return  status of operation
 */
uint32_t acfg_wsupp_set(acfg_wsupp_hdl_t *mctx, enum acfg_wsupp_set_type type,
        int val, char *str);
int
acfg_set_wps_mode (uint8_t *radio_name, uint8_t *ifname,
        enum acfg_wsupp_wps_type wps,
        int8_t *params1,  int8_t *params2);
int
acfg_set_wps (int8_t *ifname, enum acfg_wsupp_set_type type, int8_t *str);

#endif
