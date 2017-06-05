#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

//// Compatibility
#if defined POSIX
#define CLEARSCR system ( "clear" )
#elif defined MSDOS || defined WIN32
#define CLEARSCR system ( "cls" )
#endif

//// Application constants
#define TITLE               "AGENCIA VIAJES UCAM S.A."

#define FILENAME_MAX_LENGTH 50
#define MAX_LENGTH          150
#define MAX_COMMAND          150

// Errors
#define FILE_NOT_FOUND "ERROR. No existe el archivo."
#define INSUFFICIENT_MEMORY "ERROR. Memoria insuficiente."
#define CLIENT_NOT_FOUND "ERROR. Cliente no encontrado."
#define TRAVEL_NOT_FOUND "ERROR. Viaje no encontrado."

#include "client_utils.h"
#include "travel_utils.h"

typedef struct {
  int action;
  client* cli;
  travel* trav;
} command;

//// Prototypes
void show_menu(void);
char get_option(void);
void execute(void);
void display_all(void);

void set_filename(char[]);
void clean_string(char c1[]);
int alphabetize (char *a, char *b);

#endif // COMMON_H_INCLUDED
