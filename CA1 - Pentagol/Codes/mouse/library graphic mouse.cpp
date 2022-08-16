#include "Headergraphicmouse.h"
void spot_cleaner(char game_table[7][7]) {
    for (int i = 1; i < 7; i++) {                               //filling all the spots with dots (.) at the start of the game
        for (int j = 1; j < 7; j++) {
            game_table[i][j] = 96;
        }
    }
}
void display_printer(int Round, char table[7][7]) {            //prints the table
    int i, j;
    cleardevice();
    setcolor(WHITE);
    rectangle(20, 20, 580, 580);
    setfillstyle(SOLID_FILL, RED);
    floodfill(30, 30, WHITE);
    setcolor(WHITE);
    for (i = 80; i <= 520; i = i + 80) {                       //printing all 36 circles
        for (j = 80; j <= 520; j = j + 80) {
            if (j == 320)
                j += 40;
            circle(i, j, 30);
        }
        if (i == 240)
            i += 40;
    }
    line(300, 20, 300, 580);
    line(20, 300, 580, 300);
    setcolor(LIGHTGREEN);
    if (Round % 2 == 0)
        outtextxy(260, 2, "BLACK's turn: ");
    if (Round % 2 == 1)
        outtextxy(260, 2, "WHITE's turn: ");
    for (i = 1; i < 7; i++) {                                  //checking the arrays, if they are 'w' or 'b' then floodfill the related circle
        for (j = 1; j < 7; j++) {
            if (table[i][j] == 'w') {
                setfillstyle(SOLID_FILL, WHITE);
                floodfill(j * 85, i * 85, WHITE);
            }
            if (table[i][j] == 'b') {
                setfillstyle(SOLID_FILL, BLACK);
                floodfill(j * 85, i * 85, WHITE);
            }
        }
    }
}
void keyboard_move_input(int r, char table[7][7]) {                  //checks the key that the player presses and finds the related array
    printf("Enter the move:");
    int counter1 = 1, counter2 = 1, x, y, a = 1, b = 1, i = 0, j = 0;
    display_printer(r, table);
    while (1) {                                                  //getting player's input as long as he wants
        if (mousex() <= 120 && mousex() >= 40)
            counter1 = 1;
        if (mousex() <= 200 && mousex() >= 120)
            counter1 = 2;
        if (mousex() <= 280 && mousex() >= 200)
            counter1 = 3;
        if (mousex() <= 400 && mousex() >= 320)
            counter1 = 4;
        if (mousex() <= 480 && mousex() >= 400)
            counter1 = 5;
        if (mousex() <= 560 && mousex() >= 480)
            counter1 = 6;
        if (mousey() <= 120 && mousey() >= 40)
            counter2 = 1;
        if (mousey() <= 200 && mousey() >= 120)
            counter2 = 2;
        if (mousey() <= 280 && mousey() >= 200)
            counter2 = 3;
        if (mousey() <= 400 && mousey() >= 320)
            counter2 = 4;
        if (mousey() <= 480 && mousey() >= 400)
            counter2 = 5;
        if (mousey() <= 560 && mousey() >= 480)
            counter2 = 6;
        if (counter1 <= 3 && counter2 <= 3) {
            setcolor(RED);
            if (a != counter1 || b != counter2) {                   //printing rectangle around circles
                if (a > 3 && b > 3)
                    rectangle(240 + (a - 3) * 80, 240 + (b - 3) * 80, a * 80 + 80, b * 80 + 80);
                else if (a > 3 && b <= 3)
                    rectangle(240 + (a - 3) * 80, b * 80 - 40, a * 80 + 80, b * 80 + 40);
                else if (a <= 3 && b > 3)
                    rectangle(a * 80 - 40, 240 + (b - 3) * 80, a * 80 + 40, b * 80 + 80);
                else
                    rectangle(a * 80 - 40, b * 80 - 40, a * 80 + 40, b * 80 + 40);
            }
            setcolor(LIGHTGREEN);
            rectangle(counter1 * 80 - 40, counter2 * 80 - 40, counter1 * 80 + 40, counter2 * 80 + 40);
            a = counter1;
            b = counter2;
        }
        if (counter1 > 3 && counter2 > 3) {
            if (a != counter1 || b != counter2) {
                setcolor(RED);
                if (a <= 3 && b <= 3)
                    rectangle(a * 80 - 40, b * 80 - 40, a * 80 + 40, b * 80 + 40);
                else if (a > 3 && b <= 3)
                    rectangle(240 + (a - 3) * 80, b * 80 - 40, a * 80 + 80, b * 80 + 40);
                else if (a <= 3 && b > 3)
                    rectangle(a * 80 - 40, 240 + (b - 3) * 80, a * 80 + 40, b * 80 + 80);
                else
                    rectangle(240 + (a - 3) * 80, 240 + (b - 3) * 80, a * 80 + 80, b * 80 + 80);
            }
            setcolor(LIGHTGREEN);
            rectangle(240 + (counter1 - 3) * 80, 240 + (counter2 - 3) * 80, counter1 * 80 + 80, counter2 * 80 + 80);
            a = counter1;
            b = counter2;
        }
        if (counter1 > 3 && counter2 <= 3) {
            if (a != counter1 || b != counter2) {
                setcolor(RED);
                if (a <= 3 && b <= 3)
                    rectangle(a * 80 - 40, b * 80 - 40, a * 80 + 40, b * 80 + 40);
                else if (a > 3 && b > 3)
                    rectangle(240 + (a - 3) * 80, 240 + (b - 3) * 80, a * 80 + 80, b * 80 + 80);
                else if (a <= 3 && b > 3)
                    rectangle(a * 80 - 40, 240 + (b - 3) * 80, a * 80 + 40, b * 80 + 80);
                else
                    rectangle(240 + (a - 3) * 80, b * 80 - 40, a * 80 + 80, b * 80 + 40);
            }
            setcolor(LIGHTGREEN);
            rectangle(240 + (counter1 - 3) * 80, counter2 * 80 - 40, counter1 * 80 + 80, counter2 * 80 + 40);
            a = counter1;
            b = counter2;
        }
        if (counter1 <= 3 && counter2 > 3) {
            if (a != counter1 || b != counter2) {
                setcolor(RED);
                if (a <= 3 && b <= 3)
                    rectangle(a * 80 - 40, b * 80 - 40, a * 80 + 40, b * 80 + 40);
                else if (a > 3 && b > 3)
                    rectangle(240 + (a - 3) * 80, 240 + (b - 3) * 80, a * 80 + 80, b * 80 + 80);
                else if (a > 3 && b <= 3)
                    rectangle(240 + (a - 3) * 80, b * 80 - 40, a * 80 + 80, b * 80 + 40);
                else
                    rectangle(a * 80 - 40, 240 + (b - 3) * 80, a * 80 + 40, b * 80 + 80);
            }
            setcolor(LIGHTGREEN);
            rectangle(counter1 * 80 - 40, 240 + (counter2 - 3) * 80, counter1 * 80 + 40, counter2 * 80 + 80);
            a = counter1;
            b = counter2;
        }
        getmouseclick(WM_LBUTTONDOWN, y, x);                    //getting the place the player clicks and find the circle
        if (x <= 120 && x >= 40)
            i = 1;
        if (x <= 200 && x >= 120)
            i = 2;
        if (x <= 280 && x >= 200)
            i = 3;
        if (x <= 400 && x >= 320)
            i = 4;
        if (x <= 480 && x >= 400)
            i = 5;
        if (x <= 560 && x >= 480)
            i = 6;
        if (y <= 120 && y >= 40)
            j = 1;
        if (y <= 200 && y >= 120)
            j = 2;
        if (y <= 280 && y >= 200)
            j = 3;
        if (y <= 400 && y >= 320)
            j = 4;
        if (y <= 480 && y >= 400)
            j = 5;
        if (y <= 560 && y >= 480)
            j = 6;
        if (i >= 1 && i <= 6 && j >= 1 && j <= 6) {
            if (table[i][j] == 'w' || table[i][j] == 'b') {             //checks if the selected spot is full or not
                system("cls");
                printf("Spot is Full, find another one");
                continue;
            }
            else if (r % 2 == 0) {                                      //saving the selected array with 'w' or 'b'
                table[i][j] = 'b';
                break;
            }
            else if (r % 2 == 1) {
                table[i][j] = 'w';
                break;
            }
        }
    }
    return;
}
int rotator(int Round, char rotation, char game_table[7][7], int section_number) {
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
    for (int i = ii; i < ii + 3; i++) {                              //moving the selected section into a 3x3 array
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
    for (int i = 1; i < 4; i++) {                                   //switching rows and columns
        for (int j = i; j < 4; j++) {
            temp = section[i][j];
            section[i][j] = section[j][i];
            section[j][i] = temp;
        }
    }
    for (int j = 1; j < 4; j++) {                                  //changing column 1 with column 3, and now it is rotated clockwise
        temp = section[j][1];
        section[j][1] = section[j][3];
        section[j][3] = temp;
    }
    for (int i = ii; i < ii + 3; i++) {                            //returning the 3x3 array into the section
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
void left_rotator_for_section(int sec, char table[7][7]) {       //the function that rotates the selected section 90 degrees anticlockwise
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
    for (int i = ii; i < ii + 3; i++) {                          //putting the section into a 3x3 array
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
    for (int i = 1; i < 4; i++) {                                 //switching rows and columns
        for (int j = i; j < 4; j++) {
            temp = section[i][j];
            section[i][j] = section[j][i];
            section[j][i] = temp;
        }
    }
    for (int i = 1; i < 4; i++) {                                 //changing row 1 and 3, and now it's rotated
        temp = section[1][i];
        section[1][i] = section[3][i];
        section[3][i] = temp;
    }
    for (int i = ii; i < ii + 3; i++) {                           //returning the 3x3 array into the section
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
int rectangle_for_section_mover(int r, char table[7][7]) {        //checks the move that the player gives and finds the related array
    system("cls");
    int sec, x, y;
    display_printer(r, table);
    printf("Choose The Section by mouse");
    outtextxy(20, 2, "Choose The Section by mouse");
    while (1) {
        setcolor(YELLOW);                                        //printing rectangle around sections that mouse is in it
        if (mousex() <= 300 && mousex() >= 20 && mousey() <= 300 && mousey() >= 20)
            rectangle(30, 30, 290, 290);
        else {
            setcolor(RED);
            rectangle(30, 30, 290, 290);
        }
        setcolor(YELLOW);
        if (mousex() <= 580 && mousex() >= 300 && mousey() <= 580 && mousey() >= 300)
            rectangle(310, 310, 570, 570);
        else {
            setcolor(RED);
            rectangle(310, 310, 570, 570);
        }
        setcolor(YELLOW);
        if (mousex() <= 580 && mousex() >= 300 && mousey() <= 300 && mousey() >= 20)
            rectangle(310, 30, 570, 290);
        else {
            setcolor(RED);
            rectangle(310, 30, 570, 290);
        }
        setcolor(YELLOW);
        if (mousex() <= 300 && mousex() >= 20 && mousey() <= 580 && mousey() >= 300)
            rectangle(30, 310, 290, 570);
        else {
            setcolor(RED);
            rectangle(30, 310, 290, 570);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);                    //getting the place the player clicks and find the selected section
        if (x >= 20 && x <= 300) {
            if (y >= 20 && y <= 300) {
                sec = 2;
                break;
            }
            else if (y >= 300 && y <= 580) {
                sec = 3;
                break;
            }
        }
        else if (x >= 300 && x <= 580) {
            if (y >= 20 && y <= 300) {
                sec = 1;
                break;
            }
            else if (y >= 300 && y <= 580) {
                sec = 4;
                break;
            }
        }

    }
    return sec;
}
int rotation_flesh_right_or_left(int r, int sec, char table[7][7]) {   //printing a sign that shows the selected rotation direction
    int x, y, right = 0, left = 0;
    char rotate;
    int i = 160, j = 160;
    if (sec == 1)
        i += 280;
    if (sec == 3)
        j += 280;
    if (sec == 4) {
        i += 280;
        j += 280;
    }
    display_printer(r, table);
    system("cls");
    printf("Choose The Direction (switch by 'a'or'd') Press 'f' to continue: ");
    outtextxy(i - 100, j - 159, "Choose Direction by mouse");
    while (1) {
        if (mousex() <= i && mousex() >= i - 150 && mousey() <= j + 160 && mousey() >= j - 160)
            left = 1;
        else
            left = 0;
        if (mousex() <= i + 150 && mousex() >= i && mousey() <= j + 160 && mousey() >= j - 160)
            right = 1;
        else
            right = 0;
        if (left == 1) {                                                 //printing the right sign
            setcolor(WHITE);
            arc(i - 80, j - 80, 110, 160, 55);
            arc(i - 80, j - 80, 110, 160, 40);
            line(i - 93, j - 117, i - 99, j - 133);
            line(i - 115, j - 93, i - 134, j - 100);
            line(i - 115, j - 93, i - 130, j - 80);
            line(i - 130, j - 80, i - 134, j - 100);
            setcolor(LIGHTGREEN);
            setfillstyle(SOLID_FILL, LIGHTGREEN);
            floodfill(i - 110, j - 115, WHITE);
            floodfill(i - 120, j - 90, WHITE);
            setfillstyle(SOLID_FILL, RED);
            floodfill(i + 110, j - 110, WHITE);
            floodfill(i + 120, j - 90, WHITE);
            setcolor(RED);
            arc(i + 80, j - 80, 20, 70, 55);
            arc(i + 80, j - 80, 20, 70, 40);
            line(i + 93, j - 117, i + 97, j - 133);
            line(i + 115, j - 93, i + 134, j - 100);
            line(i + 115, j - 93, i + 130, j - 80);
            line(i + 130, j - 80, i + 134, j - 100);
        }
        if (right == 1) {                                               //printing the left sign
            setcolor(WHITE);
            arc(i + 80, j - 80, 20, 70, 55);
            arc(i + 80, j - 80, 20, 70, 40);
            line(i + 93, j - 117, i + 97, j - 133);
            line(i + 115, j - 93, i + 134, j - 100);
            line(i + 115, j - 93, i + 130, j - 80);
            line(i + 130, j - 80, i + 134, j - 100);
            setfillstyle(SOLID_FILL, LIGHTGREEN);
            floodfill(i + 110, j - 110, WHITE);
            floodfill(i + 120, j - 90, WHITE);
            setfillstyle(SOLID_FILL, RED);
            floodfill(i - 110, j - 115, WHITE);
            floodfill(i - 120, j - 90, WHITE);
            setcolor(RED);
            arc(i - 80, j - 80, 110, 160, 55);
            arc(i - 80, j - 80, 110, 160, 40);
            line(i - 93, j - 117, i - 99, j - 133);
            line(i - 115, j - 93, i - 134, j - 100);
            line(i - 115, j - 93, i - 130, j - 80);
            line(i - 130, j - 80, i - 134, j - 100);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if (x <= i && x >= i - 150 && y <= j + 160 && y >= j - 160) {     //if the player clicks on the left side
            rotate = '-';
            break;
        }
        if (x <= i + 150 && x >= i && y <= j + 160 && y >= j - 160) {     //if the player clicks on the right side
            rotate = '+';
            break;
        }
    }
    system("cls");
    return rotate;
}
int black_wining_checker(char game_table[7][7], int r) {                 //checking if black player wins in each possible condition
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
int white_wining_checker(char game_table[7][7], int r) {                 //checking if white player wins in each possible condition
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
int vertical_winner_checker(char a, char table[7][7]) {   //checks whether any of players win the game in vertical pattern (4 same characters in a row and one up or down at the end of it)
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
int horizontal_winner_checker(char a, char table[7][7]) {            //checks whether any of players win the game in horizontal pattern
    int i, j, Flag = 0;
    for (j = 1; j < 7; j++) {
        for (i = 1; i < 7; i++) {
            if (table[i][j] == a)
                Flag++;
            else
                Flag = 0;
            if (Flag == 4) {                                         //4 characters in a row and one right or left at the end of it should be same
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
int restarting_the_game(int restart) {                   //checks if the players want to restart the game or not
    int x, y, z;
    outtextxy(120, 26, "left click to Restart the Game or right click to Exit");
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_RBUTTONDOWN);
    while (1) {
        getmouseclick(WM_LBUTTONDOWN, x, y);
        getmouseclick(WM_RBUTTONDOWN, z, y);
        if (x != -1) {
            break;
        }
        if (z != -1) {
            system("cls");
            restart = 0;
            break;
        }
    }
    return restart;
}
void winner_printer(int w, int b, int r) {
    if (b == 5 && w == 6) {                            //checking if both of the players won the game or just each of them
        system("cls");
        printf("Both Players win at the same time!!!! ");
        outtextxy(180, 2, "Both Players win at the same time!!!! ");
        return;
    }
    else if (b == 5) {
        outtextxy(240, 2, "BLACK Player wins! ");
        printf("BLACK Player wins! ");
        return;
    }
    else if (w == 6) {
        outtextxy(240, 2, "WHITE Player wins! ");
        printf("WHITE Player wins! ");
        return;
    }
    else if (r == 36) {
        setcolor(LIGHTGREEN);
        outtextxy(255, 2, "   It's A Draw!  ");
        printf("It's A Tie!\n");
        return;
    }
    else if (r % 2 == 0)
        printf("BLACK players turn: ");
    else if (r % 2 == 1)
        printf("WHITE players turn: ");
}