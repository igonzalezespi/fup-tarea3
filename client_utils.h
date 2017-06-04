#ifndef CLIENT_UTILS_H_INCLUDED
#define CLIENT_UTILS_H_INCLUDED

#include "travel_list_utils.h"

typedef struct {
  char *dni;
  char *name;
  char *surname;
  char *address;
  int travel_autoincrement;
  trav_node* travel_head;
} client;

void add_client(void);
void remove_client(void);

#endif // CLIENT_UTILS_H_INCLUDED
