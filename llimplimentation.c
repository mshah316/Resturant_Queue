
#include "proj4.h"


typedef struct node {
	int size;
	int res_status;
	char* name;
	struct node *next;
} NODE;


struct list_struct {
	NODE *front;
	NODE *back;
	int len;
};



LIST *lst_create() {
	LIST *l = malloc(sizeof(LIST));

	l->front = NULL;
	l->back = NULL;
	l->len = 0;
	return l;
}



void lst_free(LIST *l) {
	NODE *p = l->front;
	NODE *pnext;

	while (p != NULL) {
		pnext = p->next;   // keeps us from de-referencing a freed ptr
		free(p);
		p = pnext;
	}
	// now free the LIST 
	free(l);
}

void lst_push_front(LIST *l, int s, char*n) {
	NODE *p = malloc(sizeof(NODE));

	p->size = s;
	p->name = n;
	p->res_status = TRUE;
	p->next = l->front;

	l->front = p;
	if (l->back == NULL)   // was empty, now one elem
		l->back = p;

	(l->len)++;
}

void lst_push_back(LIST *l, int s, char*n) {
	NODE *p;

	if (l->back == NULL)   // list empty - same as push_front
		lst_push_front(l,s,n);
	else {  // at least one element before push
		p = malloc(sizeof(NODE));
		p->size = s;
		p->name = n;
		p->res_status = TRUE;
		p->next = NULL;
		l->back->next = p;
		l->back = p;
		(l->len)++;
	}
}
void addToList(LIST *l, char*n, int s,int callahead) {
	lst_push_back(l, s, n);
	if (callahead == 1) { l->back->res_status = FALSE; }
}


boolean doesNameExist(LIST *l, char*n) {
	NODE *p = l->front;
	 
	while (p != NULL) {
		if (strcmp(p->name, n) == 0) 
		{ return TRUE; }
		p = p->next;
	}
	return FALSE;
}
boolean updateStatus(LIST *l, char*n) {
	NODE *p = l->front;
	
		while (p != NULL) {
			if (strcmp(p->name, n) == 0) { 
				if (p->res_status == FALSE) { p->res_status = TRUE; return TRUE; }
				else { return FALSE; }
			}
			p = p->next;
		}
	
}

boolean lst_is_empty(LIST *l) {
	if (l->front == NULL) { return TRUE; }
	else { return FALSE; }
	
}

char *lst_pop_front(LIST *l) {
	char* ret;
	NODE *p;


	if (lst_is_empty(l))
		return NULL;   // no-op

	ret = l->front->name;

	if (l->front == l->back) {  // one element
		free(l->front);
		l->front = NULL;
		l->back = NULL;
	}
	else {
		p = l->front;  // don't lose node being deleted
		l->front = l->front->next;  // hop over
		free(p);
	}
	(l->len)--;
	printf("removing group %s from waiting list\n", ret);
	return ret;
}

char *lst_remove_first(LIST *l, int x) {
	NODE *p;
	NODE *tmp;
	char* ret;
	if (l->front == NULL) return NULL;
	if (l->front->size <= x && l->front->res_status==TRUE) {
		return lst_pop_front(l);
	}
	// lst non-empty; no match on 1st elem
	p = l->front;

	while (p->next != NULL) {
		if (p->next->size <= x && p->next->res_status == TRUE) {
			ret = p->next->name;
			//printf("%d must be <= %d\n",x, p->next->size);
			printf("removing group %s from waiting list\n", ret);
			tmp = p->next;
			p->next = tmp->next;
			if (tmp == l->back)
				l->back = p;
			free(tmp);
			(l->len)--;      
			return ret;
		}
		p = p->next;
	}
	return NULL;
}

char *retrieveAndRemove(LIST *l,int s) {
	return lst_remove_first(l,s); 
}

void countGroupsAhead(LIST * l, char * n){
	NODE *p = l->front;
	int counter = 0;
	while (p != NULL) {
		
		if (strcmp(p->name, n) == 0){
			printf("%d groups are ahead of group \"%s\" \n",counter,n);
			return;
		}
		p = p->next;
		counter++;
	}
}

void displayGroupSizeAhead(LIST * l, char * n){
	NODE *p = l->front;

	printf("The groups that are ahead of group \"%s\" are listed below \n", n);
	printf("front[ ");
	while (p != NULL) {
		if (strcmp(p->name, n) == 0) { return; }
		printf("group \"%s\" ", p->name);
		p = p->next;
		printf(" ] rear\n");
	}
}



void displayListInformation(LIST *l) {
	NODE *p = l->front;
	printf("Total number of groups in waiting list:%d \n",l->len);
	while (p != NULL) {
		if(p->res_status){ printf(" group \"%s\" of size %d is currently in the resturant\n", p->name, p->size); }
		else{ printf(" group \"%s\" of size %d is not currently in the resturant\n", p->name, p->size); }
		p = p->next;
	}
}