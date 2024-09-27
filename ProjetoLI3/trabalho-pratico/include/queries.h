#ifndef QUERIES_H
#define QUERIES_H

typedef struct airportinfo AirportInfo;

typedef struct nameinfo NameInfo;

typedef struct flightinfo FlightInfo;

typedef struct output2 Output2;

typedef struct output4 Output4;

typedef struct out6 Out6;


/**
 * Compara duas datas representadas como arrays de três inteiros (dia, mês e ano).
 *
 * @param date1 Array que representa a primeira data a ser comparada.
 * @param date2 Array que representa a segunda data a ser comparada.
 * 
 * @return Um valor inteiro:
 *         -1 se date1 for anterior a date2,
 *          0 se as datas forem iguais,
 *          1 se date1 for posterior a date2.
 */
int func_compare_dates (int date1[3], int date2[3]);


/**
 * Compara duas datas representadas como arrays de seis inteiros (dia, mês e ano).
 *
 * @param date1 Array que representa a primeira data a ser comparada.
 * @param date2 Array que representa a segunda data a ser comparada.
 * 
 * @return Um valor inteiro:
 *         -1 se date1 for anterior a date2,
 *          0 se as datas forem iguais,
 *          1 se date1 for posterior a date2.
 */
int func_compare_dates_6 (int date1[6], int date2[6]);


/**
 * Insere informações de um aeroporto ordenadamente numa lista.
 *
 * Esta função insere informações sobre um aeroporto (origem e mediana) numa lista
 * já ordenada de aeroportos, mantendo a ordem crescente com base na mediana e na origem.
 *
 * @param ordered_list_of_airports Lista ordenada de informações de aeroportos.
 * @param origin Origem do aeroporto a ser inserido.
 * @param median Valor da mediana associada ao aeroporto a ser inserido.
 * @param size Tamanho atual da lista ordenada de aeroportos.
 */
void func_insert_airport_in_order(AirportInfo* ordered_list_of_airports, char* origin, int median, int size);


/**
 * Insere um atraso de um voo em ordenadamente numa lista de atrasos.
 *
 * Esta função insere um atraso de um voo numa lista já ordenada de atrasos,
 * mantendo a ordem crescente.
 *
 * @param flight_delay Atraso do voo a ser inserido.
 * @param delays Lista de atrasos ordenada.
 * @param size Apontador para o tamanho atual da lista de atrasos.
 */
void func_insert_time_delay_in_order (int flight_delay, int* delays, int* size);


/**
 * Insere um novo nome e o correspondente id de utilizador numa lista ordenada de nomes.
 *
 * Esta função insere o user_name e o user_id fornecidos no array list_of_names
 * de uma maneira que mantém a ordem alfabética. O array list_of_names é
 * assumido como previamente ordenado, e a função ajusta a ordem conforme necessário.
 * Qunado os nomes são iguais, faz-se a ordenação pelo id.
 *
 * @param user_name O nome a ser inserido.
 * @param user_id O id de utilizador correspondente a ser inserido.
 * @param list_of_names O array de estruturas NameInfo representando a lista de nomes.
 * @param size Apontador para o tamanho do array list_of_names.
 */
void func_insert_name_in_order(char* user_name, char* user_id, NameInfo* list_of_names, int* size);


/**
 * Insere informações de um voo por ordem crescente com base na data de partida prevista.
 *
 * Esta função insere informações sobre um voo numa lista já ordenada de voos,
 * mantendo a ordem crescente com base na data de partida prevista e <ID> de voo
 *
 * @param schedule_departure_date Data de partida prevista do voo a ser inserido.
 * @param flight_id <ID> do voo a ser inserido.
 * @param flight_destination Destino do voo a ser inserido.
 * @param flight_airline Companhia aérea do voo a ser inserido.
 * @param flight_plane_model Modelo do avião do voo a ser inserido.
 * @param list_of_flights Lista ordenada de informações de voos.
 * @param size Apontador para o tamanho atual da lista de voos.
 */
void func_insert_date_in_order (int* schedule_departure_date, char* flight_id, char* flight_destination, char* flight_airline, char* flight_plane_model, FlightInfo* list_of_flights, int* size);


/**
 * Compara dois elementos do tipo Output2 para serem utilizados na ordenação.
 *
 * A ordenação é realizada primeiramente com base nas datas por ordem decrescente
 * e, em caso de datas iguais, utiliza-se os IDs por ordem crescente.
 *
 * @param a Apontador para o primeiro elemento a ser comparado.
 * @param b Apontador para o segundo elemento a ser comparado.
 * 
 * @return Um valor negativo se a > b, um valor positivo se a < b, e 0 se a == b.
 */
int func_sort(const void* a, const void* b);


/**
 * Compara dois elementos do tipo Output4 para serem utilizados na ordenação.
 *
 * A ordenação é realizada primeiramente com base nas datas por ordem decrescente
 * e, em caso de datas iguais, utiliza-se os IDs por ordem crescente.
 *
 * @param a Apontador para o primeiro elemento a ser comparado.
 * @param b Apontador para o segundo elemento a ser comparado.
 * 
 * @return Um valor negativo se a > b, um valor positivo se a < b, e 0 se a == b.
 */
int func_sort_query_4(const void* a, const void* b);


/**
 * Converte uma data representada por três inteiros numa string no formato "YYYY/MM/DD".
 *
 * Esta função recebe um ano, mês e dia como inteiros e converte esses valores numa
 * string no formato de data "YYYY/MM/DD" sendo, caso necessário, adicionados zeros para a 
 * sua formatação. A função aloca dinamicamente memória para a string de output e os buffers 
 * temporários.
 *
 * @param year O ano da data.
 * @param month O mês da data.
 * @param day O dia da data.
 * 
 * @return Um apontador para a string formatada.
 */
char* func_date_int_to_string_3(int year, int month, int day);


/**
 * Converte uma data representada por seis inteiros numa string no formato "YYYY/MM/DD hh:mm:ss".
 *
 * Esta função recebe um ano, mês, dia, hora, minuto e segundo como inteiros e converte esses valores 
 * numa string no formato de data "YYYY/MM/DD hh:mm:ss" sendo, caso necessário, adicionados zeros 
 * para a sua formatação. A função aloca dinamicamente memória para a string de output e os buffers 
 * temporários.
 *
 * @param year O ano da data.
 * @param month O mês da data.
 * @param day O dia da data.
 * @param hour A hora da data.
 * @param minute O minuto da data.
 * @param second O segundo da data.
 * 
 * @return Um apontador para a string formatada.
 */
char* func_date_int_to_string_6(int year, int month, int day, int hour, int minute, int second);


/**
 * Procura por reservas associadas a um id de utilizador numa hashTable.
 *
 * Esta função percorre uma hashTable que contém reservas e procura por todas
 * as reservas associadas a um id de utilizador específico. Os resultados são armazenados
 * num array de estruturas Output2. O array é realocado dinamicamente conforme necessário.
 *
 * @param id_user O id de utilizador para o qual as reservas serão procuradas.
 * @param reservations_hash_table A hashTable que contém as reservas.
 * @param array Um array de estruturas Output2 para armazenar os resultados da pesquisa.
 * @param n Apontador para o número atual de elementos no array.
 * 
 * @return Um apontador para o array de estruturas Output2 que contém as reservas encontradas.
 */
void func_search_reservation(char* id_user, GHashTable* reservations_hash_table, Output2* array, int* n);


/**
 * Procura por voos associados a um id de utilizador nas hashTable de passageiros e voos.
 *
 * Esta função percorre a hashTable de passageiros e procura por todos os voos
 * associados a um id de utilizador específico, recolhendo a informação dos mesmos. Os resultados
 * são armazenados num array de estruturas Output2. O array é realocado dinamicamente conforme necessário.
 *
 * @param id_user O id de utilizador para o qual os voos serão procurados.
 * @param passengers_hash_table A hashTable que contém informações dos passageiros.
 * @param flights_hash_table A hashTable que contém informações dos voos.
 * @param array Um array de estruturas Output2 para armazenar os resultados da pesquisa.
 * @param n Apontador para o número atual de elementos no array.
 * @return Um apontador para o array de estruturas Output2 que contém os voos encontrados.
 */
void func_search_flight(char* id_user, GHashTable* passengers_hash_table, GHashTable* flights_hash_table, Output2* array, int* n);


/**
 * Insere informações de um passageiro por ordem crescente com base no número de passageiros.
 *
 * Esta função insere informações sobre um passageiro numa lista já ordenada de informações,
 * mantendo a ordem crescente com base no número de passageiros e no nome do passageiro.
 *
 * @param ordered_info Lista ordenada de informações de passageiros.
 * @param name Nome do passageiro a ser inserido.
 * @param number_passengers Número de passageiros total do voo.
 * @param index Tamanho atual da lista ordenada de informações.
 */
void func_insert_passengers_in_order (Out6* ordered_info, char* name, int number_passengers, int index);


/**
 * Responde à query 1 criando uma string formatada com informações de reserva, voo ou utilizador.
 *
 * Esta função recebe um prefixo de entrada, um id e várias hashTables que contêm informações
 * sobre voos, utilizadores, reservas e passageiros. Com base no id fornecido, a função gera uma string
 * formatada com informações relevantes sobre uma reserva, voo ou utlizador, de acordo com o prefixo.
 *
 * @param input_prefix O prefixo de entrada que determina o formato da resposta ("1" ou "1F").
 * @param id O id para o qual as informações serão procuradas (reserva, voo ou utlizador).
 * @param flights_hash_table A hashTable que contém informações sobre voos.
 * @param users_hash_table A hashTable que contém informações sobre utlizadores.
 * @param reservations_hash_table A hashTable que contém informações sobre reservas.
 * @param passengers_hash_table A hashTable que contém informações sobre passageiros.
 * 
 * @return Um apontador para uma string formatada com informações relevantes. Se o id não corresponder 
 * a uma reserva, voo ou utlizador válido, retorna NULL.
 */
char* func_answer_query_1 (char* input_prefix, char* id, GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table);


/**
 * Responde à query 2 criando uma string formatada com informações de voos, reservas ou ambos.
 *
 * Esta função recebe um prefixo de entrada, um id de utilizador, um argumento responsável pelo tipo de 
 * output pedido e várias hashTables que contêm informações sobre voos, utilizadores, reservas e passageiros. 
 * Com base no argumento fornecido, a função busca informações de voos, reservas ou ambos associados ao id de
 * utilizador. A string de output é ordenada por datas de forma decrescente e é formatada conforme o prefixo
 * de entrada.
 *
 * @param input_prefix O prefixo de entrada que determina o formato da resposta ("2" ou "2F").
 * @param id_user O id de utilizador para o qual as informações serão procuradas.
 * @param id_arg O argumento adicional que indica se a busca é por "flights", "reservations" ou ambos.
 * @param flights_hash_table A hashTable que contém informações sobre voos.
 * @param users_hash_table A hashTable que contém informações sobre utilizadores.
 * @param reservations_hash_table A hashTable que contém informações sobre reservas.
 * @param passengers_hash_table A hashTable que contém informações sobre passageiros.
 * 
 * @return Um apontador para uma string formatada com informações relevantes. Se o id de utilizador não corresponder
 * a um utilizador válido, retorna NULL.
 */
char* func_answer_query_2(char* input_prefix, char* id_user, char* id_arg, GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table, GHashTable* passengers_hash_table);


/**
 * Responde à query 3 criando uma string formatada com a média de classificações para um hotel específico.
 *
 * Esta função recebe um prefixo de entrada, um id de hotel e uma hashTable que contém informações
 * sobre reservas. Com base no id do hotel, a função calcula a média das classificações das reservas
 * associadas a esse hotel. A string de output é formatada conforme o prefixo de entrada.
 *
 * @param input_prefix O prefixo de entrada que determina o formato da resposta ("3" ou "3F").
 * @param hotel_id O id do hotel para o qual a média de classificações será calculada.
 * @param reservations_hash_table A hashTable que contém informações sobre reservas.
 * 
 * @return Um apontador para uma string formatada com a média de classificações para o hotel especificado.
 */
char* func_answer_query_3(char* input_prefix, char* id, GHashTable* reservations_hash_table);


/**
 * Responde à query 4 criando uma string formatada com informações ordenadas sobre reservas para um hotel específico.
 *
 * Esta função recebe um prefixo de entrada, um id de hotel e uma hashTable que contém informações
 * sobre reservas. Com base no id do hotel, a função cria um array de estruturas Output4 ordenado por data
 * de início da reserva. A string de output é formatada conforme o prefixo de entrada.
 *
 * @param input_prefix O prefixo de entrada que determina o formato da resposta ("4" ou "4F").
 * @param hotel_id O id do hotel para o qual as informações de reserva serão geradas.
 * @param reservations_hash_table A hashTable que contém informações sobre reservas.
 * 
 * @return Um apontador para uma string formatada com informações ordenadas sobre reservas para o hotel especificado.
 */
char* func_answer_query_4(char* input_prefix, char* id, GHashTable* reservations_hash_table);


/**
 * Responde à Query 5 retornando informações de voos que atendem aos critérios fornecidos.
 *
 * Esta função busca na Hash Table por voos que têm a origem desejada e estão dentro do intervalo de datas fornecido.
 * Em seguida, gera uma resposta formatada com as informações dos voos encontrados.
 *
 * @param input_prefix Prefixo de entrada para a resposta.
 * @param origin Origem dos voos desejados.
 * @param begin_date Data de início do intervalo desejado.
 * @param end_date Data de término do intervalo desejado.
 * @param flights_hash_table Hash Table contendo informações sobre voos.
 * 
 * @return String formatada com as informações dos voos que atendem aos critérios.
 */
char* func_answer_query_5 (char* input_prefix, char* origin, int begin_date[6], int end_date[6], GHashTable* flights_hash_table);


/**
 * Responde à Query 6 retornando informações sobre aeroportos com mais passageiros em voos de um determinado ano.
 *
 * Esta função itera sobre a Hash Table, seleciona voos do ano especificado e calcula o número total 
 * de passageiros para cada aeroporto de origem e destino.
 * Em seguida, gera uma resposta formatada com as informações dos aeroportos ordenados por número de passageiros.
 *
 * @param input_prefix Prefixo de entrada para a resposta.
 * @param year Ano para o qual se deseja obter as informações dos aeroportos.
 * @param n Número de aeroportos a serem incluídos na resposta (pode ser menor que o total de aeroportos).
 * @param flights_hash_table Hash Table contendo informações sobre voos.
 * 
 * @return String formatada com as informações dos aeroportos ordenados pelo número de passageiros.
 */
char* func_answer_query_6 (char* input_prefix, int year, int n, GHashTable* flights_hash_table);


/**
 * Responde à Query 7 retornando informações sobre aeroportos ordenados por atraso médio de voos.
 *
 * Esta função itera sobre a Hash Table de voos, calcula o atraso médio para cada aeroporto de origem
 * e gera uma resposta formatada com as informações dos aeroportos ordenados por atraso médio.
 *
 * @param input_prefix Prefixo de entrada para a resposta.
 * @param N Número de aeroportos a serem incluídos na resposta (pode ser menor que o total de aeroportos).
 * @param flights_hash_table Hash Table contendo informações sobre voos.
 * 
 * @return String formatada com as informações dos aeroportos ordenados pelo atraso médio.
 */
char* func_answer_query_7 (char* input_prefix, int N, GHashTable* fligts_hash_table);


/**
 * Responde à query 8 calculando a receita de um hotel num intervalo de datas específico.
 *
 * Esta função recebe o id de um hotel, datas de início e fim, e uma hashTable que contém informações
 * sobre reservas. Com base nessas informações, a função calcula a receita total do hotel no intervalo de datas
 * especificado. A receita é calculada considerando o preço por noite de cada reserva no intervalo de datas fornecido. 
 * A função devolve a receita total do hotel para esse intervalo.
 *
 * @param hotel_id O id do hotel para o qual a receita será calculada.
 * @param begin_date Um array de três inteiros que representa a data de início do intervalo.
 * @param end_date Um array de três inteiros que representa a data de fim do intervalo.
 * @param reservations_hash_table A hashTable que contém informações sobre reservas.
 * 
 * @return A receita total do hotel no intervalo de datas especificado.
 */
char* func_answer_query_8 (char* input_prefix, char* hotel_id, int begin_date[3], int end_date[3], GHashTable* reservations_hash_table);


/**
 * Responde à query 9 obtendo uma lista de ids e nomes de utilizadores com base num prefixo.
 *
 * Esta função recebe um prefixo, consulta a hashTable de utilizadores e obtém uma lista de ids e nomes
 * de utilizadores cujos nomes começam com o prefixo fornecido. A lista é ordenada e retornada como uma string
 * formatada de acordo com o prefixo de entrada e o formato de output especificado. A função retorna uma string
 * que contém as informações dos utilizadores correspondentes.
 *
 * @param input_prefix O prefixo de entrada que especifica o formato de output (por exemplo, "9F" ou "9").
 * @param prefix O prefixo usado para filtrar os nomes dos utilizadores.
 * @param users_hash_table A hashTable que contém informações sobre os utilizadores.
 * 
 * @return Uma string que contém informações dos utilizadores cujos nomes começam com o prefixo fornecido.
 */
char* func_answer_query_9 (char* input_prefix, char* prefix, GHashTable* users_hash_table);


/**
 * Responde à Query 10 gerando estatísticas sobre o sistema para um determinado ano, mês ou dia.
 *
 * Esta função analisa os dados fornecidos e gera estatísticas sobre o número total de criações de contas,
 * voos, passageiros, passageiros únicos e reservas para um determinado ano, mês ou dia.
 *
 * @param input_prefix Prefixo de entrada para a resposta.
 * @param token Token que especifica o ano ou ano e mês a serem analisados.
 *              Se token for NULL, a função gera estatísticas para todos os anos disponíveis.
 * @param account_registrations_by_date Array tridimensional contendo o número de criações de conta por data.
 * @param number_reservations_by_date Array tridimensional contendo o número de reservas por data.
 * @param number_flights_by_date Array tridimensional contendo o número de voos por data.
 * @param number_passengers_by_date Array tridimensional contendo o número de passageiros por data.
 * @param number_unique_passengers_by_day Array tridimensional contendo o número de passageiros únicos por dia.
 * @param number_unique_passengers_by_month Array bidimensional contendo o número de passageiros únicos por mês.
 * @param number_unique_passengers_by_year Array unidimensional contendo o número de passageiros únicos por ano.
 * 
 * @return String formatada com as estatísticas geradas.
 */
char* func_answer_query_10 (char* input_prefix, char* token, int account_registrations_by_date[100][12][31], int number_reservations_by_date[100][12][31], int number_flights_by_date[100][12][31], int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100]);


#endif
