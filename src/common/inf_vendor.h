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

#endif /* INF_VENDOR_H */
