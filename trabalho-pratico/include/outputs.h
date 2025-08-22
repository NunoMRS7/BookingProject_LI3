#ifndef OUTPUTS_H
#define OUTPUTS_H


/** 
 * Cria e devolve a string de output referente às reservas na query 1,
 * atentando à forma de output pedida ("1" ou "1F").
*/
char* func_output_1_reservations(char* input_prefix, char* hotel_id, char* hotel_name, int hotel_stars, char* begin_date, char* end_date, char* includes_breakfast, int number_nights, double total_price);


/** 
 * Cria e devolve a string de output referente aos voos na query 1,
 * atentando à forma de output pedida ("1" ou "1F").
*/
char* func_output_1_flights(char* input_prefix, char* airline, char* plane_model, char* origin, char* destination, char* schedule_departure_date, char* schedule_arrival_date, int number_passengers, int time_delay);


/** 
 * Cria e devolve a string de output referente aos utilizadores na query 1,
 * atentando à forma de output pedida ("1" ou "1F").
*/
char* func_output_1_users(char*  input_prefix, char* name, char* sex, int age, char*  country_code, char* passport, int number_flights, int number_reservations, double total_spent);


/** 
 * Preenche e formata a string de output referente à query 2,
 * atentando à forma de output pedida ("2" ou "2F").
*/
void func_output_2 (char* input_prefix, char* output2, int i, int key, int size_array, char* id, char* general_date, char* type);


/** 
 * Cria e devolve a string de output referente à query 3,
 * atentando à forma de output pedida ("3" ou "3F").
*/
char* func_output_3 (char* input_prefix, double rating);


/** 
 * Preenche e formata a string de output referente à query 4,
 * atentando à forma de output pedida ("4" ou "4F").
*/
void func_output_4 (char* input_prefix, char* output4, int i, int size_array, char* id, char* begin_date, char* end_date, char* user_id, int rating, double total_price);


/** 
 * Preenche e formata a string de output referente à query 5,
 * atentando à forma de output pedida ("5" ou "5F").
*/
void func_output_5 (char* input_prefix, char* output5, int i, int size_array, char* flight_id, char* schedule_departure_date_string, char* destination, char* airline, char* plane_model);


/** 
 * Preenche e formata a string de output referente à query 6,
 * atentando à forma de output pedida ("6" ou "6F").
*/
void func_output_6 (char* input_prefix, char* output6, int i, int size_array, char* name, int number_passengers);


/** 
 * Preenche e formata a string de output referente à query 7,
 * atentando à forma de output pedida ("7" ou "7F").
*/
void func_output_7 (char* input_prefix, char* output7, int i, int size_array, char* origin, int median);


/** 
 * Cria e devolve a string de output referente à query 8,
 * atentando à forma de output pedida ("8" ou "8F").
*/
char* func_output_8 (char* input_prefix, int revenue);


/** 
 * Preenche e formata a string de output referente à query 9,
 * atentando à forma de output pedida ("9" ou "9F").
*/
void func_output_9 (char* input_prefix, char* output9, int i, int size_array, char* user_id, char* user_name);


/** 
 * Preenche e formata a string de output referente aos anos na
 * query 10, atentando à forma de output pedida ("10" ou "10F").
*/
void func_output_10_year (char* input_prefix, char* output10, int* counter, int year, int total_account_registrations, int total_flights, int total_passengers, int number_unique_passengers_by_year, int total_reservations);


/** 
 * Preenche e formata a string de output referente aos meses na
 * query 10, atentando à forma de output pedida ("10" ou "10F").
*/
void func_output_10_month (char* input_prefix, char* output10, int* counter, int month, int total_account_registrations, int total_flights, int total_passengers, int number_unique_passengers_by_month, int total_reservations);


/** 
 * Preenche e formata a string de output referente aos dias na
 * query 10, atentando à forma de output pedida ("10" ou "10F").
*/
void func_output_10_day (char* input_prefix, char* output10, int* counter, int day, int account_registrations_by_date, int number_flights_by_date, int number_passengers_by_date, int number_unique_passengers_by_day, int number_reservations_by_date);


#endif
