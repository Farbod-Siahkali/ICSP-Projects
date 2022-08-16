#include <stdio.h>

int main()
{
    int  people, money, i, ten, twenty, fourty, x = 0, y = 0;
    ten = twenty = fourty = 0;
    x = scanf_s("%d", &people);                                               //get number of people standing in line
    if (x != 1 || people < 0) {
        printf("wrong input\n");
        return (0);
    }
    for (i = 1; i <= people; i++) {                                           //run a for loop to check each money
        y = scanf_s("%d", &money);                                            //scan the input money
        if (y != 1) {
            printf("wrong input\n");
            return (0);
        }
        while (money != 10 && money != 20 && money != 40) {                      //checking if the money is authorized, otherwise stop the program
            printf("money not accepted try again.\n");
            scanf_s("%d", &money);
        }
        if (money == 10) {                                                    //if money is 10, save it
            ten++;
        }
        if (money == 20) {                                                    //if money is 20, return 10 toman
            if (ten >= 1) {
                ten--;
                twenty++;
            }
            else {                                                            //if you dont have 10 toman, then print "NO" and stop the program
                printf("NO\n");
                return(0);
            }
        }
        if (money == 40) {                                                   //if you get a 40 toman
            if ((ten >= 1 && twenty >= 1) || (ten >= 3 && twenty == 0)) {

                if (ten >= 1 && twenty >= 1) {                               //if you more than one 10 toman and more than one 20 toman
                    ten--;                                                   //get the 40 and return one 10 and one 20 toman
                    twenty--;
                    fourty++;
                }
                else {                                                       //otherwise if you have three 10 tomans, get the 40 and give three 10 tomans
                    ten = ten - 3;
                    fourty++;
                }
            }
            else {                                                          //if you dont have any of those conditions, print "NO" and stop the program
                printf("NO\n");
                return(0);
            }
        }
    }
    printf("YES\n");                                                        //if you checked all moneys and they were OK, print "YES"
    return 0;
}
