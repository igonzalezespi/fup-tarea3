#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#include "common.h"
#include "client_utils.h"
#include "client_list_utils.h"
#include "travel_utils.h"
#include "travel_list_utils.h"
#include "command_utils.h"

void add_travel() {
  FILE *file = NULL;
  char filename[FILENAME_MAX_LENGTH];
  char aux[MAX_LENGTH];
  cli_node* cli_n;
  travel* trav = (travel*)malloc(sizeof(travel));
  if (trav == NULL) {
    goto mem_err;
  }

  set_filename(filename);
  file = fopen(filename, "r");

  CLEARSCR;
  puts("Cargando viaje...");

  if (file == NULL) {
    puts(FILE_NOT_FOUND);
  } else {
    fgets(aux, MAX_LENGTH, file);
    clean_string(aux);
    cli_n = l_cli_search(aux);

    if (cli_n == NULL) {
      puts(CLIENT_NOT_FOUND);
    } else {
      char travel_id[MAX_LENGTH];
      trav_node* trav_n;
      snprintf(
        travel_id,
        MAX_LENGTH,
        "%s_%i",
        cli_n->data->dni,
        cli_n->data->travel_autoincrement
      );
      trav->id = (char*)malloc(strlen(travel_id)*sizeof(char));
      if (trav->id == NULL) {
        goto mem_err;
      }
      strcpy(trav->id, travel_id);

      fgets(aux, MAX_LENGTH, file);
      clean_string(aux);
      trav->destination = (char*)malloc(strlen(aux)*sizeof(char));
      if (trav->destination == NULL) {
        goto mem_err;
      }
      strcpy(trav->destination, aux);

      fgets(aux, MAX_LENGTH, file);
      clean_string(aux);
      trav->hotel = (char*)malloc(strlen(aux)*sizeof(char));
      if (trav->hotel == NULL) {
        goto mem_err;
      }
      strcpy(trav->hotel, aux);

      fgets(aux, MAX_LENGTH, file);
      clean_string(aux);
      trav->transport = (char*)malloc(strlen(aux)*sizeof(char));
      if (trav->transport == NULL) {
        goto mem_err;
      }
      strcpy(trav->transport, aux);

      fgets(aux, MAX_LENGTH, file);
      clean_string(aux);
      trav->nights = atoi(aux);

      fgets(aux, MAX_LENGTH, file);
      clean_string(aux);
      trav->night_cost = atof(aux);

      fgets(aux, MAX_LENGTH, file);
      clean_string(aux);
      trav->transport_cost = atof(aux);

      trav_n = l_trav_insert(trav, cli_n->data->travel_head);
      if (trav_n == NULL) {
mem_err:
        puts(INSUFFICIENT_MEMORY);
        free(trav->id);
        free(trav->destination);
        free(trav->hotel);
        free(trav->transport);
        free(trav);
        free(trav);
      } else {
        cli_n->data->travel_head = trav_n;
        cli_n->data->travel_autoincrement++;
        printf("Viaje con ID %s cargado correctamente\n", trav->id);
        remove_all_redo();
        top_undo = add_action(top_undo, 3, cli_n->data, trav);
      }
    }
    if (file != NULL) {
      fclose(file);
    }
  }
}

void remove_travel() {
  FILE *file = NULL;
  char filename[FILENAME_MAX_LENGTH];
  char aux[MAX_LENGTH];
  char travel_id[MAX_LENGTH];
  char id_to_delete[MAX_LENGTH];
  cli_node *cli_n;
  trav_node* node_to_delete;

  set_filename(filename);
  file = fopen(filename, "r");

  CLEARSCR;
  puts("Borrando viaje...");

  if (file == NULL) {
    puts(FILE_NOT_FOUND);
  } else {
    fgets(aux, MAX_LENGTH, file);
    clean_string(aux);
    cli_n = l_cli_search(aux);
    if (cli_n == NULL) {
      puts(CLIENT_NOT_FOUND);
    } else {
      puts("Identificador del viaje:");
      scanf(" %10s", travel_id);
      CLEARSCR;

      snprintf(id_to_delete, MAX_LENGTH, "%s_%s", cli_n->data->dni, travel_id);
      node_to_delete = l_trav_search(cli_n->data->travel_head, id_to_delete);
      if (node_to_delete == NULL) {
        puts(TRAVEL_NOT_FOUND);
      } else {
        cli_n->data->travel_head = l_trav_remove(cli_n->data->travel_head, node_to_delete);
        printf("Viaje con ID %s borrado con exito\n", id_to_delete);
        remove_all_redo();
        top_undo = add_action(top_undo, 4, cli_n->data, node_to_delete->data);
      }
    }
    if (file != NULL) {
      fclose(file);
    }
  }
}
