#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <windows.h>

#include "command_utils.h"
#include "command_stack_utils.h"
#include "client_list_utils.h"
#include "travel_list_utils.h"

command_node* add_action(command_node* stack, int action, client* cli, travel* trav) {
  command* com = (command*)malloc(sizeof(command));
  com->action = action;
  if (cli != NULL) {
    com->cli = cli;
  }
  if (trav != NULL) {
    com->trav= trav;
  }
  return s_command_insert(stack, com);
}

void remove_undo_action() {
  top_undo = s_command_pop(top_undo, 0);
}

void undo_action() {
  command* last_command = top_undo->data;
  if (last_command->action == 1) {
    cli_node* cli_n = l_cli_search(last_command->cli->dni);
    l_cli_remove(cli_n);
  } else if (last_command->action == 2) {
    l_cli_insert(last_command->cli);
  } else if (last_command->action == 3) {
    trav_node* trav_n =
      l_trav_search(last_command->cli->travel_head, last_command->trav->id);

    last_command->cli->travel_head =
      l_trav_remove(last_command->cli->travel_head, trav_n);
  } else if (last_command->action == 4) {
    last_command->cli->travel_head =
      l_trav_insert(last_command->trav, last_command->cli->travel_head);
  }
  top_redo = add_action(top_redo, last_command->action, last_command->cli, last_command->trav);
  remove_undo_action();
}

void remove_redo_action() {
  top_redo = s_command_pop(top_redo, 0);
}

void remove_all_redo() {
  while(top_redo != NULL) {
    top_redo = s_command_pop(top_redo, 1);
  }
}

void redo_action() {
  command* last_command = top_redo->data;
  if (last_command->action == 1) {
    l_cli_insert(last_command->cli);
  } else if (last_command->action == 2) {
    cli_node* cli_n = l_cli_search(last_command->cli->dni);
    l_cli_remove(cli_n);
  } else if (last_command->action == 3) {
    last_command->cli->travel_head =
      l_trav_insert(last_command->trav, last_command->cli->travel_head);
  } else if (last_command->action == 4) {
    trav_node* trav_n =
      l_trav_search(last_command->cli->travel_head, last_command->trav->id);

    last_command->cli->travel_head =
      l_trav_remove(last_command->cli->travel_head, trav_n);
  }
  remove_redo_action();
}
