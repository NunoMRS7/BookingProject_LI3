#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ncurses.h>
#include "menu.h"
#include "input.h"
#include "passengers.h"
#include "users.h"
#include "flights.h"
#include "reservations.h"
#include "queries.h"
#include "get_input.h"
#include "defines.h"
#include "hash_funcs.h"


int main(int argc, char *argv[]) {    
  int is_detailed = (strcmp(argv[0],"./programa-testes") == 0) ? 1 : 0; // a variável is_detailed distingue o formato de execução do programa. Se for 1, executa-se o programa-testes, se for 0 executa-se o programa-principal
  struct timespec start, end;
  double time_spent;
  if (is_detailed) clock_gettime(CLOCK_REALTIME, &start);
 
  // parse da base de dados (criam-se as hashTable)
  int account_registrations_by_date[100][12][31] = {0};
  int number_reservations_by_date[100][12][31] = {0};
  int number_flights_by_date[100][12][31] = {0};
  int number_passengers_by_date[100][12][31] = {0};
  int number_unique_passengers_by_day[100][12][31] = {0};
  int number_unique_passengers_by_month[100][12] = {0};
  int number_unique_passengers_by_year[100] = {0};


  // modo batch
  if ((argc == 3 && !is_detailed) || (argc == 4 && is_detailed)) {
    char* data_set_path = argv[1];
    char* input_path = argv[2];
    char* output_path = NULL;
    if (is_detailed) output_path = argv[3];
  	
    GHashTable* users_hash_table = func_parse_users(data_set_path, account_registrations_by_date);
    GHashTable* flights_hash_table = func_parse_flights(data_set_path, number_flights_by_date);
  	GHashTable* reservations_hash_table = func_parse_reservations(data_set_path, users_hash_table, number_reservations_by_date);
    GHashTable* passengers_hash_table = func_parse_passengers(data_set_path, users_hash_table, flights_hash_table, number_passengers_by_date, number_unique_passengers_by_day, number_unique_passengers_by_month, number_unique_passengers_by_year);
	
  	if (flights_hash_table == NULL || passengers_hash_table == NULL || reservations_hash_table == NULL || users_hash_table == NULL) {
      printf("Error loading input files .csv\n");
		  return 1;
  	}

    setlocale(LC_COLLATE, "en_US.UTF-8");
    if (input_line(input_path, output_path, flights_hash_table, users_hash_table,reservations_hash_table,passengers_hash_table, account_registrations_by_date, number_reservations_by_date, number_flights_by_date, number_passengers_by_date, number_unique_passengers_by_day, number_unique_passengers_by_month, number_unique_passengers_by_year, argc-3) == 0) {
      printf("Error loading input file .txt\n");
      return 1;
    }

    // libertações de memória finais
    func_clean_hash(flights_hash_table, users_hash_table, reservations_hash_table, passengers_hash_table);
    if (is_detailed) {
      clock_gettime(CLOCK_REALTIME, &end);
      time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
      printf("\n\nO tempo de execução do programa é %.6f segundos\n\n", time_spent);
      struct rusage r_usage;
      getrusage(RUSAGE_SELF, &r_usage);
      printf("A memória usada pelo programa é %ld KB\n\n\n", r_usage.ru_maxrss);
    }
  }
  // modo interativo
  else if (argc == 1 && !is_detailed) {
    func_interactive_mode(account_registrations_by_date,  number_reservations_by_date, number_flights_by_date, number_passengers_by_date, number_unique_passengers_by_day, number_unique_passengers_by_month, number_unique_passengers_by_year);
  }
  else if (is_detailed) {
    printf("Usage\n");
    printf("  Test mode: %s <input_folder> <command_file> <expected_output_folder>\n", argv[0]);
    return 1;
  }
  else {
    printf("Usage\n");
    printf("  Batch mode: %s <input_folder> <command_file>\n", argv[0]);
    printf("  Interactive mode: %s\n", argv[0]);
    return 1;
  }

  	return 0;
}
