#ifndef COMMAND_STACK_UTILS_H_INCLUDED
#define COMMAND_STACK_UTILS_H_INCLUDED

#include "command_utils.h"

typedef struct command_node {
  command* data;
  struct command_node* next;
} command_node;

void s_command_init(void);
void s_command_insert(command* com);
void s_command_pop(void);
int s_command_empty(void);

extern command_node* top;

#endif // COMMAND_STACK_UTILS_H_INCLUDED
