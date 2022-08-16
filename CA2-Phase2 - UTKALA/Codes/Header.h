#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buyer {
    char* username;
    char* password;
    int money;
    int num_of_goods;
    struct buyer* next;
};

struct seller {
    char* username;
    char* password;
    int money;
    int num_of_goods;
    struct seller* next;
};

struct goods {
    char* goods_name;
    int goods_price;
    int goods_count;
    float rating;
    int num_of_rates;
    int rate_able;
    char* goods_owner;
    char* goods_past_owner;
    struct goods* next;
    struct goods* right;
    struct goods* left;
};

struct goods* new_node(struct goods* node);
struct goods* binary_tree_generator(struct goods* goods, int start, int end);
char* cmd_string_reader();
char* file_string_reader(FILE* input);
int user_checker_buyers(int num, struct buyer* head, char* username);
int user_checker_sellers(int num, struct seller* head, char* username);
void signup(int logged_in_seller_num, int logged_in_buyer_num, char* user_str_input, int* buyer_num, struct buyer** buyers, struct seller** sellers, int* seller_num);
int signup_from_file(int logged_in_seller_num, int logged_in_buyer_num, char* user_str_input, int* buyer_num, struct buyer** buyers, struct seller** sellers, int* seller_num);
void login_checker(struct buyer** buyers, struct seller** sellers, char* user_str_input, int buyer_num, int seller_num, int* logged_in_buyer_num, int* logged_in_seller_num);
void logout(int* logged_in_seller_num, int* logged_in_buyer_num);
void view_account(struct buyer** buyers, int logged_in_buyer_num, struct seller** sellers, int logged_in_seller_num, struct goods** goods);
void add_goods(int logged_in_seller_num, int logged_in_buyer_num, struct seller** sellers, char* user_str_input, int num_of_sellers, struct goods** goods, int* num_of_goods);
int add_goods_from_file(char* user_str_input, struct goods** goods, int* num_of_goods);
void file_reader(struct goods** goods, int* num_of_goods, int logged_in_seller_num, int logged_in_buyer_num, int* buyer_num, struct buyer** buyers, struct seller** sellers, int* seller_num);
int sort_by_name(struct goods* goods);
void show_goods(int logged_in_buyer_num, int logged_in_seller_num, struct goods** goods);
void buy_fun(struct buyer** buyers, struct seller** sellers, struct goods** goods, int logged_in_buyer_num, char* user_str_input, int seller_num, int logged_in_seller_num, int* num_of_goods);
void deposit(char* user_str_input, int logged_in_buyer_num, int logged_in_seller_num, struct buyer** buyers);
void file_saver(struct buyer** buyers, struct seller** sellers, struct goods** goods, int num_of_goods);
void remove_goods(struct goods* root, struct seller** sellers, struct goods** goods, char* user_str_input, int logged_in_seller_num, int* num_of_goods);
void change_goods_price(struct seller** sellers, struct goods** goods, char* user_str_input, int logged_in_seller_num);
void rating(struct buyer** buyers, struct seller** sellers, struct goods** goods, char* user_str_input, int logged_in_buyer_num, int logged_in_seller_num);
void search(char* input, int logged_in_buyer_num, int logged_in_seller_num, struct goods** goods);
void free_buyers(struct buyer* buyers);
void free_sellers(struct seller* sellers);
void free_goods(struct goods* goods);
void free_pointers(char* address_of_input, struct buyer** buyers, struct seller** sellers, struct goods** goods);
struct goods* sort_and_binary_tree_make(struct goods** goods, int num_of_goods);