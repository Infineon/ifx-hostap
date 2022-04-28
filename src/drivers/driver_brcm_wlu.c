/*
 * Broadcom Corporation OUI and vendor specific assignments
 * Copyright (c) 2020, Broadcom Corporation.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "includes.h"
#include "common.h"
#include "common/brcm_vendor.h"
#include "common/brcm_wl_ioctl.h"
#include "common/brcm_wl_ioctl_defs.h"
#include "common/wpa_common.h"
#include "driver_brcm_wlu_cmd.h"

static cmd_func_t wl_rate;
static cmd_func_t wl_varint;

#define RATE_2G_USAGE							\
"\tEither \"auto\", or a simple CCK/DSSS/OFDM rate value:\n"		\
"\t1 2 5.5 11 6 9 12 18 24 36 48 54\n\n"				\
"\tOr options to specify legacy, HT, or VHT rate:\n"			\
"\t-r R, --rate=R        : legacy rate (CCK, DSSS, OFDM)\n"		\
"\t-h M, --ht=M          : HT MCS index [0-23]\n"			\
"\t-v M[xS], --vht=M[xS] : VHT MCS index M [0-9],\n"			\
"\t                      : and optionally Nss S [1-8], eg. 5x2 is MCS=5, Nss=2\n" \
"\t-c cM[sS]             : VHT (c notation) MCS index M [0-9],\n"			\
"\t                      : and optionally Nss S [1-8], eg. c5s2 is MCS=5, Nss=2\n" \
"\t-e M[xS], --he=M[xS]  : HE rate M [0-11],\n" \
"\t-s S, --ss=S          : VHT Nss [1-8], number of spatial streams, default 1.\n" \
"\t                      : Only used with -v/--vht when MxS format is not used\n" \
"\t-x T, --exp=T         : Tx Expansion, number of tx chains (NTx) beyond the minimum\n" \
"\t                      : required for the space-time-streams, exp = NTx - Nsts\n" \
"\t--stbc                : Use STBC expansion, otherwise no STBC\n"	\
"\t-l, --ldpc            : Use LDPC encoding, otherwise no LDPC\n"	\
"\t-g, --sgi             : Guard interval. Different values for HT/VHT\n" \
"\t                      : Use Short Guard Interval otherwise standard GI\n" \
"\t-i, --hegi            : Guard interval. Different values for HE\n" \
"\t                      : For HE, cp_ltf combination allowed values (0,1,2,3)\n" \
"\t-b, --bandwidth       : transmit bandwidth in MHz [2.5, 5, 10, 20, 40, 80, 160] eg. -b 20\n" \
"\t-d D, --dcm=D         : Use -d to set DCM, otherwise no DCM\n" \
"\t                      : (only when is MCS [0, 1], NSS 1, -b 20)\n" \
"\t-n R, --er=R          : R [106,242] HE Range extension\n" \
"\t                      : otherwise no Rang extension and works only in 20 MHz"

#define RATE_5G_6G_USAGE							\
"\tEither \"auto\", or a simple OFDM rate value:\n"			\
"\t6 9 12 18 24 36 48 54\n\n"						\
"\tOr options to specify legacy OFDM, HT, or VHT rate:\n"		\
"\t-r R, --rate=R        : legacy OFDM rate\n"				\
"\t-h M, --ht=M          : HT MCS index [0-23]\n"			\
"\t-v M[xS], --vht=M[xS] : VHT MCS index M [0-9],\n"			\
"\t                      : and optionally Nss S [1-8], eg. 5x2 is MCS=5, Nss=2\n" \
"\t-c cM[sS]             : VHT (c notation) MCS index M [0-9],\n"			\
"\t                      : and optionally Nss S [1-8], eg. c5s2 is MCS=5, Nss=2\n" \
"\t-e M[xS], --he=M[xS]  : HE rate M [0-11],\n"		\
"\t-s S, --ss=S          : VHT Nss [1-8], number of spatial streams, default 1.\n" \
"\t                      : Only used with -v/--vht when MxS format is not used\n" \
"\t-x T, --exp=T         : Tx Expansion, number of tx chains (NTx) beyond the minimum\n" \
"\t                      : required for the space-time-streams, exp = NTx - Nsts\n" \
"\t--stbc                : Use STBC expansion, otherwise no STBC\n"	\
"\t-l, --ldpc            : Use LDPC encoding, otherwise no LDPC\n"	\
"\t-g, --sgi             : Guard interval. Different values for HT/VHT\n" \
"\t                      : Use Short Guard Interval otherwise standard GI\n" \
"\t-i, --hegi            : Guard interval. Different values for HE\n" \
"\t                      : For HE cp_ltf combination allowed values (0,1,2,3)\n" \
"\t-b, --bandwidth       : transmit bandwidth in MHz [2.5, 5, 10, 20, 40, 80, 160] eg. -b 20\n" \
"\t-d D, --dcm=D         : Use -d to set DCM, otherwise no DCM\n" \
"\t                      : (only when is MCS [0, 1], NSS 1, -b 20)\n" \
"\t-n R, --er=R          : R [106,242] HE Range extension\n" \
"\t                      : otherwise no Rang extension and works only in 20 MHz"

/* If the new command needs to be part of 'wc.exe' tool used for WMM,
 * be sure to modify wc_cmds[] array as well
 *
 * If you add a command, please update wlu_cmd.c cmd2cat to categorize the command.
 */
cmd_t wl_cmds[] = {
	{ "2g_rate", wl_rate, WLC_GET_VAR, WLC_SET_VAR,
	"Force a fixed rate for data frames in the 2.4G band:\n\n"
	RATE_2G_USAGE
	},
	{ "2g_mrate", wl_rate, WLC_GET_VAR, WLC_SET_VAR,
	"Force a fixed rate for mulitcast/broadcast data frames in the 2.4G band:\n\n"
	RATE_2G_USAGE
	},
	{ "5g_rate", wl_rate, WLC_GET_VAR, WLC_SET_VAR,
	"Force a fixed rate for data frames in the 5G band:\n\n"
	RATE_5G_6G_USAGE
	},
	{ "5g_mrate", wl_rate, WLC_GET_VAR, WLC_SET_VAR,
	"Force a fixed rate for mulitcast/broadcast data frames in the 5G band:\n\n"
	RATE_5G_6G_USAGE
	},
	{ NULL, NULL, 0, 0, NULL }
};

cmd_t wl_varcmd = {"var", wl_varint, -1, -1, "unrecognized name, type -h for help"};

/* common function to find a command */
cmd_t *
wlu_find_cmd(char *name)
{
	cmd_t *cmd = wl_cmds;

	/* search cmd in cmd table */
	for (; cmd->name; cmd++) {
		/* stop if we find a matching name */
		if (!os_strncasecmp(cmd->name, name, os_strlen(cmd->name))) {
			break;
		}
	}

	return (cmd->name != NULL) ? cmd : NULL;
}

/*
 * Format a ratespec for output of any of the wl_rate() iovars
 */
char*
wl_rate_print(char *rate_buf, size_t buf_len, u32 rspec)
{
	uint encode, rate, txexp, bw_val;
	const char* stbc;
	const char* ldpc;
	const char* bw;
	const char* dcm;
	const char* er;
	u8 valid_encding = false;

	encode = (rspec & WL_RSPEC_ENCODING_MASK);
	rate = (rspec & WL_RSPEC_RATE_MASK);
	txexp = (rspec & WL_RSPEC_TXEXP_MASK) >> WL_RSPEC_TXEXP_SHIFT;
	bw_val = (rspec & WL_RSPEC_BW_MASK);
	stbc  = ((rspec & WL_RSPEC_STBC) != 0) ? " stbc" : "";
	ldpc  = ((rspec & WL_RSPEC_LDPC) != 0) ? " ldpc" : "";
	dcm   = ((rspec & WL_RSPEC_DCM)  != 0) ? " dcm"  : "";

	if (RSPEC_HE_ER_ENAB(rspec) != 0) {
		er = RSPEC_HE_ER_TONE(rspec) ? " er 106" : " er 242";
	} else {
		er = "";
	}

	if (bw_val == WL_RSPEC_BW_UNSPECIFIED) {
		bw = "auto";
	} else if (bw_val == WL_RSPEC_BW_20MHZ) {
		bw = "20";
	} else if (bw_val == WL_RSPEC_BW_40MHZ) {
		bw = "40";
	} else if (bw_val == WL_RSPEC_BW_80MHZ) {
		bw = "80";
	} else if (bw_val == WL_RSPEC_BW_160MHZ) {
		bw = "160";
	} else if (bw_val == WL_RSPEC_BW_10MHZ) {
		bw = "10";
	} else if (bw_val == WL_RSPEC_BW_5MHZ) {
		bw = "5";
	} else if (bw_val == WL_RSPEC_BW_2P5MHZ) {
		bw = "2.5";
	} else {
		bw = "???";
	}

	if ((rspec & ~WL_RSPEC_TXEXP_MASK) == 0) { /* Ignore TxExpansion for NULL rspec check */
		valid_encding = true;
		os_snprintf(rate_buf, buf_len, "auto");
	} else if (encode == WL_RSPEC_ENCODE_HE) {
		const char* gi_ltf[] = {" 1xLTF GI 0.8us", " 2xLTF GI 0.8us",
					" 2xLTF GI 1.6us", " 4xLTF GI 3.2us"};
		u8 gi_int = RSPEC_HE_LTF_GI(rspec);
		uint mcs = (rspec & WL_RSPEC_HE_MCS_MASK);
		uint Nss = (rspec & WL_RSPEC_HE_NSS_MASK) >> WL_RSPEC_HE_NSS_SHIFT;

		valid_encding = true;

		os_snprintf(rate_buf, buf_len, "he mcs %d Nss %d Tx Exp %d BW %s%s%s%s%s%s",
			    mcs, Nss, txexp, bw, stbc, ldpc, gi_ltf[gi_int], dcm, er);

	} else {
		const char* sgi;
		sgi = ((rspec & WL_RSPEC_SGI)  != 0) ? " sgi"  : "";
		if (encode == WL_RSPEC_ENCODE_RATE) {

			valid_encding = true;

			os_snprintf(rate_buf, buf_len, "rate %d%s Mbps Tx Exp %d",
				    rate/2, (rate % 2)?".5":"", txexp);
		} else if (encode == WL_RSPEC_ENCODE_HT) {

			valid_encding = true;

			os_snprintf(rate_buf, buf_len, "ht mcs %d Tx Exp %d BW %s%s%s%s",
				    rate, txexp, bw, stbc, ldpc, sgi);
		} else if (encode == WL_RSPEC_ENCODE_VHT) {
			uint mcs = (rspec & WL_RSPEC_VHT_MCS_MASK);
			uint Nss = (rspec & WL_RSPEC_VHT_NSS_MASK) >> WL_RSPEC_VHT_NSS_SHIFT;

			valid_encding = true;

			os_snprintf(rate_buf, buf_len, "vht mcs %d Nss %d Tx Exp %d BW %s%s%s%s",
				    mcs, Nss, txexp, bw, stbc, ldpc, sgi);
		}
	}

	if (!valid_encding) {
		os_snprintf(rate_buf, buf_len, "<unknown encoding for ratespec 0x%08X>", rspec);
	}

	return rate_buf;
}


/* parse the -v/--vht or -c argument for the wl_rate() command.
 * return FALSE if the arg does not look like MxS or cMsS, where M and S are single digits
 * return TRUE if the arg does look like MxS or cMsS, setting mcsp to M, and nssp to S
 */
static int
wl_parse_he_vht_spec(const char* cp, int* mcsp, int* nssp)
{
	char *startp, *endp;
	char c;
	int mcs, nss;
	char sx;

	if (cp == NULL || cp[0] == '\0') {
		return false;
	}

	if (cp[0] == 'c') {
		startp = (char*)cp + 1;
		sx = 's';
	}
	else {
		startp = (char*)cp;
		sx = 'x';
	}

	mcs = (int)strtol(startp, &endp, 10);
	/* verify MCS 0-11, and next char is 's' or 'x' */
	/* HE MCS is 0-11, VHT MCS 0-9 and prop MCS 10-11 */
	if (mcs < 0 || mcs > 11 || endp[0] != sx) {
		return false;
	}

	/* grab the char after the 'x'/'s' and convert to value */
	c = endp[1];
	nss = 0;
	if (isdigit((int)c)) {
		nss = c - '0';
	}

	/* consume trailing space after digit */
	cp = &endp[2];
	while (isspace((int)(*cp))) {
		cp++;
	}

	/* check for trailing garbage after digit */
	if (cp[0] != '\0') {
		return false;
	}

	if (nss < 1 || nss > 8) {
		return false;
	}

	*mcsp = mcs;
	*nssp = nss;

	return true;
}


static int
wl_rate(char *cmd, char *buf, u32 *buf_len, bool *get, bool *is_get_int)
{
	int ret = -1;
	char *pos, *param = cmd;
	bool auto_set = false;
	bool legacy_set = false, ht_set = false, vht_set = false, he_set = false;
	int rate, mcs, Nss, tx_exp, bw;
	bool stbc, ldpc, sgi, dcm, er;
	u8 hegi;

	u32 rspec = 0;
	int val_int = 0;
	char *endp;

	/* set default values */
	rate = 0;
	mcs = 0;
	Nss = 0;
	tx_exp = 0;
	stbc = false;
	ldpc = false;
	sgi = false;
	hegi = 0xFF;
	bw = 0;
	dcm = false;
	er = false;

	pos = os_strstr(cmd, "5g_rate");
	if (pos) {
		param = cmd + strlen("5g_rate");
		os_memcpy(buf, cmd, strlen("5g_rate")); //Keep last byte as 0x00
		*is_get_int = true;
		*buf_len += strlen("5g_rate");

		if (os_strncasecmp(cmd, "5g_rate ", 8) == 0) {
			param += 1;
			*get = false;
			cmd += strlen("5g_rate ");
			*buf_len += 1;
		}
	}

	pos = os_strstr(cmd, "2g_rate");
	if (pos) {
		param = cmd + strlen("2g_rate");
		os_memcpy(buf, cmd, strlen("2g_rate")); //Keep last byte as 0x00
		*is_get_int = true;
		*buf_len += strlen("2g_rate");

		if (os_strncasecmp(cmd, "2g_rate ", 8) == 0) {
			param += 1;
			*get = false;
			cmd += strlen("2g_rate ");
			*buf_len += 1;
		}
	}

	if (*get == true) {
		ret = 0;
		goto exit;
	}

	/* Option: -l or --ldpc */
	pos = os_strstr(param, "auto");
	if (pos) {
		auto_set = true;
	}

	pos = os_strstr(param, "-r ");
	if (pos) {
		pos += 3;
		rate = atoi(pos) * 2;
		rspec = WL_RSPEC_ENCODE_RATE;   /* 11abg */
		rspec |= rate;
	}

	/* Option: -e or --he */
	pos = os_strstr(param, "-e ");
	if (pos) {
		char var_str[10];
		pos += 3;
		endp = os_strchr(pos, ' ');
		if (endp == NULL)
			endp = os_strchr(pos, '\0');
		os_memcpy(var_str, pos, endp - pos);
		var_str[endp - pos] = '\0';

		val_int  = (int)strtol(var_str, &endp, 10);
		if (*endp == '\0') {
			mcs = val_int;
			he_set = true;
		} else if (wl_parse_he_vht_spec(var_str, &mcs, &Nss)) {
			he_set = true;
		} else {
			wpa_printf(MSG_DEBUG, "%s: could not parse \"%s\""
				   "as a value for %s option",
				   "5g_rate", pos, "-e");
			goto exit;
		}

		if (he_set) {
			rspec = WL_RSPEC_ENCODE_HE;	/* 11ax HE */
			if (Nss == 0) {
				Nss = WL_RSPEC_HE_NSS_UNSPECIFIED;
			}
			rspec |= (Nss << WL_RSPEC_HE_NSS_SHIFT) | mcs;
		}
	}


	pos = os_strstr(param, "-i ");
	if (pos) {
		if (!he_set) {
			wpa_printf(MSG_DEBUG, ":use -i option only in he ");
			goto exit;
		}

		pos += 3;
		val_int = (int)strtol(pos, &endp, 10);
		if (*endp == '\0') {
			if (val_int < 4)
			{
				hegi = val_int;
			}
			else {
				wpa_printf(MSG_DEBUG, "%s: could not parse "
					   "\"%s\" as a value for %s option",
					   "5g_rate", pos, "-i");
				goto exit;
			}
		}
	}

	/* Option: -l or --ldpc */
	pos = os_strstr(param, "-l");
	if (pos) {
		ldpc = true;
	}

	/* set the ratespec encoding type and basic rate value */
	if (auto_set) {
		rspec = 0;
	} else if (legacy_set) {
		rspec = WL_RSPEC_ENCODE_RATE;	/* 11abg */
		rspec |= rate;
	} else if (ht_set) {
		rspec = WL_RSPEC_ENCODE_HT;	/* 11n HT */
		rspec |= mcs;
	} else if (vht_set) {
		rspec = WL_RSPEC_ENCODE_VHT;	/* 11ac VHT */
		if (Nss == 0) {
			Nss = 1; /* default Nss = 1 if --ss option not given */
		}
		rspec |= (Nss << WL_RSPEC_VHT_NSS_SHIFT) | mcs;
	} else if (he_set) {
		rspec = WL_RSPEC_ENCODE_HE;	/* 11ax HE */
		if (Nss == 0) {
			Nss = WL_RSPEC_HE_NSS_UNSPECIFIED;
		}
		rspec |= (Nss << WL_RSPEC_HE_NSS_SHIFT) | mcs;
	} else {
		wpa_printf(MSG_ERROR,
				"%s: Invalid rate set for %s option\n",
				"wl", param);
				goto exit;
	}

	/* set the other rspec fields */
	rspec |= (tx_exp << WL_RSPEC_TXEXP_SHIFT);
	rspec |= bw;
	rspec |= (stbc ? WL_RSPEC_STBC : 0);
	rspec |= (ldpc ? WL_RSPEC_LDPC : 0);
	rspec |= (sgi  ? WL_RSPEC_SGI  : 0);
	rspec |= ((hegi != 0xFF) ? HE_GI_TO_RSPEC(hegi) : 0);
	rspec |= (dcm << WL_RSPEC_DCM_SHIFT);
	rspec |= (er << WL_RSPEC_ER_SHIFT);

	os_memcpy(buf + *buf_len, (char *)&rspec, sizeof(rspec));
	*buf_len += sizeof(rspec);

	ret = 0;
exit:
	return ret;
}

/* just issue a wl_var_setint() or a wl_var_getint() if there is a 2nd arg */
static int
wl_varint(char *cmd, char *buf, u32 *buf_len, bool *get, bool *is_get_int)
{
	return -1;
}

int wl_do_cmd(char *cmd, char *smbuf, u32 *msglen, bool *get, bool *is_get_int)
{
	cmd_t *wl_cmd = NULL;
	int ret = -1;

	/* search for command */
	wl_cmd = wlu_find_cmd(cmd);

	/* defaults to using the set_var and get_var commands */
	if (!wl_cmd) {
		wl_cmd = &wl_varcmd;
	}
	/* do command */
	ret = (*wl_cmd->func)(cmd, smbuf, msglen, get, is_get_int);
	if (ret != 0)
		goto exit;

	ret = 0;
exit:
	return ret;
}

