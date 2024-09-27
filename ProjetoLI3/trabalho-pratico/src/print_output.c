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

void func_print_output (WINDOW* input_win, int numero_query) {
  char buffer[100];
  sprintf(buffer, FILENAME_FORMAT, numero_query);
  FILE* file = fopen(buffer, "r");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  char line[MAX_LINE];
  int maxRows, maxCols;
  getmaxyx(stdscr, maxRows, maxCols);
  (void)maxCols;

  int stop = 1;
  int indice = 0;
  int page_start = 0;
  int first_line_size = 0;
  int lines_sizes[5000] = {0}; // array que guarda o tamanho das linhas

  wclear(input_win);
  wrefresh(input_win);

  while (stop) {
    werase(input_win);
    int start = 0;
    int y = 3;

    // define o pointer para o local onde o ficheiro deve começar a ler
    fseek(file, page_start, SEEK_SET);

    mvwprintw(input_win, maxRows-1, maxCols-15, "'q' for quit");

    // loop que dá print das linhas do ficheiro até a linha ser nula ou até ser atingido o fim da janela
    while (fgets(line, sizeof(line), file) != NULL && y < maxRows-3) {
      mvwprintw(input_win, y++, 3, "%s", line);
      if (start == 0) {
        first_line_size = strlen(line);
        lines_sizes[indice] = first_line_size;
        start++;
      }
    }

    wrefresh(input_win);

    // espera a tecla do user
    int input = wgetch(input_win);
    if (input == KEY_DOWN) {
      // rola para baixo
      if (fgets(line, sizeof(line), file) != NULL) {
        page_start += first_line_size;
        indice++;
      }
    } 
    else if (input == KEY_UP) {
      // rola para cima
      if (indice > 0) {
        indice--;
        page_start -= lines_sizes[indice];
      }
      else page_start = 0;
    } 
    else if (input == 'q') {
      stop = 0;  // sai quando 'q' for pressionado
    }
  }

  fclose(file);

  // limpa a janela
  werase(input_win);
  wrefresh(input_win);
}