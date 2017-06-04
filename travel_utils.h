#ifndef TRAVEL_UTILS_H_INCLUDED
#define TRAVEL_UTILS_H_INCLUDED

typedef struct {
  char *id;
  char *destination;
  char *hotel;
  char *transport;
  int nights;
  float night_cost;
  float transport_cost;
} travel;

void add_travel(void);
void remove_travel(void);

#endif // TRAVEL_UTILS_H_INCLUDED
