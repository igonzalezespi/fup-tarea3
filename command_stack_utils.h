#ifndef COMMAND_STACK_UTILS_H_INCLUDED
#define COMMAND_STACK_UTILS_H_INCLUDED

#include "common.h"

typedef struct command_node {
  command* data;
  struct command_node* next;
} command_node;

command_node* s_command_insert(command_node* stack, command* com);
command_node* s_command_pop(command_node* stack, int free_data);
int s_command_empty(command_node* stack);

extern command_node* top_undo;
extern command_node* top_redo;

#endif // COMMAND_STACK_UTILS_H_INCLUDED
