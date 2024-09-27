#ifndef PRINT_OUTPUT_H
#define PRINT_OUTPUT_H

/**
 * Imprime o conteúdo de um arquivo na janela de saída.
 *
 * Esta função lê um arquivo com base no número da consulta, exibe seu conteúdo
 * numa janela específica e permite rolar para cima e para baixo para visualizar
 * todo o conteúdo do arquivo.
 *
 * @param input_win Janela onde o conteúdo do arquivo será exibido.
 * @param numero_query Número da consulta usado para construir o nome do arquivo a ser lido.
 *
 * @details
 * A função lê o conteúdo do arquivo com o nome formatado usando o número da consulta e o imprime
 * na janela de saída. O usuário pode rolar para cima e para baixo para visualizar o conteúdo completo.
 * A tecla 'q' permite que o usuário saia da visualização do arquivo.
 */
void func_print_output(WINDOW* input_win, int numero_query);

#endif
