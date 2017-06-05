#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <windows.h>

#include "command_stack_utils.h"
#include "command_utils.h"

command_node* s_command_insert(command_node* stack, command* com) {
  command_node* new_node = (command_node*)malloc(sizeof(command_node));
  new_node->data = com;
  if (stack == NULL) {
    new_node->next = NULL;
    stack = new_node;
  } else {
    new_node->next = stack;
    stack = new_node;
  }
  return stack;
}

command_node* s_command_pop(command_node* stack, int free_data) {
  command_node* tmp = stack;
  stack = stack->next;
  tmp->next = NULL;

  if(tmp == stack)
    stack = NULL;

  if (free_data == 1) {
    if (tmp != NULL && tmp->data->cli != NULL) {
      l_trav_remove_all(tmp->data->cli->travel_head);
      free(tmp->data->cli->dni);
      free(tmp->data->cli->name);
      free(tmp->data->cli->surname);
      free(tmp->data->cli->address);
      free(tmp->data->cli);
      free(tmp->data);
      // Ponemos "else if" ya que limpiamos los viajes con l_trav_remove_all
    } else if (tmp != NULL && tmp->data->trav != NULL) {
      free(tmp->data->trav->id);
      free(tmp->data->trav->destination);
      free(tmp->data->trav->hotel);
      free(tmp->data->trav->transport);
      free(tmp->data->trav);
      free(tmp->data);
    }
  }
  free(tmp);
  return stack;
}

int s_command_empty(command_node* stack) {
  if (stack == NULL) {
    return 1;
  } else {
    return 0;
  }
}
