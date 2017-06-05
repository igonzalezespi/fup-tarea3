#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <windows.h>

#include "common.h"
#include "client_list_utils.h"
#include "travel_list_utils.h"

typedef void (*cli_callback)(cli_node* data);

int l_cli_insert(client* cli) {
  cli_node* x;
  cli_node* y;
  cli_node* e;

  cli_node* new_node = (cli_node*)malloc(sizeof(cli_node));
  if (new_node == NULL) {
    return 0;
  }
  new_node->data = cli;
  new_node->next = head;
  head = new_node;

  x = head;
  head = NULL;

  while(x != NULL) {
    e = x;
    x = x->next;
    if (head != NULL) {
      if(alphabetize(e->data->surname, head->data->surname) == 1) {
        y = head;
        while (
          (y->next != NULL)
          &&
          (alphabetize(e->data->surname, y->next->data->surname) == 1)) {
          y = y->next;
        }
        e->next = y->next;
        y->next = e;
      } else {
        e->next = head;
        head = e;
      }
    } else {
      e->next = NULL;
      head = e;
    }
  }
  return 1;
}

void l_cli_traverse(cli_callback f) {
  cli_node* cursor = head;
  while(cursor != NULL) {
    f(cursor);
    cursor = cursor->next;
  }
}

void l_cli_display(cli_node* cursor) {
  if(cursor != NULL) {
    puts("***************************");
    printf("DNI: %s\n", cursor->data->dni);
    printf("Nombre: %s %s\n", cursor->data->name, cursor->data->surname);
    printf("Direccion: %s\n", cursor->data->address);
    l_trav_traverse(cursor->data->travel_head, l_trav_display);
    puts("***************************");
  }
}

void l_cli_remove_front() {
  cli_node* cursor = head;
  head = head->next;
  cursor->next = NULL;

  if(cursor == head)
    head = NULL;

  // Al implementar el deshacer no tenemos que hacer free
//  l_trav_remove_all(cursor->data->travel_head);
//  free(cursor->data->dni);
//  free(cursor->data->name);
//  free(cursor->data->surname);
//  free(cursor->data->address);
//  free(cursor->data);
//  free(cursor);
}

void l_cli_remove_back() {
  cli_node* cursor = head;
  cli_node* back = NULL;

  while(cursor->next != NULL) {
    back = cursor;
    cursor = cursor->next;
  }

  if(back != NULL)
    back->next = NULL;

  /* if this is the last node in the list*/
  if(cursor == head)
    head = NULL;

  // Al implementar el deshacer no tenemos que hacer free
//  l_trav_remove_all(cursor->data->travel_head);
//  free(cursor->data->dni);
//  free(cursor->data->name);
//  free(cursor->data->surname);
//  free(cursor->data->address);
//  free(cursor->data);
//  free(cursor);
}

void l_cli_remove(cli_node* to_remove) {
  if(to_remove == head) {
    l_cli_remove_front();
  } else if(to_remove->next == NULL) {
    l_cli_remove_back();
  } else {
    cli_node* cursor = head;
    while(cursor != NULL) {
      if(cursor->next == to_remove)
        break;
      cursor = cursor->next;
    }

    if(cursor != NULL) {
      cli_node* tmp = cursor->next;
      cursor->next = tmp->next;
      tmp->next = NULL;

//      l_trav_remove_all(tmp->data->travel_head);
//      free(tmp->data->dni);
//      free(tmp->data->name);
//      free(tmp->data->surname);
//      free(tmp->data->address);
//      free(tmp->data);
//      free(tmp);
    }
  }
}

int l_cli_count() {
  cli_node* cursor = head;
  int c = 0;
  while(cursor != NULL) {
    c++;
    cursor = cursor->next;
  }
  return c;
}

cli_node* l_cli_search(char* dni) {
  cli_node* cursor = head;
  while(cursor != NULL) {
    if(strcmp(cursor->data->dni, dni) == 0)
      return cursor;
    cursor = cursor->next;
  }
  return NULL;
}
