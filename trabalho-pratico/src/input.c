#include <stdio.h>
#include <time.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "defines.h"
#include "passengers.h"
#include "users.h"
#include "flights.h"
#include "reservations.h"
#include "queries.h"



void func_remove_quotation_marks(char* string) {
  int length = strlen(string);

  // Verifica se a string tem pelo menos duas aspas (início e/ou fim)
  if (length >= 2) {
    // Remove as aspas do início, se existirem
    if (string[0] == '"') {
      for (int i = 0; string[i]; i++) {
        string[i] = string[i+1];
      }
      // Reduz o comprimento da string e coloca '\0' no final
      length--;
      string[length] = '\0';
    }

    // Remove as aspas do fim, se existirem
    if (length >= 2 && string[length-1] == '"') {
      // Coloca '\0' no final para remover as aspas finais
      string[length-1] = '\0';
    }
  }
}


int func_compare_lines(char* expected_file_path, char* obtained_file_path) {
  int wrong_line = 1;
  char expected_line[200], obtained_line[200];

  FILE* expected_file = fopen(expected_file_path, "r");
	if (expected_file == NULL) return -1;
  FILE* obtained_file = fopen(obtained_file_path, "r");
	if (obtained_file == NULL) return -1;

  while(fgets(expected_line, 200, expected_file) != NULL && fgets(obtained_line, 200, obtained_file) != NULL) {
    if (strcmp(expected_line, obtained_line) != 0) {
      fclose(expected_file); fclose(obtained_file);
      return wrong_line;
    }
    wrong_line++;
  }
  fclose(expected_file); fclose(obtained_file);
  return 0;
}



int func_input(char* input_path, char* output_path, GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table, GHashTable* passengers_hash_table, int account_registrations_by_date[100][12][31], int number_reservations_by_date[100][12][31], int number_flights_by_date[100][12][31], int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100], int counter, int detailed) {
    struct timespec start, end;
    double time_spent;

    char *token;
    token = strtok(input_path, " "); // guarda na variável token os caracteres que identificam a query a ser chamada (caracteres que precedem o primeiro espaço)

    if (strcmp(token, "1") == 0 || strcmp(token, "1F") == 0) { // caso o input seja direcionado à query 1
      char* input_prefix = strdup(token); // guarda o prefixo com ou sem "F" para ser usado posteriormente na decisão da forma do output
      char buffer1[40];
      sprintf(buffer1,FILENAME_FORMAT,counter); // o buffer guarda o nome correto do ficheiro a ser criado
      FILE* file_output1 = fopen(buffer1,"w"); // o ficheiro é criado
      token = strtok(NULL, " "); // a variável token guarda o argumento necessário para a query
      func_remove_quotation_marks(token); // removem-se quaisquer aspas do argumento

      if (detailed) clock_gettime(CLOCK_REALTIME, &start); // inicia a contagem do tempo de execução da query
      
      char* output1 = func_answer_query_1 (input_prefix, token, flights_hash_table, users_hash_table, reservations_hash_table); // o output é gerado, já formatado corretamente
      if (output1 != NULL) fprintf(file_output1,"%s",output1); // o output gerado é escrito no ficheiro respetivo
      fclose(file_output1);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end); // termina a contagem do tempo de execução da query
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter); // o buffer guarda o nome correto do ficheiro de output esperado
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // cálculo do tempo de execução da query
        int resultado = func_compare_lines(output_buffer, buffer1); // comparação dos ficheiros de output
        if (resultado == 0) printf("A query 1 está correta\n");
        else if (resultado > 0) printf("A query 1 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 1 é %.6f segundos\n\n", time_spent);
      }
      
  	  free(input_prefix);
      free(output1);
    }
    else if (strcmp(token, "2") == 0 || strcmp(token, "2F") == 0 ) { // caso o input seja direcionado à query 2
      char* input_prefix = strdup(token);
      char buffer2[40];
      sprintf(buffer2,FILENAME_FORMAT,counter);
      FILE* file_output2 = fopen(buffer2,"w");
      int i = 0;
      char* tokens[3];
      tokens[0] = NULL;
      tokens[1] = NULL;
      tokens[2] = NULL;
      while(token != NULL) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " ");
      }
      if (tokens[2] == NULL) tokens[2] = " ";
      
      if (detailed) clock_gettime(CLOCK_REALTIME, &start);
      
      char* output2 = func_answer_query_2 (input_prefix, tokens[1], tokens[2], flights_hash_table, users_hash_table, reservations_hash_table, passengers_hash_table); // o output é gerado, já formatado corretamente
      if (output2 != NULL) fprintf(file_output2,"%s",output2);
      fclose(file_output2);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer2);
        if (resultado == 0) printf("A query 2 está correta\n");
        else if (resultado > 0) printf("A query 2 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 2 é %.6f segundos\n\n", time_spent);
      }

      free(input_prefix);
  	  free(output2);
    }
    else if (strcmp(token, "3") == 0 || strcmp(token, "3F") == 0) { // caso o input seja direcionado à query 3
      char* input_prefix = strdup(token);
      char buffer3[40];
      sprintf(buffer3,FILENAME_FORMAT,counter);
      FILE* file_output3 = fopen(buffer3,"w");
      token = strtok(NULL, " ");
      func_remove_quotation_marks(token);

      if (detailed) clock_gettime(CLOCK_REALTIME, &start);
      
      char* output3 = func_answer_query_3 (input_prefix, token, reservations_hash_table); // o output é gerado, já formatado corretamente
  	  if (output3 != NULL) fprintf(file_output3,"%s",output3);
      fclose(file_output3);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer3);
        if (resultado == 0) printf("A query 3 está correta\n");
        else if (resultado > 0) printf("A query 3 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 3 é %.6f segundos\n\n", time_spent);
      }

      free(input_prefix);
  	  free(output3);
    }
    else if (strcmp(token, "4") == 0 || strcmp(token, "4F") == 0) { // caso o input seja direcionado à query 4
      char* input_prefix = strdup(token);
      char buffer4[40];
      sprintf(buffer4,FILENAME_FORMAT,counter);
      FILE* file_output4 = fopen(buffer4,"w");
      token = strtok(NULL, " ");

      if (detailed) clock_gettime(CLOCK_REALTIME, &start);
      
      char* output4 = func_answer_query_4 (input_prefix, token, reservations_hash_table); // o output é gerado, já formatado corretamente
  	  if (output4 != NULL) fprintf(file_output4,"%s",output4);
      fclose(file_output4);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer4);
        if (resultado == 0) printf("A query 4 está correta\n");
        else if (resultado > 0) printf("A query 4 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 4 é %.6f segundos\n\n", time_spent);
      }

      free(input_prefix);
  	  free(output4);
    }
    else if (strcmp(token, "5") == 0 || strcmp(token, "5F") == 0) { // caso o input seja direcionado à query 5
      char* input_prefix = strdup(token);
      char buffer5[40];
      sprintf(buffer5,FILENAME_FORMAT,counter);
      FILE* file_output5 = fopen(buffer5,"w");


      char* origin = strtok(NULL, " "); 
      func_remove_quotation_marks(origin);

      char* begin_date_string_1 = strtok(NULL, " "); 
      func_remove_quotation_marks(begin_date_string_1);
      char* begin_date_string_2 = strtok(NULL, " "); 
      func_remove_quotation_marks(begin_date_string_2);

      char* end_date_string_1 = strtok(NULL, " ");
      func_remove_quotation_marks(end_date_string_1);
      char* end_date_string_2 = strtok(NULL, "\0");
      func_remove_quotation_marks(end_date_string_2);

      int begin_date[6], end_date[6];
      begin_date[0] = atoi(strtok(begin_date_string_1, "/"));
      begin_date[1] = atoi(strtok(NULL, "/"));
      begin_date[2] = atoi(strtok(NULL, " "));
      begin_date[3] = atoi(strtok(begin_date_string_2, ":"));
      begin_date[4] = atoi(strtok(NULL, ":"));
      begin_date[5] = atoi(strtok(NULL, "\0"));

      end_date[0]   = atoi(strtok(end_date_string_1, "/"));
      end_date[1]   = atoi(strtok(NULL, "/"));
      end_date[2]   = atoi(strtok(NULL, " "));
      end_date[3]   = atoi(strtok(end_date_string_2, ":"));
      end_date[4]   = atoi(strtok(NULL, ":"));
      end_date[5]   = atoi(strtok(NULL, "\0"));

      if (detailed) clock_gettime(CLOCK_REALTIME, &start);
      
      char* output5 = func_answer_query_5(input_prefix, origin, begin_date, end_date, flights_hash_table); // o output é gerado, já formatado corretamente
      if (output5 != NULL) fprintf(file_output5,"%s",output5);
      fclose(file_output5);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer5);
        if (resultado == 0) printf("A query 5 está correta\n");
        else if (resultado > 0) printf("A query 5 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 5 é %.6f segundos\n\n", time_spent);
      }

      free(input_prefix);
      free(output5);
    }
    else if (strcmp(token, "6") == 0 || strcmp(token, "6F") == 0) {
      char* input_prefix = strdup(token);
      char buffer6[40];
      sprintf(buffer6,FILENAME_FORMAT,counter);
      FILE* file_output6 = fopen(buffer6,"w");

      char* yearC = strtok(NULL, " ");
      int year = atoi(yearC);
      char* nC = strtok(NULL, " ");
      int n = atoi(nC);

      if (detailed) clock_gettime(CLOCK_REALTIME, &start);    
      
      char* output6 = func_answer_query_6 (input_prefix, year, n, flights_hash_table); // o output é gerado, já formatado corretamente
      if (output6 != NULL) fprintf(file_output6,"%s",output6);
      fclose(file_output6);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer6);
        if (resultado == 0) printf("A query 6 está correta\n");
        else if (resultado > 0) printf("A query 6 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 6 é %.6f segundos\n\n", time_spent);
      }

      free(input_prefix);
  	  free(output6);
    }
    else if (strcmp(token, "7") == 0 || strcmp(token, "7F") == 0) { // caso o input seja direcionado à query 7
      char* input_prefix = strdup(token);
      char buffer7[40];
      sprintf(buffer7,FILENAME_FORMAT,counter);
      FILE* file_output7 = fopen(buffer7,"w");
      token = strtok(NULL, "\0");
      func_remove_quotation_marks(token);
      int number_N = atoi(token);

      if (detailed) clock_gettime(CLOCK_REALTIME, &start);    
      
      char* output7 = func_answer_query_7 (input_prefix, number_N, flights_hash_table); // o output é gerado, já formatado corretamente
  	  if (output7 != NULL) fprintf(file_output7,"%s",output7);
      fclose(file_output7);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer7);
        if (resultado == 0) printf("A query 7 está correta\n");
        else if (resultado > 0) printf("A query 7 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 7 é %.6f segundos\n\n", time_spent);
      }

      free(input_prefix);
  	  free(output7);
    }
    else if (strcmp(token, "8") == 0 || strcmp(token, "8F") == 0) { // caso o input seja direcionado à query 8
      char buffer8[40];
      sprintf(buffer8,FILENAME_FORMAT,counter);
      char* input_prefix = strdup(token);
      FILE* file_output8 = fopen(buffer8,"w");

      char* hotel_id = strtok(NULL, " ");
      func_remove_quotation_marks(hotel_id);

      char* begin_date_string = strtok(NULL, " ");
      func_remove_quotation_marks(begin_date_string);

      char* end_date_string = strtok(NULL, "\0");
      func_remove_quotation_marks(end_date_string);


      int begin_date[3], end_date[3];
      begin_date[0] = atoi(strtok(begin_date_string, "/"));
      begin_date[1] = atoi(strtok(NULL, "/"));
      begin_date[2] = atoi(strtok(NULL, "\0"));

      end_date[0]   = atoi(strtok(end_date_string, "/"));
      end_date[1]   = atoi(strtok(NULL, "/"));
      end_date[2]   = atoi(strtok(NULL, "\0"));
      
      if (detailed) clock_gettime(CLOCK_REALTIME, &start);    
      
      char* output8 = func_answer_query_8 (token, hotel_id, begin_date, end_date, reservations_hash_table); // o output é gerado em forma de inteiro
      if (output8 != NULL) fprintf(file_output8, "%s", output8);
      fclose(file_output8);
      
      if (detailed) {
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer8);
        if (resultado == 0) printf("A query 8 está correta\n");
        else if (resultado > 0) printf("A query 8 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 8 é %.6f segundos\n\n", time_spent);
      }
      free(input_prefix);
      free(output8);
    }
    else if (strcmp(token, "9") == 0 || strcmp(token, "9F") == 0) { // caso o input seja direcionado à query 9
      char* input_prefix = strdup(token);
      char buffer9[40];
      sprintf(buffer9,FILENAME_FORMAT,counter);
      FILE* file_output9 = fopen(buffer9,"w");

      char* token = strtok(NULL, "\0"); 
      func_remove_quotation_marks(token);

      if (detailed) clock_gettime(CLOCK_REALTIME, &start);    
      
      char* output9 = func_answer_query_9(input_prefix, token, users_hash_table); // o output é gerado, já formatado corretamente
      if (output9 != NULL) fprintf(file_output9,"%s",output9);
      fclose(file_output9);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer9);
        if (resultado == 0) printf("A query 9 está correta\n");
        else if (resultado > 0) printf("A query 9 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 9 é %.6f segundos\n\n", time_spent);
      } 

      free(input_prefix);
      free(output9);
    }
    else if (strcmp(token, "10") == 0 || strcmp(token, "10F") == 0) { // caso o input seja direcionado à query 10
      char* input_prefix = strdup(token);
      char buffer10[40];
      sprintf(buffer10,FILENAME_FORMAT,counter);
      FILE* file_output10 = fopen(buffer10,"w");

      char* token = strtok(NULL, "\0"); 
      if (token != NULL) {
        func_remove_quotation_marks(token);
      }

      if (detailed) clock_gettime(CLOCK_REALTIME, &start);    
      
      char* output10 = func_answer_query_10(input_prefix, token, account_registrations_by_date, number_reservations_by_date, number_flights_by_date, number_passengers_by_date, number_unique_passengers_by_day, number_unique_passengers_by_month, number_unique_passengers_by_year); 
      if (output10 != NULL) fprintf(file_output10,"%s",output10);
      fclose(file_output10);
      
      if (detailed) { 
        clock_gettime(CLOCK_REALTIME, &end);
        char output_buffer[60];
        sprintf(output_buffer,"%s/command%d_output.txt",output_path,counter);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        int resultado = func_compare_lines(output_buffer, buffer10);
        if (resultado == 0) printf("A query 10 está correta\n");
        else if (resultado > 0) printf("A query 10 está incorreta e difere pela primeira vez na linha %d\n", resultado);
        else return 0;
        printf("O tempo de execução da query 10 é %.6f segundos\n\n", time_spent);
      }  

      free(input_prefix);
      free(output10);
    }
    else return 0;

  return 1;
}

int input_line (char* input_path, char* output_path, GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table, GHashTable* passengers_hash_table, int account_registrations_by_date[100][12][31], int number_reservations_by_date[100][12][31], int number_flights_by_date[100][12][31], int number_passengers_by_date[100][12][31], int number_unique_passengers_by_day[100][12][31], int number_unique_passengers_by_month[100][12], int number_unique_passengers_by_year[100], int detailed) {

  FILE *file = fopen(input_path, "r");
  if (file == NULL) return 0;

  char line[500]; // tamanho máximo da linha
  int counter = 1;


  while (fgets(line, sizeof(line), file) != NULL) {
    // remove o caractere '\n' da linha, se presente
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }
    if (func_input(line, output_path, flights_hash_table, users_hash_table,reservations_hash_table,passengers_hash_table, account_registrations_by_date, number_reservations_by_date, number_flights_by_date, number_passengers_by_date, number_unique_passengers_by_day, number_unique_passengers_by_month, number_unique_passengers_by_year, counter, detailed) == 0) return 0;
    counter++;
  }
  fclose(file);

  return 1;
}
