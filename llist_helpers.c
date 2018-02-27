#include "proj4.h"



void doAdd(LIST *l)
{
	/* get group size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf("Error: Add command requires an integer value of at least 1\n");
		printf("Add command is of form: a <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		printf("Error: Add command requires a name to be given\n");
		printf("Add command is of form: a <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}
	if (doesNameExist(l, name) == 1) { printf(" group \"%s\" of size %d is already in list\n", name, size); return; }
	printf("Adding group \"%s\" of size %d\n", name, size);


	addToList(l, name, size, 0);
}


void doCallAhead(LIST *l)
{
	/* get group size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf("Error: Call-ahead command requires an integer value of at least 1\n");
		printf("Call-ahead command is of form: c <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		printf("Error: Call-ahead command requires a name to be given\n");
		printf("Call-ahead command is of form: c <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}
	if (doesNameExist(l, name) == 1) { printf(" group \"%s\" of size %d is already in list\n", name, size); return; }
	printf("Call-ahead group \"%s\" of size %d\n", name, size);


	addToList(l, name, size, 1);
}

void doWaiting(LIST *l)
{
	/* get group name from input */
	char *name = getName();
	if (name == NULL)
	{
		printf("Error: Waiting command requires a name to be given\n");
		printf("Waiting command is of form: w <name>\n");
		printf("  where: <name> is the name of the group that is now waiting\n");
		return;
	}
	if (doesNameExist(l, name) == 0) { printf(" group \"%s\" is not in list\n", name); return; }
	

	if (updateStatus(l, name) == 1) { printf("Waiting group \"%s\" is now in the restaurant\n", name); }
	else{ printf(" group \"%s\" is already in the restaurant\n", name); }
	
}

void doRetrieve(LIST *l)
{
	/* get table size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf("Error: Retrieve command requires an integer value of at least 1\n");
		printf("Retrieve command is of form: r <size>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		return;
	}
	clearToEoln();


	if (retrieveAndRemove(l, size) == NULL) { printf("No group waiting which can fit a table of size %d\n", size); return; }
	else{ printf("Retrieve (and removed) the first group that can fit at a tabel of size %d\n", size); }
}

void doList(LIST *l)
{
	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		printf("Error: List command requires a name to be given\n");
		printf("List command is of form: l <name>\n");
		printf("  where: <name> is the name of the group to inquire about\n");
		return;
	}
	if (doesNameExist(l, name) == 0) { printf(" group \"%s\" is not in list\n", name); return; }
	

	countGroupsAhead(l,name);
	displayGroupSizeAhead(l, name);
}

void doDisplay(LIST *l)
{
	clearToEoln();
	printf("Display information about all groups\n");

	displayListInformation(l);
}