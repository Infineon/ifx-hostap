/*
 * Broadcom Corporation OUI and vendor specific assignments
 * Copyright (c) 2020, Broadcom Corporation.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

typedef struct cmd cmd_t;
typedef int (cmd_func_t)(char *cmd, char *buf, u32 *buf_len, bool *set, bool *is_get_int);

/* generic command line argument handler */
struct cmd {
	const char *name;
	cmd_func_t *func;
	int get;
	int set;
	const char *help;
};

/* list of command line arguments */
extern cmd_t wl_cmds[];

