#ifndef USERS_H
#define USERS_H

typedef struct user User;


/**
 * Itera por todos os elementos da hashTable e, para cada um, liberta
 * a memória alocada.
 * 
 * @param users_hash_table: A hashTable que contém os utilizadores.
 */
void func_free_users(GHashTable* users_hash_table);


/**
 * Calcula a idade de um utilizador.
 *
 * @param birth_date: String que contém a data de de nascimento de um utilizador.
 * 
 * @return A idade de um utilizador.
 */
int func_convert_age(char* birth_date);


/**
 * Cria uma nova estrutura de utilizador e inicializa-a com os dados do mesmo.
 *
 * @return Um apontador para o utilizador criado.
 */
User* func_new_user(char* id, char* name, char* birth_date, int age, char* sex, char* passport, char* country_code, char* account_creation, char* account_status);


/**
 * Faz-se o parse da informação dos utilizadores do ficheiro .csv e guarda-os na hashTable.
 *
 * A função lê o ficheiro 'users.csv' (linha a linha), cujo caminho é especificado 
 * pelo parâmetro 'path', cria uma nova estrutura de utilizador e guarada-a na hashTable, 
 * usando o id de utilizador como chave. Preenche também a matriz com o número de criação 
 * de contas organizados por data.
 *
 * Faz uso da função 'func_new_user' para definir os parâmetros no novo utilizador.
 * 
 * @param path: O caminho para a diretoria que contém o ficheiro .csv com a informação
 * dos utilizadores.
 * @param account_registrations_by_date: O array tridimensional que contém o número de reservas
 * organizadas por dia/mês/ano.
 *
 * @return Uma hashTable que contém as estruturas de utilizador com os seus ids a servirem de 
 * chave.
 */
GHashTable* func_parse_users(char* path, int account_registrations_by_date[100][12][31]);


/**
 * Define o número de voos do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user. 
 * @param number_flights Número de voos a definir.
 */
void func_set_user_number_flights(User* user, int number_flights);


/**
 * Define o número de reservas do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user. 
 * @param number_reservations Número de voos a definir.
 */
void func_set_user_number_reservations(User* user, int number_reservations);


/**
 * Define o total gasto por um utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user. 
 * @param total_spent Total gasto a definir.
 */
void func_set_user_total_spent(User* user, double total_spent);


/**
 * Obtém o <ID> do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Apondator para a string que contém o <ID> do utilizador.
 */
char* func_get_user_id(User* user);


/**
 * Obtém o nome do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Apondator para a string que contém o nome do utilizador.
 */
char* func_get_user_name(User* user);


/**
 * Obtém a idade do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Inteiro que contém a idade do utilizador.
 */
int func_get_user_age(User* user);


/**
 * Obtém o número de voos do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Inteiro que contém o número de voos do utilizador.
 */
int func_get_user_number_flights(User* user);


/**
 * Obtém o gênero utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Apondator para a string que contém o gênero utilizador.
 */
char* func_get_user_sex(User* user);


/**
 * Obtém o passaporte do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Apondator para a string que contém o passaporte do utilizador.
 */
char* func_get_user_passport(User* user);


/**
 * Obtém o código de país do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Apondator para a string que contém o código de país do utilizador.
 */
char* func_get_user_country_code(User* user);


/**
 * Obtém o estado da conta do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Apondator para a string que contém o estado da conta do utilizador.
 */
char* func_get_user_account_status(User* user);


/**
 * Obtém o número de reservas do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return Inteiro que contém o número de reservas do utilizador.
 */
int func_get_user_number_reservations(User* user);


/**
 * Obtém o total gasto do utilizador associado ao struct user.
 *
 * @param user Apondator para o struct user.
 * 
 * @return "Double" que contém o total gasto do utilizador.
 */
double func_get_user_total_spent(User* user);


#endif
