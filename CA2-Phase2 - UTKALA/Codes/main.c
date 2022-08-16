#include "Header.h"

int main() {
    int buyer_num = 0, seller_num = 0, logged_in_buyer_num = -1, logged_in_seller_num = -1, Flag = 1, num_of_goods = 0;
    struct buyer** buyers = NULL;
    struct seller** sellers = NULL;
    struct goods** goods = NULL, * root = NULL;
    char* user_str_input = NULL, * address_of_input = NULL, * command = NULL;
    buyers = (struct buyer**)malloc(sizeof(struct buyer*));                   //allocating the first row of the array
    sellers = (struct seller**)malloc(sizeof(struct seller*));
    goods = (struct goods**)malloc(sizeof(struct gooods*));
    if (goods == NULL || sellers == NULL || buyers == NULL) {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    *goods = NULL;
    *buyers = NULL;
    *sellers = NULL;
    file_reader(goods, &num_of_goods, logged_in_seller_num, logged_in_buyer_num, &buyer_num, buyers, sellers, &seller_num);
    printf("welocme to UTKALA!\n\nYou can terminate the program by command 'exit'.");
    int last_num_of_goods = num_of_goods;
    while (1) {
        printf("\n-------------------\n");
        printf("enter command:\n");
        user_str_input = cmd_string_reader();                                  //getting the input string
        address_of_input = user_str_input;
        command = strtok_s(user_str_input, " ", &user_str_input);              //seperating the first part of the string as the command
        if (command == NULL) {
            printf("invalid command\n");
            continue;
        }
        if (strcmp(command, "signup") == 0)                                    //checking the input with the defined commands. if a match found the related function will be called.
            signup(logged_in_seller_num, logged_in_buyer_num, user_str_input, &buyer_num, buyers, sellers, &seller_num);
        else if (strcmp(command, "login") == 0)
            login_checker(buyers, sellers, user_str_input, buyer_num, seller_num, &logged_in_buyer_num, &logged_in_seller_num);
        else if (strcmp(command, "logout") == 0)
            logout(&logged_in_seller_num, &logged_in_buyer_num);
        else if (strcmp(command, "view") == 0)
            view_account(buyers, logged_in_buyer_num, sellers, logged_in_seller_num, goods);
        else if (strcmp(command, "deposit") == 0)
            deposit(user_str_input, logged_in_buyer_num, logged_in_seller_num, buyers);
        else if (strcmp(command, "show_goods") == 0)
            show_goods(logged_in_buyer_num, logged_in_seller_num, goods);
        else if (strcmp(command, "add_goods") == 0)
            add_goods(logged_in_seller_num, logged_in_buyer_num, sellers, user_str_input, seller_num, goods, &num_of_goods);
        else if (strcmp(command, "buy") == 0)
            buy_fun(buyers, sellers, goods, logged_in_buyer_num, user_str_input, seller_num, logged_in_seller_num, &num_of_goods);
        else if (strcmp(command, "remove_goods") == 0)
            remove_goods(root, sellers, goods, user_str_input, logged_in_seller_num, &num_of_goods);
        else if (strcmp(command, "change_goods_price") == 0)
            change_goods_price(sellers, goods, user_str_input, logged_in_seller_num);
        else if (strcmp(command, "rate_goods") == 0)
            rating(buyers, sellers, goods, user_str_input, logged_in_buyer_num, logged_in_seller_num);
        else if (strcmp(command, "search") == 0)
            search(user_str_input, logged_in_buyer_num, logged_in_seller_num, goods);
        else if (strcmp(command, "exit") == 0) {
            printf("program closed successfully.\n");
            break;
        }
        else {
            printf("invalid command\n");
            free(address_of_input);                                           //freeing the input because it will be allocated again at the first of the loop
            continue;
        }
        file_saver(buyers, sellers, goods, num_of_goods);
        if (last_num_of_goods != num_of_goods) {
            root = sort_and_binary_tree_make(goods, num_of_goods);
            last_num_of_goods = num_of_goods;
        }
        free(address_of_input);                                              //freeing the input because it will be allocated again at the first of the loop
    }
    free_pointers(address_of_input, buyers, sellers, goods);                 //the program is about to be closed, so all the allocated memory should be freed
    return 0;
}