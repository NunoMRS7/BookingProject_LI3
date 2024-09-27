#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "reservations.h"
#include "validation.h"
#include "users.h"

typedef struct reservation {
  char* id;
  char* user_id;
  char* hotel_id;
  char* hotel_name;
  int hotel_stars;
  int city_tax;
  int begin_date[3]; // "aaaa/MM/dd" -> [aaaa,MM,dd]
  int end_date[3]; // "aaaa/MM/dd" -> [aaaa,MM,dd]
  int price_per_night;
  char* includes_breakfast;
  int rating;
} Reservation;


void func_free_reservations(GHashTable* reservations_hash_table) {
  GHashTableIter iteration;
  gpointer key, data;

  g_hash_table_iter_init(&iteration, reservations_hash_table); // inicia a iteração pela reservations_hash_table

  while (g_hash_table_iter_next(&iteration, &key, &data)) { // por cada iteração, os componentes do struct são libertados da memória
    Reservation* reservation = data;

    free(reservation->id);
    free(reservation->user_id);
	free(reservation->hotel_id);
	free(reservation->hotel_name);
	free(reservation->includes_breakfast);

    free(reservation); // libertação do próprio struct da memória
  }
}


Reservation* func_new_reservation(char* id, char* user_id, char* hotel_id, char* hotel_name, char* hotel_stars, char* city_tax, char* begin_date, char* end_date, char* price_per_night, char* includes_breakfast, char* rating) {
	Reservation* new_reservation = malloc(sizeof(Reservation)); // é necessária, posteriormente, a libertação da memória alocada
	
  	// Copia a informação providenciada para a new_reservation, sendo necessária, posteriormente, a libertação da memória alocada
  	new_reservation->id = strdup(id);
	new_reservation->user_id = strdup(user_id);
	new_reservation->hotel_id = strdup(hotel_id);
	new_reservation->hotel_name = strdup(hotel_name);
	new_reservation->hotel_stars = atoi(hotel_stars);
	new_reservation->city_tax = atoi(city_tax);
	sscanf(begin_date, "%d/%d/%d", &new_reservation->begin_date[0],
								   &new_reservation->begin_date[1],
								   &new_reservation->begin_date[2]);
    sscanf(end_date, "%d/%d/%d", &new_reservation->end_date[0],
							     &new_reservation->end_date[1],
							     &new_reservation->end_date[2]);
	new_reservation->price_per_night = atoi(price_per_night);
	new_reservation->includes_breakfast = NULL;
	if (strlen(includes_breakfast) == 0 || strcasecmp(includes_breakfast,"false") == 0 || strcasecmp(includes_breakfast,"f") == 0 || strcasecmp(includes_breakfast,"0") == 0) {
		new_reservation->includes_breakfast = malloc((strlen("False") + 1) * sizeof(char));
    	strcpy(new_reservation->includes_breakfast, "False");
	}
	else if (strcasecmp(includes_breakfast,"true") == 0 || strcasecmp(includes_breakfast,"t") == 0 || strcasecmp(includes_breakfast,"1") == 0) {
		new_reservation->includes_breakfast = malloc((strlen("True") + 1) * sizeof(char));
    	strcpy(new_reservation->includes_breakfast, "True");
	}
	new_reservation->rating = atoi(rating);

	return new_reservation;
}


GHashTable* func_parse_reservations(char* path, GHashTable* users_hash_table, int number_reservations_by_date[100][12][31]) {
	char buffer[250];
	
	// criação do caminho correto para o ficheiro reservations.csv
	char directory[100] = {0}; // inicializa com tudo vazio 
	strcat(directory,path);
	strcat(directory,"/reservations.csv"); // concatena-se o nome do ficheiro com o path fornecido (exemplo: dataset/reservations.csv)

	// abertura dos ficheiros
	FILE* reservations_file = fopen(directory,"r");
	if(reservations_file == NULL) return NULL;
	FILE* reservations_error_file = fopen("Resultados/reservations_errors.csv","a");
	if(reservations_error_file == NULL) return NULL;

	if(!fgets(buffer, 250, reservations_file)) return NULL; // guardar o cabeçalho 
  	fprintf(reservations_error_file,"%s",buffer); // escrever o cabeçalho 

	// inicialiação da hashTable
	GHashTable* reservations_hash_table = g_hash_table_new(g_str_hash, g_str_equal);

	while(fgets(buffer, 250, reservations_file)) { // enquanto se consegue ler uma linha, guarda-se a mesma no buffer
		char* buffer_aux = strdup(buffer);
		char* buffer_pointer = buffer_aux;
    
		// separação da linha em strings delimitadas por ";" a serem guardadas num array
    	char* string_store[14];
		int i;
		for(i = 0; i < 14; i++) {
			string_store[i] = strsep(&buffer_pointer,";");
		}
		int size = strlen(string_store[i-1]);
		string_store[i-1][size-1] = '\0'; // alteração do último caractere da última string, de '\n' para '\0'

    	// validação da linha
    	User* user = g_hash_table_lookup(users_hash_table,string_store[1]);
		if (user != NULL && func_valid_string(string_store[0]) && func_valid_string(string_store[1]) && func_valid_string(string_store[2]) && func_valid_string(string_store[3]) && func_valid_grade(string_store[4]) && func_valid_city_tax(string_store[5]) && func_valid_string(string_store[6]) && func_valid_date_3(string_store[7]) && func_valid_date_3(string_store[8]) && func_date_after_date_3(string_store[7],string_store[8]) && func_valid_price_per_night(string_store[9]) && func_valid_includes_breakfast(string_store[10]) && func_valid_grade(string_store[12])) {
			Reservation* reservation = func_new_reservation(string_store[0],string_store[1],string_store[2],string_store[3],string_store[4],string_store[5],string_store[7],string_store[8],string_store[9],string_store[10],string_store[12]);
    		g_hash_table_insert(reservations_hash_table, (reservation->id), reservation); // guarda na hashTable

			// o número de reservas deste utilizador incrementa
			int number_reservations = func_get_user_number_reservations(user);
			number_reservations++;
			func_set_user_number_reservations(user, number_reservations);

    		int number_nights = reservation->end_date[2] - reservation->begin_date[2];
			double total_spent = func_get_user_total_spent(user);
			total_spent += (reservation->price_per_night*number_nights)+(((double)(reservation->price_per_night*number_nights)/100)*reservation->city_tax); // o total gasto pelo utilizador incrementa
			func_set_user_total_spent(user, total_spent);

			number_reservations_by_date[reservation->begin_date[0]%100][reservation->begin_date[1]-1][reservation->begin_date[2]-1]++;
    	}
		else {
			fprintf(reservations_error_file,"%s",buffer); // caso a linha não seja validada, escreve-se a mesma no ficheiro de erros
		}
    	free(buffer_aux);
	}
	fclose(reservations_error_file);
	fclose(reservations_file);
	return reservations_hash_table;
}


char* func_get_reservation_id(Reservation* reservation) {
	return reservation->id;
}
char* func_get_reservation_user_id(Reservation* reservation) {
	return reservation->user_id;
}
char* func_get_reservation_hotel_id(Reservation* reservation) {
	return reservation->hotel_id;
}
char* func_get_reservation_hotel_name(Reservation* reservation) {
	return reservation->hotel_name;
}
int func_get_reservation_hotel_stars(Reservation* reservation) {
	return reservation->hotel_stars;
}
int func_get_reservation_city_tax(Reservation* reservation) {
	return reservation->city_tax;
}
int* func_get_reservation_begin_date(Reservation* reservation) {
	return reservation->begin_date;
}
int* func_get_reservation_end_date(Reservation* reservation) {
	return reservation->end_date;
}
int func_get_reservation_price_per_night(Reservation* reservation) {
	return reservation->price_per_night;
}
char* func_get_reservation_includes_breakfast(Reservation* reservation) {
	return reservation->includes_breakfast;
}
int func_get_reservation_rating(Reservation* reservation) {
	return reservation->rating;
}
