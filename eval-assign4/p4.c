/*
struct point2d{
    int x;
    int y;
}

int main(char* argc, char* argv){
    int m = atoi(argv[1]);
    struct point2d *p = malloc(sizeof(struct point2d));
    p->x = atoi(argv[2]);
    p->y = atoi(argv[3]);
    struct point2d *z = malloc(sizeof(struct point2d));
    z->x = 0;
    z->y = z->y - (m * p->x);
    printf("x coord: %d\n", p->x);
    printf("y coord: %d\n", p->y);
    return 0
}
*/

// There are a couple of design issues that we can immediately see need fixing
/*
- the struct should be defined in a header file and it is missing a semi-colon at the end of it
- we need to free p and z at the end to avoid a memory leak
- argc should simply be an int and not a string/array
- we should be running a check for what argc is before we just grab items from argv to avoid security issues
- we need to load in the stdlib.h library to use atoi
- z->y is accessed before it has been initialized

All of these things I noticed by just reading the code and also by compiling it used -Wall -Werror -Wextra and -pedantic
*/


// I will start by correctly configuring a header file for this code and loading all the necessary libraries
// I will then add the missing semi-colon in the struct definition and I will fix the arguments to main()
// I then added a check for the number of arguments supplied and I freed both p and z after they were used

// Next I started to think about what this code might be wanting to achieve
// Seeing the form y - m*x reminded me a lot the equation for a line
// I then realized that this looks like a case where the user inputs a slope as well as the x and y coordinate of a pointe 
// This code then could be used to calculate the intercept of a line with slope m that passes through the user supplied (x,y)

// In order to get this behavior we need to replace z->y = z->y - (m*p->x) with z->y = p->y - (m*p->x)
// Finally we should make use of this information so we should print this value of z in an informative way

// I also modularized the code by putting the main functionality into a separate function called `intercept`

#include <stdlib.h>
#include "p4.h"

void intercept(int m, int x, int y){
    struct point2d *p = malloc(sizeof(struct point2d));
    p->x = x;
    p->y = y;
    struct point2d *z = malloc(sizeof(struct point2d));
    z->x = 0;
    z->y = p->y - (m*p->x);
    printf("the line through (%d, %d) with slope %d must cross the y-axis at (0, %d)\n", p->x, p->y, m, z->y);
    free(p);
    free(z);
}

int main(int argc, char* argv[]){
    printf("note that this code expects the user supplied arguments to be integers and runs atoi() on the arguments\n");
    printf("if a user supplies arguments that are not integers the behavior will be defined by however atoi() operates on values that are not integers\n");
    // if the user supplies less than 4 arguments then accessing argv[3] will have undefined behavior
    if (argc < 4) {
        // even though the input file is one of the arguments for the user it makes sense to think og
        // the slope and two coordinates as the inputs needed from them so we subtract 1 from argc to 
        // describe how many arguments were supplied
        printf("not enough argument supplied. expected 3, but given %d\n", argc - 1);
        return 0;
    }
    if (argc > 4) {
        printf("only 3 arguments are needed, but %d were supplied.\n", argc - 1);
        return 0;
    }
    intercept(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    return 0;

}

// In order to test this code I ran several tests in the terminal
// additionally each time I compiled the file I used -Wall -Wextra -Werror -pedantic and -Wcoversion in the makefile

// After running make p4 I ran the following tests

// ./p4 1 2 3
// ./p4 1 2
// ./p4 1 2 3 4

// This was equivalence class testing on the number of arguments given to the code where we tried two incorrect numbers and one correct number
// As expected a message was printed and the program was exited when the incorrect number of arguments was supplied

// I added some print statements at the top of the code to notify the users that the code expects integer inputs and so any non-integer inputs will 
// be used in whatever way atoi() operates on them.

