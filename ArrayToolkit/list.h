#ifndef list_h
#define list_h

typedef struct Node Linklist;
void error_freelist(Linklist* head);
Linklist* get_arrlist(int len);
void print_arrlist(Linklist* head);

#endif
