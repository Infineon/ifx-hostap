/*
 * wpa_supplicant - TWT
 * Copyright (c) 2003-2016, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#include "includes.h"

#include "utils/common.h"
#include "config.h"
#include "wpa_supplicant_i.h"
#include "driver_i.h"
#include "scan.h"

#ifdef CONFIG_TWT_OFFLOAD_IFX
#define TWT_NONE 0
#define TWT_IDLE 1
#define TWT_ACTIVE 2
#define TWT_TEARDOWN_ALL 128

/**
 * wpas_twt_offload_send_setup - Send TWT Setup frame to our AP
 * @wpa_s: Pointer to wpa_supplicant
 * @dtok: Dialog token
 * @exponent: Wake-interval exponent
 * @mantissa: Wake-interval mantissa
 * @min_twt: Minimum TWT wake duration in units of 256 usec
 * @setup_cmd: 0 == request, 1 == suggest, etc.  Table 9-297
 * @twt: Target Wake Time
 * @twt_offset: Target Wake Time TSF offset
 * @requestor: Specify this is a TWT Requesting / Responding STA
 * @trigger: Specify Trigger based / Non-Trigger based TWT Session
 * @implicit: Specify Implicit / Explicit TWT session
 * @flow_type: Specify Un-Announced / Announced TWT session
 * @flow_id: Flow ID / Broacast TWT ID to be used in the TWT session
 * @protection: Specifies whether Tx within SP is protected by RTS & CTS
 * @twt_channel: Set by the HE SST non-AP STA
 * @control: Control Field in the TWT Setup Action frame
 * Returns: 0 in case of success, negative error code otherwise
 *
 */
int wpas_twt_offload_send_setup(struct wpa_supplicant *wpa_s, u8 dtok, int exponent,
				int mantissa, u8 min_twt, int setup_cmd, u64 twt,
				u64 twt_offset, bool requestor, bool trigger,
				bool implicit, bool flow_type, u8 flow_id,
				bool protection, u8 twt_channel, u8 control)
{
	int ret = 0;
	struct drv_setup_twt_params params;
	u8 negotiation_type, twt_info_frame_disabled, min_twt_unit;

	params.dtok = dtok;
	params.exponent = (u8)exponent;
	params.mantissa = (u16)mantissa;
	params.min_twt = min_twt;
	params.twt = twt;
	params.twt_offset = twt_offset;
	params.requestor = requestor ? 1 : 0;
	params.trigger = trigger ? 1 : 0;
	params.implicit = implicit ? 1 : 0;
	params.flow_type = flow_type ? 1 : 0;
	params.protection = protection ? 1 : 0;
	params.twt_channel = twt_channel;
	params.flow_id = 0;
	params.bcast_twt_id = 0;

	/* Setup Command Field - IEEE 802.11ax-2021 Table 9-297 */
	switch(setup_cmd) {
		case 0: params.setup_cmd = IFX_TWT_OPER_SETUP_CMD_TYPE_REQUEST;
			break;
		case 1: params.setup_cmd = IFX_TWT_OPER_SETUP_CMD_TYPE_SUGGEST;
			break;
		case 2: params.setup_cmd = IFX_TWT_OPER_SETUP_CMD_TYPE_DEMAND;
			break;
		case 3: params.setup_cmd = IFX_TWT_OPER_SETUP_CMD_TYPE_GROUPING;
			break;
		case 4: params.setup_cmd = IFX_TWT_OPER_SETUP_CMD_TYPE_ACCEPT;
			break;
		case 5: params.setup_cmd = IFX_TWT_OPER_SETUP_CMD_TYPE_ALTERNATE;
			break;
		case 6: params.setup_cmd = IFX_TWT_OPER_SETUP_CMD_TYPE_DICTATE;
			break;
		case 7: params.setup_cmd = IFX_TWT_OPER_SETUP_CMD_TYPE_REJECT;
			break;
		default:
			wpa_printf(MSG_ERROR,
				   "TWT offload: specified Setup cmd type not supported");
			ret = -EOPNOTSUPP;
			goto fail;
	}

	/* Control Field - IEEE 802.11ax-2021 Figure 9-687 */
	params.control = control;
							/* NDP Paging Indicator : Bit 0		 */
							/* Responder PM Mode : Bit 1		 */
	negotiation_type = (control & 0xc) >> 2;	/* Negotiation type : Bit 2-3		 */
	twt_info_frame_disabled = (control & 0x10) >> 4;/* TWT Information Frame Disabled: Bit 4 */
	min_twt_unit = (control & 0x20) >> 5;		/* Wake Duration Unit : Bit 5		 */
							/* Reserved : Bit 6-7			 */

	/* Negotiation Type Field - IEEE 802.11ax-2021 Table 9.296a */
	switch(negotiation_type) {
		case 0:	/* Individual TWT */
			params.negotiation_type = IFX_TWT_PARAM_NEGO_TYPE_ITWT;
			params.flow_id = flow_id;
			break;
		case 1: /* Wake TBTT Negotiation */
			params.negotiation_type = IFX_TWT_PARAM_NEGO_TYPE_WAKE_TBTT;
			break;
		case 2: /* Broadcast TWT IE in Beacon */
			params.negotiation_type = IFX_TWT_PARAM_NEGO_TYPE_BTWT_IE_BCN;
			break;
		case 3: /* Broadcast TWT membership */
			params.negotiation_type = IFX_TWT_PARAM_NEGO_TYPE_BTWT;
			params.bcast_twt_id = flow_id;
			break;
		default:
			wpa_printf(MSG_ERROR,
				   "TWT offload: specified Nego type not supported");
			ret = -EOPNOTSUPP;
			goto fail;
	}

	params.twt_info_frame_disabled = twt_info_frame_disabled;
	params.min_twt_unit = min_twt_unit;		/* 1 - in TUs, 0 - in 256us */

	if (wpa_drv_setup_twt(wpa_s, &params)) {
		wpa_printf(MSG_ERROR, "TWT offload: Failed to send TWT Setup Request");
		ret = -ECANCELED;
		goto fail;
	}

fail:
	return ret;
}

/**
 * wpas_twt_offload_send_teardown - send TWT teardown request to our AP
 * @wpa_s: pointer to wpa_supplicant
 * @flags: the byte that goes inside the twt teardown element
 * returns: 0 in case of success, negative error code otherwise
 *
 */
int wpas_twt_offload_send_teardown(struct wpa_supplicant *wpa_s, u8 flags)
{
	int ret = 0;
	struct drv_teardown_twt_params params;
	u8 negotiation_type, flow_id, teardown_all_twt;

	/* TWT Flow Field - IEEE 802.11ax-2021 Figure 9-965 */
	flow_id = flags & 0x07;			/* Flow ID : Bit 0-2		*/
						/* Reserved : Bit 3-4		*/
	negotiation_type = (flags & 0x60) >> 5;	/* Negotiation type : Bit 5-6	*/
	teardown_all_twt = (flags & 0x80) >> 7;	/* Teardown all TWT : Bit 7	*/

	/* Negotiation Type Field - IEEE 802.11ax-2021 Table 9.296a */
	switch(negotiation_type) {
		case 0:	/* Individual TWT */
			params.negotiation_type = IFX_TWT_PARAM_NEGO_TYPE_ITWT;
			params.flow_id = flow_id;
			break;
		case 1: /* Wake TBTT Negotiation */
			params.negotiation_type = IFX_TWT_PARAM_NEGO_TYPE_WAKE_TBTT;
			break;
		case 2: /* Broadcast TWT IE in Beacon */
			params.negotiation_type = IFX_TWT_PARAM_NEGO_TYPE_BTWT_IE_BCN;
			break;
		case 3: /* Broadcast TWT membership */
			params.negotiation_type = IFX_TWT_PARAM_NEGO_TYPE_BTWT;
			params.bcast_twt_id = flow_id;
			break;
		default:
			wpa_printf(MSG_ERROR,
				   "TWT offload: specified Nego Type Not supported");
			ret = -EOPNOTSUPP;
			goto fail;
	}

	params.teardown_all_twt = teardown_all_twt;

	if (wpa_drv_teardown_twt(wpa_s, &params)) {
		wpa_printf(MSG_ERROR, "TWT offload: Failed to send TWT Teardown frame");
		ret = -ECANCELED;
		goto fail;
	}

fail:
	return ret;
}

int wpas_twt_offload_init_default_session(struct wpa_supplicant *wpa_s)
{
	int exponent = 10, mantissa = 8192, setup_cmd = 2, flow_id = 0, ret = 0;
	unsigned long long twt = 0, twt_offset = 0;
	bool requestor = true, trigger = true, implicit = true, flow_type = true,
	     protection = false;
	u8 dtok = 1, min_twt = 255, twt_channel = 0,
	   control = BIT(4); /* Control field (IEEE P802.11ax/D8.0 Figure
                              * 9-687): B4 = TWT Information Frame Disabled */

	if (wpa_s->conf->twt_def_algo == TWT_NONE) {
		wpa_printf(MSG_DEBUG, "TWT offload: Default TWT is disabled");
		goto exit;
	}

	wpa_printf(MSG_DEBUG, "TWT offload: Init Default TWT, profile %d, freq %d",
		   wpa_s->conf->twt_def_algo, wpa_s->assoc_freq);

	if (wpa_s->conf->twt_def_algo == TWT_IDLE) {
		/* TWT profile for Idle traffic */
		if (IS_2P4GHZ(wpa_s->assoc_freq)) {
			/*
			 * 2G Band
			 * SP=2ms and SI=614.4ms
			 */
			min_twt = 8;
			mantissa = 600;
			exponent = 10;
		} else { /*
			  * 5G or 6G Band
			  * SP=512us and SI=614.4ms
			  */
			min_twt = 2;
			mantissa = 600;
			exponent = 10;
		}
	} else if (wpa_s->conf->twt_def_algo == TWT_ACTIVE) {
		/*
		 * TWT profile for Active traffic
		 * 2G, 5G and 6G Bands
		 * SP=8ms and SI=50ms
		 */
		min_twt = 31;
		mantissa = 50000;
		exponent = 0;
	} else {
		wpa_printf(MSG_ERROR, "TWT offload: Invalid Default TWT profile");
		ret = -1;
		goto exit;
	}

	ret = wpas_twt_offload_send_setup(wpa_s, dtok, exponent, mantissa,
					  min_twt, setup_cmd, twt, twt_offset,
					  requestor, trigger, implicit, flow_type,
					  flow_id, protection, twt_channel,
					  control);
exit:
	return ret;
}

int wpas_twt_offload_deinit_default_session(struct wpa_supplicant *wpa_s)
{
	int flags = TWT_TEARDOWN_ALL, ret = 0;

	if (wpa_s->conf->twt_def_algo == TWT_NONE) {
		goto exit;
	}

	/* Clear all TWT sessions created by STA including default */
	wpa_printf(MSG_DEBUG,
		   "TWT offload: De-init Default TWT, profile %d, freq %d",
		   wpa_s->conf->twt_def_algo, wpa_s->assoc_freq);

	ret = wpas_twt_offload_send_teardown(wpa_s, flags);
exit:
	return ret;
}

#else

/**
 * wpas_twt_send_setup - Send TWT Setup frame (Request) to our AP
 * @wpa_s: Pointer to wpa_supplicant
 * @dtok: Dialog token
 * @exponent: Wake-interval exponent
 * @mantissa: Wake-interval mantissa
 * @min_twt: Minimum TWT wake duration in units of 256 usec
 * @setup_cmd: 0 == request, 1 == suggest, etc.  Table 9-297
 * Returns: 0 in case of success, negative error code otherwise
 *
 */
int wpas_twt_send_setup(struct wpa_supplicant *wpa_s, u8 dtok, int exponent,
			int mantissa, u8 min_twt, int setup_cmd, u64 twt,
			bool requestor, bool trigger, bool implicit,
			bool flow_type, u8 flow_id, bool protection,
			u8 twt_channel, u8 control)
{
	struct wpabuf *buf;
	u16 req_type = 0;
	int ret = 0;

	if (wpa_s->wpa_state != WPA_COMPLETED || !wpa_s->current_ssid) {
		wpa_printf(MSG_DEBUG,
			   "TWT: No connection - cannot send TWT Setup frame");
		return -ENOTCONN;
	}

	/* 3 = Action category + Action code + Dialog token */
	/* 17 = TWT element */
	buf = wpabuf_alloc(3 + 17);
	if (!buf) {
		wpa_printf(MSG_DEBUG,
			   "TWT: Failed to allocate TWT Setup frame (Request)");
		return -ENOMEM;
	}

	wpa_printf(MSG_DEBUG,
		   "TWT: Setup request, dtok: %d  exponent: %d  mantissa: %d  min-twt: %d",
		   dtok, exponent, mantissa, min_twt);

	wpabuf_put_u8(buf, WLAN_ACTION_S1G);
	wpabuf_put_u8(buf, S1G_ACT_TWT_SETUP);
	wpabuf_put_u8(buf, dtok);

	wpabuf_put_u8(buf, WLAN_EID_TWT);
	wpabuf_put_u8(buf, 15); /* len */

	wpabuf_put_u8(buf, control);

	if (requestor)
		req_type |= BIT(0); /* This STA is a TWT Requesting STA */
	/* TWT Setup Command field */
	req_type |= (setup_cmd & 0x7) << 1;
	if (trigger)
		req_type |= BIT(4); /* TWT SP includes trigger frames */
	if (implicit)
		req_type |= BIT(5); /* Implicit TWT */
	if (flow_type)
		req_type |= BIT(6); /* Flow Type: Unannounced TWT */
	req_type |= (flow_id & 0x7) << 7;
	req_type |= (exponent & 0x1f) << 10; /* TWT Wake Interval Exponent */
	if (protection)
		req_type |= BIT(15);
	wpabuf_put_le16(buf, req_type);
	wpabuf_put_le64(buf, twt);
	wpabuf_put_u8(buf, min_twt); /* Nominal Minimum TWT Wake Duration */
	wpabuf_put_le16(buf, mantissa); /* TWT Wake Interval Mantissa */
	wpabuf_put_u8(buf, twt_channel); /* TWT Channel */

	if (wpa_drv_send_action(wpa_s, wpa_s->assoc_freq, 0, wpa_s->bssid,
				wpa_s->own_addr, wpa_s->bssid,
				wpabuf_head(buf), wpabuf_len(buf), 0) < 0) {
		wpa_printf(MSG_DEBUG, "TWT: Failed to send TWT Setup Request");
		ret = -ECANCELED;
	}

	wpabuf_free(buf);
	return ret;
}


/**
 * wpas_twt_send_teardown - Send TWT teardown request to our AP
 * @wpa_s: Pointer to wpa_supplicant
 * @flags: The byte that goes inside the TWT Teardown element
 * Returns: 0 in case of success, negative error code otherwise
 *
 */
int wpas_twt_send_teardown(struct wpa_supplicant *wpa_s, u8 flags)
{
	struct wpabuf *buf;
	int ret = 0;

	if (wpa_s->wpa_state != WPA_COMPLETED || !wpa_s->current_ssid) {
		wpa_printf(MSG_DEBUG,
			   "TWT: No connection - cannot send TWT Teardown frame");
		return -ENOTCONN;
	}

	/* 3 = Action category + Action code + flags */
	buf = wpabuf_alloc(3);
	if (!buf) {
		wpa_printf(MSG_DEBUG,
			   "TWT: Failed to allocate TWT Teardown frame");
		return -ENOMEM;
	}

	wpa_printf(MSG_DEBUG, "TWT: Teardown request, flags: 0x%x", flags);

	wpabuf_put_u8(buf, WLAN_ACTION_S1G);
	wpabuf_put_u8(buf, S1G_ACT_TWT_TEARDOWN);
	wpabuf_put_u8(buf, flags);

	if (wpa_drv_send_action(wpa_s, wpa_s->assoc_freq, 0, wpa_s->bssid,
				wpa_s->own_addr, wpa_s->bssid,
				wpabuf_head(buf), wpabuf_len(buf), 0) < 0) {
		wpa_printf(MSG_DEBUG, "TWT: Failed to send TWT Teardown frame");
		ret = -ECANCELED;
	}

	wpabuf_free(buf);
	return ret;
}

#endif /* CONFIG_TWT_OFFLOAD_IFX */
