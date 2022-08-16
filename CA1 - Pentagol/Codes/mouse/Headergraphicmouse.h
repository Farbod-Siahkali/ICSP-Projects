#include "graphics.h"
#include <stdio.h>

void spot_cleaner(char game_table[7][7]);
void display_printer(int Round, char table[7][7]);
int rotator(int Round, char rotation, char game_table[7][7], int section_number);
void right_rotator_for_section(int sec, char table[7][7]);
void left_rotator_for_section(int sec, char table[7][7]);
void keyboard_move_input(int r, char table[7][7]);
int rectangle_for_section_mover(int r, char table[7][7]);
int faced_down_oblique_winner_checker(char a, char table[7][7]);
int faced_up_oblique_winner_checker(char a, char table[7][7]);
int vertical_winner_checker(char a, char table[7][7]);
int horizontal_winner_checker(char a, char table[7][7]);
int rotation_flesh_right_or_left(int r, int sec, char table[7][7]);
void winner_printer(int w, int b, int r);
int black_wining_checker(char game_table[7][7], int r);
int white_wining_checker(char game_table[7][7], int r);
int restarting_the_game(int restart);