#include <stdio.h>
int main()
{
    float H, W, B, j;
    int x, y, z;
    x = y = z = 0;
    printf("Enter H \n");
    x = scanf_s("%f", &H);                                           //getting input H (Asghar's Height)
    if (x != 1) {                                                    //checking if input is valid. if not, print "inputs are not accepted" and stop the program
        printf("invalid input \n");
        return (0);
    }
    if (H < 0) {                                                     //checking the conditions of the question. if they are not approved, print "-1"
        printf("-1\n");
        return(0);
    }
    printf("Enter B \n");
    y = scanf_s("%f", &B);                                           //getting input B (the coefficient that changes the Height of the ball)
    if (y != 1) {                                                    //checking if inputs are valid. if not, print "inputs are not accepted" and stop the program
        printf("invalid input \n");
        return (0);
    }
    if (B < 0 || B >= 1) {                                          //checking the conditions of the question. if they are not approved, print "-1"
        printf("-1\n");
        return(0);
    }
    printf("Enter W \n");
    z = scanf_s("%f", &W);                                          //getting the input W (Mom's Height)
    if (z != 1) {                                                   //checking if inputs are valid. if they are not approved, print "inputs are not accepted" and stop the program
        printf("invalid input \n");
        return (0);
    }
    if (W < 0 || W >= H) {                                          //checking the conditions of the question. if they are not approved, print "-1"
        printf("-1\n");
        return(0);
    }
    j = 1;
    H = B * H;
    while (H >= W) {                                                //start the loop until the ball is Higher than the mom's Height or they are at the same Height
        if (H == W) {                                               //if the ball's Height is equal to the mom's Height, she will see the ball just once
            H = B * H;                                              //calculating the ball's next Height
            j++;                                                    //adding "1" to the times that the mom saw the ball
        }
        if (H > W) {                                                //if the ball goes Higher than the mom's Height, she will see the ball twice.
            H = B * H;                                              //calculating the ball's next Height
            j = j + 2;                                              //adding "2" to the times that the mom saw the ball
        }
    }
    printf("%f", j);
    return 0;
}