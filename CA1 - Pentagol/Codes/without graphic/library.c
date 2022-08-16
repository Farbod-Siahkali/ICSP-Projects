#include "Header.h"

void table_printer(char game_table[7][7]) {                        //declaring the function that prints the game table
    system("cls");
    int x = 1;
    game_table[0][0] = 32;
    printf("%c    ", game_table[0][0]);
    for (int j = 1; j < 7; j++) {
        game_table[0][j] = x;
        x++;
        printf("%d    ", game_table[0][j]);
        if (x == 4)
            printf("|    ");
    }
    printf("\n\n");
    int y;
    x = y = 1;
    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (j == 0) {
                game_table[i][0] = x;
                printf("%d    ", game_table[i][0]);
                x++;
            }
            else {
                printf("%c    ", game_table[i][j]);
                if (j == 3)
                    printf("|    ");
            }
            if (j == 6) {
                printf("\n\n");
                y++;
            }
            if (y == 4) {
                printf("--   --   --   --       --    --   --\n\n");
                y = 0;
            }
        }
    }
}
int get_int_input() {                                  //declaring a functon that checks the input until it gets an int
    int z, temp, status;
    status = scanf_s("%d", &z);
    while (status != 1) {
        while ((temp = getchar()) != EOF && temp != '\n');
        printf("Invalid input, Please Try again: ");
        status = scanf_s("%d", &z);
    }
    return z;
}
int move_checker(int seperate[2]) {                   //checks the move that the player gives and finds the related array
    int move = get_int_input();
    while (move > 66 || move < 11) {
        printf("Invalid Input, Please Try again: ");
        move = get_int_input();
    }
    seperate[0] = move % 10;                        //finding the ones
    seperate[1] = move / 10;                        //finding the tens
    while (seperate[0] == 0 || seperate[0] == 7 || seperate[0] == 8 || seperate[0] == 9 || seperate[1] == 0 || seperate[1] == 7 || seperate[1] == 8 || seperate[1] == 9) {
        printf("Invalid Input, Please Try again: ");
        move = get_int_input();
        seperate[0] = move % 10;
        seperate[1] = move / 10;
    }
    return move;
}
void spot_checker(int move, int seperate[2], char game_table[7][7], int Round) {      //checks the spot whether it's full or not, if it is full it goes to get another number
    while (game_table[seperate[1]][seperate[0]] == 'w' || game_table[seperate[1]][seperate[0]] == 'b') {
        printf("Spot is full, Please Enter another number: ");
        move = move_checker(seperate);
    }
    if (Round % 2 == 0)
        game_table[seperate[1]][seperate[0]] = 'b';
    else if (Round % 2 == 1)
        game_table[seperate[1]][seperate[0]] = 'w';
}
int rotator(int Round, char game_table[7][7], int section_number) {
    printf("Choose The Direction You Want (+ or -): ");                //getting the section and checking whether it is valid or not
    char rotation;
    while (getchar() != '\n');
    int check = 0;
    while (check == 0) {
        rotation = getchar();
        if (rotation != '+' && rotation != '-') {
            printf("Invalid Direction, Please Try again: ");
            while (getchar() != '\n');
        }
        else
            check = 1;
    }
    if (rotation == '+')                                              //if rotate is +, move the section in 3x3 matrix and rotate it clockwise by the function
        right_rotator_for_section(section_number, game_table);
    if (rotation == '-')                                              //if rotate is -, move the section in 3x3 matrix and rotate it anticlockwise by the function
        left_rotator_for_section(section_number, game_table);
    Round++;
    return Round;
}
void right_rotator_for_section(int sec, char table[7][7]) {          //the function that rotates the selected section 90 degrees clockwise
    char temp, section[4][4];
    int ii = 1, jj = 4;
    if (sec == 2)
        ii = jj = 1;
    if (sec == 3) {
        ii = 4;
        jj = 1;
    }
    if (sec == 4)
        ii = jj = 4;
    for (int i = ii; i < ii + 3; i++) {                           //moving the selected section into a 3x3 array
        for (int j = jj; j < jj + 3; j++) {
            if (sec == 1)
                section[i][j - 3] = table[i][j];
            else if (sec == 2)
                section[i][j] = table[i][j];
            else if (sec == 3) {
                if (i > 2)
                    section[i - 3][j] = table[i][j];
            }
            else if (sec == 4) {
                if (i > 2 && j > 2)
                    section[i - 3][j - 3] = table[i][j];
            }
        }
    }
    for (int i = 1; i < 4; i++) {                               //switching rows and columns
        for (int j = i; j < 4; j++) {
            temp = section[i][j];
            section[i][j] = section[j][i];
            section[j][i] = temp;
        }
    }
    for (int j = 1; j < 4; j++) {                             //changing column 1 with column 3, and now it is rotated clockwise
        temp = section[j][1];
        section[j][1] = section[j][3];
        section[j][3] = temp;
    }
    for (int i = ii; i < ii + 3; i++) {                      //returning the 3x3 array into the section
        for (int j = jj; j < jj + 3; j++) {
            if (sec == 1)
                table[i][j] = section[i][j - 3];
            else if (sec == 2)
                table[i][j] = section[i][j];
            else if (sec == 3) {
                if (i > 2)
                    table[i][j] = section[i - 3][j];
            }
            else if (sec == 4) {
                if (i > 2 && j > 2)
                    table[i][j] = section[i - 3][j - 3];
            }
        }
    }
}
void left_rotator_for_section(int sec, char table[7][7]) {     //the function that rotates the selected section 90 degrees anticlockwise
    char temp, section[4][4];
    int ii = 1, jj = 4;
    if (sec == 2)
        ii = jj = 1;
    if (sec == 3) {
        ii = 4;
        jj = 1;
    }
    if (sec == 4)
        ii = jj = 4;
    for (int i = ii; i < ii + 3; i++) {
        for (int j = jj; j < jj + 3; j++) {
            if (sec == 1)
                section[i][j - 3] = table[i][j];
            else if (sec == 2)
                section[i][j] = table[i][j];
            else if (sec == 3) {
                if (i > 2)
                    section[i - 3][j] = table[i][j];
            }
            else if (sec == 4) {
                if (i > 2 && j > 2)
                    section[i - 3][j - 3] = table[i][j];
            }
        }
    }
    for (int i = 1; i < 4; i++) {                               //switching rows and columns
        for (int j = i; j < 4; j++) {
            temp = section[i][j];
            section[i][j] = section[j][i];
            section[j][i] = temp;
        }
    }
    for (int i = 1; i < 4; i++) {                             //changing row 1 with row 3, and now it is rotated clockwise
        temp = section[1][i];
        section[1][i] = section[3][i];
        section[3][i] = temp;
    }
    for (int i = ii; i < ii + 3; i++) {                      //returning the 3x3 array into the section
        for (int j = jj; j < jj + 3; j++) {
            if (sec == 1)
                table[i][j] = section[i][j - 3];
            else if (sec == 2)
                table[i][j] = section[i][j];
            else if (sec == 3) {
                if (i > 2)
                    table[i][j] = section[i - 3][j];
            }
            else if (sec == 4) {
                if (i > 2 && j > 2)
                    table[i][j] = section[i - 3][j - 3];
            }
        }
    }
}
int vertical_winner_checker(char a, char table[7][7]) {       //checks whether any of players win the game in vertical pattern (4 same characters in a row and one up or down at the end of it)
    int i, j, Flag = 0;
    for (i = 1; i < 7; i++) {
        for (j = 1; j < 7; j++) {
            if (table[i][j] == a)
                Flag++;
            else
                Flag = 0;
            if (Flag == 4) {
                if (table[i + 1][j] == a || table[i - 1][j] == a) {
                    Flag = 5;
                    break;
                }
                if (i < 6 && j > 2)
                    if (table[i + 1][j - 3] == a) {
                        Flag = 5;
                        break;
                    }
                if (j > 2)
                    if (table[i - 1][j - 3] == a) {
                        Flag = 5;
                        break;
                    }
                if (Flag == 4)
                    Flag = 3;
            }
        }
        if (Flag == 5) {
            if (a == 'w')
                Flag++;
            return Flag;
            break;
        }
    }
    return 0;
}
int horizontal_winner_checker(char a, char table[7][7]) {         //checks whether any of players win the game in horizontal pattern
    int i, j, Flag = 0;
    for (j = 1; j < 7; j++) {
        for (i = 1; i < 7; i++) {
            if (table[i][j] == a)
                Flag++;
            else
                Flag = 0;
            if (Flag == 4) {                                     //4 characters in a row and one right or left at the end of it should be same
                if (table[i][j + 1] == a || table[i][j - 1] == a) {
                    Flag = 5;
                    break;
                }
                if (i > 2 && j < 6)
                    if (table[i - 3][j + 1] == a) {
                        Flag = 5;
                        break;
                    }
                if (i > 2)
                    if (table[i - 3][j - 1] == a) {
                        Flag = 5;
                        break;
                    }
                if (Flag == 4)
                    Flag = 3;
            }
        }
        if (Flag == 5) {
            if (a == 'w')
                Flag++;
            return Flag;
            break;
        }
    }
    return 0;
}
int faced_down_oblique_winner_checker(char a, char table[7][7]) {     //checks that whether any player win the game by having a faced down oblique ( like a backslash \ ) 
    int x, y, i, j, Flag = 0;
    for (j = 1; j < 4; j++) {
        for (i = 1; i < 4; i++) {
            x = i;
            y = j;
            while (table[x][y] == a) {
                Flag++;
                if (Flag == 4) {
                    i = x;
                    j = y;
                    break;
                }
                x++;
                y++;
            }
            if (Flag < 4 && Flag > 0)
                Flag = 0;
            if (Flag == 4) {                                     //if there is 4 same characters in a row check the neighbors
                if (table[i - 1][j + 1] == a) {
                    Flag = 5;
                }
                if (i < 6) {
                    if (table[i + 1][j - 1] == a) {
                        Flag = 5;
                    }
                }
                if (i > 1 && j > 3) {
                    if (table[i - 2][j - 4] == a)
                        Flag = 5;
                }
                if (i > 3 && j > 1) {
                    if (table[i - 4][j - 2] == a)
                        Flag = 5;
                }
                if (Flag == 4)
                    Flag = 3;
            }
            if (Flag == 5) {
                if (a == 'w')
                    Flag++;
                return Flag;
                break;
            }
        }
    }
    return 0;
}
int faced_up_oblique_winner_checker(char a, char table[7][7]) {      //checks that whether any player win the game by having a faced up oblique ( like a slash / ) 
    int x, y, i, j, Flag = 0;
    for (j = 6; j > 3; j--) {
        for (i = 1; i < 4; i++) {
            x = i;
            y = j;
            while (table[x][y] == a) {
                Flag++;
                if (Flag == 4) {
                    i = x;
                    j = y;
                    break;
                }
                x++;
                y--;
            }
            if (Flag < 4 && Flag > 0)
                Flag = 0;
            if (Flag == 4) {
                if (table[i - 1][j - 1] == a)
                    Flag = 5;
                if (j < 6 && i < 6)
                    if (table[i + 1][j + 1] == a) {
                        Flag = 5;
                    }
                if (i > 1 && j < 3)
                    if (table[i - 2][j + 4] == a) {
                        Flag = 5;
                    }
                if (i > 3 && j < 5)
                    if (table[i - 4][j + 2] == a) {
                        Flag = 5;
                    }
                if (Flag == 4)
                    Flag = 3;
            }
            if (Flag == 5) {
                if (a == 'w')
                    Flag++;
                return Flag;
                break;
            }
        }
    }
    return 0;
}
int black_wining_checker(char game_table[7][7], int r) {                      //checks if black player wins in any possile condition
    int blackwin = 0;
    if (r > 8) {
        blackwin = vertical_winner_checker('b', game_table);
        if (blackwin != 5)
            blackwin = horizontal_winner_checker('b', game_table);
        if (blackwin != 5)
            blackwin = faced_down_oblique_winner_checker('b', game_table);
        if (blackwin != 5)
            blackwin = faced_up_oblique_winner_checker('b', game_table);
    }
    return blackwin;
}
int white_wining_checker(char game_table[7][7], int r) {                      //checks if white player wins in any possible condition
    int whitewin = 0;
    if (r > 8) {
        whitewin = vertical_winner_checker('w', game_table);
        if (whitewin != 6)
            whitewin = horizontal_winner_checker('w', game_table);
        if (whitewin != 6)
            whitewin = faced_down_oblique_winner_checker('w', game_table);
        if (whitewin != 6)
            whitewin = faced_up_oblique_winner_checker('w', game_table);
    }
    return whitewin;
}
int restarting_the_game(int restart) {                                         //checks if players want to restart or not
    printf("Press 'r' to Restart the Game or other buttoms to Exit");
    char z = _getch();
    if (z != 'r') {
        system("cls");
        restart = 0;
    }
    return restart;
}
void winner_printer(int w, int b, int r, char game_table[7][7]) {             //checking if both of the players won the game or just each of them
    if (b == 5 && w == 6) {
        printf("Both Players win at the same time!!!!\n");
    }
    else if (b == 5) {
        printf("BLACK Player wins!\n");
    }
    else if (w == 6) {
        printf("WHITE Player wins!\n");
    }
    else if (r == 36) {
        printf("It's A Tie!\n");
    }
}