#ifndef COMMAND_UTILS_H_INCLUDED
#define COMMAND_UTILS_H_INCLUDED

#include "client_utils.h"
#include "travel_utils.h"
#include "command_stack_utils.h"

command_node* add_action(command_node* stack, int action, client* cli, travel* trav);

void remove_undo_action(void);
void undo_action(void);

void remove_redo_action(void);
void remove_all_redo(void);
void redo_action(void);



#endif // COMMAND_UTILS_H_INCLUDED
