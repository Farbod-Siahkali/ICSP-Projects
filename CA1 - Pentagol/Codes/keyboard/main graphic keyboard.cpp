#include "Headergraphickeyboard.h"
int main() {
    initwindow(620, 620, "PENTAGOL");
    int Round, whitewin, blackwin, restart = 1;
    char game_table[7][7];
    while (restart == 1) {
        Round = whitewin = blackwin = 0;
        spot_cleaner(game_table);                                                            //filling all spots with dots
        while (1) {
            display_printer(Round, game_table);                                              //printing the table
            winner_printer(whitewin, blackwin, Round);
            if (whitewin == 6 || blackwin == 5 || Round == 36)
                break;
            pointer_for_circles(Round, game_table);
            int section_number = pointer_for_sections(Round, game_table);                    //getting the section and checking whether it is valid or not
            char rotation = rotation_flesh_right_or_left(Round, section_number, game_table); //getting rotation direction
            Round = rotator(Round, rotation, game_table, section_number);                    //rotating the section
            whitewin = white_wining_checker(game_table, Round);                              //checking if any of players win the game
            blackwin = black_wining_checker(game_table, Round);
        }
        restart = restarting_the_game(restart);                                              //check if players want to restart the game or not
    }
    closegraph();
    return 0;
}