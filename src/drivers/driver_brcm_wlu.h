/*
 * Broadcom Corporation OUI and vendor specific assignments
 * Copyright (c) 2020, Broadcom Corporation.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

/* Format a ratespec for output of any of the wl_rate() iovars */
char* wl_rate_print(char *rate_buf, size_t buf_len, u32 rspec);

int wl_do_cmd(char *cmd, char *smbuf, u32 *msglen, bool *get, bool *is_get_int);
