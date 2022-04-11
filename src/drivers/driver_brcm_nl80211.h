/*
 * Broadcom Corporation OUI and vendor specific assignments
 * Copyright (c) 2020, Broadcom Corporation.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

struct bcm_nlmsg_hdr {
	uint cmd;	/* common ioctl definition */
	int len;	/* expected return buffer length */
	uint offset;	/* user buffer offset */
	uint set;	/* get or set request optional */
	uint magic;	/* magic number for verification */
};

enum bcmnl_attrs {
	BCM_NLATTR_UNSPEC,

	BCM_NLATTR_LEN,
	BCM_NLATTR_DATA,

	__BCM_NLATTR_AFTER_LAST,
	BCM_NLATTR_MAX = __BCM_NLATTR_AFTER_LAST - 1
};

