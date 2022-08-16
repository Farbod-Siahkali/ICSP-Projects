#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void table_printer(char game_table[7][7]);
int rotator(int Round, char game_table[7][7], int section_number);
void right_rotator_for_section(int sec, char table[7][7]);
void left_rotator_for_section(int sec, char table[7][7]);
int vertical_winner_checker(char a, char table[7][7]);
int horizontal_winner_checker(char a, char table[7][7]);
int faced_down_oblique_winner_checker(char a, char table[7][7]);
int faced_up_oblique_winner_checker(char a, char table[7][7]);
int black_wining_checker(char game_table[7][7], int r);
int white_wining_checker(char game_table[7][7], int r);
int restarting_the_game(int restart);
int get_int_input();
int move_checker(int seperate[2]);
void spot_checker(int move, int seperate[2], char game_table[7][7], int Round);
void winner_printer(int w, int b, int r, char game_table[7][7]);