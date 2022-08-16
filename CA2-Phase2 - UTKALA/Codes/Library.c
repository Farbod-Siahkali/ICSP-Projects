#include "Header.h"

struct goods* new_node(struct goods* node) {
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct goods* binary_tree_generator(struct goods* goods, int start, int end) {
    if (start > end)
        return NULL;
    int mid = (start + end) / 2;
    int counter = 0;
    struct goods* head = goods;
    while (counter != mid) {
        head = head->next;
        counter++;
    }
    struct goods* root = NULL;
    if (head != NULL)
        root = new_node(head);
    if (root != NULL) {
        root->left = binary_tree_generator(goods, start, mid - 1);
        root->right = binary_tree_generator(goods, mid + 1, end);
    }
    return root;
}

char* cmd_string_reader() {                                       //this is going to get the input string
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

char* file_string_reader(FILE* input) {                                       //this is going to get the input string
    char* str = NULL;
    char c = 0;
    int i = 0;
    str = (char*)malloc(sizeof(char));                                   //at first it allocates memory with the size of a single character
    if (str == NULL) {
        printf("memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    while (c != EOF) {
        c = fgetc(input);
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

int user_checker_buyers(int num, struct buyer* head, char* username) { //a loop that checks all the buyers usernames to see if the username is new or not
    int Flag_same = 2;
    for (int i = 0; i < num; i++) {
        if (strcmp(head->username, username) == 0) {
            printf("username already taken\n");
            Flag_same = 1;
            break;
        }
        head = head->next;
    }
    return Flag_same;
}

int user_checker_sellers(int num, struct seller* head, char* username) {//a loop that checks all the sellers usernames to see if the username is new or not
    int Flag_same = 2;
    for (int i = 0; i < num; i++) {
        if (strcmp(head->username, username) == 0) {
            printf("username already taken\n");
            Flag_same = 1;
            break;
        }
        head = head->next;
    }
    return Flag_same;
}

void signup(int logged_in_seller_num, int logged_in_buyer_num, char* user_str_input, int* buyer_num, struct buyer** buyers, struct seller** sellers, int* seller_num) {
    int Flag_same = 2;
    if (logged_in_seller_num == -1 && logged_in_buyer_num == -1) {
        char* username = strtok_s(user_str_input, " ", &user_str_input);                        //getting the username's data
        char* password = strtok_s(user_str_input, " ", &user_str_input);
        char* role = strtok_s(user_str_input, " ", &user_str_input);
        if (username == NULL || password == NULL || role == NULL) {                             //checking whether the input is valid or not
            printf("command was incomplete.\n");
            return;
        }
        int user_len = strlen(username);
        int pass_len = strlen(password);
        if (strcmp(role, "buyer") == 0) {                                                       //if the user wants to signup as a buyer
            struct buyer* head = *buyers;
            Flag_same = user_checker_buyers(*buyer_num, head, username);
            if (Flag_same == 1)
                return;
            (*buyer_num)++;
            struct buyer* new_user = (struct buyer*)malloc(sizeof(struct buyer));               //if it's the first buyer account, we should malloc
            if (new_user == NULL) {
                printf("memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            new_user->username = (char*)malloc((user_len + 1) * sizeof(char));     //allocating enough memory to save username
            if (new_user->username == NULL) {
                printf("memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            new_user->password = (char*)malloc((pass_len + 1) * sizeof(char));     //allocating enough memory to save password
            if (new_user->password == NULL) {
                printf("memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            new_user->money = 0;                                                   //saving the data and then returning it
            new_user->num_of_goods = 0;
            strcpy(new_user->username, username);
            strcpy(new_user->password, password);
            new_user->username[user_len] = '\0';
            new_user->password[pass_len] = '\0';
            new_user->next = NULL;
            head = *buyers;
            if ((*buyer_num) > 1) {
                while (head->next != NULL)
                    head = head->next;
                head->next = new_user;
            }
            else
                (*buyers) = new_user;
            FILE* input = fopen("users.txt", "a");
            fwrite(new_user->username, sizeof(char), user_len, input);
            fwrite(",", sizeof(char), 1, input);
            fwrite(new_user->password, sizeof(char), pass_len, input);
            fwrite(",", sizeof(char), 1, input);
            fwrite("buyer\n", sizeof(char), 6, input);
            fclose(input);
            printf("signup was successful!\n");
        }
        else if (strcmp(role, "seller") == 0) {                                    //if the user wants a seller account, we do just like what we did for buyer
            struct seller* head = *sellers;
            Flag_same = user_checker_sellers(*seller_num, head, username);
            if (Flag_same == 1)
                return;
            (*seller_num)++;
            struct seller* new_user = (struct seller*)malloc(sizeof(struct seller));
            if (new_user == NULL) {
                printf("memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            new_user->username = (char*)malloc((user_len + 1) * sizeof(char));     //allocating enough memory to save username
            if (new_user->username == NULL) {
                printf("memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            new_user->password = (char*)malloc((pass_len + 1) * sizeof(char));     //allocating enough memory to save password
            if (new_user->password == NULL) {
                printf("memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            new_user->money = 0;                                                   //saving the data and then returning it
            new_user->num_of_goods = 0;
            strcpy(new_user->username, username);
            strcpy(new_user->password, password);
            new_user->username[user_len] = '\0';
            new_user->password[pass_len] = '\0';
            head = *sellers;
            new_user->next = NULL;
            if ((*seller_num) > 1) {
                while (head->next != NULL)
                    head = head->next;
                head->next = new_user;
            }
            else
                (*sellers) = new_user;
            FILE* input = fopen("users.txt", "a");
            fwrite(new_user->username, sizeof(char), user_len, input);
            fwrite(",", sizeof(char), 1, input);
            fwrite(new_user->password, sizeof(char), pass_len, input);
            fwrite(",", sizeof(char), 1, input);
            fwrite("seller\n", sizeof(char), 6, input);
            fclose(input);
            printf("signup was successful!\n");
        }
        else
            printf("role does not exist.\n");
    }
    else
        printf("please log out first!\n");
    return;
}

int signup_from_file(int logged_in_seller_num, int logged_in_buyer_num, char* user_str_input, int* buyer_num, struct buyer** buyers, struct seller** sellers, int* seller_num) {
    int Flag_same = 2;
    if (logged_in_seller_num == -1 && logged_in_buyer_num == -1) {
        while (1) {
            char* username = strtok_s(user_str_input, ",", &user_str_input);                        //getting the username's data
            char* password = strtok_s(user_str_input, ",", &user_str_input);
            char* role = strtok_s(user_str_input, ",", &user_str_input);
            if (username == NULL || password == NULL || role == NULL) {                             //checking whether the input is valid or not
                Flag_same = 1;
                return Flag_same;
            }
            int money = atoi(strtok_s(user_str_input, ",", &user_str_input));
            int num_of_goods = atoi(strtok_s(user_str_input, "\n", &user_str_input));
            if (username == NULL || password == NULL || role == NULL) {                             //checking whether the input is valid or not
                Flag_same = 1;
                return Flag_same;
            }
            int user_len = strlen(username);
            int pass_len = strlen(password);
            if (strcmp(role, "buyer") == 0) {                                                       //if the user wants to signup as a buyer
                struct buyer* head = *buyers;
                Flag_same = user_checker_buyers(*buyer_num, head, username);
                if (Flag_same == 1)
                    return Flag_same;
                (*buyer_num)++;
                struct buyer* new_user = (struct buyer*)malloc(sizeof(struct buyer));               //if it's the first buyer account, we should malloc
                if (new_user == NULL) {
                    printf("memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                new_user->username = (char*)malloc((user_len + 1) * sizeof(char));     //allocating enough memory to save username
                if (new_user->username == NULL) {
                    printf("memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                new_user->password = (char*)malloc((pass_len + 1) * sizeof(char));     //allocating enough memory to save password
                if (new_user->password == NULL) {
                    printf("memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                new_user->money = money;                                               //saving the data and then returning it
                new_user->num_of_goods = num_of_goods;
                strcpy(new_user->username, username);
                strcpy(new_user->password, password);
                new_user->username[user_len] = '\0';
                new_user->password[pass_len] = '\0';
                new_user->next = NULL;
                head = *buyers;
                if ((*buyer_num) > 1) {
                    while (head->next != NULL)
                        head = head->next;
                    head->next = new_user;
                }
                else
                    (*buyers) = new_user;
            }
            else if (strcmp(role, "seller") == 0) {                                    //if the user wants a seller account, we do just like what we did for buyer
                struct seller* head = *sellers;
                Flag_same = user_checker_sellers(*seller_num, head, username);
                if (Flag_same == 1)
                    return Flag_same;
                (*seller_num)++;
                struct seller* new_user = (struct seller*)malloc(sizeof(struct seller));
                if (new_user == NULL) {
                    printf("memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                new_user->username = (char*)malloc((user_len + 1) * sizeof(char));     //allocating enough memory to save username
                if (new_user->username == NULL) {
                    printf("memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                new_user->password = (char*)malloc((pass_len + 1) * sizeof(char));     //allocating enough memory to save password
                if (new_user->password == NULL) {
                    printf("memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                new_user->money = money;                                               //saving the data and then returning it
                new_user->num_of_goods = num_of_goods;
                strcpy(new_user->username, username);
                strcpy(new_user->password, password);
                new_user->username[user_len] = '\0';
                new_user->password[pass_len] = '\0';
                head = *sellers;
                new_user->next = NULL;
                if ((*seller_num) > 1) {
                    while (head->next != NULL)
                        head = head->next;
                    head->next = new_user;
                }
                else
                    (*sellers) = new_user;
            }
            else
                printf("role does not exist.\n");
        }
    }
    else
        printf("please log out first!\n");
    return Flag_same;
}

void login_checker(struct buyer** buyers, struct seller** sellers, char* user_str_input, int buyer_num, int seller_num, int* logged_in_buyer_num, int* logged_in_seller_num) {
    if (*logged_in_buyer_num == -1 && *logged_in_seller_num == -1) {
        char* username = strtok_s(user_str_input, " ", &user_str_input);                       //getting the user's data
        char* password = strtok_s(user_str_input, " ", &user_str_input);
        char* role = strtok_s(user_str_input, " ", &user_str_input);
        if (username == NULL || password == NULL || role == NULL) {                            //checking whether the data is valid or not
            printf("command was incomplete.\n");
            return;
        }
        int i = 1, j = 1;
        if (strcmp(role, "buyer") == 0) {                                                      //if he wants to log into a buyer's account
            struct buyer* head = *buyers;
            while (head != NULL) {                                                             //start searching all the buyers to find an account that has the same username and password
                if (strcmp(head->username, username) == 0 && strcmp(head->password, password) == 0) {
                    *logged_in_buyer_num = i;                                                  //if account found, save the related number of it
                    break;
                }
                if (strcmp(head->username, username) == 0 && strcmp(head->password, password) != 0) {
                    printf("worng password\n");                                               //maybe username found, but password was incorrect
                    i = -2;
                    break;
                }
                head = head->next;
                i++;
            }
            if (head == NULL)                                                                 //maybe there was no username
                printf("username not found.\n");
            if (*logged_in_buyer_num != -1)
                printf("login as a buyer was successful\n");
        }
        if (strcmp(role, "seller") == 0) {                                                    //we'll do the same thing for a user that wants to login as a seller
            struct buyer* head = *sellers;
            while (head != NULL) {
                if (strcmp(head->username, username) == 0 && strcmp(head->password, password) == 0) {
                    *logged_in_seller_num = j;
                    break;
                }
                if (strcmp(head->username, username) == 0 && strcmp(head->password, password) != 0) {
                    printf("worng password.\n");
                    j = -2;
                    break;
                }
                head = head->next;
                j++;
            }
            if (head == NULL)
                printf("username not found.\n");
            if (*logged_in_seller_num != -1)
                printf("login as a seller was successful.\n");
        }
    }
    else {
        printf("Please logout first.\n");
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

void view_account(struct buyer** buyers, int logged_in_buyer_num, struct seller** sellers, int logged_in_seller_num, struct goods** goods) {
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {               // at first, you should be logged in
        printf("please login first.\n");
        return;
    }
    if (logged_in_seller_num != -1) {                                            //if the logged in account is a seller, at first we print his/her info
        struct seller* head = *sellers;
        for (int i = 1; i < logged_in_seller_num; i++)
            head = head->next;
        printf("username: %s\n", head->username);
        printf("role: seller\n");
        printf("money: %d\n", head->money);
        struct goods* goods_head = *goods;
        int flag = 0;
        while (goods_head != NULL) {                                             //then we start printing the goods he/she owns
            while (strcmp(goods_head->goods_owner, head->username) != 0 || goods_head->goods_past_owner != NULL) {
                goods_head = goods_head->next;
                if (goods_head == NULL) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
            printf("-------------------\n");
            printf("goods name: %s\n", goods_head->goods_name);
            printf("goods price: %d\n", goods_head->goods_price);
            printf("goods count: %d\n", goods_head->goods_count);
            goods_head = goods_head->next;
        }
    }
    else if (logged_in_buyer_num != -1) {                                       //we'll do the same thing if the account is a buyer
        struct buyer* head = *buyers;
        for (int i = 1; i < logged_in_buyer_num; i++)
            head = head->next;
        printf("username: %s\n", head->username);
        printf("role: buyer\n");
        printf("money: %d\n", head->money);
        struct goods* goods_head = *goods;
        int flag = 0;
        while (goods_head != NULL) {
            while (strcmp(goods_head->goods_owner, head->username) != 0 || goods_head->goods_past_owner == NULL) {
                goods_head = goods_head->next;
                if (goods_head == NULL) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
            printf("-------------------\n");
            printf("goods name: %s\n", goods_head->goods_name);
            printf("goods price: %d\n", goods_head->goods_price);
            printf("goods count: %d\n", goods_head->goods_count);
            printf("goods seller: %s\n", goods_head->goods_owner);
            goods_head = goods_head->next;
        }
    }
}

void add_goods(int logged_in_seller_num, int logged_in_buyer_num, struct seller** sellers, char* user_str_input, int num_of_sellers, struct goods** goods, int* num_of_goods) {
    int good_is_in_stock = 0;
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {
        printf("please login first.\n");
        return;
    }
    if (logged_in_seller_num != -1) {                                                     //the logged in account must be a seller because seller's can add goods
        char* new_goods_name = strtok_s(user_str_input, " ", &user_str_input);
        char* newgoodprice = strtok_s(user_str_input, " ", &user_str_input);
        char* new_goods_count1 = strtok_s(user_str_input, " ", &user_str_input);
        if (new_goods_name == NULL || newgoodprice == NULL || new_goods_count1 == NULL) {  //checking if the input is complete or not
            printf("command was incomplete.\n");
            return;
        }
        int new_goods_price = atoi(newgoodprice);
        int a = new_goods_price, counter = 0;
        while (a > 0) {
            a = a / 10;
            counter++;
        }
        if (new_goods_price <= 0 || strlen(newgoodprice) != counter) {
            printf("price is invalid.\n");
            return;
        }
        struct seller* head = *sellers;
        for (int i = 1; i < logged_in_seller_num; i++)
            head = head->next;
        struct goods* goods_head = *goods;
        for (int i = 0; i < num_of_sellers; i++)                                           //ta's said that the name of the product must be uniqe, so here i'm checking whether it's uniqe or not
            while (goods_head != NULL) {
                if (strcmp(goods_head->goods_name, new_goods_name) == 0) {
                    printf("name already taken.\n");
                    return;
                }
                goods_head = goods_head->next;
            }
        int new_goods_count = atoi(new_goods_count1);
        if (new_goods_count <= 0) {
            printf("good's count is invalid!\n");
            return;
        }
        goods_head = *goods;
        if (head->num_of_goods >= 1)                             //if the seller already has the product, we should only update the number of it
            while (goods_head != NULL) {
                if (strcmp(goods_head->goods_name, new_goods_name) == 0 && goods_head->goods_price == new_goods_price) {
                    goods_head->goods_count += new_goods_count;
                    good_is_in_stock = 1;
                    break;
                }
                goods_head = goods_head->next;
            }
        if (good_is_in_stock == 0) {                                                      //if the product wasn't in the stock:
            head->num_of_goods++;
            (*num_of_goods)++;
            struct goods* new_goods = (struct goods*)malloc(sizeof(struct goods));
            if (new_goods == NULL) {
                printf("memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            new_goods->goods_name = (char*)malloc((strlen(new_goods_name) + 1) * sizeof(char));
            if (new_goods->goods_name == NULL) {
                printf("memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            new_goods->goods_owner = (char*)malloc((strlen(head->username) + 1) * sizeof(char));
            if (new_goods->goods_owner == NULL) {
                printf("memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            //saving the data of the product given by the user in the structure defined for it
            new_goods->rate_able = 0;
            new_goods->rating = 0;
            new_goods->num_of_rates = 0;
            strcpy(new_goods->goods_name, new_goods_name);
            new_goods->goods_name[strlen(new_goods_name)] = '\0';
            strcpy(new_goods->goods_owner, head->username);
            new_goods->goods_owner[strlen(head->username)] = '\0';
            new_goods->goods_price = new_goods_price;
            new_goods->goods_count = new_goods_count;
            new_goods->next = NULL;
            new_goods->goods_past_owner = NULL;
            goods_head = *goods;
            if (*num_of_goods > 1) {
                while (goods_head->next != NULL)
                    goods_head = goods_head->next;
                goods_head->next = new_goods;
            }
            else
                (*goods) = new_goods;
        }
        printf("goods added successfully!\n");
    }
    else
        printf("you can not add goods!\n");
}

int add_goods_from_file(char* user_str_input, struct goods** goods, int* num_of_goods) {
    char* num_goods = strtok_s(user_str_input, "\n", &user_str_input);
    if (num_goods == NULL) {  //checking if the input is complete or not
        return 1;
    }
    *num_of_goods = atoi(num_goods);
    int i = 1;
    while (num_of_goods != i) {
        char* new_goods_name = strtok_s(user_str_input, ",", &user_str_input);
        char* newgoodprice = strtok_s(user_str_input, ",", &user_str_input);
        char* new_goods_count1 = strtok_s(user_str_input, ",", &user_str_input);
        char* new_goods_owner = strtok_s(user_str_input, ",", &user_str_input);
        char* new_goods_rate = strtok_s(user_str_input, ",", &user_str_input);
        char* new_goods_num_rate = strtok_s(user_str_input, ",", &user_str_input);
        char* rate_able = strtok_s(user_str_input, ",", &user_str_input);
        char* new_goods_last_owner = strtok_s(user_str_input, "\n", &user_str_input);
        if (new_goods_name == NULL || newgoodprice == NULL || new_goods_count1 == NULL) {  //checking if the input is complete or not
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
        struct goods* goods_head = *goods;
        int new_goods_count = atoi(new_goods_count1);
        if (new_goods_count <= 0) {
            printf("good's count is invalid!\n");
            return 1;
        }
        goods_head = *goods;
        struct goods* new_goods = (struct goods*)malloc(sizeof(struct goods));
        if (new_goods == NULL) {
            printf("memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        new_goods->goods_name = (char*)malloc((strlen(new_goods_name) + 1) * sizeof(char));
        if (new_goods->goods_name == NULL) {
            printf("memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        new_goods->goods_owner = (char*)malloc((strlen(new_goods_owner) + 1) * sizeof(char));
        if (new_goods->goods_owner == NULL) {
            printf("memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        //saving the data of the product given by the user in the structure defined for it
        new_goods->rate_able = atoi(rate_able);
        new_goods->rating = atof(new_goods_rate);
        new_goods->num_of_rates = atoi(new_goods_num_rate);
        strcpy(new_goods->goods_name, new_goods_name);
        new_goods->goods_name[strlen(new_goods_name)] = '\0';
        strcpy(new_goods->goods_owner, new_goods_owner);
        new_goods->goods_owner[strlen(new_goods_owner)] = '\0';
        new_goods->goods_price = new_goods_price;
        new_goods->goods_count = new_goods_count;
        new_goods->next = NULL;
        if (strcmp(new_goods_last_owner, ",") == 0)
            new_goods->goods_past_owner = NULL;
        else {
            new_goods->goods_past_owner = (char*)malloc(strlen(new_goods_last_owner) * sizeof(char));
            strncpy(new_goods->goods_past_owner, new_goods_last_owner, strlen(new_goods_last_owner) - 1);
            new_goods->goods_past_owner[strlen(new_goods_last_owner) - 1] = '\0';
        }
        goods_head = *goods;
        if (i > 1) {
            while (goods_head->next != NULL)
                goods_head = goods_head->next;
            goods_head->next = new_goods;
        }
        else
            (*goods) = new_goods;
        i++;
    }
    return 2;
}

void file_reader(struct goods** goods, int* num_of_goods, int logged_in_seller_num, int logged_in_buyer_num, int* buyer_num, struct buyer** buyers, struct seller** sellers, int* seller_num) {
    int Flag = 0;
    FILE* input = fopen("users.txt", "r");
    if (input == NULL) {
        input = fopen("users.txt", "w");
        fclose(input);
        input = fopen("users.txt", "r");
    }
    if (input != NULL) {
        char* c = file_string_reader(input);
        char* str = c;
        Flag = signup_from_file(logged_in_seller_num, logged_in_buyer_num, c, buyer_num, buyers, sellers, seller_num);
        free(str);
        fclose(input);
    }
    input = fopen("goods.txt", "r");
    if (input == NULL) {
        input = fopen("goods.txt", "w");
        fclose(input);
        input = fopen("goods.txt", "r");
    }
    if (input != NULL) {
        char* c = file_string_reader(input);
        char* str = c;
        Flag = add_goods_from_file(str, goods, num_of_goods);
        free(str);
        fclose(input);
    }
}

int sort_by_name(struct goods* goods) {
    if (goods->next == NULL || goods->next->next == NULL)
        return 0;
    sort_by_name(goods->next);
    if (strcmp(goods->next->goods_name, goods->next->next->goods_name) > 0) {
        struct goods* temp = goods->next->next;
        goods->next->next = goods->next->next->next;
        temp->next = goods->next;
        goods->next = temp;
        sort_by_name(goods->next);
    }
    return 1;
}

void show_goods(int logged_in_buyer_num, int logged_in_seller_num, struct goods** goods) {
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) { //someone should log in to user this command
        printf("please login first.\n");
        return;
    }
    struct goods* goods_head = (struct goods*)malloc(sizeof(struct goods));
    goods_head->next = *goods;
    int flag1 = sort_by_name(goods_head);
    *goods = goods_head->next;
    free(goods_head);
    int flag = 0;
    goods_head = *goods;
    while (goods_head != NULL) {                                  //starts printing any goods the seller have for sale
        if (goods_head->goods_past_owner != NULL) {
            goods_head = goods_head->next;
            continue;
        }
        if (goods_head->rating < 2 && goods_head->num_of_rates > 4) {
            goods_head = goods_head->next;
            continue;
        }
        printf("\n");
        printf("seller's username: %s\n", goods_head->goods_owner);
        printf("goods name: %s\n", goods_head->goods_name);
        printf("goods price: %d\n", goods_head->goods_price);
        printf("goods count: %d\n", goods_head->goods_count);
        printf("goods rating: %f\n", goods_head->rating);
        printf("-------------------\n");
        goods_head = goods_head->next;
    }
}

void buy_fun(struct buyer** buyers, struct seller** sellers, struct goods** goods, int logged_in_buyer_num, char* user_str_input, int seller_num, int logged_in_seller_num, int* num_of_goods) {
    int selected_seller = -1, Flag = 0, Flag_buyer_had = 0;
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {                                  //checks if anyone logged in or not
        printf("please login first.\n");
        return;
    }
    if (logged_in_buyer_num != -1 && logged_in_seller_num == -1) {                                  //a buyer must be logged in to buy a product
        char* to_buy_good_name = strtok_s(user_str_input, " ", &user_str_input);
        char* to_buy_good_count1 = strtok_s(user_str_input, " ", &user_str_input);
        char* to_buy_good_seller = strtok_s(user_str_input, " ", &user_str_input);
        if (to_buy_good_count1 == NULL || to_buy_good_name == NULL || to_buy_good_seller == NULL) { //checking whether the inputs are valid or not
            printf("command is incomplete.\n");
            return;
        }
        int to_buy_good_count = atoi(to_buy_good_count1);
        if (to_buy_good_count <= 0) {
            printf("invalid good's count.\n");
            return;
        }
        struct seller* sellers_head = *sellers;
        while (sellers_head != NULL) {    //finding the seller of the wanted product
            if (strcmp(sellers_head->username, to_buy_good_seller) == 0)
                break;
            selected_seller++;
            sellers_head = sellers_head->next;
        }
        if (sellers_head == NULL) {
            printf("seller not found.\n");
            return;
        }
        struct buyer* buyers_head = *buyers;
        for (int i = 1; i < logged_in_buyer_num; i++)
            buyers_head = buyers_head->next;
        struct goods* goods_head = *goods;
        while (goods_head != NULL) {                                                                 //start searching inside the products of that seller
            if (strcmp(goods_head->goods_name, to_buy_good_name) == 0 && goods_head->goods_count >= to_buy_good_count && buyers_head->money >= (to_buy_good_count * goods_head->goods_price)) {
                if (goods_head->rating < 2 && goods_head->num_of_rates > 4) {
                    printf("this goods is not available because of rating.\n");
                    return;
                }
                struct goods* goods_destination = *goods;
                while (goods_destination != NULL) {                       //if the buyer already had some of the wanted product, then we should just increase the number of it
                    if (strcmp(goods_destination->goods_name, to_buy_good_name) == 0) {
                        if (strncmp(goods_destination->goods_owner, buyers_head->username, strlen(buyers_head->username)) == 0) {
                            Flag = 1;
                            goods_destination->goods_count += to_buy_good_count;
                            goods_head->goods_count -= to_buy_good_count;
                            buyers_head->money -= to_buy_good_count * goods_head->goods_price;
                            sellers_head->money += to_buy_good_count * goods_head->goods_price;
                            goods_destination->rate_able = 0;
                            printf("the buying action was successful!\n");
                            Flag_buyer_had = 1;
                        }
                    }
                    if (Flag == 1)
                        break;
                    goods_destination = goods_destination->next;
                }
                if (Flag == 1)
                    break;
                //if the buyer does not have the good already 
                if (Flag_buyer_had == 0) {
                    buyers_head->num_of_goods++;
                    (*num_of_goods)++;
                    //memory allocating for structure & pointers inside
                    struct goods* new_goods = (struct goods*)malloc(sizeof(struct goods));
                    if (new_goods == NULL) {
                        printf("memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    new_goods->goods_name = (char*)malloc((strlen(to_buy_good_name) + 1) * sizeof(char));
                    if (new_goods->goods_name == NULL) {
                        printf("memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    new_goods->goods_past_owner = (char*)malloc((strlen(sellers_head->username) + 1) * sizeof(char));
                    if (new_goods->goods_past_owner == NULL) {
                        printf("memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    new_goods->goods_owner = (char*)malloc((strlen(buyers_head->username) + 1) * sizeof(char));
                    if (new_goods->goods_owner == NULL) {
                        printf("memory allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    Flag = 1;
                    //saving the good's name and the seller's username
                    new_goods->rate_able = 0;
                    strcpy(new_goods->goods_name, to_buy_good_name);
                    strcpy(new_goods->goods_past_owner, to_buy_good_seller);
                    strcpy(new_goods->goods_owner, buyers_head->username);
                    new_goods->goods_past_owner[strlen(sellers_head->username)] = '\0';
                    new_goods->goods_name[strlen(to_buy_good_name)] = '\0';
                    //removing the wanted number of goods from the sellers structure
                    goods_head->goods_count -= to_buy_good_count;
                    //changing the money between buyer and seller
                    buyers_head->money -= to_buy_good_count * goods_head->goods_price;
                    sellers_head->money += to_buy_good_count * goods_head->goods_price;
                    //saving the good's price and count
                    new_goods->goods_count = to_buy_good_count;
                    new_goods->goods_price = goods_head->goods_price;
                    new_goods->num_of_rates = goods_head->num_of_rates;
                    new_goods->rating = goods_head->rating;
                    new_goods->next = NULL;
                    goods_head = *goods;
                    while (goods_head->next != NULL)
                        goods_head = goods_head->next;
                    goods_head->next = new_goods;
                    printf("the buying action was successful.\n");
                    break;
                }
            }
            else if (strcmp(goods_head->goods_name, to_buy_good_name) == 0) {
                if (goods_head->goods_count < to_buy_good_count) {
                    printf("the seller doesn't have enough goods.\n");
                    continue;
                }
                if (buyers_head->money < (to_buy_good_count * goods_head->goods_price)) {
                    printf("you don't have enough money.\n");
                    break;
                }
            }
            goods_head = goods_head->next;
        }
        if (Flag == 0)
            printf("goods not found.\n");
    }
    else
        printf("sellers can't buy goods.\n");
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
            struct buyer* head = *buyers;
            for (int i = 1; i < logged_in_buyer_num; i++)
                head = head->next;
            head->money += temp;
            printf("deposit was successful.\n");
        }
        else
            printf("input is invalid.\n");
    }
    else
        printf("only buyers can deposit.\n");
}

void file_saver(struct buyer** buyers, struct seller** sellers, struct goods** goods, int num_of_goods) {
    FILE* input = fopen("users.txt", "w");
    struct seller* head_sellers = *sellers;
    while (head_sellers != NULL) {                        //saving buyers account in users.txt in a way that can be read later
        fwrite(head_sellers->username, sizeof(char), strlen(head_sellers->username), input);
        fwrite(",", sizeof(char), 1, input);
        fwrite(head_sellers->password, sizeof(char), strlen(head_sellers->password), input);
        fwrite(",seller,", sizeof(char), 8, input);
        fprintf(input, "%d,", head_sellers->money);
        fprintf(input, "%d\n", head_sellers->num_of_goods);
        head_sellers = head_sellers->next;
    }
    struct buyer* head_buyers = *buyers;
    while (head_buyers != NULL) {                        //saving buyers account in users.txt in a way that can be read later
        fwrite(head_buyers->username, sizeof(char), strlen(head_buyers->username), input);
        fwrite(",", sizeof(char), 1, input);
        fwrite(head_buyers->password, sizeof(char), strlen(head_buyers->password), input);
        fwrite(",buyer", sizeof(char), 6, input);
        fprintf(input, ",%d", head_buyers->money);
        fprintf(input, ",%d\n", head_buyers->num_of_goods);
        head_buyers = head_buyers->next;
    }
    fclose(input);
    input = fopen("goods.txt", "w");                      //saving the total number of goods at the first of goods.txt
    fprintf(input, "%d\n", num_of_goods);
    struct goods* head_goods = *goods;
    while (head_goods != NULL) {                          //saving the goods in file with a format that can be read later
        fwrite(head_goods->goods_name, sizeof(char), strlen(head_goods->goods_name), input);
        fprintf(input, ",%d", head_goods->goods_price);
        fprintf(input, ",%d,", head_goods->goods_count);
        fwrite(head_goods->goods_owner, sizeof(char), strlen(head_goods->goods_owner), input);
        fprintf(input, ",%f,", head_goods->rating);
        fprintf(input, "%d,", head_goods->num_of_rates);
        fprintf(input, "%d,", head_goods->rate_able);
        if (head_goods->goods_past_owner != NULL)
            fwrite(head_goods->goods_past_owner, sizeof(char), strlen(head_goods->goods_past_owner), input);
        fwrite(",\n", sizeof(char), 2, input);
        head_goods = head_goods->next;
    }
    fclose(input);
}

void remove_goods(struct goods* root, struct seller** sellers, struct goods** goods, char* user_str_input, int logged_in_seller_num, int* num_of_goods) {
    int flag = 0;
    if (logged_in_seller_num == -1) {
        printf("Please login as a seller to use this command.\n");
        return;
    }
    char* goods_name = strtok_s(user_str_input, "\n", &user_str_input);
    struct goods* goods_head = root;
    struct seller* sellers_head = *sellers;
    for (int i = 1; i < logged_in_seller_num; i++)                   //finding the seller who used the command
        sellers_head = sellers_head->next;
    struct goods* temp = NULL;
    while (goods_head != NULL) {
        if (strcmp(goods_head->goods_name, goods_name) < 0) {
            temp = goods_head;
            goods_head = goods_head->right;
            continue;
        }
        if (strcmp(goods_head->goods_name, goods_name) > 0) {
            temp = goods_head;
            goods_head = goods_head->left;
            continue;
        }
        if (strcmp(goods_head->goods_name, goods_name) == 0 && strcmp(goods_head->goods_owner, sellers_head->username) == 0) {
            if (temp != NULL) {
                if (temp->left != NULL)                               //placing null in binary tree
                    if (strcmp(temp->left->goods_name, goods_name) == 0)
                        temp->left = NULL;
                if (temp->right != NULL)
                    if (strcmp(temp->right->goods_name, goods_name) == 0)
                        temp->right = NULL;
            }
            temp = goods_head;
            goods_head = *goods;
            if (goods_head == temp) {
                *goods = goods_head->next;
            }
            else {
                while (goods_head->next != temp)                      //start from the begining of the list, until we get to the wanted goods
                    goods_head = goods_head->next;
                goods_head->next = goods_head->next->next;            //connecting the previous node to the next one
            }
            free(temp->goods_name);                                  //freeing the pointers inside the structure. in the end we free the structure itself
            free(temp->goods_owner);
            if (temp->goods_past_owner != NULL)
                free(temp->goods_past_owner);
            free(temp);
            (*num_of_goods)--;
            printf("goods is removed.\n");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        printf("goods not found.\n");
}

// function that removes the node without binary tree
/*void remove_goods(struct seller** sellers, struct goods** goods, char* user_str_input, int logged_in_seller_num) {
    int flag = 0;
    if (logged_in_seller_num == -1) {
        printf("Please login as a seller to use this command.\n");
        return;
    }
    char* goods_name = strtok_s(user_str_input, "\n", &user_str_input);
    struct goods* goods_head = *goods;
    struct seller* sellers_head = *sellers;
    for (int i = 1; i < logged_in_seller_num; i++)                   //finding the seller who used the command
        sellers_head = sellers_head->next;
    while (goods_head != NULL) {
        if (strcmp(goods_head->goods_name, goods_name) == 0 && strcmp(goods_head->goods_owner, sellers_head->username) == 0) {
            struct goods* temp = goods_head;
            goods_head = *goods;
            while (goods_head->next != temp)                        //start from the begining of the list, until we get to the wanted goods
                goods_head = goods_head->next;
            goods_head->next = goods_head->next->next;             //connecting the previous node to the next one
            free(temp->goods_name);                                //freeing the pointers inside the structure. in the end we free the structure itself
            free(temp->goods_owner);
            if (temp->goods_past_owner != NULL)
                free(temp->goods_past_owner);
            free(temp);
            printf("goods is removed.\n");
            flag = 1;
            break;
        }
        goods_head = goods_head->next;
    }
    if (flag == 0)
        printf("goods not found.\n");
}
*/

void change_goods_price(struct seller** sellers, struct goods** goods, char* user_str_input, int logged_in_seller_num) {
    if (logged_in_seller_num == -1) {
        printf("please login as a seller first.\n");
        return;
    }
    int new_goods_price;
    char* goods_name = strtok_s(user_str_input, " ", &user_str_input);
    char* newgoodprice = strtok_s(user_str_input, "\n", &user_str_input);
    if (newgoodprice != NULL)
        new_goods_price = atoi(newgoodprice);
    else {
        printf("Please Enter the new price.\n");
        return;
    }
    int a = new_goods_price, counter = 0, flag = 0;                  //checking if the new price is valid or not
    while (a > 0) {
        a = a / 10;
        counter++;
    }
    if (new_goods_price <= 0 || strlen(newgoodprice) != counter) {
        printf("price is invalid.\n");
        return;
    }
    struct goods* goods_head = *goods;
    struct seller* sellers_head = *sellers;
    for (int i = 1; i < logged_in_seller_num; i++)
        sellers_head = sellers_head->next;
    while (goods_head != NULL) {                                    //starts finding the product and updates the price
        if (strcmp(goods_head->goods_name, goods_name) == 0 && strcmp(goods_head->goods_owner, sellers_head->username) == 0) {
            goods_head->goods_price = new_goods_price;
            printf("price changed successfully.\n");
            flag = 1;
            break;
        }
        goods_head = goods_head->next;
    }
    if (flag == 0)
        printf("no related goods found in your stock.\n");
}

void rating(struct buyer** buyers, struct seller** sellers, struct goods** goods, char* user_str_input, int logged_in_buyer_num, int logged_in_seller_num) {
    if (logged_in_buyer_num == -1) {
        printf("please login as a buyer first.\n");
        return;
    }
    int flag = 0, counter = 0;
    char* goods_name = strtok_s(user_str_input, " ", &user_str_input);
    char* goods_seller = strtok_s(user_str_input, " ", &user_str_input);
    char* rate = strtok_s(user_str_input, "\n", &user_str_input);
    if (goods_name == NULL || goods_seller == NULL || rate == NULL) {        //checking whether the data is valid or not
        printf("command was incomplete.\n");
        return;
    }
    int rating = atoi(rate);
    int a = rating;
    while (a > 0) {
        a = a / 10;
        counter++;
    }
    if (rating > 5 || rating < 1 || strlen(rate) != counter) {
        printf("rating is invalid.\n");
        return;
    }
    struct buyer* buyer_head = *buyers;
    for (int i = 1; i < logged_in_buyer_num; i++)
        buyer_head = buyer_head->next;
    struct goods* head = *goods;
    struct goods* baught_goods_head = *goods;
    while (strcmp(baught_goods_head->goods_name, goods_name) != 0 || strcmp(baught_goods_head->goods_owner, buyer_head->username) != 0)
        baught_goods_head = baught_goods_head->next;
    if (baught_goods_head->rate_able == 1) {                                //see if the goods already have been rated or not
        printf("you already rated this goods.\n");
        return;
    }
    while (head != NULL) {                                                //starts finding the product and rates it
        if (head->goods_past_owner == NULL && strcmp(head->goods_name, goods_name) == 0) {
            head->rating = head->rating * head->num_of_rates;
            head->rating += rating;
            head->num_of_rates++;
            head->rating = head->rating / head->num_of_rates;
            printf("rating submitted.\n");
            head = *goods;
            baught_goods_head->rate_able = 1;
            flag = 1;
            break;
        }
        head = head->next;
    }
    if (head == NULL) {
        printf("cannot find the goods.\n");
    }
    else if (flag == 0)
        printf("you have permission to rate goods you baught.\n");
}

void search(char* input, int logged_in_buyer_num, int logged_in_seller_num, struct goods** goods) {
    if (logged_in_buyer_num == -1 && logged_in_seller_num == -1) {       //someone should log in to use this command
        printf("please login first.\n");
        return;
    }
    char* first = NULL, * second = NULL, * third = NULL, * fourth = NULL;
    char* address_to_free1 = NULL, * address_to_free2 = NULL, * address_to_free3 = NULL, * address_to_free4 = NULL;
    char* name = NULL, * seller_username = NULL;
    int min_price = 0, max_price = 0;
    char* goods_attribute[4];
    char* attribute_value[4];
    for (int i = 0; i < 4; i++)
        goods_attribute[i] = NULL;
    for (int i = 0; i < 4; i++)
        attribute_value[i] = NULL;
    char* num_of_con = strtok_s(input, " ", &input);                    //getting the number of conditions
    int num_of_conditions = atoi(num_of_con);
    int a = num_of_conditions, counter = 0;
    while (a > 0) {
        a = a / 10;
        counter++;
    }
    if (num_of_conditions > 4 || num_of_conditions < 1 || strlen(num_of_con) != counter) {
        printf("invalid number of conditions.\n");
        return;
    }
    if (num_of_conditions == 1) {                                      //getting strings by the related function
        first = cmd_string_reader();
    }
    else if (num_of_conditions == 2) {
        first = cmd_string_reader();
        second = cmd_string_reader();
    }
    else if (num_of_conditions == 3) {
        first = cmd_string_reader();
        second = cmd_string_reader();
        third = cmd_string_reader();
    }
    else if (num_of_conditions == 4) {
        first = cmd_string_reader();
        second = cmd_string_reader();
        third = cmd_string_reader();
        fourth = cmd_string_reader();
    }
    if (first != NULL) {
        address_to_free1 = first;
        goods_attribute[0] = strtok_s(first, " ", &first);
        attribute_value[0] = strtok_s(first, "\n", &first);
    }
    if (second != NULL) {
        address_to_free2 = second;
        goods_attribute[1] = strtok_s(second, " ", &second);
        attribute_value[1] = strtok_s(second, "\n", &second);
    }
    if (third != NULL) {
        address_to_free3 = third;
        goods_attribute[2] = strtok_s(third, " ", &third);
        attribute_value[2] = strtok_s(third, "\n", &third);
    }
    if (fourth != NULL) {
        address_to_free4 = fourth;
        goods_attribute[3] = strtok_s(fourth, " ", &fourth);
        attribute_value[3] = strtok_s(fourth, "\n", &fourth);
    }
    int flag = 0;
    for (int i = 0; i < 4; i++) {
        if (goods_attribute[i] != NULL)
            flag++;
    }
    if (flag != num_of_conditions) {
        printf("you didn't write %d conditions.\n", num_of_conditions);
        return;
    }
    flag = 0;
    for (int i = 0; i < 4; i++) {                                     //checking if the strings are the defined ones or not
        if (goods_attribute[i] != NULL) {
            if (strcmp(goods_attribute[i], "name") == 0) {
                if (name == NULL)
                    name = attribute_value[i];
                else
                    flag = 1;
            }
            else if (strcmp(goods_attribute[i], "min_price") == 0) {
                if (min_price == 0)
                    min_price = atoi(attribute_value[i]);
                else
                    flag = 1;
            }
            else if (strcmp(goods_attribute[i], "max_price") == 0) {
                if (max_price == 0)
                    max_price = atoi(attribute_value[i]);
                else
                    flag = 1;
            }
            else if (strcmp(goods_attribute[i], "seller_username") == 0) {
                if (seller_username == NULL)
                    seller_username = attribute_value[i];
                else
                    flag = 1;
            }
            else {
                printf("invalid command.\n");
                return;
            }
            if (flag == 1) {
                printf("two similar commands has been written.\n");
                return;
            }
        }
    }
    struct goods* goods_head = (struct goods*)malloc(sizeof(struct goods));
    goods_head->next = *goods;
    int flag1 = sort_by_name(goods_head);
    *goods = goods_head->next;
    free(goods_head);
    goods_head = *goods;
    while (goods_head != NULL) {                                    //starts printing any goods the sellers have for sale that have the wanted trait
        if (goods_head->goods_past_owner != NULL) {
            goods_head = goods_head->next;
            continue;
        }
        if (name != NULL)
            if (strcmp(goods_head->goods_name, name) != 0) {
                goods_head = goods_head->next;
                continue;
            }
        if (seller_username != NULL)
            if (strcmp(goods_head->goods_owner, seller_username) != 0) {
                goods_head = goods_head->next;
                continue;
            }
        if (max_price != 0 && goods_head->goods_price > max_price) {
            goods_head = goods_head->next;
            continue;
        }
        if (min_price != 0 && goods_head->goods_price < min_price) {
            goods_head = goods_head->next;
            continue;
        }
        if (goods_head->rating < 2 && goods_head->num_of_rates > 4) {
            goods_head = goods_head->next;
            continue;
        }
        printf("\n");
        printf("seller's username: %s\n", goods_head->goods_owner);
        printf("goods name: %s\n", goods_head->goods_name);
        printf("goods price: %d\n", goods_head->goods_price);
        printf("goods count: %d\n", goods_head->goods_count);
        printf("goods rating: %f\n", goods_head->rating);
        printf("-------------------\n");
        goods_head = goods_head->next;
    }
    if (address_to_free1 != NULL)                            //freeing the strings
        free(address_to_free1);
    if (address_to_free2 != NULL)
        free(address_to_free2);
    if (address_to_free3 != NULL)
        free(address_to_free3);
    if (address_to_free4 != NULL)
        free(address_to_free4);
}

void free_buyers(struct buyer* buyers) {                   //starting from the end of the list and coming back
    if (buyers->next != NULL)
        free_buyers(buyers->next);
    free(buyers->username);                               //freeing pointers inside the struct first
    free(buyers->password);
    free(buyers);
}

void free_sellers(struct seller* sellers) {               //starting from the end of the list and coming back
    if (sellers->next != NULL)
        free_sellers(sellers->next);
    free(sellers->username);                              //freeing pointers inside the struct first
    free(sellers->password);
    free(sellers);
}

void free_goods(struct goods* goods) {                   //starting from the end of the list and coming back
    if (goods->next != NULL)
        free_goods(goods->next);
    free(goods->goods_name);                             //freeing pointers inside the struct first
    free(goods->goods_owner);
    if (goods->goods_past_owner != NULL)
        free(goods->goods_past_owner);
    free(goods);
}

void free_pointers(char* address_of_input, struct buyer** buyers, struct seller** sellers, struct goods** goods) {
    free(address_of_input);                               //at first we'll free all of the pointers inside the structures one by one, then we'll free the structure itself
    if ((*buyers) != NULL)                                //doing it for the buyers linked list
        free_buyers(*buyers);
    free(buyers);
    if ((*sellers) != NULL)                              //doing it for the sellers linked list
        free_sellers(*sellers);
    free(sellers);
    if ((*goods) != NULL)                                //doing it for the goods linked list
        free_goods(*goods);
    free(goods);
}

struct goods* sort_and_binary_tree_make(struct goods** goods, int num_of_goods) {
    struct goods* goods_head = (struct goods*)malloc(sizeof(struct goods));
    goods_head->next = *goods;
    int flag1 = sort_by_name(goods_head);                                     //at first we sort the goods
    *goods = goods_head->next;
    free(goods_head);
    struct goods* root = binary_tree_generator(*goods, 0, num_of_goods - 1);  //then we start making the binary tree
    return root;
}