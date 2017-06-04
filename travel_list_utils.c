#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#include "travel_list_utils.h"

typedef void (*trav_callback)(trav_node* data);

trav_node* l_trav_insert(travel* trav, trav_node* next) {
  trav_node* new_node = (trav_node*)malloc(sizeof(trav_node));
  if(new_node == NULL) {
    return NULL;
  }
  new_node->data = trav;
  new_node->next = next;

  return new_node;
}

void l_trav_traverse(trav_node* head, trav_callback f) {
  trav_node* cursor = head;
  while(cursor != NULL) {
    f(cursor);
    cursor = cursor->next;
  }
}

trav_node* l_trav_remove_front(trav_node* head) {
  trav_node* cursor = head;
  head = head->next;
  cursor->next = NULL;
  /* is this the last node in the list */
  if(cursor == head)
    head = NULL;

  free(cursor->data->id);
  free(cursor->data->destination);
  free(cursor->data->hotel);
  free(cursor->data->transport);
  free(cursor->data);
  free(cursor);

  return head;
}

trav_node* l_trav_remove_back(trav_node* head) {
  trav_node* cursor = head;
  trav_node* back = NULL;

  while(cursor->next != NULL) {
    back = cursor;
    cursor = cursor->next;
  }

  if(back != NULL)
    back->next = NULL;

  /* if this is the last node in the list*/
  if(cursor == head)
    head = NULL;

  free(cursor->data->id);
  free(cursor->data->destination);
  free(cursor->data->hotel);
  free(cursor->data->transport);
  free(cursor->data);
  free(cursor);

  return head;
}

trav_node* l_trav_remove(trav_node* head, trav_node* to_remove) {
  if(to_remove == head) {
    /* if the node is the first node */
    return l_trav_remove_front(head);
  } else if(to_remove->next == NULL) {
    /* if the node is the last node */
    return l_trav_remove_back(head);
  } else {
    /* if the node is in the middle */
    trav_node* cursor = head;
    while(cursor != NULL) {
      if(cursor->next == to_remove)
        break;
      cursor = cursor->next;
    }

    if(cursor != NULL) {
      trav_node* tmp = cursor->next;
      cursor->next = tmp->next;
      tmp->next = NULL;
      free(tmp->data->id);
      free(tmp->data->destination);
      free(tmp->data->hotel);
      free(tmp->data->transport);
      free(tmp->data);
      free(tmp);
    }
    return head;
  }
}

void l_trav_remove_all(trav_node* head) {
  trav_node* cursor = head;
  while(cursor != NULL) {
    cursor = l_trav_remove_front(cursor);
  }
}

int l_trav_count(trav_node* head) {
  trav_node* cursor = head;
  int c = 0;
  while(cursor != NULL) {
    c++;
    cursor = cursor->next;
  }
  return c;
}

void l_trav_display(trav_node* cursor) {
  if(cursor != NULL) {
    puts("--------------------------");
    printf("\t\tID: %s\n", cursor->data->id);
    printf("\t\tDestino: %s\n", cursor->data->destination);
    printf("\t\tHotel: %s\n", cursor->data->hotel);
    printf("\t\tTransporte: %s\n", cursor->data->transport);
    printf("\t\tNoches: %i\n", cursor->data->nights);
    printf("\t\tPrecio noche: %f\n", cursor->data->night_cost);
    printf("\t\tPrecio transporte: %f\n", cursor->data->transport_cost);
  }
}

trav_node* l_trav_search(trav_node* head, char* id) {
  trav_node* cursor = head;
  while(cursor != NULL) {
    if(strcmp(cursor->data->id, id) == 0)
      return cursor;
    cursor = cursor->next;
  }
  return NULL;
}
