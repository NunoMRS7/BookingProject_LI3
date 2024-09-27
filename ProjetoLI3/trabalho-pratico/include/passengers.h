#ifndef PASSENGERS_H
#define PASSENGERS_H

typedef struct passenger Passenger;


/**
 * Itera por todos os elementos da hashTable e, para cada um, liberta
 * a memória alocada.
 * 
 * @param passengers_hash_table: A hashTable que contém os passageiros.
 */
void func_free_passengers(GHashTable* passengers_hash_table);


/**
 * Cria uma nova estrutura de passageiro e inicializa-a com os dados do mesmo.
 *
 * @return Um apontador para o passageiro criado.
 */
Passenger* func_new_passenger(char* flight_id, char* user_id);


/**
 * Faz-se o parse da informação dos passageiros do ficheiro .csv e guarda-os na hashTable.
 *
 * A função lê o ficheiro 'passengers.csv' (linha a linha), cujo caminho é especificado 
 * pelo parâmetro 'path', cria uma nova estrutura de passageiro e guarada-a na hashTable.
 * Preenche também a matriz com o número de reservas organizados por data, assim como
 * preenche as duas matrizes e o array com o número de passageiros únicos.
 *
 * Faz uso da função 'func_new_passenger' para definir os parâmetros no novo passageiro.
 * 
 * @param path: O caminho para a diretoria que contém o ficheiro .csv com a informação
 * dos passageiros.
 * @param users_hash_table: A hashTable que contém os utilizadores.
 * @param flights_hash_table: A hashTable que contém os voos.
 * @param number_reservations_by_date: O array tridimensional que contém o número de reservas
 * organizadas por dia/mês/ano. 
 * @param number_unique_passengers_by_day: O array tridimensional que contém o número de passageiros
 * únicos organizados por dia/mês/ano. 
 * @param number_unique_passengers_by_month: O array que contém o número de passageiros únicos organizados
 * por mês/ano. 
 * @param number_unique_passengers_by_year: O array que contém o número de passageiros únicos organizados 
 * por ano. 
 * 
 * @return Uma hashTable que contém as estruturas de passageiro.
 */
GHashTable* func_parse_passengers(char* path, GHashTable* users_hash_table, GHashTable* flights_hash_table, int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100]);


/**
 * Obtém o <ID> do voo associado ao struct passageiro.
 *
 * @param passenger Apondator para o struct passageiro.
 * 
 * @return Apondator para a string que contém o <ID> do voo do passageiro.
 */
char* func_get_passenger_flight_id(Passenger* passenger);


/**
 * Obtém o <ID> do utilizador associado ao struct passageiro.
 *
 * @param passenger Apondator para o struct passageiro.
 * 
 * @return Apondator para a string que contém o <ID> do utilizador.
 */
char* func_get_passenger_user_id(Passenger* passenger);


#endif
