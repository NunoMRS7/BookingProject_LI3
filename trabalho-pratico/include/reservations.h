#ifndef RESERVATIONS_H
#define RESERVATIONS_H

typedef struct reservation Reservation;


/**
 * Itera por todos os elementos da hashTable e, para cada um, liberta
 * a memória alocada.
 * 
 * @param reservations_hash_table: A hashTable que contém as reservas.
 */
void func_free_reservations(GHashTable* reservations_hash_table);


/**
 * Cria uma nova estrutura de reserva e inicializa-a com os dados da mesma.
 * 
 * @return Um apontador para a reserva criada.
 */
Reservation* func_new_reservation(char* id, char* user_id, char* hotel_id, char* hotel_name, char* hotel_stars, char* city_tax, char* begin_date, char* end_date, char* price_per_night, char* includes_breakfast, char* rating);


/**
 * Faz-se o parse da informação das reservas do ficheiro .csv e guarda-as na hashTable.
 *
 * A função lê o ficheiro 'reservations.csv' (linha a linha), cujo caminho é especificado 
 * pelo parâmetro 'path', cria uma nova estrutura de reserva e guarada-a na hashTable, 
 * usando o id de reserva como chave. Preenche também a matriz com o número de reservas
 * organizados por data.
 * 
 * Faz uso da função 'func_new_reservation' para definir os parâmetros na nova reserva.
 *
 * @param path: O caminho para a diretoria que contém o ficheiro .csv com a informação
 * das reservas.
 * @param users_hash_table: A hashTable que contém os utilizadores.
 * @param number_reservations_by_date: O array tridimensional que contém o número de reservas
 * organizadas por dia/mês/ano. 
 *
 * @return Uma hashTable que contém as estruturas de reserva com os seus ids a servirem de
 * chave.
 */
GHashTable* func_parse_reservations(char* path, GHashTable* users_hash_table, int number_reservations_by_date[100][12][31]);


/**
 * Obtém o <ID> da reserva associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Apondator para a string que contém o <ID> da reserva.
 */
char* func_get_reservation_id(Reservation* reservation);


/**
 * Obtém o <ID> da reserva associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Apondator para a string que contém o <ID> da reserva.
 */
char* func_get_reservation_user_id(Reservation* reservation);


/**
 * Obtém o <ID> do hotel associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Apondator para a string que contém o <ID> do hotel da reserva.
 */
char* func_get_reservation_hotel_id(Reservation* reservation);


/**
 * Obtém o nome do hotel associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Apondator para a string que contém o nome do hotel da reserva.
 */
char* func_get_reservation_hotel_name(Reservation* reservation);


/**
 * Obtém o número de estrelas associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Inteiro que contém o número de estrelas do hotel.
 */
int func_get_reservation_hotel_stars(Reservation* reservation);


/**
 * Obtém o imposto da cidade associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Inteiro que contém o imposto da cidade da reserva.
 */
int func_get_reservation_city_tax(Reservation* reservation);


/**
 * Obtém a data de início da reserva associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Lista de inteiros que contêm a data de início da reserva.
 */
int* func_get_reservation_begin_date(Reservation* reservation);


/**
 * Obtém a data de fim da reserva associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Lista de inteiros que contêm a data de fim da reserva.
 */
int* func_get_reservation_end_date(Reservation* reservation);


/**
 * Obtém o preço por noite da reserva associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Inteiro que contém o preço por noite da reserva.
 */
int func_get_reservation_price_per_night(Reservation* reservation);


/**
 * Obtém a informação da inclusão de pequeno-almoço associado ao struct reserva.
 *§
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Apondator para a string que contém a informação da inclusão de pequeno-almoço da reserva.
 */
char* func_get_reservation_includes_breakfast(Reservation* reservation);


/**
 * Obtém a classificação da reserva associado ao struct reserva.
 *
 * @param reservation Apondator para o struct reserva.
 * 
 * @return Inteiro que contém a classificação da reserva.
 */
int func_get_reservation_rating(Reservation* reservation);


#endif
