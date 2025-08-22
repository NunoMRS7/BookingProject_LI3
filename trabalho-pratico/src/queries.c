#include <stdio.h>
#include <glib.h>
#include <string.h>
#include "queries.h"
#include "users.h"
#include "reservations.h"
#include "passengers.h"
#include "flights.h"
#include "outputs.h"


typedef struct airportinfo {
  char* origin;
  int delays[24000];
  int size;
  int median;
} AirportInfo;


typedef struct nameinfo {
    char* user_name;
    char* user_id;
} NameInfo;

typedef struct flightinfo {
    char* flight_id;
    int schedule_departure_date[6];
    char* destination;
    char* airline;
    char* plane_model;
} FlightInfo;

typedef struct output2 {
  char* id;
  int date[6]; // "aaaa/MM/dd" -> [aaaa,MM,dd]
  char* type;
} Output2;

typedef struct output4 {
  char* id;
  int begin_date[3]; // "aaaa/MM/dd" -> [aaaa,MM,dd]
  int end_date[3]; // "aaaa/MM/dd" -> [aaaa,MM,dd]
  char* user_id;
  int rating;
  double total_price;
} Output4;

typedef struct out6 {
  int number_passengers; //nº de passageiros
  char* name; //origem ou destino
} Out6;

int func_compare_dates (int date1[3], int date2[3]) {
  if (date1[0] < date2[0]) return -1;
  if (date1[0] > date2[0]) return 1;
  if (date1[1] < date2[1]) return -1;
  if (date1[1] > date2[1]) return 1;
  if (date1[2] < date2[2]) return -1;
  if (date1[2] > date2[2]) return 1;
  return 0; // caso único em que as datas são iguais
}


int func_compare_dates_6 (int date1[6], int date2[6]) {
  if (date1[0] < date2[0]) return -1;
  if (date1[0] > date2[0]) return 1;
  if (date1[1] < date2[1]) return -1;
  if (date1[1] > date2[1]) return 1;
  if (date1[2] < date2[2]) return -1;
  if (date1[2] > date2[2]) return 1;
  if (date1[3] < date2[3]) return -1;
  if (date1[3] > date2[3]) return 1;
  if (date1[4] < date2[4]) return -1;
  if (date1[4] > date2[4]) return 1;
  if (date1[5] < date2[5]) return -1;
  if (date1[5] > date2[5]) return 1;
  return 0; // caso único em que as datas são iguais
}

void func_insert_airport_in_order(AirportInfo* ordered_list_of_airports, char* origin, int median, int size) {
  int i,j;

  // encontrar a posição correta para inserir o aerporto
  for (i = 0; i < size; i++) {
    if (ordered_list_of_airports[i].median < median || (median == ordered_list_of_airports[i].median && strcoll(origin,ordered_list_of_airports[i].origin) < 0)) {
      break;
    }
  }

  // deslocar elementos para a direita para abrir espaço para o aerporto
  for (j = size; j > i; j--) {
    ordered_list_of_airports[j] = ordered_list_of_airports[j-1];
  }

  // inserir a informação na posição correta
  ordered_list_of_airports[i].origin = origin; // neste caso ordered_list_of_airports[i].origin é apenas um apontador para origin, parâmetro que é garantido já ser uma duplicação de uma outra string na função que chama a func_insert_airport_in_order
  ordered_list_of_airports[i].median = median;
}


void func_insert_time_delay_in_order (int flight_delay, int* delays, int* size) {
  int i,j;
  // encontrar a posição correta para inserir o novo delay
  for (i = 0; i < (*size); i++) {
    if (delays[i] <= flight_delay) {
      break;
    }
  }

  // deslocar elementos para a direita para abrir espaço para o novo delay
  for (j = (*size); j > i; j--) {
    delays[j] = delays[j-1];
  }

  // inserir o novo delay de voo na posição correta
  delays[i] = flight_delay;

  // atualizar o tamanho do array list_of_airports
  (*size)++;
}


void func_insert_date_in_order (int* schedule_departure_date, char* flight_id, char* flight_destination, char* flight_airline, char* flight_plane_model, FlightInfo* list_of_flights, int* size) {
  int i,j;

  // encontrar a posição correta para inserir o novo voo
  for (i = 0; i < (*size); i++) {
    if (func_compare_dates_6(schedule_departure_date,list_of_flights[i].schedule_departure_date) > 0 || (func_compare_dates_6(schedule_departure_date,list_of_flights[i].schedule_departure_date) == 0 && strcoll(flight_id,list_of_flights[i].flight_id) < 0)) {
      break;
    }
  }

  // deslocar elementos para a direita para abrir espaço para o novo voo
  for (j = (*size); j > i; j--) {
    list_of_flights[j] = list_of_flights[j-1];
  }

  // inserir a informação na posição correta
  list_of_flights[i].flight_id = strdup(flight_id);
  for (int k = 0; k < 6; k++) { 
    list_of_flights[i].schedule_departure_date[k] = schedule_departure_date[k];
  }
  list_of_flights[i].destination = strdup(flight_destination);
  list_of_flights[i].airline = strdup(flight_airline);
  list_of_flights[i].plane_model = strdup(flight_plane_model);

  // atualizar o 100anho do array list_of_flights
  (*size)++;
}


void func_insert_name_in_order(char* user_name, char* user_id, NameInfo* list_of_names, int* size) {
  int i,j;

  // encontrar a posição correta para inserir o novo nome
  for (i = 0; i < (*size); i++) {
    if (strcoll(user_name,list_of_names[i].user_name) < 0 || (strcoll(user_name,list_of_names[i].user_name) == 0 && strcoll(user_id,list_of_names[i].user_id) < 0)) {
      break;
    }
  }

  // deslocar elementos para a direita para abrir espaço para o novo nome
  for (j = (*size); j > i; j--) {
    list_of_names[j] = list_of_names[j-1];
  }

  // inserir o novo nome e id de utilizador na posição correta
  list_of_names[i].user_name = strdup(user_name);
  list_of_names[i].user_id = strdup(user_id);

  // atualizar o tamanho do array list_of_names
  (*size)++;
}


int func_sort(const void* a, const void* b) {

  // Converte os apontadores para o tipo de dados apropriado
  const Output2* outA = (const Output2*)a;
  const Output2* outB = (const Output2*)b;

  // Compara as datas em ordem decrescente
  if (outA->date[0] != outB->date[0]) return outB->date[0] - outA->date[0];
  if (outA->date[1] != outB->date[1]) return outB->date[1] - outA->date[1];
  if (outA->date[2] != outB->date[2]) return outB->date[2] - outA->date[2];
  if (outA->date[3] != outB->date[3]) return outB->date[3] - outA->date[3];
  if (outA->date[4] != outB->date[4]) return outB->date[4] - outA->date[4];
  if (outA->date[5] != outB->date[5]) return outB->date[5] - outA->date[5];
  
  // Se as datas forem iguais, compara os IDs em ordem crescente
  return strcmp(outA->id,outB->id);
}


int func_sort_query_4(const void* a, const void* b) {

  // Converte os apontadores para o tipo de dados apropriado
  const Output4* outputA = (const Output4*)a;
  const Output4* outputB = (const Output4*)b;

  // Compara as datas em ordem decrescente
  if (outputA->begin_date[0] != outputB->begin_date[0]) return outputB->begin_date[0] - outputA->begin_date[0];
  if (outputA->begin_date[1] != outputB->begin_date[1]) return outputB->begin_date[1] - outputA->begin_date[1];
  if (outputA->begin_date[2] != outputB->begin_date[2]) return outputB->begin_date[2] - outputA->begin_date[2];
  
  // Se as datas forem iguais, compara os IDs em ordem crescente
  return strcmp(outputA->id,outputB->id);
}


char* func_date_int_to_string_3(int year, int month, int day) {
  // Aloca memória para a string a ser devolvida
  char* output = malloc(11 * sizeof(char));

  // Inicia a string de output com o ano
  sprintf(output, "%d/", year);

  // Adiciona o mês à string de output
  if (month < 10) strcat(output, "0");
  char month_string[3];
  sprintf(month_string, "%d", month);
  strcat(output, month_string);
  strcat(output, "/");

  // Adiciona o dia à string de output
  if (day < 10) strcat(output, "0");
  char day_string[3];
  sprintf(day_string, "%d", day);
  strcat(output, day_string);

  return output;

}


char* func_date_int_to_string_6(int year, int month, int day, int hour, int minute, int second) {
  // Aloca memória para a string a ser devolvida
  char* output = malloc(20 * sizeof(char));

  // Inicia a string de output com o ano
  sprintf(output, "%d/", year);

  // Adiciona o mês à string de output
  if (month < 10) strcat(output, "0");
  char month_string[3];
  sprintf(month_string, "%d", month);
  strcat(output, month_string);
  strcat(output, "/");

  // Adiciona o dia à string de output
  if (day < 10) strcat(output, "0");
  char day_string[3];
  sprintf(day_string, "%d", day);
  strcat(output, day_string);
  strcat(output, " ");

  // Adiciona a hora à string de output
  if (hour < 10) strcat(output, "0");
  char hour_string[3];
  sprintf(hour_string, "%d", hour);
  strcat(output, hour_string);
  strcat(output, ":");

  // Adiciona o minuto à string de output
  if (minute < 10) strcat(output, "0");
  char minute_string[3];
  sprintf(minute_string, "%d", minute);
  strcat(output, minute_string);
  strcat(output, ":");

  // Adiciona o segundo à string de output
  if (second < 10) strcat(output, "0");
  char second_string[3];
  sprintf(second_string, "%d", second);
  strcat(output, second_string);

  return output;
}


void func_search_reservation(char* id_user, GHashTable* reservations_hash_table, Output2* array, int* n) {
  GHashTableIter iteration;
  gpointer key, data;

  // inicia a iteração pela hashTable
  g_hash_table_iter_init(&iteration,reservations_hash_table);

  // itera sobre as reservas na hashTable
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
      
    Reservation* reservation = (Reservation*)data;

    // verifica se a reserva pertence ao utilizador específico
    if (strcmp(func_get_reservation_user_id(reservation),id_user) == 0) {

      int* begin_date = func_get_reservation_begin_date(reservation);
      // preenche os dados da reserva no array de output
      array[*n].id = func_get_reservation_id(reservation);
      array[*n].date[0] = begin_date[0];
      array[*n].date[1] = begin_date[1];
      array[*n].date[2] = begin_date[2];
      array[*n].date[3] = 0;
      array[*n].date[4] = 0;
      array[*n].date[5] = 0;
      array[*n].type = "reservation";
      
      (*n)++;
    }
  }
}

void func_search_flight(char* id_user, GHashTable* passengers_hash_table, GHashTable* flights_hash_table, Output2* array, int* n) {
  GHashTableIter iteration;
  gpointer key, data;

  // inicia a iteração pela hashTable
  g_hash_table_iter_init(&iteration,passengers_hash_table);

  // itera sobre os passageiros na hashTable
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
    Passenger* passenger = (Passenger*)data;
    
    // verifica se o utilizador está num voo específico
    if (strcmp(func_get_passenger_user_id(passenger),id_user) == 0) {
      char* flight_id = func_get_passenger_flight_id(passenger);
      Flight* flight = g_hash_table_lookup(flights_hash_table, flight_id);

      int* schedule_departure_date = func_get_flight_schedule_departure_date(flight);
      // preenche os dados do voo no array de output
      array[*n].id = flight_id;
      array[*n].date[0] = schedule_departure_date[0];
      array[*n].date[1] = schedule_departure_date[1];
      array[*n].date[2] = schedule_departure_date[2];
      array[*n].date[3] = schedule_departure_date[3];
      array[*n].date[4] = schedule_departure_date[4];
      array[*n].date[5] = schedule_departure_date[5];
      array[*n].type = "flight";

      (*n)++;
    }
  }
}


void func_insert_passengers_in_order (Out6* ordered_info, char* name, int number_passengers, int index) {
  int i,j;

  // encontrar a posição correta para inserir o aerporto
  for (i = 0; i < index; i++) {
    if (ordered_info[i].number_passengers < number_passengers || (number_passengers == ordered_info[i].number_passengers && strcoll(name,ordered_info[i].name) < 0)) {
      break;
    }
  }

  // deslocar elementos para a direita para abrir espaço para o aerporto
  for (j = index; j > i; j--) {
    ordered_info[j] = ordered_info[j-1];
  }

  // inserir a informação na posição correta
  ordered_info[i].name = name; // neste caso ordered_info[i].name é apenas um apontador para name, parâmetro que é garantido já ser uma duplicação de uma outra string na função que chama a func_insert_passenger_in_order
  ordered_info[i].number_passengers = number_passengers;
}


char* func_answer_query_1 (char* input_prefix, char* id, GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table) {
  char* output;
  
  if (strncmp(id,"Book",4) == 0) { // se o id apresenta o prefixo "Book", então o mesmo diz respeito ao id de uma reservation
    Reservation* reservation = g_hash_table_lookup (reservations_hash_table,id);
    if (reservation == NULL) return NULL; // verifica se a reserva existe
    
    int* begin_date_int = func_get_reservation_begin_date(reservation);
    int* end_date_int = func_get_reservation_end_date(reservation);
    // converte as datas de início e fim para strings no formato "YYYY/MM/DD"
    char* begin_date = func_date_int_to_string_3(begin_date_int[0],begin_date_int[1],begin_date_int[2]);
    char* end_date = func_date_int_to_string_3(end_date_int[0],end_date_int[1],end_date_int[2]);

    // calcula o número de noites da reserva e o preço total
    int price_per_night = func_get_reservation_price_per_night(reservation);
    int number_nights = end_date_int[2] - begin_date_int[2];
    double total_price = (price_per_night*number_nights)+(((double)(price_per_night*number_nights)/100)*func_get_reservation_city_tax(reservation));
    
    output = func_output_1_reservations(input_prefix, func_get_reservation_hotel_id(reservation), func_get_reservation_hotel_name(reservation), func_get_reservation_hotel_stars(reservation), begin_date, end_date, func_get_reservation_includes_breakfast(reservation), number_nights, total_price); 

    free(begin_date);
    free(end_date);
  }
  else if (id[0] >= '0' && id[0] <= '9') { // se o id começa por um algarismo, então o mesmo diz respeito ao id de um flight
    Flight* flight = g_hash_table_lookup (flights_hash_table,id);
    if (flight == NULL) return NULL; // verifica se o voo existe
    
    // converte as datas de partida e chegada para strings no formato "YYYY/MM/DD hh:mm:ss"
    int* schedule_departure_date_int = func_get_flight_schedule_departure_date(flight);
    int* schedule_arrival_date_int = func_get_flight_schedule_arrival_date(flight);
    char* schedule_departure_date = func_date_int_to_string_6(schedule_departure_date_int[0],schedule_departure_date_int[1],schedule_departure_date_int[2],schedule_departure_date_int[3],schedule_departure_date_int[4],schedule_departure_date_int[5]);
    char* schedule_arrival_date = func_date_int_to_string_6(schedule_arrival_date_int[0],schedule_arrival_date_int[1],schedule_arrival_date_int[2],schedule_arrival_date_int[3],schedule_arrival_date_int[4],schedule_arrival_date_int[5]);
    
    output = func_output_1_flights(input_prefix, func_get_flight_airline(flight), func_get_flight_plane_model(flight), func_get_flight_origin(flight), func_get_flight_destination(flight), schedule_departure_date, schedule_arrival_date, func_get_flight_number_passengers(flight), func_get_flight_time_delay(flight));

    free(schedule_departure_date);
    free(schedule_arrival_date);
  }
  else { // se o id não apresenta o prefixo "Book" e não começa por um algarismo, então o mesmo diz respeito ao id de um user
    User* user = g_hash_table_lookup (users_hash_table,id); 
    if (user == NULL || strcasecmp(func_get_user_account_status(user),"active") != 0) return NULL; // verifica se o user existe, e, se sim, se tem a sua conta ativa
        
    output = func_output_1_users(input_prefix, func_get_user_name(user),func_get_user_sex(user),func_get_user_age(user),func_get_user_country_code(user),func_get_user_passport(user),func_get_user_number_flights(user),func_get_user_number_reservations(user), func_get_user_total_spent(user));
  }
  return output;
}


char* func_answer_query_2(char* input_prefix, char* id_user, char* id_arg, GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table, GHashTable* passengers_hash_table) {
  User* user = g_hash_table_lookup (users_hash_table,id_user);

  // verifica se o utilizador existe e está ativo
  if (user == NULL || strcasecmp(func_get_user_account_status(user),"inactive") == 0) return NULL;

  int n = 0;
  int key = 0;
  Output2 array[100];

  // realiza a procura de informações com base no argumento fornecido
  if (strcmp(id_arg,"flights") == 0) {
    func_search_flight(id_user, passengers_hash_table, flights_hash_table , array, &n);
  }
  else if (strcmp(id_arg,"reservations") == 0) {
    func_search_reservation(id_user, reservations_hash_table, array, &n);
  }
  else { // se o argumento for diferente de "flights" ou "reservations", procura ambas as informações
    func_search_flight(id_user, passengers_hash_table, flights_hash_table , array, &n);
    func_search_reservation(id_user, reservations_hash_table, array, &n);
    key = 1;
  }

  int size_array = n;
  qsort(array, size_array, sizeof(Output2), func_sort);
  char* output2 = malloc(70*(size_array + 1)*sizeof(char));
  output2[0] = '\0';

  for (int i = 0; i < size_array; i++) {
    char* general_date = func_date_int_to_string_3(array[i].date[0],array[i].date[1],array[i].date[2]);
    func_output_2(input_prefix, output2, i, key, size_array, array[i].id, general_date, array[i].type);
    free(general_date);
  }
  return output2;
}


char* func_answer_query_3(char* input_prefix, char* hotel_id, GHashTable* reservations_hash_table) {
  GHashTableIter iteration;
  gpointer key, data;
  int n = 0;
  double rating = 0.0;

  // inicia a iteração pela hashTable
  g_hash_table_iter_init(&iteration,reservations_hash_table);

  // itera sobre as reservas na hashTable
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
    Reservation* reservation = (Reservation*)data;

    // verifica se a reserva pertence ao hotel específico
    if (strcmp(func_get_reservation_hotel_id(reservation),hotel_id) == 0) {
      rating += (double)func_get_reservation_rating(reservation);
      n++;
    }
  }

  // calcula a média das classificações, se houver pelo menos uma reserva
  if (n > 0) {
    rating = rating / n;
  }
  
  // aloca memória para a string de output
  char* output3 = func_output_3 (input_prefix, rating);

  return output3;
}


char* func_answer_query_4(char* input_prefix, char* hotel_id, GHashTable* reservations_hash_table) {
  GHashTableIter iteration;
  gpointer key, data;
  int n = 0;
  Output4 array[70000];

  // inicia a iteração pela hashTable
  g_hash_table_iter_init(&iteration,reservations_hash_table);

  // itera sobre as reservas na hashTable
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
    Reservation* reservation = (Reservation*)data;

    // verifica se a reserva pertence ao hotel específico
    if (strcmp(hotel_id, func_get_reservation_hotel_id(reservation)) == 0) {

      int* reservation_begin_date = func_get_reservation_begin_date(reservation);
      int* reservation_end_date = func_get_reservation_end_date(reservation);
      char* reservation_id = func_get_reservation_id(reservation);
      char* reservation_user_id = func_get_reservation_user_id(reservation);
      int reservation_rating = func_get_reservation_rating(reservation);
      int reservation_price_per_night = func_get_reservation_price_per_night(reservation);
      int reservation_city_tax = func_get_reservation_city_tax(reservation);

      // insere a reserva no array que será ordeado posteriormente
      array[n].id = strdup(reservation_id);
      memcpy(array[n].begin_date, reservation_begin_date, sizeof(array[(n)].begin_date));
      memcpy(array[n].end_date, reservation_end_date, sizeof(array[(n)].end_date));
      array[n].user_id = strdup(reservation_user_id);
      array[n].rating = reservation_rating;
      // calcular e armazenar o preço total 
      int price_per_night = reservation_price_per_night;
      int nDias = array[n].end_date[2] - array[n].begin_date[2];
      array[n].total_price = nDias*price_per_night + (((double)(price_per_night*nDias)/100)*reservation_city_tax); // this var will store the total price instead of the price per night
      n++;
    }
  }
  qsort(array, n, sizeof(Output4), func_sort_query_4);

  // aloca memória para a string de output
  char* output4 = malloc(150*(n + 1)*sizeof(char)); // soma-se 1 para não haver o caso onde se solicita a alocação de 0 bytes de memória
  output4[0] = '\0';

  for (int i = 0; i < n; i++) {
    char* begin_date = func_date_int_to_string_3(array[i].begin_date[0],array[i].begin_date[1],array[i].begin_date[2]);
    char* end_date = func_date_int_to_string_3(array[i].end_date[0],array[i].end_date[1],array[i].end_date[2]);

    func_output_4(input_prefix, output4, i, n, array[i].id, begin_date, end_date, array[i].user_id, array[i].rating, array[i].total_price);
    
    free(array[i].id);
    free(array[i].user_id);
    free(begin_date);
    free(end_date);
  }
  return output4;
}


char* func_answer_query_5 (char* input_prefix, char* origin, int begin_date[6], int end_date[6], GHashTable* flights_hash_table) {
  FlightInfo list_of_flights[3000];

  list_of_flights[0].schedule_departure_date[0] = -1;
  list_of_flights[0].schedule_departure_date[1] = -1;
  list_of_flights[0].schedule_departure_date[2] = -1;
  list_of_flights[0].schedule_departure_date[3] = -1;
  list_of_flights[0].schedule_departure_date[4] = -1;
  list_of_flights[0].schedule_departure_date[5] = -1;
  list_of_flights[0].flight_id = "\0";

  GHashTableIter iteration;
	gpointer key, data; // ::(void*)

  // inicia a iteração pela hashTable
  g_hash_table_iter_init(&iteration, flights_hash_table);

  int counter = 0;

  // itera sobre os voos na hashTable
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
    Flight* current_flight = data;

    int* schedule_departure_date = func_get_flight_schedule_departure_date(current_flight);
    // verifica se a origem do voo é igual à origem fornecida e se as datas de partida e chegada do voo estão enquadradas nas datas fornecidas
    if (strcmp(origin,func_get_flight_origin(current_flight)) == 0 && func_compare_dates_6(schedule_departure_date,begin_date) >= 0 && func_compare_dates_6(schedule_departure_date,end_date) <= 0) {
      // insere o voo na lista ordenada

      char* flight_id = func_get_flight_id(current_flight);
      char* flight_destination = func_get_flight_destination(current_flight);
      char* flight_airline = func_get_flight_airline(current_flight);
      char* flight_plane_model = func_get_flight_plane_model(current_flight);

      func_insert_date_in_order(schedule_departure_date, flight_id, flight_destination, flight_airline, flight_plane_model, list_of_flights, &counter);
    }
  }


  char* output5 = malloc(155*(counter + 1)*sizeof(char)); // soma-se 1 para não haver o caso onde se solicita a alocação de 0 bytes de memória
  output5[0] = '\0';

  for (int i = 0; i < counter; i++) {
    char* schedule_departure_date_string = func_date_int_to_string_6(list_of_flights[i].schedule_departure_date[0],list_of_flights[i].schedule_departure_date[1],list_of_flights[i].schedule_departure_date[2],list_of_flights[i].schedule_departure_date[3],list_of_flights[i].schedule_departure_date[4],list_of_flights[i].schedule_departure_date[5]);

    func_output_5 (input_prefix, output5, i, counter, list_of_flights[i].flight_id, schedule_departure_date_string, list_of_flights[i].destination, list_of_flights[i].airline, list_of_flights[i].plane_model);
    
    free(list_of_flights[i].flight_id);
    free(list_of_flights[i].destination);
    free(list_of_flights[i].airline);
    free(list_of_flights[i].plane_model);
    free(schedule_departure_date_string);
  }
  return output5;
}


char* func_answer_query_6 (char* input_prefix, int year, int n, GHashTable* flights_hash_table) {
  Out6 info[100];
  int index = 0;

  info[0].name = "\0";
  info[0].number_passengers = 0;

  GHashTableIter iteration;
  gpointer key, data;

  g_hash_table_iter_init(&iteration, flights_hash_table);

  //itera pela hash de flights e seleciona os n flights com mais passageiros
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
    Flight* current_flight = data;

    int number_passengers = func_get_flight_number_passengers(current_flight);
    int* schedule_departure_date = func_get_flight_schedule_departure_date(current_flight);
    char* origin = func_get_flight_origin(current_flight);

    if (schedule_departure_date[0] == year) { // verifica se o voo apresenta a data pedida
      // verificação da origem no array info
      int i;
      for (i = 0; i < index; i++) {
        if (strcasecmp(origin,info[i].name) == 0) {
          info[i].number_passengers += number_passengers;
          break;
        }
      }
      if (i == index) {
        info[i].name = strdup(func_get_flight_origin(current_flight));
        info[i].number_passengers = number_passengers;
        index++;
      }

      // verificação do destino no array info
      char* destination = func_get_flight_destination(current_flight);
      
      int j;
      for (j = 0; j < index; j++) {
        if (strcasecmp(destination,info[j].name) == 0) {
          info[j].number_passengers += number_passengers;
          break;
        }
      }
      if (j == index) {
        info[j].name = strdup(destination);
        info[j].number_passengers = number_passengers;
        index++;
      }
    }
  }

  Out6 ordered_info[index];
  for (int k = 0; k < index; k++) {
    func_insert_passengers_in_order(ordered_info, info[k].name, info[k].number_passengers, k);
  }
    
  int true_size = (n < index) ? n : index; // se n for inferior ao valor de index (número total de aeroportos) então dá-se print de exatamente n aeroportos, caso contrário, dá-se print de todos os aeroportos possíveis
  
  // aloca memória para a string de output
  char* output6 = malloc(45*(true_size + 1)*sizeof(char)); // soma-se 1 para não haver o caso onde se solicita a alocação de 0 bytes de memória
  output6[0] = '\0';

  for (int i = 0; i < true_size; i++) func_output_6 (input_prefix, output6, i, true_size, ordered_info[i].name, ordered_info[i].number_passengers);

  for (int k = 0; k < index; k++) free(info[k].name);
  
  return output6;
}


char* func_answer_query_7 (char* input_prefix, int N, GHashTable* flights_hash_table) {
  AirportInfo list_of_airports[50];
  int capacity = 0;

  list_of_airports[0].origin = "\0";
  list_of_airports[0].size = 0;
  
  GHashTableIter iteration;
	gpointer key, data; // ::(void*)

  // inicia a iteração pela hashTable
  g_hash_table_iter_init(&iteration, flights_hash_table);

  // itera sobre as reservas na hashTable
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
    Flight* current_flight = data;

    char* origin = func_get_flight_origin(current_flight);
    int time_delay = func_get_flight_time_delay(current_flight);
    
    int i;
    for (i = 0; i < capacity; i++) {
      if (strcasecmp(origin,list_of_airports[i].origin) == 0) {
        func_insert_time_delay_in_order(time_delay, list_of_airports[i].delays, &(list_of_airports[i].size));
        break;
      }
    }
    if (i == capacity) {
      list_of_airports[i].origin = strdup(origin);
      list_of_airports[i].size = 0;
      func_insert_time_delay_in_order(time_delay, list_of_airports[i].delays, &(list_of_airports[i].size));
      capacity++;
    }
  } 
  
  AirportInfo ordered_list_of_airports[capacity];
  for (int j = 0; j < capacity; j++) {
    int size = list_of_airports[j].size;
    list_of_airports[j].median = (size % 2 == 0) ? ((list_of_airports[j].delays[(size / 2) - 1] + list_of_airports[j].delays[(size / 2)]) / 2) : list_of_airports[j].delays[(size / 2)]; 
    
    func_insert_airport_in_order(ordered_list_of_airports, list_of_airports[j].origin, list_of_airports[j].median, j);
  }

  int true_size = (N < capacity) ? N : capacity; // se N for inferior ao valor de capacity (número total de aeroportos) então dá-se print de exatamente N aeroportos, caso contrário, dá-se print de todos os aeroportos possíveis
  
  // aloca memória para a string de output
  char* output7 = malloc(45*(true_size + 1)*sizeof(char)); // soma-se 1 para não haver o caso onde se solicita a alocação de 0 bytes de memória
  output7[0] = '\0';

  for (int i = 0; i < true_size; i++) func_output_7 (input_prefix, output7, i, true_size, ordered_list_of_airports[i].origin, ordered_list_of_airports[i].median);

  // a memória alocada para as origens na list_of_airports só pode ser libertada após todas as origens da ordered_list_of_airports terem sido usadas para os outputs, pois estas últimas apontavam para as primeiras
  for (int k = 0; k < capacity; k++) free(list_of_airports[k].origin);
  
  return output7;
}



char* func_answer_query_8 (char* input_prefix, char* hotel_id, int begin_date[3], int end_date[3], GHashTable* reservations_hash_table) {  
  GHashTableIter iteration;
	gpointer key, data; // ::(void*)
  int true_begin_date[3];
  int true_end_date[3];
  int revenue = 0;
  
  // inicia a iteração pela hashTable
  g_hash_table_iter_init(&iteration, reservations_hash_table);

  // itera sobre as reservas na hashTable
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
    Reservation* current_reservation = data;

    // verifica se a reserva pertence ao hotel específico
    if (strcmp(func_get_reservation_hotel_id(current_reservation),hotel_id) == 0) {
      int price_per_night = func_get_reservation_price_per_night(current_reservation);
      int* reservation_begin_date = func_get_reservation_begin_date(current_reservation);
      int* reservation_end_date = func_get_reservation_end_date(current_reservation);

      if (func_compare_dates(reservation_begin_date,begin_date) >= 0) {
        true_begin_date[0] = reservation_begin_date[0];
        true_begin_date[1] = reservation_begin_date[1];
        true_begin_date[2] = reservation_begin_date[2];
      }  
      else {
        true_begin_date[0] = begin_date[0];
        true_begin_date[1] = begin_date[1];
        true_begin_date[2] = begin_date[2];
      }      
      if (func_compare_dates(reservation_end_date,end_date) <= 0) {
        true_end_date[0] = reservation_end_date[0];
        true_end_date[1] = reservation_end_date[1];
        true_end_date[2] = reservation_end_date[2];
      }
      else {
        true_end_date[0] = end_date[0];
        true_end_date[1] = end_date[1];
        true_end_date[2] = end_date[2] + 1;
      }
      
      if (func_compare_dates(true_begin_date,true_end_date) < 0) revenue += ((true_end_date[2] - true_begin_date[2])) * price_per_night; // caso em que a data de início é de facto menor do que a data de fim
    }
  }
  char* output8 = func_output_8 (input_prefix, revenue);
  return output8;
}


char* func_answer_query_9 (char* input_prefix, char* prefix, GHashTable* users_hash_table) {
  NameInfo list_of_names[10000];

  list_of_names[0].user_id = "\0";
  list_of_names[0].user_name = "\0";

  GHashTableIter iteration;
	gpointer key, data; // ::(void*)

  int size_of_prefix = strlen(prefix);
  int counter = 0;

  // inicia a iteração pela hashTable
  g_hash_table_iter_init(&iteration, users_hash_table);

  // itera sobre os utilizadores na hashTable
  while (g_hash_table_iter_next(&iteration, &key, &data)) {
    User* current_user = data;

    char* user_name = func_get_user_name(current_user);

    // verifica se o nome do utilizador começa com o prefixo fornecido e se a conta está ativa
    if (strncmp(user_name, prefix, size_of_prefix) == 0 && strcasecmp(func_get_user_account_status(current_user),"active") == 0) {
      // insere o nome na lista ordenada
      func_insert_name_in_order (user_name, func_get_user_id(current_user), list_of_names, &counter);
    }  
  }

  // aloca memória para a string de output
  char* output9 = malloc((counter + 1)*80*sizeof(char)); // soma-se 1 para não haver o caso onde se solicita a alocação de 0 bytes de memória
  output9[0] = '\0';

  for (int i = 0; i < counter; i++) {
    func_output_9 (input_prefix, output9, i, counter, list_of_names[i].user_id, list_of_names[i].user_name);

    free(list_of_names[i].user_id);
    free(list_of_names[i].user_name);
  }
  return output9;
}    


char* func_answer_query_10 (char* input_prefix, char* token, int account_registrations_by_date[100][12][31], int number_reservations_by_date[100][12][31], int number_flights_by_date[100][12][31], int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100]) {
  int year,month;
  int counter = 1;
  char* output10;

  // caso em que é necessário percorrer todos os anos
  if (token == NULL) {
    output10 = malloc(15*115*sizeof(char));
    output10[0] = '\0';

    for(int i = 0; i < 100; i++) { // percorrem-se os anos
      int total_account_registrations = 0, total_flights = 0, total_passengers = 0, total_reservations = 0;
      for(int j = 0; j < 12; j++) { // percorrem-se os meses
        for(int k = 0; k < 31; k++) { // percorrem-se os dias
          total_account_registrations += account_registrations_by_date[i][j][k];
          total_flights += number_flights_by_date[i][j][k];
          total_passengers += number_passengers_by_date[i][j][k];
          total_reservations += number_reservations_by_date[i][j][k];
        }
      }
      if (total_account_registrations != 0 || total_flights != 0 || total_passengers != 0 || number_unique_passengers_by_year[i] != 0 || total_reservations != 0) {   
        func_output_10_year (input_prefix, output10, &counter, (i+2000), total_account_registrations, total_flights, total_passengers, number_unique_passengers_by_year[i], total_reservations);
      }
    }  
    if (strcmp(input_prefix,"10F") == 0) output10[strlen(output10) - 1] = '\0'; // último caso escrito do formato F deve conter apenas um '\n' e não dois
  }
  // caso em que é necessário percorrer todos os meses, num certo ano
  else if (strlen(token) == 4) {
    year = atoi(token);

    output10 = malloc(12*115*sizeof(char));
    output10[0] = '\0';

    for(int j = 0; j < 12; j++) { // percorrem-se os meses
      int total_account_registrations = 0, total_flights = 0, total_passengers = 0, total_reservations = 0;
      for(int k = 0; k < 31; k++) { // percorrem-se os dias
        total_account_registrations += account_registrations_by_date[year%100][j][k];
        total_flights += number_flights_by_date[year%100][j][k];
        total_passengers += number_passengers_by_date[year%100][j][k];
        total_reservations += number_reservations_by_date[year%100][j][k];
      }
      if (total_account_registrations != 0 || total_flights != 0 || total_passengers != 0 || number_unique_passengers_by_month[year%100][j] != 0 || total_reservations != 0) {
        func_output_10_month (input_prefix, output10, &counter, (j+1), total_account_registrations, total_flights, total_passengers, number_unique_passengers_by_month[year%100][j], total_reservations);
      }
    } 
    if (strcmp(input_prefix,"10F") == 0) output10[strlen(output10) - 1] = '\0'; // último caso escrito do formato F deve conter apenas um '\n' e não dois   
  } 
  // caso em que é necessário percorrer todos os dias de um dado mês, num certo ano
  else {
    year = atoi(strtok(token," "));
    month = atoi(strtok(NULL,"\0"));

    output10 = malloc(31*115*sizeof(char));
    output10[0] = '\0';


    for(int k = 0; k < 31; k++) { // percorrem-se os dias
      if (account_registrations_by_date[year%100][month-1][k] != 0 || number_flights_by_date[year%100][month-1][k] != 0 || number_passengers_by_date[year%100][month-1][k] != 0 || number_unique_passengers_by_day[year%100][month-1][k] != 0 || number_reservations_by_date[year%100][month-1][k] != 0) {
        func_output_10_day (input_prefix, output10, &counter, (k+1), account_registrations_by_date[year%100][month-1][k], number_flights_by_date[year%100][month-1][k], number_passengers_by_date[year%100][month-1][k], number_unique_passengers_by_day[year%100][month-1][k], number_reservations_by_date[year%100][month-1][k]);
      }
    }
    if (strcmp(input_prefix,"10F") == 0) output10[strlen(output10) - 1] = '\0'; // último caso escrito do formato F deve conter apenas um '\n' e não dois  
  }    
    
  return output10;
}
