#ifndef VALIDATION_H
#define VALIDATION_H

/**
 * Verifica se uma string é válida.
 *
 * Uma string é considerada válida apenas quando não é vazia.
 * 
 * @param string: A string a ser testada.
 *
 * @return 1 no caso onde foi validada, 0 em caso contrário.
 */
int func_valid_string(char* string);


/**
 * Verifica se o número total de assentos de um avião é válido.
 *
 * O número total de assentos é considerado válido apenas quando não é uma string 
 * vazia e quando o número é maior que 0.
 * 
 * @param total_seats: A string que contém o número total de assentos a 
 * ser testado.
 *
 * @return 1 no caso onde foi validado, 0 em caso contrário.
 */
int func_valid_total_seats(char* total_seats);


/**
 * Verifica se uma sigla é válida.
 *
 * Uma sigla é considerada válida apenas quando tem, especificamente, o número
 * de caracteres passado como argumento.
 * 
 * @param acronym: A string que contém a sigla a ser testada.
 * @param number_chars: O número de caracteres que a sigla deve ter
 *
 * @return 1 no caso onde foi validada, 0 em caso contrário.
 */
int func_valid_acronym(char* acronym, size_t number_chars);


/**
 * Verifica se uma data com apenas ano, mês e dia é válida.
 *
 * A data é considerada válida quando a sua string tem exatamente
 * 10 caracteres e quando os valores de ano, mês e dia são válidos.
 * 
 * @param date: A string que contém a data a ser testada.
 *
 * @return 1 no caso onde foi validada, 0 em caso contrário.
 */
int func_valid_date_3(char* date);


/**
 * Verifica se uma data com ano, mês, dia, hora, minuto e segundo é válida.
 *
 * A data é considerada válida quando a sua string tem exatamente 19 caracteres
 * e quando os valores de ano, mês, dia, hora, minuto e segundo são válidos.
 * 
 * @param date: A string que contém a data ser testada.
 *
 * @return 1 no caso onde foi validada, 0 em caso contrário.
 */
int func_valid_date_6(char* date);


/**
 * Verifica se uma data é inferior a uma outra data. Ambas as datas têm apenas
 * ano, mês e dia.
 * 
 * @param date1: A string que contém uma das datas a ser testada (data anterior).
 * @param date2: A string que contém a outra data a ser testada (data posterior).
 *
 * @return 1 no caso onde foram validadas, 0 em caso contrário.
 */
int func_date_after_date_3(char* date1, char* date2);


/**
 * Verifica se uma data é inferior a uma outra data. Ambas as datas têm ano,
 * mês, dia, hora, minuto e segundo.
 * 
 * @param date1: A string que contém uma das datas a ser testada (data anterior).
 * @param date2: A string que contém a outra data a ser testada (data posterior).
 *
 * @return 1 no caso onde foram validadas, 0 em caso contrário.
 */
int func_date_after_date_6(char* date1, char* date2);


/**
 * Verifica se o email de um utilizador, de formato "<username>@<domain>.<TLD>",
 * é válido.
 *
 * O email é considerado válido quando todos o username, domain e TLD são strings 
 * não vazias, necessitando a última de ter pelo menos dois caracteres.
 * 
 * @param user_email: A string que contém o email de um utiliador a ser testado.
 *
 * @return 1 no caso onde foi validado, 0 em caso contrário.
 */
int func_valid_email(char* user_email);


/**
 * Verifica se o número de telemóvel de um utilizador é válido.
 *
 * O número de telemóvel é considerado válido quando segue um dos seguintes formatos:
 * "(351) nnn nnn nnn", "(351) nnnnnnnnn", "nnn nnn nnn", "nnnnnnnnn", "+351nnnnnnnnn".
 * 
 * @param user_phone_number: A string que contém o número de telemóvel a ser testado.
 *
 * @return 1 no caso onde foi validado, 0 em caso contrário.
 */
int func_valid_phone_number(char* user_phone_number);


/**
 * Verifica se o estado de conta de utilizador é válido.
 *
 * O estado de conta é considerado válido quando é uma variação da string "active" ou
 * da string "inactive".
 * 
 * @param user_account_status: A string que contém o estado de conta a ser testado.
 *
 * @return 1 no caso onde foi validado, 0 em caso contrário.
 */
int func_valid_account_status (char* user_account_status);


/**
 * Verifica se uma classificação é válida.
 *
 * Uma classificação é considerada válida apenas quando é uma string 
 * com um único caractere, e quando o número se encontra entre 1 e 5.
 * 
 * @param grade: A string que contém a classificação a ser testada.
 *
 * @return 1 no caso onde foi validada, 0 em caso contrário.
 */
int func_valid_grade(char* grade);


/**
 * Verifica se o imposto da cidade de uma reserva é válido.
 *
 * O imposto da cidade é considerado válido apenas quando não é uma string vazia,
 * sem a presença do caractere '.', e quando o valor é maior do que 0.
 * 
 * @param reservation_city_tax: A string que contém o imposto da cidade a 
 * ser testado.
 *
 * @return 1 no caso onde foi validado, 0 em caso contrário.
 */
int func_valid_city_tax(char* reservation_city_tax);


/**
 * Verifica se o preço por noite de uma reserva é válido.
 *
 * O preço por noite é considerado válido apenas quando não é uma string vazia,
 * sem a presença do caractere '.', e quando o valor é maior do que 0.
 * 
 * @param reservation_price_per_night: A string que contém o preço por noite a 
 * ser testado.
 *
 * @return 1 no caso onde foi validado, 0 em caso contrário.
 */
int func_valid_price_per_night(char* reservation_price_per_night);


/**
 * Verifica se a informação de que uma reserva inclui ou não pequeno-almoço é válida.
 *
 * A informação é considerada válida quando é uma variação das strings "" ou "f" ou
 * "false" ou "0" ou "t" ou "true" ou "1".
 * 
 * @param reservation_includes_breakfast: A string que contém a informação a ser testada.
 *
 * @return 1 no caso onde foi validada, 0 em caso contrário.
 */
int func_valid_includes_breakfast(char* reservation_includes_breakfast);


#endif
