#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* func_output_1_reservations (char* input_prefix, char* hotel_id, char* hotel_name, int hotel_stars, char* begin_date, char* end_date, char* includes_breakfast, int number_nights, double total_price) {
    // é necessário libertar esta memória assim que possível, o que é feito no input.c
    char* output1 = malloc(220*sizeof(char)); 

    // formata a string de output com base no prefixo de entrada
    if (strcmp(input_prefix,"1F") == 0) snprintf(output1,220,"--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %d\nbegin_date: %s\nend_date: %s\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f\n",hotel_id,hotel_name,hotel_stars,begin_date,end_date,includes_breakfast,number_nights,total_price);
    else if (strcmp(input_prefix,"1") == 0) snprintf(output1,220,"%s;%s;%d;%s;%s;%s;%d;%.3f\n",hotel_id,hotel_name,hotel_stars,begin_date,end_date,includes_breakfast,number_nights,total_price);

    return output1;
}


char* func_output_1_flights (char* input_prefix, char* airline, char* plane_model, char* origin, char* destination, char* schedule_departure_date, char* schedule_arrival_date, int number_passengers, int time_delay) {
    // é necessário libertar esta memória assim que possível, o que é feito no input.c
    char* output1 = malloc(220*sizeof(char));
    
    // formata a string de output com base no prefixo de entrada
    if (strcmp(input_prefix,"1F") == 0) snprintf(output1,220,"--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d\n", airline, plane_model, origin, destination, schedule_departure_date, schedule_arrival_date, number_passengers, time_delay);
    else if (strcmp(input_prefix,"1") == 0) snprintf(output1,220,"%s;%s;%s;%s;%s;%s;%d;%d\n", airline, plane_model, origin, destination, schedule_departure_date, schedule_arrival_date, number_passengers, time_delay);

    return output1;
}


char* func_output_1_users (char*  input_prefix, char* name, char* sex, int age, char*  country_code, char* passport, int number_flights, int number_reservations, double total_spent) {
    // é necessário libertar esta memória assim que possível, o que é feito no input.c
    char* output1 = malloc(220*sizeof(char));

    // formata a string de output com base no prefixo de entrada
    if (strcmp(input_prefix,"1F") == 0) snprintf(output1,220,"--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f\n",name,sex,age,country_code,passport,number_flights,number_reservations, total_spent);
    else if (strcmp(input_prefix,"1") == 0) snprintf(output1,220,"%s;%s;%d;%s;%s;%d;%d;%.3f\n",name,sex,age,country_code,passport,number_flights,number_reservations,total_spent);

    return output1;
}


void func_output_2 (char* input_prefix, char* output2, int i, int key, int size_array, char* id, char* general_date, char* type) {
    char temp[70]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"2F") == 0) {  
        if (key == 1) snprintf(temp, 70, "--- %d ---\nid: %s\ndate: %s\ntype: %s\n\n",(i+1),id,general_date,type);
        else snprintf(temp, 70, "--- %d ---\nid: %s\ndate: %s\n\n",(i+1),id,general_date);
    
        // só é utilizado um \n no fim da última linha
        if (size_array > 0 && i == size_array-1) temp[strlen(temp)-1] = '\0';
    }
    else if (strcmp(input_prefix,"2") == 0) {  
        if (key == 1) snprintf(temp, 70, "%s;%s;%s\n", id,general_date,type);
        else snprintf(temp, 70, "%s;%s\n",id,general_date);      
    }
    // concatena a linha formatada ao output
    strcat(output2,temp);
}


char* func_output_3 (char* input_prefix, double rating) {
    // é necessário libertar esta memória assim que possível, o que é feito no input.c
    char* output3 = malloc(30*sizeof(char));

    // formata a string de output com base no prefixo de entrada
    if (strcmp(input_prefix,"3F") == 0) {
        snprintf(output3, 30, "--- 1 ---\nrating: %.3f\n", rating);
    } else if (strcmp(input_prefix,"3") == 0) {
        snprintf(output3, 30, "%.3f\n", rating);
    }
    return output3;
}


void func_output_4 (char* input_prefix, char* output4, int i, int size_array, char* id, char* begin_date, char* end_date, char* user_id, int rating, double total_price) {
    char temp[150]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"4F") == 0) {
        snprintf(temp, 150, "--- %d ---\nid: %s\nbegin_date: %s\nend_date: %s\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n\n", (i+1), id, begin_date, end_date, user_id, rating, total_price);

        // só é utilizado um \n no fim da última linha
        if (size_array > 0 && i == size_array-1) temp[strlen(temp)-1] = '\0';
    }
    else if (strcmp(input_prefix,"4") == 0) {
        snprintf(temp, 150, "%s;%s;%s;%s;%d;%.3f\n", id, begin_date, end_date, user_id, rating, total_price);
    }
    // concatena a linha formatada ao output
    strcat(output4,temp);
}


void func_output_5 (char* input_prefix, char* output5, int i, int size_array, char* flight_id, char* schedule_departure_date_string, char* destination, char* airline, char* plane_model) {
    char temp[155]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"5F") == 0) {
        snprintf(temp, 155,"--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n\n",(i+1),flight_id,schedule_departure_date_string,destination,airline,plane_model);
    
        // só é utilizado um \n no fim da última linha
        if (size_array > 0 && i == size_array-1) temp[strlen(temp)-1] = '\0';
    }
    else if (strcmp(input_prefix,"5") == 0) {
        snprintf(temp, 155,"%s;%s;%s;%s;%s\n",flight_id,schedule_departure_date_string,destination,airline,plane_model);
    }
    // concatena a linha formatada ao output
    strcat(output5,temp);
}


void func_output_6 (char* input_prefix, char* output6, int i, int size_array, char* name, int number_passengers) {
    char temp[45]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"6F") == 0) {
        snprintf(temp, 45, "--- %d ---\nname: %s\npassengers: %d\n\n", (i+1), name, number_passengers);
        
        // só é utilizado um \n no fim da última linha
        if (size_array > 0 && i == size_array-1) temp[strlen(temp)-1] = '\0';
    }
    else if (strcmp(input_prefix,"6") == 0) {
        snprintf(temp, 45, "%s;%d\n", name, number_passengers);
    }
    // concatena a linha formatada ao output
    strcat(output6, temp);
}


void func_output_7 (char* input_prefix, char* output7, int i, int size_array, char* origin, int median) {
    char temp[45]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"7F") == 0) {  
        snprintf(temp, 45,"--- %d ---\nname: %s\nmedian: %d\n\n",(i+1), origin, median);

        // só é utilizado um \n no fim da última linha
        if (size_array > 0 && i == size_array-1) temp[strlen(temp)-1] = '\0';
    }
    else if (strcmp(input_prefix,"7") == 0) {      
        snprintf(temp, 45,"%s;%d\n", origin, median);
    }
    // concatena a linha formatada ao output
    strcat(output7,temp);
}


char* func_output_8 (char* input_prefix, int revenue) {
    // é necessário libertar esta memória assim que possível, o que é feito no input.c
    char* output8 = malloc(30*sizeof(char));

    // formata a string de output com base no prefixo de entrada
    if (strcmp(input_prefix,"8F") == 0) snprintf(output8, 30, "--- 1 ---\nrevenue: %d\n", revenue);
    else if (strcmp(input_prefix,"8") == 0) snprintf(output8, 30, "%d\n", revenue);

    return output8;
}


void func_output_9 (char* input_prefix, char* output9, int i, int size_array, char* user_id, char* user_name) {
    char temp[80]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"9F") == 0) {
        snprintf(temp, 80,"--- %d ---\nid: %s\nname: %s\n\n",(i+1), user_id, user_name);
     
        // só é utilizado um \n no fim da última linha
        if (size_array > 0 && i == size_array-1) temp[strlen(temp)-1] = '\0';
    } 
    else if (strcmp(input_prefix,"9") == 0) {
        snprintf(temp, 80,"%s;%s\n", user_id, user_name);
    }
    // concatena a linha formatada ao output
    strcat(output9,temp);
}




void func_output_10_year (char* input_prefix, char* output10, int* counter, int year, int total_account_registrations, int total_flights, int total_passengers, int number_unique_passengers_by_year, int total_reservations) {
    char temp[115]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"10F") == 0) {
        snprintf(temp,115,"--- %d ---\nyear: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d\n\n", (*counter), year, total_account_registrations, total_flights, total_passengers, number_unique_passengers_by_year, total_reservations);
    } else if (strcmp(input_prefix,"10") == 0) {
        snprintf(temp,115,"%d;%d;%d;%d;%d;%d\n", year, total_account_registrations, total_flights, total_passengers, number_unique_passengers_by_year, total_reservations);
    }
    // concatena a linha formatada ao output
    strcat(output10,temp);
    (*counter)++;
}




void func_output_10_month (char* input_prefix, char* output10, int* counter, int month, int total_account_registrations, int total_flights, int total_passengers, int number_unique_passengers_by_month, int total_reservations) {
    char temp[115]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"10F") == 0) {
        snprintf(temp,115,"--- %d ---\nmonth: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d\n\n", (*counter), month, total_account_registrations, total_flights, total_passengers, number_unique_passengers_by_month, total_reservations);
    } else if (strcmp(input_prefix,"10") == 0) {
        snprintf(temp,115,"%d;%d;%d;%d;%d;%d\n", month, total_account_registrations, total_flights, total_passengers, number_unique_passengers_by_month, total_reservations);
    }
    // concatena a linha formatada ao output
    strcat(output10,temp);
    (*counter)++;
}



void func_output_10_day (char* input_prefix, char* output10, int* counter, int day, int account_registrations_by_date, int number_flights_by_date, int number_passengers_by_date, int number_unique_passengers_by_day, int number_reservations_by_date) {
    char temp[115]; // linha que será concatenada à string de output
    // formata a linha com base no prefixo de entrada
    if (strcmp(input_prefix,"10F") == 0) {
        snprintf(temp,115,"--- %d ---\nday: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d\n\n", (*counter), day, account_registrations_by_date, number_flights_by_date, number_passengers_by_date, number_unique_passengers_by_day, number_reservations_by_date);
    } else if (strcmp(input_prefix,"10") == 0) {
        snprintf(temp,115,"%d;%d;%d;%d;%d;%d\n", day, account_registrations_by_date, number_flights_by_date, number_passengers_by_date, number_unique_passengers_by_day, number_reservations_by_date);
    }
    // concatena a linha formatada ao output
    strcat(output10,temp);
    (*counter)++;
}
