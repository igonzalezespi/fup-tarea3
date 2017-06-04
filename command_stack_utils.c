#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <windows.h>

#include "command_stack_utils.h"
#include "command_utils.h"

void s_command_insert(command* com) {
  command_node* new_node = (command_node*)malloc(sizeof(command_node));
  new_node->data = com;
  if (top == NULL) {
    new_node->next = NULL;
    top = new_node;
  } else {
    new_node->next = top;
    top = new_node;
  }
}

void s_command_pop() {
  command_node* tmp = top;
  top = top->next;
  tmp->next = NULL;

  if(tmp == top)
    top = NULL;

  free(tmp);
}

int s_command_empty() {
  if (top == NULL) {
    return 1;
  } else {
    return 0;
  }
}
