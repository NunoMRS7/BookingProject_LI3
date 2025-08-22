#include <stdio.h>
#include <ncurses.h>
#include <glib.h>
#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "defines.h"
#include "menu.h"
#include "input.h"
#include "passengers.h"
#include "users.h"
#include "flights.h"
#include "reservations.h"
#include "queries.h"
#include "get_input.h"
#include "defines.h"
#include "hash_funcs.h"
#include "print_output.h"


int func_interactive_mode (int account_registrations_by_date[100][12][31], int number_reservations_by_date[100][12][31], int number_flights_by_date[100][12][31], int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100]) {
  int run = 0;
  char* dataset_path = NULL;
  while (run == 0) { 
    func_init_ncurses();
    clear();
    refresh();

    // inicialização do menu
    int start_program = func_start_menu();

    // chamada da query
    if (start_program == 1) {
      WINDOW* input_win;
      int maxRows, maxCols;
      getmaxyx(stdscr, maxRows, maxCols);
      input_win = newwin(maxRows, maxCols, 0, 0);
      keypad(input_win, TRUE);
      wbkgd(input_win, COLOR_PAIR(TITLE_COLOR));

      if (dataset_path == NULL) dataset_path = func_get_files_path(input_win); // "dataset/data";
      else mvwprintw(input_win, 3, 3, "The path for the files is %s ", dataset_path);
    
      int numero_query = 0;
      char* input_path = func_call_query(input_win, &numero_query);
      if (input_path != NULL) {
          
        GHashTable* users_hash_table = func_parse_users(dataset_path, account_registrations_by_date);
        GHashTable* flights_hash_table = func_parse_flights(dataset_path, number_flights_by_date);
        GHashTable* reservations_hash_table = func_parse_reservations(dataset_path, users_hash_table, number_reservations_by_date);
        GHashTable* passengers_hash_table = func_parse_passengers(dataset_path, users_hash_table, flights_hash_table, number_passengers_by_date, number_unique_passengers_by_day, number_unique_passengers_by_month, number_unique_passengers_by_year);

        if (flights_hash_table == NULL || passengers_hash_table == NULL || reservations_hash_table == NULL || users_hash_table == NULL) {
          mvwprintw(input_win, 8, 3, "Error loading input files .csv\n");
          return 1;
        }
        setlocale(LC_COLLATE, "en_US.UTF-8");

        func_input(input_path, NULL, flights_hash_table, users_hash_table, reservations_hash_table,passengers_hash_table, account_registrations_by_date, number_reservations_by_date, number_flights_by_date, number_passengers_by_date, number_unique_passengers_by_day, number_unique_passengers_by_month, number_unique_passengers_by_year, numero_query, 0);
        
        // Verificação do input
        char input2[40];
        sprintf(input2,"Resultados/command%d_output.txt", numero_query);
        if (func_valida_input2(input2) == 1) {
          mvwprintw(input_win, maxRows/2, maxCols/2, "Ficheiro vazio");
          mvwprintw(input_win, maxRows/2+1, maxCols/2, "A query não foi chamada corretamente (2º parametro incorreto)");
          mvwprintw(input_win, maxRows/2+2, maxCols/2, "ou output nulo");
          while (wgetch(input_win) != '\n') {}
        }
        else func_print_output(input_win, numero_query);

        func_clean_hash(flights_hash_table, users_hash_table, reservations_hash_table, passengers_hash_table);
      }

      wclear (input_win); // limpar a janela
      wrefresh (input_win); // refresh da janela
      delwin (input_win);  // apagar a janela

      // libertações de memória finais
      free(input_path);
    }
    else if (start_program == 2) {}
    else run = 1; // exit

    clear();
    refresh();
  }
  endwin();
  return 0;
}

char* func_get_user_input (WINDOW* input_win, int posicao) {
  char input[256] = {0};
  int ch;
  int length = 0, x = 0, y = 0;          
    
  // modifica o x e o y para dar print na posição correta
  if (posicao == 1) { // posição para o texto com o caminho para os ficheiros
    x = 33;
    y = 3;
  }
  else if (posicao == 2) { // posição para o texto com o nº da query
    x = 23;
    y = 5;
  }
  else if (posicao == 3) { // posição para o texto com os dados
    x = 3;
    y = 9;
  }

  while ((ch = mvwgetch(input_win, y, x)) != '\n') {
    if (ch == KEY_BACKSPACE || ch == 127) {
      // lida com as teclas Backspace e delete
      if (length > 0) {
        // apaga o último caracter do input
        length--;
        input[length] = '\0';

        // limpa a linha e dá print do input atualizado
        wmove(input_win, y, x);
        wclrtoeol(input_win);
        mvwprintw(input_win, y, x, "%s", input);

        // move o cursor de volta para a posição atualizada
        wmove(input_win, y, x + length);
      }
    } 
    else{
      // adiciona o caractere à string de entrada
      input[length++] = ch;

      // exibe o input em tempo real
      mvwprintw(input_win, y, x, "%s", input);

      // move o cursor para a posição seguinte
      wmove(input_win, y, x + length);
    }
    // atualiza a janela para exibir as alterações
    wrefresh(input_win);
  }
  
  char* result = malloc((length + 1) * sizeof(char));
  strcpy(result, input);
  
  return result;
}

int func_valida_input1 (char* query_number_character) {
  if (*query_number_character >= '1' && *query_number_character <= '9') {
    while (isdigit(*(++query_number_character))); // verifica se os caracteres restantes são dígitos
    if (*query_number_character == 'F' || *query_number_character == '\0') return 1; // entrada válida
  } 
  else if (*query_number_character == '1' && *(query_number_character + 1) == '0') { // para o caso especial de '10'
    query_number_character += 2;

    // Verifica se o último caractere é opcionalmente um 'F'
    if (*query_number_character == 'F' || *query_number_character == '\0') return 1; // entrada válida
  }
  return 0;  // Entrada inválida
}

int func_valida_input2 (char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) return 1; 

  // posiciona o indicador de posição no final do arquivo
  fseek(file, 0, SEEK_END);

  // obtém a posição atual do indicador de posição
  long size = ftell(file);

  // fecha o arquivo
  fclose(file);

  // verifica se o tamanho é zero (arquivo vazio)
  if (size == 0) return 1; // arquivo vazio
  return 0; // arquivo não vazio
}

char* func_call_query (WINDOW* input_win, int* numero_query) {
  char* line = malloc(70 * sizeof(char));

  // pergunta ao user por informação sobre a query
  // nº da query
  mvwprintw(input_win, 5, 3, "Enter query number: ");
  wrefresh(input_win);

  char* query_number_character = func_get_user_input(input_win, 2);
  if (func_valida_input1(query_number_character) == 0) {
    mvwprintw(input_win, 6, 3, "Input inválido (query number deve ser do tipo 1 ou 1F)");
    mvwprintw(input_win, 7, 3, "'r' para recomeçar ou 'm' para voltar para o menu");
    
    int userInput = wgetch(input_win);
    
    while (userInput != 'm') {
      if (userInput == 'r') {
        werase(input_win);
        func_call_query(input_win, numero_query);
      }
      wrefresh(input_win);
      userInput = 'm';
    }
    free(query_number_character);
    free(line);
    return NULL;
  }

  int query_number = atoi(query_number_character);
  *numero_query = query_number;
  mvwprintw(input_win, 7, 3, "Input type: %s", func_select_instruction(query_number));
  wrefresh(input_win);

  char* input = func_get_user_input(input_win, 3);
  wrefresh(input_win);
    
  sprintf(line, "%s %s", query_number_character, input);
  
  free(input);
  free(query_number_character);
  return line;
}

char* func_get_files_path (WINDOW* input_win) {
  //Ask user for the path
  mvwprintw(input_win, 3, 3, "Enter the path for the files: ");
  wrefresh(input_win);
  char* files_path = func_get_user_input(input_win, 1);

  wrefresh(input_win);

  return files_path;
}
