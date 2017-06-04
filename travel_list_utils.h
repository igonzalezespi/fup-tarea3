#ifndef TRAVEL_LIST_UTILS_H_INCLUDED
#define TRAVEL_LIST_UTILS_H_INCLUDED

#include "travel_utils.h"

typedef struct trav_node {
  travel* data;
  struct trav_node* next;
} trav_node;

typedef void (*trav_callback)(trav_node* data);

trav_node* l_trav_insert(travel* trav, trav_node* next);
trav_node* l_trav_remove_front(trav_node* head);
trav_node* l_trav_remove_back(trav_node* head);
trav_node* l_trav_remove(trav_node* head, trav_node* toRemove);
void l_trav_remove_all(trav_node* head);
void l_trav_traverse(trav_node* head, trav_callback f);
int l_trav_count(trav_node* head);
void l_trav_display(trav_node* head);
trav_node* l_trav_search(trav_node* head, char* id);

#endif // TRAVEL_LIST_UTILS_H_INCLUDED
