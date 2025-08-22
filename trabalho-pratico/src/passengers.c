#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "validation.h"
#include "passengers.h"
#include "users.h"
#include "flights.h"

typedef struct passenger{
  char* flight_id;
  char* user_id;
} Passenger;



void func_free_passengers(GHashTable* passengers_hash_table) {
  GHashTableIter iteration;
  gpointer key, data;

  g_hash_table_iter_init(&iteration, passengers_hash_table); // inicia a iteração pela passengers_hash_table

  while (g_hash_table_iter_next(&iteration, &key, &data)) { // por cada iteração, os componentes do struct são libertados da memória
    Passenger* passenger = data;

    free(passenger->flight_id);
    free(passenger->user_id);

    free(passenger);  // libertação do próprio struct da memória
  }
}


Passenger* func_new_passenger(char* flight_id, char* user_id) {
	Passenger* new_passenger = malloc(sizeof(Passenger)); // é necessária, posteriormente, a libertação da memória alocada
	
  	// Copia a informação providenciada para o new_passenger, sendo necessária, posteriormente, a libertação da memória alocada
 	new_passenger->flight_id = strdup(flight_id);
	new_passenger->user_id = strdup(user_id);
	
	return new_passenger;
}


GHashTable* func_parse_passengers(char* path, GHashTable* users_hash_table, GHashTable* flights_hash_table, int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100]) {
	char buffer[60];

  	// criação do caminho correto para o ficheiro passengers.csv
	char directory[100] = {0}; // inicializa com tudo vazio 
	strcat(directory,path);
	strcat(directory,"/passengers.csv"); // concatena-se o nome do ficheiro com o path fornecido (exemplo: dataset/passengers.csv)
  	
	// abertura dos ficheiros
	FILE* passengers_file = fopen(directory,"r");
	if (passengers_file == NULL) return NULL;
	FILE* passengers_error_file = fopen("Resultados/passengers_errors.csv","a");
	if (passengers_error_file == NULL) return NULL;

	if(!fgets(buffer, 60, passengers_file)) return NULL; // guardar o cabeçalho 
	fprintf(passengers_error_file,"%s",buffer); // escrever o cabeçalho

	// inicialiação da hashTable
	GHashTable *passengers_hash_table = g_hash_table_new(g_int_hash, g_int_equal);
	
	// criação de um array de inteiros, onde em cada posição "i" (com 0 <= i < 200000) se encontra o número de passageiros do voo com id "i+1"
	int number_passengers_array[200000] = {0}; // inicializa com tudo vazio
	while (fgets(buffer, 60, passengers_file)) { // enquanto se consegue ler uma linha, guarda-se a mesma no buffer
		char* buffer_aux = strdup(buffer);
		char* buffer_pointer = buffer_aux;

		// separação da linha em strings delimitadas por ";" a serem guardadas num array
		char* string_store[2];
		string_store[0] = strsep(&buffer_pointer,";");
		string_store[1] = strsep(&buffer_pointer,"\0");
		int size = strlen(string_store[1]);
		string_store[1][size-1] = '\0'; // alteração do último caractere da última string, de '\n' para '\0'

		if (strlen(string_store[0]) > 0 && g_hash_table_lookup(users_hash_table,string_store[1]) != NULL) { // verifica se o id de voo e o passageiro em questão são válidos
			number_passengers_array[atoi(string_store[0]) - 1]++; // incrementa-se o número de passageiros do voo em causa
		}

		free(buffer_aux);
	}
	fclose(passengers_file);

	// segunda abertura do ficheiro, de forma a restaurar o buffer
	passengers_file = fopen(directory,"r");
	if (passengers_file == NULL) return NULL;

	if(!fgets(buffer, 60, passengers_file)) return NULL; // ignorar o cabeçalho 


	// inicialização das matrizes/arrays de hashtables
	GHashTable *passengers_by_day[100][12][31];
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 12; j++) {
			for (int k = 0; k < 31; k++) passengers_by_day[i][j][k] = g_hash_table_new(g_str_hash, g_str_equal);
		}
	}


	GHashTable *passengers_by_month[100][12];
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 12; j++) passengers_by_month[i][j] = g_hash_table_new(g_str_hash, g_str_equal);
	}


	GHashTable *passengers_by_year[100];
	for (int i = 0; i < 100; i++) passengers_by_year[i] = g_hash_table_new(g_str_hash, g_str_equal);
	
	int key = 1;

	while (fgets(buffer, 60, passengers_file)) { // enquanto se consegue ler uma linha, guarda-se a mesma no buffer
		char* buffer_aux = strdup(buffer);
		char* buffer_pointer = buffer_aux;

		// separação da linha em strings delimitadas por ";" a serem guardadas num array
		char* string_store[2];	
		string_store[0] = strsep(&buffer_pointer,";");
		string_store[1] = strsep(&buffer_pointer,"\0");
		int size = strlen(string_store[1]);
		string_store[1][size-1] = '\0'; // alteração do último caractere da última string, de '\n' para '\0'

		Flight* flight = g_hash_table_lookup(flights_hash_table,string_store[0]);
		User* user = g_hash_table_lookup(users_hash_table,string_store[1]);
		
		int current_number_passengers = number_passengers_array[atoi(string_store[0]) - 1];
		// validação da linha
		if (func_valid_string(string_store[0]) && func_valid_string(string_store[1]) && user != NULL && flight != NULL && func_get_flight_total_seats(flight) >= current_number_passengers) {
    		Passenger* passenger = func_new_passenger(string_store[0], string_store[1]);
			
			// definir número de passageiros do voo
			func_set_flight_number_passengers(flight, current_number_passengers);			
			
			// incrementar o número de voos do utlizador
			int number_flights = func_get_user_number_flights(user);
			number_flights++;
			func_set_user_number_flights(user, number_flights);
			
			// definir o número de passageiros de acordo com a data do voo
			int* schedule_departure_date = func_get_flight_schedule_departure_date(flight);
			int year = schedule_departure_date[0];
			int month = schedule_departure_date[1];
			int day = schedule_departure_date[2];
			number_passengers_by_date[year%100][month - 1][day - 1]++;


			if (g_hash_table_lookup(passengers_by_day[year%100][month - 1][day - 1], passenger->user_id) == NULL) { // verificar se o passageiro já existia num certo dia
				g_hash_table_insert(passengers_by_day[year%100][month - 1][day - 1], passenger->user_id, passenger->user_id); // caso o passageiro ainda não exista na hash table, é inserido e aumenta-se o número de passageiros únicos nesse dia
				number_unique_passengers_by_day[year%100][month - 1][day - 1]++;

			 	if (g_hash_table_lookup(passengers_by_month[year%100][month - 1], passenger->user_id) == NULL) { // verificar se o passageiro já existia num certo mês
			    	g_hash_table_insert(passengers_by_month[year%100][month - 1], passenger->user_id, passenger->user_id); // caso o passageiro ainda não exista na hash table, é inserido e aumenta-se o número de passageiros únicos nesse mês
			    	number_unique_passengers_by_month[year%100][month - 1]++;

			    	if (g_hash_table_lookup(passengers_by_year[year%100], passenger->user_id) == NULL) { // verificar se o passageiro já existia num certo ano
			        	g_hash_table_insert(passengers_by_year[year%100], passenger->user_id, passenger->user_id); // caso o passageiro ainda não exista na hash table, é inserido e aumenta-se o número de passageiros únicos nesse ano
			        	number_unique_passengers_by_year[year%100]++;
					}
				}
			}

			key++;

			g_hash_table_insert(passengers_hash_table, &key, passenger); // guarda na hashTable
		} else {
			fprintf(passengers_error_file,"%s",buffer); // caso a linha não seja validada, escreve-se a mesma no ficheiro de erros
		}
		free(buffer_aux);
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 12; j++) {
			for (int k = 0; k < 31; k++) g_hash_table_destroy(passengers_by_day[i][j][k]);
		}
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 12; j++) g_hash_table_destroy(passengers_by_month[i][j]);
	}

	for (int i = 0; i < 100; i++) g_hash_table_destroy(passengers_by_year[i]);
	

	fclose(passengers_file);
	return passengers_hash_table;
}


char* func_get_passenger_flight_id(Passenger* passenger) {
	return passenger->flight_id;
}
char* func_get_passenger_user_id(Passenger* passenger) {
	return passenger->user_id;
}
