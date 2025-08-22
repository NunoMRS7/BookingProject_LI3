#ifndef MENU_H
#define MENU_H

/**
 * Inicializa a biblioteca ncurses e configura as opções de interface gráfica.
 *
 * Esta função configura as opções da biblioteca ncurses para fornecer uma interface gráfica básica
 * no terminal. Inclui a configuração de cores e outras opções visuais.
 */
void func_init_ncurses(void);


/**
 * Seleciona a instrução correspondente ao número da consulta.
 *
 * Esta função retorna a instrução correspondente ao número da consulta passado como argumento.
 *
 * @param query_number Número da consulta para o qual a instrução deve ser selecionada.
 *
 * @return Retorna uma string contendo a instrução correspondente ao número da consulta.
 */
char* func_select_instruction(int query_number);


/**
 * Imprime um menu na janela especificada com opções destacadas.
 *
 * Esta função exibe um menu na janela especificada, destacando a opção atualmente selecionada.
 *
 * @param menu_win Janela onde o menu será exibido.
 * @param highlight Índice da opção que deve ser destacada.
 */
void func_print_menu(WINDOW *menu_win, int highlight);


/**
 * Exibe as instruções do programa quando a opção "instructions" é selecionada.
 *
 * Esta função exibe as instruções do programa numa janela, permitindo ao utilizador retornar ao menu principal.
 *
 * @param menu_win Janela onde as instruções serão exibidas.
 */
void func_print_instructions(WINDOW *menu_win);


/**
 * Lida com a seleção de opções do menu.
 *
 * Esta função é chamada quando o utilizador pressiona ENTER e seleciona a ação com base na opção escolhida.
 *
 * @param menu_win Janela onde as opções do menu estão sendo exibidas.
 * @param choice Índice da opção escolhida.
 * @param in_query Apontador para a variável que indica se a aplicação está num estado de consulta.
 */
void func_select_option(WINDOW *menu_win, int choice, int *in_query);


/**
 * Inicia o menu principal do programa e lida com a navegação e seleção de opções.
 *
 * Esta função cria uma janela para exibir o menu principal, onde o utilizador pode navegar e selecionar opções.
 * A função retorna um valor indicando a ação a ser tomada com base na opção selecionada.
 *
 * @return Retorna 1 se a aplicação deve entrar no modo de consulta, 2 se o utilizador selecionar "instructions", 3 para sair do programa.
 */
int func_start_menu(void);


#endif
