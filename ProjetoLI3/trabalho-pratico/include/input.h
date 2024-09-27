#ifndef INPUT_H
#define INPUT_H


/**
 * Remove as aspas de uma string se estiverem presentes nas extremidades.
 *
 * Esta função remove as aspas de uma string se a string tiver pelo menos
 * três caracteres e se as aspas estiverem presentes nas extremidades da string.
 *
 * @param string A string da qual as aspas devem ser removidas, se presentes.
 */
void func_remove_quotation_marks(char* string);

/**
 * Esta função compara dois ficheiros, um esperado e outro obtido, linha por linha.
 *
 * @param expected_file_path Caminho para o ficheiro esperado.
 * @param obtained_file_path Caminho para o ficheiro obtido.
 * @return Retorna 0 se os ficheiros forem iguais, caso contrário, retorna o número da primeira linha onde se diferem.
 *         Retorna -1 se houver um erro ao abrir os ficheiros.
 */
int func_compare_lines(char* expected_file_path, char* obtained_file_path);

/**
 * Lê um input e responde a queries com base no mesmo.
 *
 * Esta função lê um comando específico, realiza a
 * respetivas querie e escreve os output num ficheiro de saída. As queries
 * estão relacionadas com voos, reservas, utilizadores e passageiros.
 *
 * @param input_path O caminho para o ficheiro input.
 * @param flights_hash_table A hashTable que contém os voos.
 * @param users_hash_table A hashTable que contém os utilizadores.
 * @param reservations_hash_table A hashTable que contém as reservas.
 * @param passengers_hash_table A hashTable que contém os passageiros.
 *
 * @return 1 se a função executa com sucesso, 0 em caso contrário.
 */
int func_input (char* input_path, char* output_path, GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table, GHashTable* passengers_hash_table, int account_registrations_by_date[100][12][31], int number_reservations_by_date[100][12][31], int number_flights_by_date[100][12][31], int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100], int count, int detailed);

/**
 * Lê um input de um ficheiro e responde a queries com base no mesmo.
 *
 * Esta função lê comandos de um ficheiro de input específico, realiza as
 * respetivas queries e escreve os outputs em ficheiros de saída. As queries
 * estão relacionadas com voos, reservas, utilizadores e passageiros.
 *
 * @param input_path O caminho para o ficheiro input.
 * @param flights_hash_table A hashTable que contém os voos.
 * @param users_hash_table A hashTable que contém os utilizadores.
 * @param reservations_hash_table A hashTable que contém as reservas.
 * @param passengers_hash_table A hashTable que contém os passageiros.
 *
 * @return 1 se a função executa com sucesso, 0 em caso contrário.
 */
int input_line (char* input_path, char* output_path, GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table, GHashTable* passengers_hash_table, int account_registrations_by_date[100][12][31], int number_reservations_by_date[100][12][31], int number_flights_by_date[100][12][31], int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100], int detailed);
#endif
