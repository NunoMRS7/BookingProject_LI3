#ifndef GET_INPUT_H
#define GET_INPUT_H

/**
 * Função responsável pelo modo interativo do programa.
 *
 * Esta função inicia o modo interativo do programa, permitindo ao usuário navegar por um menu
 * e realizar consultas com base em arquivos de dados fornecidos.
 *
 * @param account_registrations_by_date Matriz para armazenar o número de registros de conta por data.
 * @param number_reservations_by_date Matriz para armazenar o número de reservas por data.
 * @param number_flights_by_date Matriz para armazenar o número de voos por data.
 *
 * @return Retorna 0 se o programa for encerrado com sucesso, caso contrário, retorna um código de erro.
 */
int func_interactive_mode(int account_registrations_by_date[100][12][31], int number_reservations_by_date[100][12][31], int number_flights_by_date[100][12][31], int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100]);


/**
 * Obtém o input para o número da consulta da query, dados e hora a partir de uma janela ncurses.
 *
 * Esta função permite ao usuário inserir dados numa janela específica e retorna a string resultante.
 *
 * @param input_win Janela onde o input será exibido.
 * @param posicao Posição que determina a área de entrada (1 para o caminho para os ficheiros, 2 para 
 * número da query, 3 para dados de input para a query).
 *
 * @return Retorna a string inserida pelo usuário.
 *
 * @details
 * A função aguarda o input em tempo real, permitindo inserir e apagar caracteres e navegação no texto. 
 * A posição de inserção é determinada pela variável 'posicao'.
 *
 * - Para 'posicao' igual a 1 (dados), o input é esperada na posição (33, 3).
 * - Para 'posicao' igual a 2 (número da consulta), o input é esperada na posição (23, 5).
 * - Para 'posicao' igual a 3 (dados), o input é esperada na posição (3, 9).
 *
 * A tecla Enter finaliza o input, e a função retorna a string inserida.
 */
char* func_get_user_input(WINDOW* input_win, int posicao);

/**
 * Valida o input do número e estilo de output da query.
 *
 * Esta função verifica se o input do usuário para o número da consulta é válido.
 * O input válido deve começar com um número de '1' a '10' seguido opcionalmente por 'F'.
 *
 * @param query_number_c String representando o número da consulta fornecido pelo usuário.
 *
 * @return Retorna 1 se o input for válido, 0 se for inválido.
 *
 * @note
 * A função considera válidas entradas como '1', '2', ..., '9', '10', '10F', etc.
 */
int func_valida_input1(char* query_number_c);


/**
 * Valida se o conteúdo de um arquivo é vazio.
 *
 * Esta função verifica se o conteúdo de um arquivo é vazio, fornecendo o nome do arquivo como entrada.
 *
 * @param filename Nome do arquivo a ser verificado.
 *
 * @return Retorna 1 se o arquivo estiver vazio ou não puder ser aberto, 0 se o arquivo contiver dados.
 *
 * @note
 * A função tenta abrir o arquivo no modo de leitura. Se o arquivo não puder ser aberto,
 * é considerado vazio. Se o arquivo for aberto com sucesso, a função verifica se o tamanho do
 * arquivo é zero para determinar se está vazio.
 */
int func_valida_input2(char *filename);


/**
 * Solicita informações ao usuário para a entrada da query.
 *
 * Esta função interage com o usuário para obter informações sobre o número e o tipo do output,
 * bem como os dados necessários para a chamada da query. Em seguida, gera uma linha de consulta apropriada.
 *
 * @param input_win Janela onde as interações com o usuário serão exibidas.
 * @param numero_query Apontador para a variável que armazenará o número da consulta.
 *
 * @return Retorna uma string contendo a linha de consulta gerada. Em caso de entrada inválida, retorna NULL.
 */
char* func_call_query(WINDOW* input_win, int *numero_query);


/**
 * Solicita ao usuário o caminho para os arquivos e retorna a string correspondente.
 *
 * Esta função exibe uma mensagem na janela de entrada para solicitar ao usuário o caminho
 * para os arquivos necessários. O usuário pode inserir o caminho desejado, e a função retorna
 * a string correspondente.
 *
 * @param input_win Janela onde a solicitação e interações com o usuário serão exibidas.
 *
 * @return Retorna uma string contendo o caminho para os arquivos inserido pelo usuário.
 */
char* func_get_files_path (WINDOW* input_win);


#endif
