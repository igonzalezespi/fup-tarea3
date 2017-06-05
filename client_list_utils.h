#ifndef CLIENT_LIST_UTILS_H_INCLUDED
#define CLIENT_LIST_UTILS_H_INCLUDED

#include "client_utils.h"

typedef struct cli_node {
  client* data;
  struct cli_node* next;
} cli_node;

typedef void (*cli_callback)(cli_node* data);

int l_cli_insert(client* cli);
void l_cli_traverse(cli_callback f);
void l_cli_display(cli_node* cursor);
void l_cli_remove_front(void);
void l_cli_remove_back(void);
void l_cli_remove(cli_node* to_remove);
int l_cli_count(void);
cli_node* l_cli_search(char* dni);

extern cli_node* head;

#endif // CLIENT_LIST_UTILS_H_INCLUDED
