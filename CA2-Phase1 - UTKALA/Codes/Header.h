#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buyer {
    char* username;
    char* password;
    int money;
    int num_of_goods;
    struct goods** buyergoods;
};

struct seller {
    char* username;
    char* password;
    int money;
    int num_of_goods;
    struct goods** sellergoods;
};

struct goods {
    char* goods_name;
    int goods_price;
    int goods_count;
    char* goods_seller;
};

struct buyer* signup_buyer(char* username, char* password);
struct seller* signup_seller(char* username, char* password);
char* string__getter_and_maker();
int user_checker_buyers(int num, struct buyer** buyers, char* username);
int user_checker_sellers(int num, struct seller** sellers, char* username);
int signup(int logged_in_seller_num, int logged_in_buyer_num, char* user_str_input, int* buyer_num, struct buyer** buyers, struct seller** sellers, int* seller_num);
void login_checker(struct buyer** buyers, struct seller** sellers, char* user_str_input, int buyer_num, int seller_num, int* logged_in_buyer_num, int* logged_in_seller_num);
void logout(int* logged_in_seller_num, int* logged_in_buyer_num);
void view_account(struct buyer** buyers, int logged_in_buyer_num, struct seller** sellers, int logged_in_seller_num);
int add_goods(int logged_in_seller_num, int logged_in_buyer_num, struct seller** sellers, char* user_str_input, int num_of_sellers);
void show_goods(int logged_in_buyer_num, int logged_in_seller_num, struct buyer** buyers, struct seller** sellers, int buyer_num, int seller_num);
int buy_fun(struct buyer** buyers, struct seller** sellers, int logged_in_buyer_num, char* user_str_input, int seller_num, int logged_in_seller_num);
void deposit(char* user_str_input, int logged_in_buyer_num, int logged_in_seller_num, struct buyer** buyers);
void free_pointers(char* address_of_input, struct buyer** buyers, struct seller** sellers, int buyer_num, int seller_num);