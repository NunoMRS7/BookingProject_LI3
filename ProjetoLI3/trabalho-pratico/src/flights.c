#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "flights.h"
#include "validation.h"

typedef struct flight {
    char* id;
    char* airline;
    char* plane_model;
    int total_seats;
    int number_passengers;
    char* origin; 
    char* destination; 
    int schedule_departure_date[6]; // "aaaa/MM/dd hh:mm:ss" -> [aaaa, MM, dd, hh, mm, ss]
    int schedule_arrival_date[6]; // "aaaa/MM/dd hh:mm:ss" -> [aaaa, MM, dd, hh, mm, ss] 
    int real_departure_date[6]; // "aaaa/MM/dd hh:mm:ss" -> [aaaa, MM, dd, hh, mm, ss]
    int real_arrival_date[6]; // "aaaa/MM/dd hh:mm:ss" -> [aaaa, MM, dd, hh, mm, ss]
    int time_delay;
} Flight;

void func_convert_to_upper_case(char *string) {
    for (int i = 0; string[i]; i++) {
        if (string[i] >= 97 && string[i] <= 122) string[i] -= 32;
    }
}


void func_free_flights(GHashTable* flights_hash_table) {
    GHashTableIter iteration;
    gpointer key, data;

    g_hash_table_iter_init(&iteration, flights_hash_table); // inicia a iteração pela flights_hash_table

    while (g_hash_table_iter_next(&iteration, &key, &data)) { // por cada iteração, os componentes do struct são libertados da memória
        Flight* flight = data;

        free(flight->id);
        free(flight->airline);
        free(flight->plane_model);
        free(flight->origin);
        free(flight->destination);

        free(flight); // libertação do próprio struct da memória
    }
}


int func_calculate_time_difference(int schedule_departure_date[6], int real_departure_date[6]) {
    int sec_diff = 0;

    sec_diff += (real_departure_date[2] - schedule_departure_date[2]) * 24 * 60 * 60; // dias para segundos
    sec_diff += (real_departure_date[3] - schedule_departure_date[3]) * 60 * 60;      // horas para segundos
    sec_diff += (real_departure_date[4] - schedule_departure_date[4]) * 60;           // minutos para segundos
    sec_diff +=  real_departure_date[5] - schedule_departure_date[5];                 // segundos

    return sec_diff;
}


Flight* func_new_flight(char* id, char* airline, char* plane_model, char* total_seats, char* origin, char* destination, char* schedule_departure_date, char* schedule_arrival_date, char* real_departure_date, char* real_arrival_date) {
    Flight* new_flight = malloc(sizeof(Flight)); // é necessária, posteriormente, a libertação da memória alocada
  
    // Copia a informação providenciada para o new_flight, sendo necessária, posteriormente, a libertação da memória alocada
	new_flight->id = strdup(id);
	new_flight->airline = strdup(airline);
	new_flight->plane_model = strdup(plane_model);
	new_flight->total_seats = atoi(total_seats);
	char* aux1 = strdup(origin);
    func_convert_to_upper_case(aux1);
    new_flight->origin = aux1;
    char* aux2 = strdup(destination);
    func_convert_to_upper_case(aux2);
    new_flight->destination = aux2;
    sscanf(schedule_departure_date, "%d/%d/%d %d:%d:%d", &new_flight->schedule_departure_date[0], &new_flight->schedule_departure_date[1],
                                                         &new_flight->schedule_departure_date[2], &new_flight->schedule_departure_date[3],
                                                         &new_flight->schedule_departure_date[4], &new_flight->schedule_departure_date[5]);
    sscanf(schedule_arrival_date, "%d/%d/%d %d:%d:%d", &new_flight->schedule_arrival_date[0], &new_flight->schedule_arrival_date[1],
                                                       &new_flight->schedule_arrival_date[2], &new_flight->schedule_arrival_date[3],
                                                       &new_flight->schedule_arrival_date[4], &new_flight->schedule_arrival_date[5]);
    sscanf(real_departure_date, "%d/%d/%d %d:%d:%d", &new_flight->real_departure_date[0], &new_flight->real_departure_date[1],
                                                     &new_flight->real_departure_date[2], &new_flight->real_departure_date[3],
                                                     &new_flight->real_departure_date[4], &new_flight->real_departure_date[5]);
    sscanf(real_arrival_date, "%d/%d/%d %d:%d:%d", &new_flight->real_arrival_date[0], &new_flight->real_arrival_date[1],
                                                   &new_flight->real_arrival_date[2], &new_flight->real_arrival_date[3],
                                                   &new_flight->real_arrival_date[4], &new_flight->real_arrival_date[5]);
    new_flight->time_delay = func_calculate_time_difference(new_flight->schedule_departure_date,new_flight->real_departure_date);

	return new_flight;
}


GHashTable* func_parse_flights(char* path, int number_flights_by_date[100][12][31]) {
	char buffer[260];
  
    // criação do caminho correto para o ficheiro flights.csv
	char directory[100] = {0}; // inicializa com tudo vazio 
	strcat(directory,path);
	strcat(directory,"/flights.csv"); // concatena-se o nome do ficheiro com o path fornecido (exemplo: dataset/flights.csv)

    // abertura dos ficheiros
	FILE* flights_file = fopen(directory,"r");
    if(flights_file == NULL) return NULL;
    FILE* flights_error_file = fopen("Resultados/flights_errors.csv","a");
	if(flights_error_file == NULL) return NULL;

	if (!fgets(buffer, 260, flights_file)) return NULL; // guardar o cabeçalho 
	fprintf(flights_error_file,"%s",buffer); // escrever o cabeçalho

    // inicialiação da hashTable
    GHashTable* flights_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
  
	while(fgets(buffer, 260, flights_file)) { // enquanto se consegue ler uma linha, guarda-se a mesma no buffer
		char* buffer_aux = strdup(buffer); 
        char* buffer_pointer = buffer_aux;

        // separação da linha em strings delimitadas por ";" a serem guardadas num array
        char* string_store[13];
		int i;
		for(i = 0; i < 13; i++) {
		      string_store[i] = strsep(&buffer_pointer,";");
		}
		int size = strlen(string_store[i-1]);
		string_store[i-1][size-1] = '\0'; // alteração do último caractere da última string, de '\n' para '\0'

        // validação da linha
		if (func_valid_string(string_store[0]) && func_valid_string(string_store[1]) && func_valid_string(string_store[2]) && func_valid_total_seats(string_store[3]) && func_valid_acronym(string_store[4], 3) && func_valid_acronym(string_store[5], 3) && func_valid_date_6(string_store[6]) && func_valid_date_6(string_store[7]) && func_date_after_date_6(string_store[6], string_store[7]) && func_valid_date_6(string_store[8]) && func_valid_date_6(string_store[9]) && func_date_after_date_6(string_store[8], string_store[9]) && func_valid_string(string_store[10]) && func_valid_string(string_store[11])) {
            Flight* flight = func_new_flight(string_store[0],string_store[1],string_store[2],string_store[3],string_store[4],string_store[5],string_store[6],string_store[7],string_store[8],string_store[9]);
            g_hash_table_insert(flights_hash_table ,(flight->id),flight); // guarda na hashTable

            number_flights_by_date[flight->schedule_departure_date[0]%100][flight->schedule_departure_date[1]-1][flight->schedule_departure_date[2]-1]++;
        }
        else {
			fprintf(flights_error_file,"%s",buffer); // caso a linha não seja validada, escreve-se a mesma no ficheiro de erros
		}
        free(buffer_aux);
	}
	fclose(flights_error_file);
    fclose(flights_file);
    return flights_hash_table;
}


void func_set_flight_number_passengers (Flight* flight, int number_passengers) {
    flight->number_passengers = number_passengers;
}

char* func_get_flight_id(Flight* flight) {
    return flight->id;
}
char* func_get_flight_airline(Flight* flight) {
    return flight->airline;
}
char* func_get_flight_plane_model (Flight* flight) {
    return flight->plane_model;
}
int func_get_flight_total_seats (Flight* flight) {
    return flight->total_seats;
}
int func_get_flight_number_passengers (Flight* flight) {
    return flight->number_passengers;
}
char* func_get_flight_origin (Flight* flight) {
    return flight->origin;
}
char* func_get_flight_destination (Flight* flight) {
    return flight->destination;
}
int* func_get_flight_schedule_departure_date (Flight* flight) {
    return flight->schedule_departure_date;
}
int* func_get_flight_schedule_arrival_date (Flight* flight) {
    return flight->schedule_arrival_date;
}
int* func_get_flight_real_departure_date (Flight* flight) {
    return flight->real_departure_date;
}
int* func_get_flight_real_arrival_date (Flight* flight) {
    return flight->real_arrival_date;
}
int func_get_flight_time_delay (Flight* flight) {
    return flight->time_delay;
}
