#include <stdio.h>
#include <glib.h>
#include "passengers.h"
#include "users.h"
#include "flights.h"
#include "reservations.h"



// libertações de memória finais
void func_clean_hash (GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table, GHashTable* passengers_hash_table) {
  func_free_flights(flights_hash_table);
  g_hash_table_destroy(flights_hash_table);

  func_free_passengers(passengers_hash_table);
  g_hash_table_destroy(passengers_hash_table);

  func_free_reservations(reservations_hash_table);
  g_hash_table_destroy(reservations_hash_table);

  func_free_users(users_hash_table);
  g_hash_table_destroy(users_hash_table);
}
