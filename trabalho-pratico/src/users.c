#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "validation.h"
#include "defines.h"


typedef struct user {
  	char* id;
  	char* name;
  	int birth_date[3]; // "aaaa/MM/dd" -> [aaaa,MM,dd]
  	int age;
	int number_flights;
  	char* sex;
  	char* passport;
  	char* country_code;
  	int account_creation[6]; // "aaaa/MM/dd hh:mm:ss" -> [aaaa, MM, dd, hh, mm, ss]
  	char* account_status;
	int number_reservations;
	double total_spent;
} User;


void func_free_users(GHashTable* users_hash_table) {
  	GHashTableIter iteration;
  	gpointer key, data;

  	g_hash_table_iter_init(&iteration, users_hash_table); // inicia a iteração pela users_hash_table

  	while (g_hash_table_iter_next(&iteration, &key, &data)) { // por cada iteração, os componentes do struct são libertados da memória
    	User* user = data;

    	free(user->id);
    	free(user->name);
		free(user->sex);
		free(user->passport);
		free(user->country_code);
		free(user->account_status);

    	free(user); // libertação do próprio struct da memória
  	}
}


int func_convert_age(char* birth_date) {
	int birth_year,birth_month,birth_day;
	sscanf(birth_date,"%d/%d/%d", &birth_year, &birth_month, &birth_day);

    int age = CURRENT_YEAR - birth_year;
    if (CURRENT_MONTH < birth_month || (CURRENT_MONTH == birth_month && CURRENT_DAY < birth_day)) {
        age--;
    }
    return age;
}


User* func_new_user(char* id, char* name, char* birth_date, int age, char* sex, char* passport, char* country_code, char* account_creation, char* account_status) {
	User* new_user = malloc(sizeof(User)); // é necessária, posteriormente, a libertação da memória alocada
	
	// Copia a informação providenciada para o new_user, sendo necessária, posteriormente, a libertação da memória alocada
	new_user->id = strdup(id);
	new_user->name = strdup(name);
	sscanf(birth_date, "%d/%d/%d", &new_user->birth_date[0],
								   &new_user->birth_date[1],
								   &new_user->birth_date[2]);
	new_user->age = age;
	new_user->number_flights = 0; // inicializa o número de voos do utilizador a 0
	new_user->sex = strdup(sex);
	new_user->passport = strdup(passport);
	new_user->country_code = strdup(country_code);
	sscanf(account_creation, "%d/%d/%d %d:%d:%d", &new_user->account_creation[0], &new_user->account_creation[1],
												  &new_user->account_creation[2], &new_user->account_creation[3],
												  &new_user->account_creation[4], &new_user->account_creation[5]);
	new_user->account_status = strdup(account_status);
	new_user->number_reservations = 0;
	new_user->total_spent = 0;
	
	return new_user;
}


GHashTable* func_parse_users(char* path, int account_registrations_by_date[100][12][31]) {
	char buffer[250];
	
    // criação do caminho correto para o ficheiro users.csv
	char directory[100] = {0}; // inicializa com tudo vazio 
	strcat(directory,path);
	strcat(directory,"/users.csv"); // concatena-se o nome do ficheiro com o path fornecido (exemplo: dataset/users.csv)

	// abertura dos ficheiros
	FILE* users_file = fopen(directory,"r");
	if(users_file == NULL) return NULL;
	FILE* users_error_file = fopen("Resultados/users_errors.csv","a");
	if(users_error_file == NULL) return NULL;

	if(!fgets(buffer, 250, users_file)) return NULL; // guardar o cabeçalho
	fprintf(users_error_file,"%s",buffer); // escrever o cabeçalho

	// inicialiação da hashTable
	GHashTable* users_hash_table = g_hash_table_new(g_str_hash, g_str_equal);

	while(fgets(buffer, 250, users_file)) { // enquanto se consegue ler uma linha, guarda-se a mesma no buffer
		char* buffer_aux = strdup(buffer);
		char* buffer_pointer = buffer_aux;

		// separação da linha em strings delimitadas por ";" a serem guardadas num array
		char* string_store[12];
		int i;
		for(i = 0; i < 12; i++) {
			string_store[i] = strsep(&buffer_pointer,";");
		}
		int size = strlen(string_store[i-1]);
		string_store[i-1][size-1] = '\0'; // alteração do último caractere da última string, de '\n' para '\0'

		// validação da linha
		if (func_valid_string(string_store[0]) && func_valid_string(string_store[1]) && func_valid_email(string_store[2]) && func_valid_phone_number(string_store[3]) && func_valid_date_3(string_store[4]) && func_valid_string(string_store[5]) && func_valid_string(string_store[6]) && func_valid_acronym(string_store[7], 2) && func_valid_string(string_store[8]) && func_valid_date_6(string_store[9]) && func_date_after_date_3(string_store[4], string_store[9]) && func_valid_string(string_store[10]) && func_valid_account_status(string_store[11])) {
			int age = func_convert_age(string_store[4]);
			User* user = func_new_user(string_store[0],string_store[1],string_store[4],age,string_store[5],string_store[6],string_store[7],string_store[9],string_store[11]);
    		g_hash_table_insert(users_hash_table, (user->id), user); // guarda na hashTable

			account_registrations_by_date[user->account_creation[0]%100][user->account_creation[1]-1][user->account_creation[2]-1]++;
		}
		else {
			fprintf(users_error_file,"%s",buffer); // caso a linha não seja validada, escreve-se a mesma no ficheiro de erros
		}
		free(buffer_aux);
	}
	fclose(users_error_file);
	fclose(users_file);
	return users_hash_table;
}



void func_set_user_number_flights(User* user, int number_flights) {
	user->number_flights = number_flights;
}
void func_set_user_number_reservations(User* user, int number_reservations) {
	user->number_reservations = number_reservations;
}
void func_set_user_total_spent(User* user, double total_spent) {
	user->total_spent = total_spent;
}


char* func_get_user_id(User* user) {
	return user->id;
}
char* func_get_user_name(User* user) {
	return user->name;
}
int func_get_user_age(User* user) {
	return user->age;
}
int func_get_user_number_flights(User* user) {
	return user->number_flights;
}
char* func_get_user_sex(User* user) {
	return user->sex;
}
char* func_get_user_passport(User* user) {
	return user->passport;
}
char* func_get_user_country_code(User* user) {
	return user->country_code;
}
char* func_get_user_account_status(User* user) {
	return user->account_status;
}
int func_get_user_number_reservations(User* user) {
	return user->number_reservations;
}
double func_get_user_total_spent(User* user) {
	return user->total_spent;
}
