//// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#include "common.h"
#include "client_list_utils.h"
#include "client_utils.h"
#include "travel_list_utils.h"
#include "travel_utils.h"
#include "command_stack_utils.h"
#include "command_utils.h"

int data;

cli_node* head = NULL;
command_node* top = NULL;
cli_callback disp = l_cli_display;

//// Main

int main() {
  SetConsoleTitle(TITLE);
  execute();
  system("PAUSE");
  return (EXIT_SUCCESS);
}

//// Primary functions

void show_menu() {
  int client_count = l_cli_count();
  int command_empty = s_command_empty();
  CLEARSCR;
  puts("======================");
  puts("Seleccione una opcionnn");
  puts("======================");
  puts("");
  puts("# Acciones");
  if (client_count > 0) {
    puts("   L - Listar catalogo");
  }
  puts("   S - Salir");
  puts("");
  if (command_empty == 0) {
    puts("# Comandos");
    puts("   D - Deshacer");
//    puts("   R - Rehacer");
  }
  puts("");
  puts("# Clientes");
  puts("   1 - Alta");
  if (client_count > 0) {
    puts("   2 - Baja");
    puts("");
    puts("# Viajes");
    puts("   3 - Alta");
    puts("   4 - Eliminar");
  }
}

char get_option() {
  char aux;
  scanf(" %c", &aux); // Ignoring trailing whitespace
  if (islower(aux)) {
    aux = toupper(aux); // Comparing to uppercase
  }
  return aux;
}

void execute() {
  char option;
  int client_count = l_cli_count();
  int command_empty = s_command_empty();
  int pause = 0;
  show_menu();
  option = get_option();
  if (client_count > 0 && option == 'L') {
    display_all();
    pause = 1;
  } else if (option == 'S') {
    exit(EXIT_SUCCESS);
  } else if (option == '1') {
    add_client();
    pause = 1;
  } else if (client_count > 0 && option == '2') {
    remove_client();
    pause = 1;
  } else if (client_count > 0 && option == '3') {
    add_travel();
    pause = 1;
  } else if (client_count > 0 && option == '4') {
    remove_travel();
    pause = 1;
  } else if (command_empty == 0 && option == 'D') {
    undo_action();
//  } else if (command_empty == 0 && option == 'R') {
//    redo_action();
    done = 1;
  }
  if (pause == 1) {
    system("PAUSE");
  }
  execute();
}

void display_all() {
  int client_count = l_cli_count();
  CLEARSCR;
  if(client_count == 0) {
    puts("Lista de clientes vacia");
  } else {
    puts("/****** AGENCIA DE VIAJES *******/");
    puts("");
    l_cli_traverse(l_cli_display);
  }
}

// Secondary functions

void set_filename(char filename[]) {
  char input[FILENAME_MAX_LENGTH];

  CLEARSCR;
  filename[0] = '\0';
  puts("Nombre del archivo:");
  scanf(" %49s", input);

  strcat(filename, "./");
  strcat(filename, input);
  clean_string(filename);
}

void clean_string(char c1[]) {
  int i;
  for (i = 0; i<strlen(c1); i++) {
    if (c1[i] == '\n') {
      c1[i] = '\0';
    }
  }
}

int alphabetize (char *a, char *b) {
  int r = strcasecmp(a, b);
  if (r) return r;
  return -strcmp(a, b);
}










