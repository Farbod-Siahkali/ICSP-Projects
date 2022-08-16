#include "Header.h"
int main() {
    char game_table[7][7];
    int restart = 1, seperate[2];
    while (restart == 1) {
        int i, j, Round = 0, whitewin = 0, blackwin = 0;
        for (i = 1; i < 7; i++) {                                                 //filling all the spots with dots (.) at the start of the game
            for (j = 1; j < 7; j++) {
                game_table[i][j] = 96;
            }
        }
        while (1) {
            table_printer(game_table);                                             //printing the game table
            winner_printer(whitewin, blackwin, Round, game_table);
            if (whitewin == 6 || blackwin == 5 || Round == 36)
                break;
            if (Round % 2 == 0)
                printf("BLACK players turn: ");
            if (Round % 2 == 1)
                printf("WHITE players turn: ");
            int move = move_checker(seperate);                                     //getting the move input
            spot_checker(move, seperate, game_table, Round);                       //checks if spot is full or not
            table_printer(game_table);
            printf("Choose The Section You want to Rotate (type from 1 to 4):");
            int section_number = get_int_input();                                  //getting the section and checking whether it is valid or not
            while (section_number != 1 && section_number != 2 && section_number != 3 && section_number != 4) {
                printf("Invalid Input, Please Try again: ");
                section_number = get_int_input();
            }
            Round = rotator(Round, game_table, section_number);                    //rotating the section
            whitewin = white_wining_checker(game_table, Round);                    //checks if white player wins
            blackwin = black_wining_checker(game_table, Round);                    //checks if black players wins
        }
        restart = restarting_the_game(restart);                                    //checks if players want to restart or not
    }
    return 0;
}