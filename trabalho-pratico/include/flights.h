#ifndef FLIGHTS_H
#define FLIGHTS_H

typedef struct flight Flight;


/**
 * Itera por todos os elementos da hashTable e, para cada um, liberta
 * a memória alocada.
 * 
 * @param flights_hash_table: A hashTable que contém os voos.
 */
void func_free_flights(GHashTable* flights_hash_table);


/**
 * Calcula a diferença entre duas datas.
 *
 * @param schedule_departure_date: Data de partida prevista.
 * @param real_departure_date: Data de partida real.
 * 
 * @return A diferença entre as datas em segundos.
 */
int func_calculate_time_difference (int schedule_departure_date[6], int real_departure_date[6]);


/**
 * Cria uma nova estrutura de voo e inicializa-a com os dados do mesmo.
 *
 * @return Um apontador para o voo criado.
 */
Flight* func_new_flight(char* id, char* airplane, char* plane_model, char* total_seats, char* origin, char* destination, char* schedule_departure_date, char* schedule_arrival_date, char* real_departure_date, char* real_arrival_date);


/**
 * Faz-se o parse da informação dos voos do ficheiro .csv e guarda-os na hashTable.
 *
 * A função lê o ficheiro 'flights.csv' (linha a linha), cujo caminho é especificado 
 * pelo parâmetro 'path', cria uma nova estrutura de voo e guarada-a na hashTable, 
 * usando o id de voo como chave. Preenche também a matriz com o número de voos
 * organizados por data.
 *
 * Faz uso da função 'func_new_flight' para definir os parâmetros no novo voo.
 * 
 * @param path: O caminho para a diretoria que contém o ficheiro .csv com a informação
 * dos voos.
 * @param number_reservations_by_date: O array tridimensional que contém o número de voos
 * organizados por dia/mês/ano. 
 *
 * @return Uma hashTable que contém as estruturas de voo com os seus ids a servirem de 
 * chave.
 */
GHashTable* func_parse_flights(char* path, int number_flights_by_date[100][12][31]);


/**
 * Define o número de passageiros do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo. 
 * @param number_passengers Número de passageiros a definir.
 */
void func_set_flight_number_passengers (Flight* flight, int number_passengers);


/**
 * Obtém o <ID> do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Apondator para a string que contém o <ID> do voo.
 */
char* func_get_flight_id(Flight* flight);


/**
 * Obtém a companhia do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Apondator para a string que contém a companhia do voo.
 */
char* func_get_flight_airline(Flight* flight);


/**
 * Obtém o modelo do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Apondator para a string que contém o modelo do voo.
 */
char* func_get_flight_plane_model (Flight* flight);


/**
 * Obtém o númeo de lugares do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Inteiro que contém o númeo de lugares do voo.
 */
int func_get_flight_total_seats (Flight* flight);


/**
 * Obtém o número de passageiros do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Inteiro que contém o número de passageiros do voo.
 */
int func_get_flight_number_passengers (Flight* flight);


/**
 * Obtém a origem do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Apondator para a string que contém a origem do voo.
 */
char* func_get_flight_origin (Flight* flight);


/**
 * Obtém o destino associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Apondator para a string que contém o destino.
 */
char* func_get_flight_destination (Flight* flight);


/**
 * Obtém a data esperada de partida do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Lista de interos que contêm a data esperada de partida do voo.
 */
int* func_get_flight_schedule_departure_date (Flight* flight);


/**
 * Obtém a data esperada de chegada do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Lista de inteiros que contêm a data esperada de chegada do voo.
 */
int* func_get_flight_schedule_arrival_date (Flight* flight);


/**
 * Obtém a data real de partida do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Lista de inteiros que contêm a data real de partida do voo.
 */
int* func_get_flight_real_departure_date (Flight* flight);


/**
 * Obtém a data real de chegada do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Lista de inteiros que contêm a data real de chegada do voo.
 */
int* func_get_flight_real_arrival_date (Flight* flight);


/**
 * Obtém o atraso do voo associado ao struct voo.
 *
 * @param flight Apondator para o struct voo.
 * 
 * @return Inteiro que contém o atraso do voo.
 */
int func_get_flight_time_delay (Flight* flight);


#endif
