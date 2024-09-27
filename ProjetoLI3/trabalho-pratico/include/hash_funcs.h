#ifndef HASH_FUNCS_H
#define HASH_FUNCS_H

/**
 * Realiza as operações finais de libertação de memória para as Hash Tables
 * associadas a voos, utilizadores, reservas e passageiros.
 *
 * @param flights_hash_table Hash Tables de voos.
 * @param users_hash_table Hash Tables de utilizadores.
 * @param reservations_hash_table Hash Tables de reservas.
 * @param passengers_hash_table Hash Tables de passageiros.
 */
void func_clean_hash(GHashTable* flights_hash_table, GHashTable* users_hash_table, GHashTable* reservations_hash_table, GHashTable* passengers_hash_table);


#endif
