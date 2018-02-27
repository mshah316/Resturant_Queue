#pragma once
/* sample .h file */

/* include all libraries here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* put any #define statements here */
typedef enum { FALSE = 0, TRUE, NO = 0, YES } boolean;
//#define TRUE 1
//#define FALSE 0
/* put any structure declarations here */
typedef struct list_struct LIST;
/* helper functions */
void doAdd(LIST *l);
void doCallAhead(LIST *l);
void doWaiting(LIST *l);
void doRetrieve(LIST *l);
void doList(LIST *l);
void doDisplay(LIST *l);

/* List implimentation functions */
LIST *lst_create();
void lst_free(LIST *l);
void addToList(LIST *l, char*n, int s, int callahead);
boolean doesNameExist(LIST *l, char*n);
boolean updateStatus(LIST *l, char*n);
char *retrieveAndRemove(LIST *l, int s);
void countGroupsAhead(LIST *l, char*n);
void displayGroupSizeAhead(LIST *l, char*n);
void displayListInformation(LIST *l);