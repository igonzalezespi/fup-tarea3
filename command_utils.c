#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <windows.h>

#include "command_utils.h"
#include "command_stack_utils.h"
#include "client_list_utils.h"
#include "travel_list_utils.h"

void add_action(int action, client* cli, travel* trav) {
  command* com = (command*)malloc(sizeof(command));
  com->action = action;
  if (cli != NULL) {
    com->cli = cli;
  }
  if (trav != NULL) {
    com->trav= trav;
  }
  s_command_insert(com);
}

void remove_action() {
  s_command_pop();
}

void undo_action() {
  command* last_command = top->data;
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
  remove_action();
}
