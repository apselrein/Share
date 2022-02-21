/*
Double linked list
Feb 21 2022
Zyryanov Alexander
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


//------------------ DOUBLE LINKED LIST ----------------------
/*
	Schematic see this:

	<---prev---|DL_LIST|---next--->
		
*/

typedef struct dl_list { 
	int data; 
	struct dl_list* prev;
	struct dl_list* next;
} dl_list;

/* Creates element of list
* Param:
* int d - data
*/
dl_list* create_dl_list(int d) {
	dl_list* dl = malloc(sizeof(dl_list));
	dl->data = d;
	dl->prev = NULL;
	dl->next = NULL;
	return dl;
}

/* Find and return head of list
* Param:
* dl_list* dl - any element of list
*/
dl_list* head_of_dl(dl_list* dl) {
	while (dl->prev != NULL)
		dl = dl->prev;
	return dl;
}

/* Find and return tail of list
* Param:
* dl_list* dl - any element of list
*/
dl_list* tail_of_dl(dl_list* dl) {
	while (dl->next != NULL)
		dl = dl->next;
	return dl;
}

/* Returns count of elements of list
* Param:
* dl_list* dl - any element of list
*/
int count_of_dl(dl_list* dl) {
	int size = 1;
	dl = head_of_dl(dl);
	for (dl_list* iter = dl; iter->next != NULL; iter = iter->next)
		size++;
	return size;
}

/* Print in string all elements of list with '->' delimiter
* Param:
* dl_list* dl - any element of list
*/
void print_dl(dl_list* dl) {
	dl = head_of_dl(dl);
	printf("-> ");
	for (dl_list* iter = dl; iter->next != NULL; iter = iter->next)
		printf("%d -> ", iter->data);
	printf("\n\n");
}

/* Print in 10 colums all elements of list
* Param:
* dl_list* dl - any element of list
* char* title - Title of list (will be printed as header)
*/
void print_dl_10_cols(dl_list* dl, char* title) {
	dl = head_of_dl(dl);
	printf("%s\n\n", title);
	for (int i = 0; (i < 10) && (dl != NULL); i = (i + 1) % 10, dl = dl->next) {
		printf("%4d", dl->data);
		if (i == 9) printf("\n");
	}
	printf("\n\n");
}

/* Print in 10 colums all elements of list
* Param:
* dl_list* dl - any element of list
*/
dl_list* add_prev_dl(int d, dl_list* dl) {
	dl = head_of_dl(dl);
	dl_list* p = create_dl_list(d);
	p->data = d;
	dl->prev = p;
	p->next = dl;
	return p;
}

/* Add element to existing list
* Param:
* dl_list* dl - any element of list
* ind d - Data
*/
dl_list* add_next_dl(int d, dl_list* dl) {
	dl = tail_of_dl(dl);
	dl_list* p = create_dl_list(d);
	p->data = d;
	dl->next = p;
	p->prev = dl;
	return p;	
}

/* Swap datas of two elements in list
* Param:
* dl_list* a, b - any element of list
*/
void swap_dl(dl_list* a, dl_list* b) { // Swap data of two elements
	int tmp;
	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}


/* Free memory space
* Param:
* dl_list* dl - any element of list
*/
void delete_dl(dl_list* dl) {
	dl = head_of_dl(dl);	
	while (dl->next != NULL) {
		dl = dl->next;
		free(dl->prev);
		dl->prev = NULL;
	}
	free(dl);
	printf("\n Memory space is free.\n");
}

/* Creates double linked list with random[0;49] data.
* Param:
* int size - count of elements
*/
dl_list* create_random_dl(int size) {
	srand(time(NULL));
	dl_list* head = create_dl_list(rand() % 50);
	for (int i = 1; i < size; i++)
		head = add_next_dl((rand() % 50), head);
	return head_of_dl(head);
}

/* Sort list
* Param:
* dl_list* dl - any element of list
*/
void sort_dl(dl_list* dl) {
	dl = head_of_dl(dl);
	int size = count_of_dl(dl);
	
	for (int i = size; i > 1; i--) {
		dl_list* iter = dl;
		for (int j = 0; j < (i - 1); j++, iter = iter->next)
			if (iter->data > (iter->next)->data) swap_dl(iter, iter->next);
	}
}

/* Delete all element with same values of data
* Param:
* dl_list* dl - any element of list
*/
dl_list* delete_same_dl(dl_list* dl) {
	dl = head_of_dl(dl);
	while (dl->next != NULL) {
		dl = dl->next;
		if (dl->data == (dl->prev)->data) {
			if ((dl->prev)->prev == NULL) {
				free(dl->prev);
				dl->prev = NULL;
			}
			else {
				dl_list* tmp = (dl->prev)->prev;
				tmp->next = dl;
				free(dl->prev);
				dl->prev = tmp;
			}
		}
	}
	dl = head_of_dl(dl);
	return dl;
}


//-------------  MAIN  ----------------------------------

int main(int argc, char* argv[]) {
	dl_list* rand_dl_list = create_random_dl(200);
	print_dl_10_cols(rand_dl_list, "Original list:");

	sort_dl(rand_dl_list);
	print_dl_10_cols(rand_dl_list, "Sorted list:");

	rand_dl_list = delete_same_dl(rand_dl_list);
	print_dl_10_cols(rand_dl_list, "Cleaned list:");

	delete_dl(rand_dl_list);	
	return 0;	
}