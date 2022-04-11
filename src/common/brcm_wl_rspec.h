/*
 * Broadcom Corporation OUI and vendor specific assignments
 * Copyright (c) 2020, Broadcom Corporation.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

/* Rate spec. definitions */
#define WL_RSPEC_RATE_MASK	0x000000FF	/**< Legacy rate or MCS or MCS + NSS */
#define WL_RSPEC_TXEXP_MASK	0x00000300	/**< Tx chain expansion beyond Nsts */
#define WL_RSPEC_TXEXP_SHIFT	8
#define WL_RSPEC_HE_GI_MASK	0x00000C00	/* HE GI indices */
#define WL_RSPEC_HE_GI_SHIFT	10
#define WL_RSPEC_BW_MASK	0x00070000	/**< Band width */
#define WL_RSPEC_BW_SHIFT	16
#define WL_RSPEC_ER_MASK	0x0000C000	/**< Range extension mask */
#define WL_RSPEC_ER_SHIFT	14
#define WL_RSPEC_ER_ENAB_MASK	0x00008000	/**< Range extension enable */
#define WL_RSPEC_ER_ENAB_SHIFT	15
#define WL_RSPEC_ER_TONE_MASK	0x00004000	/**< Range extension tone config */
#define WL_RSPEC_ER_TONE_SHIFT	14

#define WL_RSPEC_DCM		0x00080000	/**< Dual Carrier Modulation */
#define WL_RSPEC_DCM_SHIFT	19
#define WL_RSPEC_STBC		0x00100000	/**< STBC expansion, Nsts = 2 * Nss */
#define WL_RSPEC_TXBF		0x00200000
#define WL_RSPEC_LDPC		0x00400000
#define WL_RSPEC_SGI		0x00800000
#define WL_RSPEC_SHORT_PREAMBLE	0x00800000	/**< DSSS short preable - Encoding 0 */
#define WL_RSPEC_ENCODING_MASK	0x03000000	/**< Encoding of RSPEC_RATE field */
#define WL_RSPEC_ENCODING_SHIFT 24

#define WL_RSPEC_OVERRIDE_RATE	0x40000000	/**< override rate only */
#define WL_RSPEC_OVERRIDE_MODE	0x80000000	/**< override both rate & mode */

/* ======== RSPEC_HE_GI|RSPEC_SGI fields for HE ======== */

/* GI for HE */
#define RSPEC_HE_LTF_GI(rspec)  (((rspec) & WL_RSPEC_HE_GI_MASK) >> WL_RSPEC_HE_GI_SHIFT)
#define WL_RSPEC_HE_1x_LTF_GI_0_8us	(0x0)
#define WL_RSPEC_HE_2x_LTF_GI_0_8us	(0x1)
#define WL_RSPEC_HE_2x_LTF_GI_1_6us	(0x2)
#define WL_RSPEC_HE_4x_LTF_GI_3_2us	(0x3)
#define RSPEC_ISHEGI(rspec)	(RSPEC_HE_LTF_GI(rspec) > WL_RSPEC_HE_1x_LTF_GI_0_8us)
#define HE_GI_TO_RSPEC(gi)	(((gi) << WL_RSPEC_HE_GI_SHIFT) & WL_RSPEC_HE_GI_MASK)

/* RSPEC Macros for extracting and using HE-ER and DCM */
#define RSPEC_HE_DCM(rspec)		(((rspec) & WL_RSPEC_DCM) >> WL_RSPEC_DCM_SHIFT)
#define RSPEC_HE_ER(rspec)		(((rspec) & WL_RSPEC_ER_MASK) >> WL_RSPEC_ER_SHIFT)
#define RSPEC_HE_ER_ENAB(rspec)		(((rspec) & WL_RSPEC_ER_ENAB_MASK) >> \
					WL_RSPEC_ER_ENAB_SHIFT)
#define RSPEC_HE_ER_TONE(rspec)		(((rspec) & WL_RSPEC_ER_TONE_MASK) >> \
					WL_RSPEC_ER_TONE_SHIFT)
/* ======== RSPEC_RATE field ======== */

/* Encoding 0 - legacy rate */
/* DSSS, CCK, and OFDM rates in [500kbps] units */
#define WL_RSPEC_LEGACY_RATE_MASK	0x0000007F
#define WLC_RATE_1M	2
#define WLC_RATE_2M	4
#define WLC_RATE_5M5	11
#define WLC_RATE_11M	22
#define WLC_RATE_6M	12
#define WLC_RATE_9M	18
#define WLC_RATE_12M	24
#define WLC_RATE_18M	36
#define WLC_RATE_24M	48
#define WLC_RATE_36M	72
#define WLC_RATE_48M	96
#define WLC_RATE_54M	108

/* Encoding 1 - HT MCS */
#define WL_RSPEC_HT_MCS_MASK		0x0000007F	/**< HT MCS value mask in rspec */

/* Encoding 2 - VHT MCS + NSS */
#define WL_RSPEC_VHT_MCS_MASK		0x0000000F	/**< VHT MCS value mask in rspec */
#define WL_RSPEC_VHT_NSS_MASK		0x000000F0	/**< VHT Nss value mask in rspec */
#define WL_RSPEC_VHT_NSS_SHIFT		4		/**< VHT Nss value shift in rspec */

/* Encoding 3 - HE MCS + NSS */
#define WL_RSPEC_HE_MCS_MASK		0x0000000F	/**< HE MCS value mask in rspec */
#define WL_RSPEC_HE_NSS_MASK		0x000000F0	/**< HE Nss value mask in rspec */
#define WL_RSPEC_HE_NSS_SHIFT		4		/**< HE Nss value shift in rpsec */

/* ======== RSPEC_BW field ======== */

#define WL_RSPEC_BW_UNSPECIFIED	0
#define WL_RSPEC_BW_20MHZ	0x00010000
#define WL_RSPEC_BW_40MHZ	0x00020000
#define WL_RSPEC_BW_80MHZ	0x00030000
#define WL_RSPEC_BW_160MHZ	0x00040000
#define WL_RSPEC_BW_10MHZ	0x00050000
#define WL_RSPEC_BW_5MHZ	0x00060000
#define WL_RSPEC_BW_2P5MHZ      0x00070000

/* ======== RSPEC_ENCODING field ======== */

#define WL_RSPEC_ENCODE_RATE		0x00000000	/**< Legacy rate is stored in RSPEC_RATE */
#define WL_RSPEC_ENCODE_HT		0x01000000	/**< HT MCS is stored in RSPEC_RATE */
#define WL_RSPEC_ENCODE_VHT		0x02000000	/**< VHT MCS and NSS are stored in RSPEC_RATE */
#define WL_RSPEC_ENCODE_HE		0x03000000	/**< HE MCS and NSS are stored in RSPEC_RATE */
#define WL_RSPEC_HE_NSS_UNSPECIFIED	0xF

