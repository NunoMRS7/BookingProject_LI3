#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "defines.h"
#include "get_input.h"

char *choices[] = {
  "START",
  "INSTRUCTIONS",
  "QUIT"};
int n_choices = sizeof(choices) / sizeof(char *);


char *titulo[] = {

"                88       888   8888888               ",
"                88       888        88               ",
"                88       888     88888               ",
"                88       888        88               ",
"                8888888  888   8888888               "};

int n_titulo = sizeof(titulo)/ sizeof(char *);


char *instructions[]={          
  "                                                                                                  ",
  "  INPUT TYPES:                                                                                    ",
  "                                                                                                  ",
  "  QUERY 1                                                                                         ",
  "  Lista o resumo de um utilizador, voo, ou reserva                                                ",
  "  <ID>                                                                                            ",
  "                                                                                                  ",
  "  QUERY 2                                                                                         ",
  "  Lista os voos e/ou reservas de um utilizador                                                    ",
  "  <ID> [flights|reservations]                                                                     ",
  "                                                                                                  ",
  "  QUERY 3                                                                                         ",
  "  Apresenta a classificação média de um hotel                                                     ",
  "  <ID>                                                                                            ",
  "                                                                                                  ",  
  "  QUERY 4                                                                                         ",
  "  Lista as reservas de um hotel                                                                   ",
  "  <ID>                                                                                            ",
  "                                                                                                  ",
  "  QUERY 5                                                                                         ",
  "  Listar os voos com origem num dado aeroporto entre duas datas                                   ",
  "  <Name> <Begin_date> <End_date>                                                                  ",
  "                                                                                                  ",
  "  QUERY 6                                                                                         ",
  "  Lista o top N aeroportos com mais passageiros para um dado ano                                  ",
  "  <Year> <N>                                                                                      ",
  "                                                                                                  ",
  "  QUERY 7                                                                                         ",
  "  Lista o top N aeroportos com a maior mediana de atraso                                          ",
  "  <N>                                                                                             ",
  "                                                                                                  ",
  "  QUERY 8                                                                                         ",
  "  Apresenta a receita total de um hotel entre duas datas                                          ",
  "  <Id> <Begin_date> <End_date>                                                                    ",
  "                                                                                                  ",
  "  QUERY 9                                                                                         ",
  "  Lista todos os utilizadores cujo nome começa com o prefixo passado por argumento                ",
  "  <Prefix>                                                                                        ",
  "                                                                                                  ",
  "  QUERY 10                                                                                        ",
  "  Apresenta o número de novos utilizadores, o número de voos, o número de passageiros, o          ",
  "  número de passageiros únicos e número de reservas                                               ",
  "  [year [month]]                                                                                  ",
  "                                                                                                  ",
};
int n_instructions = sizeof(instructions)/ sizeof(char *);

void func_init_ncurses (void) {
  // inicialização do nCurses
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // verifica o suporte de cor no terminal
  if (has_colors() == FALSE) {
      endwin();
      printf("Your terminal does not support color\n");
      exit(1);
  }

  init_color(1, 0, 0, 502); // background de cor roxo escuro
  init_color(2, 300, 0, 551); // cor da opção selecionada

  // definição dos pares de cores
  init_pair(BACKGROUND_COLOR, COLOR_WHITE, 1);
  init_pair(SELECTED_OPTION_COLOR, COLOR_WHITE, 2);
  init_pair(TITLE_COLOR, COLOR_WHITE, 1);

  raw();
  noecho();
  curs_set(FALSE);

  // ativação do uso de cores
  use_default_colors();
  curs_set(0);
  noecho();
}

char* func_select_instruction (int query_number) {
  int indice = 5 + 4 * (query_number - 1);
  if (query_number == 10) indice++;
  return instructions[indice];
}


void func_print_menu (WINDOW *menu_win, int highlight) {
  int x, y, i;
  int maxRows, maxCols;
  getmaxyx(stdscr, maxRows, maxCols);

  x = (maxCols - 12) / 2;
  y = maxRows / 2;

  werase(menu_win);
  wbkgd(menu_win, COLOR_PAIR(BACKGROUND_COLOR)); // cor do background

  // print titulo
  int x1 = (maxCols - 65)/2;
  int y1 = 2;
  wattron(menu_win, COLOR_PAIR(TITLE_COLOR));
  for (i = 0; i < n_titulo; ++i) {
    // highlight da opção selecionada
    mvwprintw(menu_win, y1, x1, "%s", titulo[i]);
    y1++;
  }
  wattroff(menu_win, COLOR_PAIR(TITLE_COLOR));

  // print de todas as opções 
  for (i = 0; i < n_choices; ++i) {
    if (highlight == i + 1) { // highlight da opção selecionada
      wattron(menu_win, COLOR_PAIR(SELECTED_OPTION_COLOR));
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, COLOR_PAIR(SELECTED_OPTION_COLOR));
    }
    else { // tirar o highlight das opções não selecionadas
      wattron(menu_win, COLOR_PAIR(BACKGROUND_COLOR));
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, COLOR_PAIR(BACKGROUND_COLOR));
    }
    ++y;
  }
  // update do menu
  wrefresh(menu_win);
}


void func_print_instructions (WINDOW *menu_win) {
  wrefresh(menu_win);
  int x = 1, y = 1;
  int maxRows, maxCols;
  getmaxyx(stdscr, maxRows, maxCols);

  werase(menu_win);
  wbkgd(menu_win, COLOR_PAIR(BACKGROUND_COLOR)); // cor do background

  // print das instruções
  wattron(menu_win, COLOR_PAIR(BACKGROUND_COLOR));
  for (int i = 0; i < n_instructions; ++i) {
    mvwprintw(menu_win, y, x, "%s", instructions[i]);
    ++y;
  }
  wattroff(menu_win, COLOR_PAIR(BACKGROUND_COLOR));

  // display do botão "Back to menu"
  wattron(menu_win, COLOR_PAIR(SELECTED_OPTION_COLOR));
  mvwprintw(menu_win, maxRows-2, maxCols-20, "BACK TO MENU"); // print no canto inferior direito
  wattroff(menu_win, COLOR_PAIR(SELECTED_OPTION_COLOR));

  // Update do menu
  wrefresh(menu_win);

  while (1) {
    switch (wgetch(menu_win)) {
      case 10: // KEY_ENTER
        wrefresh(menu_win);
        wmove(menu_win, 0, 0);
        wclear(menu_win);
        func_print_menu(menu_win, 2);
        return;
      case KEY_RESIZE:
        // redimensionamento da janela, recriar a janela e imprimir novamente as instruções
        wrefresh(menu_win);
        func_print_instructions(menu_win);
        break;
      default:
        break;
    }
    wrefresh(menu_win);
  }
}


void func_select_option (WINDOW *menu_win, int choice, int *in_query) {
  switch (choice) {
  case 1:
    *in_query = 1;
    break;
  case 2:
    func_print_instructions(menu_win);
    *in_query = 2;
    break;
  default:
    *in_query = 3;
    break;
  }
}


int func_start_menu (void) {
  WINDOW *menu_win;
  int choice = 0, in_menu = 0, in_query = 0;
  int highlight = 1; // opção selecionada
  int maxRows, maxCols;
  getmaxyx(stdscr, maxRows, maxCols);

  // janela de menu
  menu_win = newwin(maxRows, maxCols, 0, 0);
  keypad(menu_win, TRUE);

  func_print_menu(menu_win, highlight);

  while (in_menu == 0) {
    switch (wgetch(menu_win)) {
      case KEY_UP:
        if (highlight == 1) highlight = n_choices;
        else highlight--;
        break;
      case KEY_DOWN:
        if (highlight == n_choices) highlight = 1;
        else highlight++;
        break;
      case 10: // KEY_ENTER 
        choice = highlight;
        func_select_option(menu_win, choice, &in_query);
        in_menu = 1;
        break;
      default:
        refresh();
        break;
    }
    func_print_menu(menu_win, highlight);
  }

  wclear(menu_win); // limpar a janela
  wrefresh(menu_win); // refresh da janela
  delwin(menu_win);  // apagar a janela
  endwin();

  return in_query;
}
