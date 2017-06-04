#ifndef COMMAND_UTILS_H_INCLUDED
#define COMMAND_UTILS_H_INCLUDED

#include "client_utils.h"
#include "travel_utils.h"

typedef struct {
  int action;
  client* cli;
  travel* trav;
} command;

void add_action(int action, client* cli, travel* trav);
void remove_action(void);

void undo_action(void);
void redo_action(void);



#endif // COMMAND_UTILS_H_INCLUDED
