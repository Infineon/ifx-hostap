/*
 * Infineon: vendor OUI and specific assignments
 *
 * ©2022 Cypress Semiconductor Corporation (an Infineon company)
 * or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
 * This software, including source code, documentation and related materials
 * ("Software") is owned by Cypress Semiconductor Corporation or one of its
 * affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license agreement
 * accompanying the software package from which you obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software source code
 * solely for use in connection with Cypress's integrated circuit products.
 * Any reproduction, modification, translation, compilation, or representation
 * of this Software except as specified above is prohibited without
 * the expresswritten permission of Cypress.
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * Cypress reserves the right to make changes to the Software without notice.
 * Cypress does not assume any liability arising out of the application or
 * use of the Software or any product or circuit described in the Software.
 * Cypress does not authorize its products for use in any products where a malfunction
 * or failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product").
 * By including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing so
 * agrees to indemnify Cypress against all liability.
 */

#ifndef IFX_VENDOR_H
#define IFX_VENDOR_H

/*
 * This file is a registry of identifier assignments from the Infineon
 * OUI 00:03:19 for purposes other than MAC address assignment. New identifiers
 * can be assigned through normal review process for changes to the upstream
 * hostap.git repository.
 */
#define OUI_IFX		0x000319

/*
 * enum ifx_nl80211_vendor_subcmds - IFX nl80211 vendor command identifiers
 *
 * @IFX_VENDOR_SCMD_UNSPEC: Reserved value 0
 *
 * @IFX_VENDOR_SCMD_FRAMEBURST: Vendor command to enable/disable Frameburst
 *
 * @IFX_VENDOR_SCMD_MUEDCA_OPT_ENABLE: Vendor command to enable/disable HE MU-EDCA opt
 *
 * @IFX_VENDOR_SCMD_LDPC_CAP: Vendor command enable/disable LDPC Capability
 *
 * @IFX_VENDOR_SCMD_AMSDU: Vendor command to enable/disable AMSDU on all the TID queues
 *
 * @IFX_VENDOR_SCMD_TWT: Vendor subcommand to configure TWT
 *	Uses attributes defined in enum ifx_vendor_attr_twt.
 * @IFX_VENDOR_SCMD_MBO: Vendor subcommand to configure MBO
 *	Uses attribute IFX_VENDOR_ATTR_MBO to configure.
 *
 * @IFX_VENDOR_SCMD_MAX: This acts as a the tail of cmds list.
 *      Make sure it located at the end of the list.
 */
enum ifx_nl80211_vendor_subcmds {
	/*
	 * TODO: IFX Vendor subcmd enum IDs between 1-10 are reserved
	 * to be be filled later with BRCM Vendor subcmds that are
	 * already used by IFX.
	 */
	IFX_VENDOR_SCMD_UNSPEC		= 0,
	/* Reserved 1-5 */
	IFX_VENDOR_SCMD_FRAMEBURST	= 6,
	/* Reserved 7-10 */
	IFX_VENDOR_SCMD_MUEDCA_OPT_ENABLE = 11,
	IFX_VENDOR_SCMD_LDPC_CAP	= 12,
	IFX_VENDOR_SCMD_AMSDU		= 13,
	IFX_VENDOR_SCMD_TWT		= 14,
	/* Reserved 15-17 */
	IFX_VENDOR_SCMD_MBO		= 18,
	IFX_VENDOR_SCMD_MAX
};

/*
 * enum ifx_vendor_attr - IFX nl80211 vendor attributes
 *
 * @IFX_VENDOR_ATTR_UNSPEC: Reserved value 0
 *
 * @IFX_VENDOR_ATTR_MAX: This acts as a the tail of attrs list.
 *      Make sure it located at the end of the list.
 */
enum ifx_vendor_attr {
	/*
	 * TODO: IFX Vendor attr enum IDs between 0-10 are reserved
	 * to be filled later with BRCM Vendor attrs that are
	 * already used by IFX.
	 */
	IFX_VENDOR_ATTR_UNSPEC		= 0,
	/* Reserved 1-10 */
	IFX_VENDOR_ATTR_MAX		= 11
};

enum ifx_vendor_attr_mbo {
	IFX_VENDOR_ATTR_MBO_UNSPEC,
	IFX_VENDOR_ATTR_MBO_CMD,
	IFX_VENDOR_ATTR_MBO_PARAMS,
	IFX_VENDOR_ATTR_MBO_MAX
};

/*
 * enum ifx_vendor_attr_twt - Attributes for the TWT vendor command
 *
 * @IFX_VENDOR_ATTR_TWT_UNSPEC: Reserved value 0
 *
 * @IFX_VENDOR_ATTR_TWT_OPER: To specify the type of TWT operation
 *	to be performed. Uses attributes defined in enum ifx_twt_oper.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAMS: Nester attributes representing the
 *	parameters configured for TWT. These parameters are defined in
 *	the enum ifx_vendor_attr_twt_param.
 *
 * @IFX_VENDOR_ATTR_TWT_MAX: This acts as a the tail of cmds list.
 *      Make sure it located at the end of the list.
 */
enum ifx_vendor_attr_twt {
	IFX_VENDOR_ATTR_TWT_UNSPEC,
	IFX_VENDOR_ATTR_TWT_OPER,
	IFX_VENDOR_ATTR_TWT_PARAMS,
	IFX_VENDOR_ATTR_TWT_MAX
};

/*
 * enum ifx_twt_oper - TWT operation to be specified using the vendor
 * attribute IFX_VENDOR_ATTR_TWT_OPER
 *
 * @IFX_TWT_OPER_UNSPEC: Reserved value 0
 *
 * @IFX_TWT_OPER_SETUP: Setup a TWT session. Required parameters are
 *	obtained through the nested attrs under IFX_VENDOR_ATTR_TWT_PARAMS.
 *
 * @IFX_TWT_OPER_TEARDOWN: Teardown the already negotiated TWT session.
 *	Required parameters are obtained through the nested attrs under
 *	IFX_VENDOR_ATTR_TWT_PARAMS.
 *
 * @IFX_TWT_OPER_MAX: This acts as a the tail of the list.
 *      Make sure it located at the end of the list.
 */
enum ifx_twt_oper {
	IFX_TWT_OPER_UNSPEC,
	IFX_TWT_OPER_SETUP,
	IFX_TWT_OPER_TEARDOWN,
	IFX_TWT_OPER_MAX
};

/*
 * enum ifx_vendor_attr_twt_param - TWT parameters
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_UNSPEC: Reserved value 0
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_NEGO_TYPE: Specifies the type of Negotiation to be
 *	done during Setup. The four possible types are
 *	0 - Individual TWT Negotiation
 *	1 - Wake TBTT Negotiation
 *	2 - Broadcast TWT in Beacon
 *	3 - Broadcast TWT Membership Negotiation
 *
 *	The possible values are defined in the enum ifx_twt_param_nego_type
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_SETUP_CMD_TYPE: Specifies the type of TWT Setup frame
 *	when sent by the TWT Requesting STA
 *	0 - Request
 *	1 - Suggest
 *	2 - Demand
 *
 *	when sent by the TWT Responding STA.
 *	3 - Grouping
 *	4 - Accept
 *	5 - Alternate
 *	6 - Dictate
 *	7 - Reject
 *
 *	The possible values are defined in the enum ifx_twt_oper_setup_cmd_type.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_DIALOG_TOKEN: Dialog Token used by the TWT Requesting STA to
 *	identify the TWT Setup request/response transaction.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_WAKE_TIME: Target Wake Time.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_WAKE_TIME_OFFSET: Target Wake Time Offset.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION: Nominal Minimum TWT Wake Duration.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_EXPONENT: TWT Wake Interval Exponent.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_MANTISSA: TWT Wake Interval Mantissa.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_REQUESTOR: Specify this is a TWT Requesting / Responding STA.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_TRIGGER: Specify Trigger based / Non-Trigger based TWT Session.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_IMPLICIT: Specify Implicit / Explicit TWT session.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_FLOW_TYPE: Specify Un-Announced / Announced TWT session.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_FLOW_ID: Flow ID of an iTWT session.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_BCAST_TWT_ID: Brocast TWT ID of a bTWT session.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_PROTECTION: Specifies whether Tx within SP is protected.
 *	Set to 1 to indicate that TXOPs within the TWT SPs shall be initiated
 *	with a NAV protection mechanism, such as (MU) RTS/CTS or CTS-to-self frame;
 *	otherwise, it shall set it to 0.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_CHANNEL: TWT channel field which is set to 0, unless
 * 	the HE STA sets up a subchannel selective transmission operation.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_TWT_INFO_FRAME_DISABLED: TWT Information frame RX handing
 *	disabled / enabled.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION_UNIT: Nominal Minimum TWT Wake Duration
 *	Unit. 0 represents unit in "256 usecs" and 1 represents unit in "TUs".
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_TEARDOWN_ALL_TWT: Teardown all negotiated TWT sessions.
 *
 * @IFX_VENDOR_ATTR_TWT_PARAM_MAX: This acts as a the tail of the list.
 *      Make sure it located at the end of the list.
 */
enum ifx_vendor_attr_twt_param {
	IFX_VENDOR_ATTR_TWT_PARAM_UNSPEC,
	IFX_VENDOR_ATTR_TWT_PARAM_NEGO_TYPE,
	IFX_VENDOR_ATTR_TWT_PARAM_SETUP_CMD_TYPE,
	IFX_VENDOR_ATTR_TWT_PARAM_DIALOG_TOKEN,
	IFX_VENDOR_ATTR_TWT_PARAM_WAKE_TIME,
	IFX_VENDOR_ATTR_TWT_PARAM_WAKE_TIME_OFFSET,
	IFX_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION,
	IFX_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_EXPONENT,
	IFX_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_MANTISSA,
	IFX_VENDOR_ATTR_TWT_PARAM_REQUESTOR,
	IFX_VENDOR_ATTR_TWT_PARAM_TRIGGER,
	IFX_VENDOR_ATTR_TWT_PARAM_IMPLICIT,
	IFX_VENDOR_ATTR_TWT_PARAM_FLOW_TYPE,
	IFX_VENDOR_ATTR_TWT_PARAM_FLOW_ID,
	IFX_VENDOR_ATTR_TWT_PARAM_BCAST_TWT_ID,
	IFX_VENDOR_ATTR_TWT_PARAM_PROTECTION,
	IFX_VENDOR_ATTR_TWT_PARAM_CHANNEL,
	IFX_VENDOR_ATTR_TWT_PARAM_TWT_INFO_FRAME_DISABLED,
	IFX_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION_UNIT,
	IFX_VENDOR_ATTR_TWT_PARAM_TEARDOWN_ALL_TWT,
	IFX_VENDOR_ATTR_TWT_PARAM_MAX
};

enum ifx_twt_param_nego_type {
	IFX_TWT_PARAM_NEGO_TYPE_INVALID			= -1,
	IFX_TWT_PARAM_NEGO_TYPE_ITWT			= 0,
	IFX_TWT_PARAM_NEGO_TYPE_WAKE_TBTT		= 1,
	IFX_TWT_PARAM_NEGO_TYPE_BTWT_IE_BCN		= 2,
	IFX_TWT_PARAM_NEGO_TYPE_BTWT			= 3,
	IFX_TWT_PARAM_NEGO_TYPE_MAX			= 4
};

enum ifx_twt_oper_setup_cmd_type {
	IFX_TWT_OPER_SETUP_CMD_TYPE_INVALID	= -1,
	IFX_TWT_OPER_SETUP_CMD_TYPE_REQUEST	= 0,
	IFX_TWT_OPER_SETUP_CMD_TYPE_SUGGEST	= 1,
	IFX_TWT_OPER_SETUP_CMD_TYPE_DEMAND	= 2,
	IFX_TWT_OPER_SETUP_CMD_TYPE_GROUPING	= 3,
	IFX_TWT_OPER_SETUP_CMD_TYPE_ACCEPT	= 4,
	IFX_TWT_OPER_SETUP_CMD_TYPE_ALTERNATE	= 5,
	IFX_TWT_OPER_SETUP_CMD_TYPE_DICTATE	= 6,
	IFX_TWT_OPER_SETUP_CMD_TYPE_REJECT	= 7,
	IFX_TWT_OPER_SETUP_CMD_TYPE_MAX		= 8
};

enum ifx_mbo_config_cmd_type {
	IFX_MBO_CONFIG_CMD_TYPE_INVALID		= -1,
	//align internal definition
	IFX_MBO_CONFIG_CMD_ADD_CHAN_PREF	= 1,
	IFX_MBO_CONFIG_CMD_DEL_CHAN_PREF	= 2,
	IFX_MBO_CONFIG_CMD_LIST_CHAN_PREF	= 3,
	IFX_MBO_CONFIG_CMD_CELLULAR_DATA_CAP	= 4,
	IFX_MBO_CONFIG_CMD_DUMP_COUNTER		= 5,
	IFX_MBO_CONFIG_CMD_CLEAR_COUNTER	= 6,
	IFX_MBO_CONFIG_CMD_FORCE_ASSOC		= 7,
	IFX_MBO_CONFIG_CMD_BSSTRANS_REJ		= 8,
	IFX_MBO_CONFIG_CMD_SEND_NOTIF		= 9,
	IFX_MBO_CONFIG_CMD_CLR_CHAN_PREF	= 10,
	IFX_MBO_CONFIG_CMD_NBR_INFO_CACHE	= 11,
	IFX_MBO_CONFIG_CMD_ANQPO_SUPPORT	= 12,
	IFX_MBO_CONFIG_CMD_DBG_EVENT_CHECK	= 13,
	IFX_MBO_CONFIG_CMD_EVENT_MASK		= 14,
	IFX_MBO_CONFIG_CMD_ASSOC_DISALLOWED	= 15,
	IFX_MBO_CONFIG_CMD_CELLULAR_DATA_PREF	= 16,
	IFX_MBO_CONFIG_CMD_TYPE_MAX		= 17
};

enum ifx_vendor_attr_mbo_param {
	IFX_VENDOR_ATTR_MBO_PARAM_UNSPEC,
	IFX_VENDOR_ATTR_MBO_PARAM_OPCLASS,
	IFX_VENDOR_ATTR_MBO_PARAM_CHAN,
	IFX_VENDOR_ATTR_MBO_PARAM_PREFERENCE,
	IFX_VENDOR_ATTR_MBO_PARAM_REASON_CODE,
	IFX_VENDOR_ATTR_MBO_PARAM_CELL_DATA_CAP,
	IFX_VENDOR_ATTR_MBO_PARAM_COUNTERS,
	IFX_VENDOR_ATTR_MBO_PARAM_ENABLE,
	IFX_VENDOR_ATTR_MBO_PARAM_SUB_ELEM_TYPE,
	IFX_VENDOR_ATTR_MBO_PARAM_BTQ_TRIG_START_OFFSET,
	IFX_VENDOR_ATTR_MBO_PARAM_BTQ_TRIG_RSSI_DELTA,
	IFX_VENDOR_ATTR_MBO_PARAM_ANQP_CELL_SUPP,
	IFX_VENDOR_ATTR_MBO_PARAM_BIT_MASK,
	IFX_VENDOR_ATTR_MBO_PARAM_ASSOC_DISALLOWED,
	IFX_VENDOR_ATTR_MBO_PARAM_CELLULAR_DATA_PREF,
	IFX_VENDOR_ATTR_MBO_PARAM_MAX
};

#endif /* IFX_VENDOR_H */
