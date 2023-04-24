/*
 * Infineon OUI and vendor specific assignments
 * Copyright (c) 2023, Cypress Semiconductor Corporation (an Infineon company)
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef INF_VENDOR_H
#define INF_VENDOR_H

/*
 * This file is a registry of identifier assignments from the Infineon
 * OUI 00:03:19 for purposes other than MAC address assignment. New identifiers
 * can be assigned through normal review process for changes to the upstream
 * hostap.git repository.
 */
#define OUI_INF		0x000319

/*
 * enum inf_nl80211_vendor_subcmds - INF nl80211 vendor command identifiers
 *
 * @INF_VENDOR_SCMD_UNSPEC: Reserved value 0
 *
 * @INF_VENDOR_SCMD_DCMD: Handle the Dongle commands triggered from the userspace utilities.
 *	These commands will be passed to the Dongle for processing.
 *
 * @INF_VENDOR_SCMD_FRAMEBURST: Control the Frameburst feature in the Dongle. This feature
 *	allows more efficient use of the airtime between the transmitting and receiving WLAN
 *	devices.
 *
 * @INF_VENDOR_SCMD_ACS: Configure the Automatic Channel Selection (ACS) feature
 *
 * @INF_VENDOR_SCMD_SET_MAC_P2P_DEV: Set MAC address for a P2P Discovery device.
 *	Uses Vendor attribute INF_VENDOR_ATTR_MAC_ADDR to pass the MAC address.
 *
 * @INF_VENDOR_SCMD_MUEDCA: Configure Multi User Enhanced Distrubuted Channel Access (MU-EDCA).
 *
 * @INF_VENDOR_SCMD_LDPC: Enable support for handling Low Density Parity Check (LDPC) Coding
 *	in received payload.
 *
 * @INF_VENDOR_SCMD_AMSDU: Control AMSDU aggregation for both TX & RX on all the TID queues.
 *
 * @INF_VENDOR_SCMD_TWT_OFFLOAD: Offload Target Wake Time (TWT) Session configuration to the Dongle.
 *	Uses Vendor attributes defined in the enum inf_vendor_attr_twt to pass needed parameters.
 *
 * @INF_VENDOR_SCMD_OCE: Configure the Optimized Connectivity Experience (OCE) functionality
 *	related parameters.
 *
 * @INF_VENDOR_SCMD_BSSCOLOR: Set BSS Color (1-63) for AP Mode operation in HE.
 *
 * @INF_VENDOR_SCMD_RAND_MAC: Configure the Random MAC module in the Dongle.
 *
 * @INF_VENDOR_SCMD_MPC: Control the Minimum Power Consumption (MPC) feature in the Dongle.
 *	This is a STA-only power saving feature and not related to 802.11 power save.
 *
 * @INF_VENDOR_SCMD_GIANTRX: Allow handling RX MGMT Packts of size 1840 bytes in the Dongle.
 *
 * @INF_VENDOR_SCMD_PFN_CONFIG: Send the Preferred Network (PFN) information to the Dongle
 *	through the driver.
 *
 * @INF_VENDOR_SCMD_PFN_STATUS: Fetch the Preferred Network (PFN) information from the Dongle
 *	through the driver.
 *
 * @INF_VENDOR_SCMD_MAX: This acts as a the tail of cmds list.
 *      Make sure it located at the end of the list.
 */
enum inf_nl80211_vendor_subcmds {
	INF_VENDOR_SCMD_UNSPEC			= 0,
	INF_VENDOR_SCMD_DCMD			= 1,
	/* Reserved 2-5 */
	INF_VENDOR_SCMD_FRAMEBURST		= 6,
	/* Reserved 7-8 */
	INF_VENDOR_SCMD_ACS			= 9,
	INF_VENDOR_SCMD_SET_MAC_P2P_DEV		= 10,
	INF_VENDOR_SCMD_MUEDCA			= 11,
	INF_VENDOR_SCMD_LDPC			= 12,
	INF_VENDOR_SCMD_AMSDU			= 13,
	INF_VENDOR_SCMD_TWT_OFFLOAD		= 14,
	INF_VENDOR_SCMD_OCE			= 15,
	INF_VENDOR_SCMD_BSSCOLOR		= 16,
	INF_VENDOR_SCMD_RAND_MAC		= 17,
	/* Reserved 18 */
	INF_VENDOR_SCMD_MPC			= 19,
	INF_VENDOR_SCMD_GIANTRX			= 20,
	INF_VENDOR_SCMD_PFN_CONFIG		= 21,
	INF_VENDOR_SCMD_PFN_STATUS		= 22,
	INF_VENDOR_SCMD_MAX
};

/*
 * enum inf_vendor_attr - INF nl80211 vendor attributes
 *
 * @INF_VENDOR_ATTR_UNSPEC: Reserved value 0
 *
 * @INF_VENDOR_ATTR_LEN: Dongle Command Message Body Length.
 *
 * @INF_VENDOR_ATTR_DATA: Dongle Commend Message Body.
 *
 * @INF_VENDOR_ATTR_MAC_ADDR: Medium Access Control (MAC) address.
 *
 * @INF_VENDOR_ATTR_MAX: This acts as a the tail of attrs list.
 *      Make sure it located at the end of the list.
 */
enum inf_vendor_attr {
	INF_VENDOR_ATTR_UNSPEC		= 0,
	INF_VENDOR_ATTR_LEN		= 1,
	INF_VENDOR_ATTR_DATA		= 2,
	INF_VENDOR_ATTR_MAC_ADDR	= 3,
	INF_VENDOR_ATTR_MAX
};

/*
 * enum inf_vendor_attr_twt - Attributes for the TWT vendor command
 *
 * @INF_VENDOR_ATTR_TWT_UNSPEC: Reserved value 0
 *
 * @INF_VENDOR_ATTR_TWT_OPER: To specify the type of TWT operation
 *	to be performed. Uses attributes defined in enum inf_twt_oper.
 *
 * @INF_VENDOR_ATTR_TWT_PARAMS: Nester attributes representing the
 *	parameters configured for TWT. These parameters are defined in
 *	the enum inf_vendor_attr_twt_param.
 *
 * @INF_VENDOR_ATTR_TWT_MAX: This acts as a the tail of cmds list.
 *      Make sure it located at the end of the list.
 */
enum inf_vendor_attr_twt {
	INF_VENDOR_ATTR_TWT_UNSPEC,
	INF_VENDOR_ATTR_TWT_OPER,
	INF_VENDOR_ATTR_TWT_PARAMS,
	INF_VENDOR_ATTR_TWT_MAX
};

/*
 * enum inf_twt_oper - TWT operation to be specified using the vendor
 * attribute INF_VENDOR_ATTR_TWT_OPER
 *
 * @INF_TWT_OPER_UNSPEC: Reserved value 0
 *
 * @INF_TWT_OPER_SETUP: Setup a TWT session. Required parameters are
 *	obtained through the nested attrs under %INF_VENDOR_ATTR_TWT_PARAMS.
 *
 * @INF_TWT_OPER_TEARDOWN: Teardown the already negotiated TWT session.
 *	Required parameters are obtained through the nested attrs under
 *	INF_VENDOR_ATTR_TWT_PARAMS.
 *
 * @INF_TWT_OPER_MAX: This acts as a the tail of the list.
 *      Make sure it located at the end of the list.
 */
enum inf_twt_oper {
	INF_TWT_OPER_UNSPEC,
	INF_TWT_OPER_SETUP,
	INF_TWT_OPER_TEARDOWN,
	INF_TWT_OPER_MAX
};

/*
 * enum inf_vendor_attr_twt_param - TWT parameters
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_UNSPEC: Reserved value 0
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_NEGO_TYPE: Specifies the type of Negotiation to be
 *	done during Setup. The four possible types are
 *	0 - Individual TWT Negotiation
 *	1 - Wake TBTT Negotiation
 *	2 - Broadcast TWT in Beacon
 *	3 - Broadcast TWT Membership Negotiation
 *
 *	The possible values are defined in the enum inf_twt_param_nego_type
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_SETUP_CMD_TYPE: Specifies the type of TWT Setup frame
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
 *	The possible values are defined in the enum inf_twt_oper_setup_cmd_type.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_DIALOG_TOKEN: Dialog Token used by the TWT Requesting STA to
 *	identify the TWT Setup request/response transaction.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_WAKE_TIME: Target Wake Time TSF at which the STA has to wake up.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_WAKE_TIME_OFFSET: Target Wake Time TSF Offset from current TSF
 *	in microseconds.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION: Nominal Minimum TWT Wake Duration.
 *	Used along with %INF_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION_UNIT to derive Wake Duration.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_EXPONENT: TWT Wake Interval Exponent.
 *	Used along with %INF_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_MANTISSA to derive Wake Interval.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_MANTISSA: TWT Wake Interval Mantissa.
 *	Used along with %INF_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_EXPONENT to derive Wake Interval.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_REQUESTOR: Specify this is a TWT Requesting / Responding STA.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_TRIGGER: Specify Trigger based / Non-Trigger based TWT Session.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_IMPLICIT: Specify Implicit / Explicit TWT session.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_FLOW_TYPE: Specify Un-Announced / Announced TWT session.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_FLOW_ID: Flow ID is the unique identifier of an iTWT session.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_BCAST_TWT_ID: Broadcast TWT ID is the unique identifier of a
 *	bTWT session.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_PROTECTION: Specifies whether Tx within SP is protected.
 *	Set to 1 to indicate that TXOPs within the TWT SPs shall be initiated
 *	with a NAV protection mechanism, such as (MU) RTS/CTS or CTS-to-self frame;
 *	otherwise, it shall set it to 0.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_CHANNEL: TWT channel field which is set to 0, unless
 *	the HE STA sets up a subchannel selective transmission operation.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_TWT_INFO_FRAME_DISABLED: TWT Information frame RX handing
 *	disabled / enabled.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION_UNIT: Nominal Minimum TWT Wake Duration
 *	Unit. 0 represents unit in "256 usecs" and 1 represents unit in "TUs".
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_TEARDOWN_ALL_TWT: Teardown all negotiated TWT sessions.
 *
 * @INF_VENDOR_ATTR_TWT_PARAM_MAX: This acts as a the tail of the list.
 *      Make sure it located at the end of the list.
 */
enum inf_vendor_attr_twt_param {
	INF_VENDOR_ATTR_TWT_PARAM_UNSPEC,
	INF_VENDOR_ATTR_TWT_PARAM_NEGO_TYPE,
	INF_VENDOR_ATTR_TWT_PARAM_SETUP_CMD_TYPE,
	INF_VENDOR_ATTR_TWT_PARAM_DIALOG_TOKEN,
	INF_VENDOR_ATTR_TWT_PARAM_WAKE_TIME,
	INF_VENDOR_ATTR_TWT_PARAM_WAKE_TIME_OFFSET,
	INF_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION,
	INF_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_EXPONENT,
	INF_VENDOR_ATTR_TWT_PARAM_WAKE_INTVL_MANTISSA,
	INF_VENDOR_ATTR_TWT_PARAM_REQUESTOR,
	INF_VENDOR_ATTR_TWT_PARAM_TRIGGER,
	INF_VENDOR_ATTR_TWT_PARAM_IMPLICIT,
	INF_VENDOR_ATTR_TWT_PARAM_FLOW_TYPE,
	INF_VENDOR_ATTR_TWT_PARAM_FLOW_ID,
	INF_VENDOR_ATTR_TWT_PARAM_BCAST_TWT_ID,
	INF_VENDOR_ATTR_TWT_PARAM_PROTECTION,
	INF_VENDOR_ATTR_TWT_PARAM_CHANNEL,
	INF_VENDOR_ATTR_TWT_PARAM_TWT_INFO_FRAME_DISABLED,
	INF_VENDOR_ATTR_TWT_PARAM_MIN_WAKE_DURATION_UNIT,
	INF_VENDOR_ATTR_TWT_PARAM_TEARDOWN_ALL_TWT,
	INF_VENDOR_ATTR_TWT_PARAM_MAX
};

/*
 * enum inf_twt_param_nego_type - TWT Session Negotiation Type Parameters
 *
 * @INF_TWT_PARAM_NEGO_TYPE_ITWT: Individual TWT negotiation between TWT requesting STA
 *	and TWT responding STA or individual TWT announcement by TWT Responder
 *
 * @INF_TWT_PARAM_NEGO_TYPE_WAKE_TBTT: Wake TBTT and Wake interval negotiation between
 *	TWT scheduled STA and TWT scheduling AP.
 *
 * @INF_TWT_PARAM_NEGO_TYPE_BTWT_IE_BCN: Provide Broadcast TWT schedules to TWT scheduled
 *	STAs by including the TWT element in broadcast Managemnet frames sent by TWT
 *	scheduling AP.
 *
 * @INF_TWT_PARAM_NEGO_TYPE_BTWT: Broadcast TWT negotiation between TWT requesting STA
 *	and TWT responding STA. Manage Memberships in broadcast TWT schedules by including
 *	the TWT element in individually addressed Management frames sent by either a TWT
 *	scheduled STA or a TWT scheduling AP.
 *
 * @INF_TWT_PARAM_NEGO_TYPE_MAX: This acts as a the tail of the list.
 *      Make sure it located at the end of the list.
 */
enum inf_twt_param_nego_type {
	INF_TWT_PARAM_NEGO_TYPE_INVALID		= -1,
	INF_TWT_PARAM_NEGO_TYPE_ITWT		= 0,
	INF_TWT_PARAM_NEGO_TYPE_WAKE_TBTT	= 1,
	INF_TWT_PARAM_NEGO_TYPE_BTWT_IE_BCN	= 2,
	INF_TWT_PARAM_NEGO_TYPE_BTWT		= 3,
	INF_TWT_PARAM_NEGO_TYPE_MAX		= 4
};

/*
 * enum inf_vendor_attr_twt_param - TWT Session setup command types
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_REQUEST: A TWT requesting or TWT scheduled STA
 *	requests to join a TWT without specifying a target wake time. This type needs to
 *	be used only by the TWT requesting STA.
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_SUGGEST: A TWT requesting or TWT scheduled STA requests to
 *	join a TWT without specifying a target wake time. This type needs to be used only
 *	by the TWT requesting STA.
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_DEMAND: A TWT requesting or TWT scheduled STA requests to
 *	join a TWT and specifies a demanded set of TWT parameters. If the demanded set of
 *	TWT parameters is not accommodated by the responding STA or TWT scheduling AP, then
 *	the TWT requesting STA or TWT scheduled STA will reject the TWT setup. This type
 *	needs to be used only by the TWT requesting STA.
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_GROUPING: The TWT responding STA suggests TWT group
 *	parameters that are different from the suggested or demanded TWT parameters of the
 *	TWT requesting STA. This type needs to be used only by the S1G TWT Responding STA in
 *	case of ITWT Setup Negotiation.
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_ACCEPT: A TWT responding STA or TWT scheduling AP accepts
 *	the TWT request with the TWT parameters (see NOTE) indicated in the TWT element
 *	transmitted by the TWT requesting STA or TWT scheduled STA. This value is also used
 *	in unsolicited TWT responses. This needs type needs to be used only by the TWT
 *	responding STA.
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_ALTERNATE: A TWT responding STA or TWT scheduling AP suggests
 *	TWT parameters that are different from those suggested by the TWT requesting STA or
 *	TWT scheduled STA. This needs type needs to be used only by the TWT reponding STA.
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_DICTATE: A TWT responding STA or TWT scheduling AP indicates
 *	TWT parameters that are different from those suggested by the TWT requesting STA or
 *	TWT scheduled STA. This needs type needs to be used only by the TWT responding STA.
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_REJECT: A TWT responding STA or TWT scheduling AP rejects
 *	setup, or a TWT scheduling AP terminates an existing broadcast TWT, or a TWT
 *	scheduled STA terminates its membership in a broadcast TWT.
 *
 * @INF_TWT_OPER_SETUP_CMD_TYPE_MAX: This acts as a the tail of the list.
 *	Make sure it located at the end of the list.
 */
enum inf_twt_oper_setup_cmd_type {
	INF_TWT_OPER_SETUP_CMD_TYPE_INVALID	= -1,
	INF_TWT_OPER_SETUP_CMD_TYPE_REQUEST	= 0,
	INF_TWT_OPER_SETUP_CMD_TYPE_SUGGEST	= 1,
	INF_TWT_OPER_SETUP_CMD_TYPE_DEMAND	= 2,
	INF_TWT_OPER_SETUP_CMD_TYPE_GROUPING	= 3,
	INF_TWT_OPER_SETUP_CMD_TYPE_ACCEPT	= 4,
	INF_TWT_OPER_SETUP_CMD_TYPE_ALTERNATE	= 5,
	INF_TWT_OPER_SETUP_CMD_TYPE_DICTATE	= 6,
	INF_TWT_OPER_SETUP_CMD_TYPE_REJECT	= 7,
	INF_TWT_OPER_SETUP_CMD_TYPE_MAX		= 8
};

#endif /* INF_VENDOR_H */
