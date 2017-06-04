#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#include "common.h"
#include "client_utils.h"
#include "client_list_utils.h"
#include "command_utils.h"

void add_client() {
  FILE *file;
  char filename[FILENAME_MAX_LENGTH];
  char aux[MAX_LENGTH];
  client* cli = (client*)malloc(sizeof(client));
  if (cli == NULL) {
    goto mem_err;
  }

  set_filename(filename);
  file = fopen(filename, "r");

  CLEARSCR;
  puts("Cargando cliente...");

  if (file == NULL) {
    puts(FILE_NOT_FOUND);
  } else {
    fgets(aux, MAX_LENGTH, file);
    clean_string(aux);
    cli->dni = (char*)malloc(strlen(aux)*sizeof(char));
    if (cli->dni == NULL) {
      goto mem_err;
    }
    strcpy(cli->dni, aux);

    fgets(aux, MAX_LENGTH, file);
    clean_string(aux);
    cli->name = (char*)malloc(strlen(aux)*sizeof(char));
    if (cli->name == NULL) {
      goto mem_err;
    }
    strcpy(cli->name, aux);

    fgets(aux, MAX_LENGTH, file);
    clean_string(aux);
    cli->surname = (char*)malloc(strlen(aux)*sizeof(char));
    if (cli->surname == NULL) {
      goto mem_err;
    }
    strcpy(cli->surname, aux);

    fgets(aux, MAX_LENGTH, file);
    clean_string(aux);
    cli->address = (char*)malloc(strlen(aux)*sizeof(char));
    if (cli->address == NULL) {
      goto mem_err;
    }
    strcpy(cli->address, aux);

    cli->travel_head = NULL;
    cli->travel_autoincrement = 1;

    fclose(file);
//    add_action(1, cli, NULL);

    if (l_cli_insert(cli) != 1) {
mem_err:
      puts(INSUFFICIENT_MEMORY);
      free(cli->dni);
      free(cli->name);
      free(cli->surname);
      free(cli->address);
      free(cli);
    } else {
      printf("Cliente con DNI %s cargado correctamente\n", cli->dni);
    }
    fclose(file);
  }
}

void remove_client() {
  FILE *file;
  char filename[FILENAME_MAX_LENGTH];
  char aux[MAX_LENGTH];
  cli_node* node_to_delete;

  set_filename(filename);
  file = fopen(filename, "r");

  CLEARSCR;
  puts("Borrando cliente...");

  if (file == NULL) {
    puts(FILE_NOT_FOUND);
  } else {
    fgets(aux, MAX_LENGTH, file);
    clean_string(aux);
    node_to_delete = l_cli_search(aux);
    if (node_to_delete == NULL) {
      puts(CLIENT_NOT_FOUND);
    } else {
      l_cli_remove(node_to_delete);
      printf("Cliente con DNI %s borrado correctamente\n", aux);
//      add_action(2, node_to_delete->data, NULL);
    }
    fclose(file);
  }
}
