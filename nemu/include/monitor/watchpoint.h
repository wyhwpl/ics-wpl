#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;
    int old_value;
	int new_value;
	char *expr;
	/* TODO: Add more members if necessary */


} WP;
int set_watchpoint(char *e);
void list_watchpoint();
bool delete_watchpoint(int NO);
bool delete_watchpoint_all();
WP* scan_watchpoint();
#endif
