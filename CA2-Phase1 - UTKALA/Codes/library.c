#include "Header.h"

char* string__getter_and_maker() {                                       //this is going to get the input string
    char* str = NULL;
    char c = 0;
    int i = 0;
    str = (char*)malloc(sizeof(char));                                   //at first it allocates memory with the size of a single character
    if (str == NULL) {
        printf("memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    while (c != '\n') {
        c = getc(stdin);
        str = (char*)realloc(str, (i + 1) * sizeof(char));              //it gets memory for another character every time the loop runs until the user presses enter.
        if (str == NULL) {
            printf("memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        str[i] = c;
        i++;
    }
    str[i - 1] = '\0';                                                  //we'll save null character at the end of the string manually.
    return str;
}

struct buyer* signup_buyer(char* username, char* password) {            //this function will allocate memory for a buyer struct and then saves the data given by the user and returns it
    int user_len = strlen(username);
    int pass_len = strlen(password);
    struct buyer* buyer = (struct buyer*)malloc(sizeof(struct buyer));
    if (buyer == NULL) {
        printf("memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    buyer->username = (char*)malloc((user_len + 1) * sizeof(char));     //allocating enough memory to save username
    if (buyer->username == NULL) {
        printf("memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    buyer->password = (char*)malloc((pass_len + 1) * sizeof(char));     //allocating enough memory to save password
    if (buyer->password == NULL) {
        printf("memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    buyer->money = 0;                                                   //saving the data and then returning it
    buyer->num_of_goods = 0;
    strcpy(buyer->username, username);
    strcpy(buyer->password, password);
    buyer->username[user_len] = '\0';
    buyer->password[pass_len] = '\0';
    return buyer;
}

struct seller* signup_seller(char* username, char* password) {           //this function will allocate memory for a buyer struct and then saves the data given by the user and returns it
    int user_len = strlen(username);
    int pass_len = strlen(password);
    struct seller* seller = (struct seller*)malloc(sizeof(struct seller));
    if (seller == NULL) {
        printf("memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    seller->username = (char*)malloc((user_len + 1) * sizeof(char));     //allocating enough memory to save username
    if (seller->username == NULL) {
        printf("memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    seller->password = (char*)malloc((pass_len + 1) * sizeof(char));     //allocating enough memory to save password
    if (seller->password == NULL) {
        printf("memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    seller->money = 0;                                                   //saving the data and then returning it
    seller->num_of_goods = 0;
    strcpy(seller->username, username);
    strcpy(seller->password, password);
    seller->username[user_len] = '\0';
    seller->password[pass_len] = '\0';
    return seller;
}

int user_checker_buyers(int num, struct buyer** buyers, char* username) { //a loop that checks all the buyers usernames to see if the username is new or not
    int Flag_same = 2;
    for (int i = 0; i < num; i++) {
        if (strcmp(buyers[i]->username, username) == 0) {
            printf("username already taken\n");
            Flag_same = 1;
            break;
        }
    }
    return Flag_same;
}

int user_checker_sellers(int num, struct seller** sellers, char* username) {//a loop that checks all the sellers usernames to see if the username is new or not
    int Flag_same = 2;
    for (int i = 0; i < num; i++) {
        if (strcmp(sellers[i]->username, username) == 0) {
            printf("username already taken\n");
            Flag_same = 1;
            break;
        }
    }
    return Flag_same;
}

int signup(int logged_in_seller_num, int logged_in_buyer_num, char* user_str_input, int* buyer_num, struct buyer** buyers, struct seller** sellers, int* seller_num) {
    int Flag_same = 2;
    if (logged_in_seller_num == -1 && logged_in_buyer_num == -1) {
        char* username = strtok_s(user_str_input, " ", &user_str_input);                        //getting the username's data
        char* password = strtok_s(user_str_input, " ", &user_str_input);
        char* role = strtok_s(user_str_input, " ", &user_str_input);
        if (username == NULL || password == NULL || role == NULL) {                             //checking whether the input is valid or not
            printf("command was incomplete.\n");
            Flag_same = 1;
            return Flag_same;
        }
        if (strcmp(role, "buyer") == 0) {                                                       //if the user wants to signup as a buyer
            Flag_same = user_checker_buyers(*buyer_num, buyers, username);
            if (Flag_same == 1)
                return Flag_same;
            (*buyer_num)++;
            if (*buyer_num == 1)
                buyers[0] = (struct buyer*)malloc(sizeof(struct buyer));                        //if it's the first buyer account, we should malloc
            else
                buyers[0] = (struct buyer*)realloc(buyers[0], *buyer_num * sizeof(struct buyer));//if it's not the first one, we realloc
            if (buyers[0] == NULL) {
                printf("memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            buyers[*buyer_num - 1] = signup_buyer(username, password);                         //now we save the data in an structure, then we assign it
            printf("signup was successful!\n");
        }
        else if (strcmp(role, "seller") == 0) {                                                //if the user wants a seller account, we do just like what we did for buyer
            Flag_same = user_checker_sellers(*seller_num, sellers, username);
            if (Flag_same == 1)
                return Flag_same;
            (*seller_num)++;
            if (*seller_num == 1)
                sellers[0] = (struct seller*)malloc(sizeof(struct seller));
            else
                sellers[0] = (struct seller*)realloc(sellers[0], *seller_num * sizeof(struct seller));
            if (sellers[0] == NULL) {
                printf("memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            sellers[*seller_num - 1] = signup_seller(username, password);
            printf("signup was successful!\n");
        }
        else
            printf("role does not exist.\n");
    }
    else
        printf("please log out first!\n");
    return Flag_same;
}

void login_checker(struct buyer** buyers, struct seller** sellers, char* user_str_input, int buyer_num, int seller_num, int* logged_in_buyer_num, int* logged_in_seller_num) {
    char* username = strtok_s(user_str_input, " ", &user_str_input);                       //getting the user's data
    char* password = strtok_s(user_str_input, " ", &user_str_input);
    char* role = strtok_s(user_str_input, " ", &user_str_input);
    if (username == NULL || password == NULL || role == NULL) {                            //checking whether the data is valid or not
        printf("command was incomplete.\n");
        return;
    }
    int i = 0, j = 0;
    if (strcmp(role, "buyer") == 0) {                                                      //if he wants to log into a buyer's account
        for (i = 0; i < buyer_num; i++) {                                                  //start searching all the buyers to find an account that has the same username and password
            if (strcmp(buyers[i]->username, username) == 0 && strcmp(buyers[i]->password, password) == 0) {
                *logged_in_buyer_num = i;                                                  //if account found, save the related number of it
                break;
            }
            if (strcmp(buyers[i]->username, username) == 0 && strcmp(buyers[i]->password, password) != 0) {
                printf("worng password\n");                                               //maybe username found, but password was incorrect
                i = -2;
                break;
            }
        }
        if (buyer_num == 0)                                                               //maybe there was no username
            printf("username not found.\n");
        else if (i == buyer_num)
            printf("username not found\n");
        if (*logged_in_buyer_num != -1)
            printf("login as a buyer was successful\n");
    }
    if (strcmp(role, "seller") == 0) {                                                    //we'll do the same thing for a user that wants to login as a seller
        for (j = 0; j < seller_num; j++) {
            if (strcmp(sellers[j]->username, username) == 0 && strcmp(sellers[j]->password, password) == 0) {
                *logged_in_seller_num = j;
                break;
            }
            if (strcmp(sellers[j]->username, username) == 0 && strcmp(sellers[j]->password, password) != 0) {
                printf("worng password.\n");
                j = -2;
                break;
            }
        }
        if (seller_num == 0)
            printf("username not found.\n");
        else if (j == seller_num)
            printf("username not found.\n");
        if (*logged_in_seller_num != -1)
            printf("login as a seller was successful.\n");
    }
}

void logout(int* logged_in_seller_num, int* logged_in_buyer_num) {               //it just sets the two numbers that indicates being logged in or not, to -1
    if (*logged_in_seller_num != -1 || *logged_in_buyer_num != -1) {
        *logged_in_seller_num = -1;
        *logged_in_buyer_num = -1;
        printf("you have successfully logged out.\n");
    }
    else
        printf("you already logged out!\n");
}

void view_account(struct buyer** buyers, int logged_in_buyer_num, struct seller** sellers, int logged_in_seller_num) {
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {               // at first, you should be logged in
        printf("please login first.\n");
        return;
    }
    if (logged_in_seller_num != -1) {                                            //if the logged in account is a seller, at first we print his/her info
        printf("username: %s\n", sellers[logged_in_seller_num]->username);
        printf("role: seller\n");
        printf("money: %d\n", sellers[logged_in_seller_num]->money);
        for (int i = 0; i < sellers[logged_in_seller_num]->num_of_goods; i++) {  //then we start printing the goods he/she owns
            printf("-------------------\n");
            printf("goods name: %s\n", sellers[logged_in_seller_num]->sellergoods[i]->goods_name);
            printf("goods price: %d\n", sellers[logged_in_seller_num]->sellergoods[i]->goods_price);
            printf("goods count: %d\n", sellers[logged_in_seller_num]->sellergoods[i]->goods_count);
        }
    }
    else if (logged_in_buyer_num != -1) {                                       //we'll do the same thing if the account is a buyer
        printf("username: %s\n", buyers[logged_in_buyer_num]->username);
        printf("role: buyer\n");
        printf("money: %d\n", buyers[logged_in_buyer_num]->money);
        for (int i = 0; i < buyers[logged_in_buyer_num]->num_of_goods; i++) {
            printf("-------------------\n");
            printf("goods name: %s\n", buyers[logged_in_buyer_num]->buyergoods[i]->goods_name);
            printf("goods price: %d\n", buyers[logged_in_buyer_num]->buyergoods[i]->goods_price);
            printf("goods count: %d\n", buyers[logged_in_buyer_num]->buyergoods[i]->goods_count);
            printf("goods seller: %s\n", buyers[logged_in_buyer_num]->buyergoods[i]->goods_seller);
        }
    }
}

int add_goods(int logged_in_seller_num, int logged_in_buyer_num, struct seller** sellers, char* user_str_input, int num_of_sellers) {
    int good_is_in_stock = 0;
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {
        printf("please login first.\n");
        return 1;
    }
    if (logged_in_seller_num != -1) {                                                     //the logged in account must be a seller because seller's can add goods
        char* new_goods_name = strtok_s(user_str_input, " ", &user_str_input);
        char* newgoodprice = strtok_s(user_str_input, " ", &user_str_input);
        char* new_goods_count1 = strtok_s(user_str_input, " ", &user_str_input);
        if (new_goods_name == NULL || newgoodprice == NULL || new_goods_count1 == NULL) {  //checking if the input is complete or not
            printf("command was incomplete.\n");
            return 1;
        }
        int new_goods_price = atoi(newgoodprice);
        int a = new_goods_price, counter = 0;
        while (a > 0) {
            a = a / 10;
            counter++;
        }
        if (new_goods_price <= 0 || strlen(newgoodprice) != counter) {
            printf("price is invalid.\n");
            return 1;
        }
        for (int i = 0; i < num_of_sellers; i++)                                           //ta's said that the name of the product must be uniqe, so here i'm checking whether it's uniqe or not
            for (int j = 0; j < sellers[i]->num_of_goods; j++) {
                if (strcmp(sellers[i]->sellergoods[j]->goods_name, new_goods_name) == 0) {
                    printf("name already taken.\n");
                    return 1;
                }
            }
        int new_goods_count = atoi(new_goods_count1);
        if (new_goods_count <= 0) {
            printf("good's count is invalid!\n");
            return 1;
        }
        if (sellers[logged_in_seller_num]->num_of_goods >= 1)                             //if the seller already has the product, we should only update the number of it
            for (int i = 0; i < sellers[logged_in_seller_num]->num_of_goods; i++) {
                if (strcmp(sellers[logged_in_seller_num]->sellergoods[i]->goods_name, new_goods_name) == 0 && sellers[logged_in_seller_num]->sellergoods[i]->goods_price == new_goods_price) {
                    sellers[logged_in_seller_num]->sellergoods[i]->goods_count += new_goods_count;
                    good_is_in_stock = 1;
                }
            }
        if (good_is_in_stock == 0) {                                                      //if the product wasn't in the stock:
            sellers[logged_in_seller_num]->num_of_goods++;
            if (sellers[logged_in_seller_num]->num_of_goods == 1) {
                sellers[logged_in_seller_num]->sellergoods = (struct goods**)malloc(sizeof(struct goods*));  //we'll allocate memory for it
                if (sellers[logged_in_seller_num]->sellergoods == NULL) {
                    printf("memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
            }
            sellers[logged_in_seller_num]->sellergoods[sellers[logged_in_seller_num]->num_of_goods - 1] = (struct goods*)malloc(sizeof(struct goods));
            if (sellers[logged_in_seller_num]->sellergoods[sellers[logged_in_seller_num]->num_of_goods - 1] == NULL) {
                printf("memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            sellers[logged_in_seller_num]->sellergoods[sellers[logged_in_seller_num]->num_of_goods - 1]->goods_name = (char*)malloc((strlen(new_goods_name) + 1) * sizeof(char));
            if (sellers[logged_in_seller_num]->sellergoods[sellers[logged_in_seller_num]->num_of_goods - 1]->goods_name == NULL) {
                printf("memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            //saving the data of the product given by the user in the structure defined for it
            strcpy(sellers[logged_in_seller_num]->sellergoods[sellers[logged_in_seller_num]->num_of_goods - 1]->goods_name, new_goods_name);
            sellers[logged_in_seller_num]->sellergoods[sellers[logged_in_seller_num]->num_of_goods - 1]->goods_name[strlen(new_goods_name)] = '\0';
            sellers[logged_in_seller_num]->sellergoods[sellers[logged_in_seller_num]->num_of_goods - 1]->goods_price = new_goods_price;
            sellers[logged_in_seller_num]->sellergoods[sellers[logged_in_seller_num]->num_of_goods - 1]->goods_count = new_goods_count;
        }
        printf("goods added successfully!\n");
    }
    else
        printf("you can not add goods!\n");
    return 2;
}

void show_goods(int logged_in_buyer_num, int logged_in_seller_num, struct buyer** buyers, struct seller** sellers, int buyer_num, int seller_num) {
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {       //someone should log in to user this command
        printf("please login first.\n");
        return;
    }
    for (int i = 0; i < seller_num; i++) {
        for (int j = 0; j < sellers[i]->num_of_goods; j++) {             //starts printing any goods the seller have for sale
            printf("\n");
            printf("seller's username: %s\n", sellers[i]->username);
            printf("goods name: %s\n", sellers[i]->sellergoods[j]->goods_name);
            printf("goods price: %d\n", sellers[i]->sellergoods[j]->goods_price);
            printf("goods count: %d\n", sellers[i]->sellergoods[j]->goods_count);
            printf("-------------------\n");
        }
    }
}

int buy_fun(struct buyer** buyers, struct seller** sellers, int logged_in_buyer_num, char* user_str_input, int seller_num, int logged_in_seller_num) {
    int selected_seller = -1, Flag = 0, Flag_buyer_had = 0;
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {                                    //checks if anyone logged in or not
        printf("please login first.\n");
        return 1;
    }
    if (logged_in_buyer_num != -1 && logged_in_seller_num == -1) {                                    //a buyer must be logged in to buy a product
        char* to_buy_good_name = strtok_s(user_str_input, " ", &user_str_input);
        char* to_buy_good_count1 = strtok_s(user_str_input, " ", &user_str_input);
        char* to_buy_good_seller = strtok_s(user_str_input, " ", &user_str_input);
        if (to_buy_good_count1 == NULL || to_buy_good_name == NULL || to_buy_good_seller == NULL) {   //checking whether the inputs are valid or not
            printf("command is incomplete.\n");
            return 1;
        }
        int to_buy_good_count = atoi(to_buy_good_count1);
        if (to_buy_good_count <= 0) {
            printf("invalid good's count.\n");
            return 1;
        }
        for (int i = 0; i < seller_num; i++)
            if (strcmp(sellers[i]->username, to_buy_good_seller) == 0) {                             //finding the seller of the wanted product
                selected_seller = i;
                break;
            }
        if (selected_seller == -1) {
            printf("seller not found.\n");
            return 1;
        }
        for (int i = 0; i < sellers[selected_seller]->num_of_goods; i++) {                           //start searching inside the products of that seller
            if (strcmp(sellers[selected_seller]->sellergoods[i]->goods_name, to_buy_good_name) == 0 && sellers[selected_seller]->sellergoods[i]->goods_count >= to_buy_good_count && buyers[logged_in_buyer_num]->money >= (to_buy_good_count * sellers[selected_seller]->sellergoods[i]->goods_price)) {
                for (int j = 0; j < buyers[logged_in_buyer_num]->num_of_goods; j++) {               //if the buyer already had some of the wanted product, then we should just increase the number of it
                    if (strcmp(buyers[logged_in_buyer_num]->buyergoods[j]->goods_name, to_buy_good_name) == 0 && sellers[selected_seller]->sellergoods[i]->goods_price == buyers[logged_in_buyer_num]->buyergoods[j]->goods_price) {
                        Flag = 1;
                        buyers[logged_in_buyer_num]->buyergoods[j]->goods_count += to_buy_good_count;
                        sellers[selected_seller]->sellergoods[i]->goods_count -= to_buy_good_count;
                        buyers[logged_in_buyer_num]->money -= to_buy_good_count * sellers[selected_seller]->sellergoods[i]->goods_price;
                        sellers[selected_seller]->money += to_buy_good_count * sellers[selected_seller]->sellergoods[i]->goods_price;
                        //buyers[logged_in_buyer_num]->buyergoods[j]->goods_seller = (char*)malloc(strlen(to_buy_good_seller) * sizeof(char));
                        strcpy(buyers[logged_in_buyer_num]->buyergoods[j]->goods_seller, to_buy_good_seller);
                        printf("the buying action was successful!\n");
                        Flag_buyer_had = 1;
                    }
                }
                //if the buyer does not have the good already 
                if (Flag_buyer_had == 0) {
                    buyers[logged_in_buyer_num]->num_of_goods++;
                    if (buyers[logged_in_buyer_num]->num_of_goods == 1) {
                        buyers[logged_in_buyer_num]->buyergoods = NULL;
                        buyers[logged_in_buyer_num]->buyergoods = (struct goods**)malloc(sizeof(struct goods*));
                        if (buyers[logged_in_buyer_num]->buyergoods == NULL) {
                            printf("memory allocation failed\n");
                            exit(0);
                        }
                        buyers[logged_in_buyer_num]->buyergoods[0] = NULL;
                        buyers[logged_in_buyer_num]->buyergoods[0] = (struct goods*)malloc(sizeof(struct goods));
                        if (buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1] == NULL) {
                            printf("memory allocation failed\n");
                            exit(0);
                        }

                    }
                    //allocating memory with the size of struct and checking if allocations were successful or not
                    if (buyers[logged_in_buyer_num]->num_of_goods > 1)
                        buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1] = (struct goods*)malloc(buyers[logged_in_buyer_num]->num_of_goods * sizeof(struct goods));
                    if (buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1] == NULL) {
                        printf("memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_name = (char*)malloc((strlen(to_buy_good_name) + 1) * sizeof(char));
                    if (buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_name == NULL) {
                        printf("memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_seller = (char*)malloc((strlen(sellers[selected_seller]->username) + 1) * sizeof(char));
                    if (buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_count == NULL) {
                        printf("memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    Flag = 1;
                    //saving the good's name and the seller's username
                    strcpy(buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_name, to_buy_good_name);
                    strcpy(buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_seller, to_buy_good_seller);
                    buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_seller[strlen(sellers[selected_seller]->username)] = '\0';
                    buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_name[strlen(to_buy_good_name)] = '\0';
                    //removing the wanted number of goods from the sellers structure
                    sellers[selected_seller]->sellergoods[i]->goods_count -= to_buy_good_count;
                    //changing the money between buyer and seller
                    buyers[logged_in_buyer_num]->money -= to_buy_good_count * sellers[selected_seller]->sellergoods[i]->goods_price;
                    sellers[selected_seller]->money += to_buy_good_count * sellers[selected_seller]->sellergoods[i]->goods_price;
                    //saving the good's price and count
                    buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_count = to_buy_good_count;
                    buyers[logged_in_buyer_num]->buyergoods[buyers[logged_in_buyer_num]->num_of_goods - 1]->goods_price = sellers[selected_seller]->sellergoods[i]->goods_price;
                    printf("the buying action was successful.\n");
                }
            }
            else if (strcmp(sellers[selected_seller]->sellergoods[i]->goods_name, to_buy_good_name) == 0) {
                if (sellers[selected_seller]->sellergoods[i]->goods_count < to_buy_good_count) {
                    printf("the seller doesn't have enough goods.\n");
                    continue;
                }
                if (buyers[logged_in_buyer_num]->money < (to_buy_good_count * sellers[selected_seller]->sellergoods[i]->goods_price)) {
                    printf("you don't have enough money.\n");
                    break;;
                }
            }
        }
        if (Flag == 0)
            printf("goods not found.\n");
    }
    else
        printf("sellers can't buy goods.\n");
    return 1;
}

void deposit(char* user_str_input, int logged_in_buyer_num, int logged_in_seller_num, struct buyer** buyers) {
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {
        printf("please login first.\n");
        return;
    }
    if (logged_in_buyer_num != -1) {                   //a buyer should be online to use this command
        char* amount = strtok_s(user_str_input, " ", &user_str_input);
        int temp, a, counter = 0;
        temp = atoi(amount);
        a = temp;
        while (a > 0) {                                //checking whether the input (amount of money) is valid or not
            a = a / 10;
            counter++;
        }
        if (temp != 0 && counter == strlen(amount)) {  //adding the money to the buyer's structure
            buyers[logged_in_buyer_num]->money += temp;
            printf("deposit was successful.\n");
        }
        else
            printf("input is invalid.\n");
    }
    else
        printf("only buyers can deposit.\n");
}

void free_pointers(char* address_of_input, struct buyer** buyers, struct seller** sellers, int buyer_num, int seller_num) {
    free(address_of_input);                                     //at first we'll free all of the pointers inside the structures one by one, then we'll free the structure itself
    for (int i = 0; i < buyer_num; i++) {                       //doing the deallocation for buyers
        free(buyers[i]->username);
        free(buyers[i]->password);
        for (int j = 0; j < buyers[i]->num_of_goods; j++) {     //deallocating the goods
            free(buyers[i]->buyergoods[j]->goods_name);
            free(buyers[i]->buyergoods[j]->goods_seller);
            free(buyers[i]->buyergoods[j]);
        }
        free(buyers[i]);
    }
    for (int i = 0; i < seller_num; i++) {                      //doing the deallocation for sellers
        free(sellers[i]->username);
        free(sellers[i]->password);
        for (int j = 0; j < sellers[i]->num_of_goods; j++) {    //deallocating the goods
            free(sellers[i]->sellergoods[j]->goods_name);
            free(sellers[i]->sellergoods[j]);
        }
        free(sellers[i]);
    }
}