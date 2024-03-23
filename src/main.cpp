#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int main() {
    CarsList all_cars = {(CarNode**) calloc(100, sizeof(CarNode)), 0};
    printf("List of commands:\n0 - Close program\n1 - Add node\n2 - Find node\n3 - Print all nodes\n4 - Sort\n");
    while (true) {
        UserTask user_task = (UserTask) get_user_task();
        switch (user_task) {
            case CLOSE_PROGRAM:
                close_program(&all_cars);
                break;
            case ADD_NODE:
                add_node(&all_cars);
                break;
            case FIND_NODE:
                find_node(&all_cars);
                break;
            case PRINT_LIST:
                print_list(&all_cars);
                break;
            case SORT_LIST:
                sort_list(&all_cars);
                break;
            default:
                printf("Your input doesn't match with any of command. Input again\n");
                break;
        }
    }
}

void clean_input() {
    while (getchar() != '\n');
}

int get_user_task() {
    int user_task = 0;
    printf("Choose command: ");
    scanf("%d", &user_task);
    clean_input();
    return user_task;
}

void close_program(CarsList* all_cars) {
    char* output_string = (char*) calloc(all_cars->len, sizeof(CarNode));
    for (int i = 0; i < all_cars->len; i++) {
        CarNode* node = all_cars->list[i];
        char* temp = (char*) calloc(1, sizeof(CarNode));
        sprintf(temp, "%s; %s; %s; %s; %s; %s\n", node->p_name, node->p_birthday, node->p_phone,
                node->c_sign, node->c_passport, node->c_police_code);
        strcat(output_string, temp);
        free(temp);
    }
    FILE* file = fopen("list.txt", "w");
    fputs(output_string, file);
    fclose(file);
    free(output_string);
    printf("The program is corrently terminated\n");
    exit(0);
}

void add_node(CarsList* all_cars) {
    printf("\nEnter data using next template:\n"
            "Name; Birthday; Phone; Car_Sign; Car_Passport; Code_of_transport_police\n");
    CarNode* car = (CarNode*) calloc(1, sizeof(CarNode));
    scanf("%[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^\n]", car->p_name, car->p_birthday, 
            car->p_phone, car->c_sign, car->c_passport, car->c_police_code);
    clean_input();
    all_cars->list[all_cars->len] = car;
    all_cars->len++;
    printf("Node has added\n\n");
}

void find_node(CarsList* all_cars) {
    printf("\nChoose info to search:\n1 - Name\n2 - Birthday\n3 - Phone\n4 - Car Sign\n"
            "5 - Car Passport\n6 - Transport Police Code\n");
    NodeField field;
    scanf("%d", (int*) &field);
    clean_input();
    if (field < 0 || field > 5) {
        printf("Entered wrong field code\n");
        return;
    }

    printf("Enter searcing data: ");
    char* user_input = (char*) calloc(21, sizeof(char));
    scanf("%[^\n]", user_input);
    clean_input();

    printf("Founded data:\n");
    for (int i = 0; i < all_cars->len; i++) {
        CarNode* node = all_cars->list[i];
        int diff = 21;
        switch (field) {
            case NAME:
                diff = strcmp(node->p_name, user_input);
                break;
            case BIRTHDAY:
                diff = strcmp(node->p_birthday, user_input);
                break;
            case PHONE:
                diff = strcmp(node->p_phone, user_input);
                break;
            case SIGN:
                diff = strcmp(node->c_sign, user_input);
                break;
            case PASSPORT:
                diff = strcmp(node->c_passport, user_input);
                break;
            case POLICE_NUM:
                diff = strcmp(node->c_police_code, user_input);
                break;
            default:
                printf("Error");
                break;
        }
        if (diff == 0) {
            printf("%d: %s; %s; %s; %s; %s; %s\n", i, node->p_name, node->p_birthday, node->p_phone,
                    node->c_sign, node->c_passport, node->c_police_code);
        }
    }
}

void print_list(CarsList* all_cars) {
    printf("\n");
    for (int i = 0; i < all_cars->len; i++) {
        CarNode* node = all_cars->list[i];
        printf("%d: %s; %s; %s; %s; %s; %s\n", i, node->p_name, node->p_birthday, node->p_phone,
                    node->c_sign, node->c_passport, node->c_police_code);
    }
}

void sort_list(CarsList* all_cars) {
    printf("\nChoose info to search:\n1 - Name\n2 - Birthday\n3 - Phone\n4 - Car Sign\n"
            "5 - Car Passport\n6 - Transport Police Code\n");
    NodeField field;
    scanf("%d", (int*) &field);
    clean_input();
    if (field < 0 || field > 5) {
        printf("Entered wrong field code\n");
        return;
    }

    bool is_sorted = false;
    CarNode* node_1 = nullptr;
    CarNode* node_2 = nullptr;
    int diff = 0;

    while (!is_sorted) {
        is_sorted = true;
        for (int i = 0; i < all_cars->len - 1; i++) {
            node_1 = all_cars->list[i];
            node_2 = all_cars->list[i+1];
            switch (field) {
                case NAME:
                    diff = strcmp(node_1->p_name, node_2->p_name);
                    break;
                case BIRTHDAY:
                    diff = strcmp(node_1->p_birthday, node_2->p_birthday);
                    break;
                case PHONE:
                    diff = strcmp(node_1->p_phone, node_2->p_phone);
                    break;
                case SIGN:
                    diff = strcmp(node_1->c_sign, node_2->c_sign);
                    break;
                case PASSPORT:
                    diff = strcmp(node_1->c_passport, node_2->c_passport);
                    break;
                case POLICE_NUM:
                    diff = strcmp(node_1->c_police_code, node_2->c_police_code);
                    break;
                default:
                    printf("Ërror");
                    break;
            }
            if (diff > 0) {
                is_sorted = false;
                all_cars->list[i] = node_2;
                all_cars->list[i+1] = node_1;
            }
        }
    }
}