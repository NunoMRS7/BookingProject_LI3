#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include "validation.h"



int func_valid_string(char* string) {
    return (strlen(string) > 0);
}

int func_valid_total_seats(char* total_seats) {
    if (strlen(total_seats) == 0) return 0;
    return (atoi(total_seats) > 0);
} 

int func_valid_acronym(char* acronym, size_t number_chars) {
    return (strlen(acronym) == number_chars);
}

int func_valid_date_3(char* date) { 
    if (strlen(date) != 10) return 0;
    int year, month, day;
    if (sscanf(date,"%d/%d/%d",&year, &month, &day) != 3) return 0;
    return (year >= 1000 && year <= 9999) && (month >= 1 && month <= 12) && (day >= 1 && day <= 31);
}

int func_valid_date_6(char* date) {
    if (strlen(date) != 19) return 0;
    int year, month, day, hour, minute, second;
    if (sscanf(date,"%d/%d/%d %d:%d:%d",&year, &month, &day, &hour, &minute, &second) != 6) return 0;
    return (year >= 1000 && year <= 9999) && (month >= 1 && month <= 12) && (day >= 1 && day <= 31) && (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59) && (second >= 0 && second <= 59);
} 

int func_date_after_date_3(char* date1, char* date2) { // cuidado com a ordem na account_creation after erej
    int year1, month1, day1;
    if (sscanf(date1, "%d/%d/%d", &year1, &month1, &day1) != 3) return 0;
    int year2, month2, day2;
    if (sscanf(date2, "%d/%d/%d", &year2, &month2, &day2) != 3) return 0;

    if (year2 == year1 && month2 == month1 && day2 > day1) return 1;
    if (year2 == year1 && month2 > month1) return 1;
    if (year2 > year1) return 1;
    return 0;
}

int func_date_after_date_6(char* date1, char* date2) {
    int year1, month1, day1, hour1, minute1, second1;
    if (sscanf(date1, "%d/%d/%d %d:%d:%d", &year1, &month1, &day1, &hour1, &minute1, &second1) != 6) return 0;
    int year2, month2, day2, hour2, minute2, second2;
    if (sscanf(date2, "%d/%d/%d %d:%d:%d", &year2, &month2, &day2, &hour2, &minute2, &second2) != 6) return 0;

    if (year2 == year1 && month2 == month1 && day2 == day1 && hour2 == hour1 && minute2 == minute1 && second2 > second1) return 1;
    if (year2 == year1 && month2 == month1 && day2 == day1 && hour2 == hour1 && minute2 >  minute1) return 1;
    if (year2 == year1 && month2 == month1 && day2 == day1 && hour2 >  hour1) return 1;
    if (year2 == year1 && month2 == month1 && day2 >  day1) return 1;
    if (year2 == year1 && month2 >  month1) return 1;
    if (year2 >  year1) return 1;
    return 0;
}

int func_valid_email(char* user_email) {
    char email_username[40];
    char email_domain[40];
    char email_TLD[10];

    if (sscanf(user_email, "%39[^@]@%39[^.].%9s", email_username, email_domain, email_TLD) == 3) {
        if (strlen(email_TLD) >= 2) {
            return 1;
        }
    }

    return 0;
}

int func_valid_phone_number(char* user_phone_number) {
    char first_digits[4]; 
    char second_digits[4]; 
    char third_digits[4]; 
    char all_digits[10];
    
    if (sscanf(user_phone_number, "(351) %3s %3s %3s", first_digits, second_digits, third_digits) == 3) {
        if (strlen(first_digits) == 3 && strlen(second_digits) == 3 && strlen(third_digits) == 3) {
            return 1;
        }
    } else if (sscanf(user_phone_number, "(351) %9s", all_digits) == 1) {
        if (strlen(all_digits) == 9) {
            return 1;
        }
    } else if (sscanf(user_phone_number, "%3s %3s %3s", first_digits, second_digits, third_digits) == 3) {
        if (strlen(first_digits) == 3 && strlen(second_digits) == 3 && strlen(third_digits) == 3) {
            return 1;
        }
    } else if (sscanf(user_phone_number, "%9s", all_digits) == 1) {
        if (strlen(all_digits) == 9) {
            return 1;
        }
    } else if (sscanf(user_phone_number, "+351%9s", all_digits) == 1) {
        if (strlen(all_digits) == 9) {
            return 1;
        }
    }
    return 0;
}

int func_valid_account_status (char* user_account_status) {
    if (strcasecmp(user_account_status,"active") == 0 || strcasecmp(user_account_status,"inactive") == 0) return 1;
    return 0;
}

int func_valid_grade(char* grade) {
    if (strlen(grade) != 1) return 0;
    int grade_int;
    if (sscanf(grade,"%d",&grade_int) != 1) return 0;
    return (grade_int >= 1 && grade_int <= 5);
}

int func_valid_city_tax(char* reservation_city_tax) {
    if (strlen(reservation_city_tax) == 0 || strchr(reservation_city_tax,'.') != NULL) return 0; // se existir um '.', então o número não é inteiro
    int city_tax;
    if (sscanf(reservation_city_tax,"%d",&city_tax) != 1) return 0;
    return (city_tax >= 0);
} 

int func_valid_price_per_night(char* reservation_price_per_night) {
    if (strlen(reservation_price_per_night) == 0 || strchr(reservation_price_per_night,'.') != NULL) return 0; // se existir um '.', então o número não é inteiro
    int price_per_night;
    if (sscanf(reservation_price_per_night,"%d",&price_per_night) != 1) return 0;
    return (price_per_night > 0);
}

int func_valid_includes_breakfast(char* reservation_includes_breakfast) {
    return (strlen(reservation_includes_breakfast) == 0 || 
            strcasecmp(reservation_includes_breakfast,"f") == 0 || 
            strcasecmp(reservation_includes_breakfast,"false") == 0 || 
            strcmp(reservation_includes_breakfast,"0") == 0 || 
            strcasecmp(reservation_includes_breakfast,"t") == 0 || 
            strcasecmp(reservation_includes_breakfast,"true") == 0 || 
            strcmp(reservation_includes_breakfast,"1") == 0);
}

