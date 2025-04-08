#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 3

// this code is a representation of the game Tower of Hanoi, which
// the player needs to put all the tiles from the left column to the
// right column, moving one tile at a time and not having a bigger
// tile above a smaller one

// the game takes the player inputs as origin column and destination
// column, taking the tile on top. if a move is illegal, it is not
// computed and the number of moves stays the same

// i recommend just using around 20 tiles max, because the plotting isnt
// so fast from there

int check(int (*hanoi)[COLUMNS], int n){

    // this secondary function is a game checker, if the person puts all
    // the tiles on the third tower, they win
    int a = 0;
    for(int i= 0; i<n; i++){
        if(hanoi[i][COLUMNS-1] != i+1){
            a =1;
        }
    }
    return a;
}

void tile(int n, int h){

    // this function has just the purpose to show the machine how it
    // will display the tiles

    if(h == 0){
        // in case the number in the array is 0, it will be shown
        //differently than the other numbers
        goto caseZero;
    }

    int i;
    int k = 2*h-1;

    // these are for tiles that dont have a value of 0 (all of them lmao)
    for(i = 1; i<=n-h; i++){
        printf(" ");
    }
    printf("(");
    for(i =1; i<=k; i++){
        printf("O");
    }
    printf(")");
    for(i = 1; i<=n-h; i++){
        printf(" ");
    }
    goto end;

    caseZero:
        for(i =1; i<n-h+1; i++){
            printf(" ");
        }
        printf("|");
        for(i =1; i<n-h+1; i++){
            printf(" ");
        }
    end:
}

void plot(int (*hanoi)[COLUMNS], int n){

    //this function is just for plotting the tiles, using the tile() function

    for(int i=0; i<n; i++){
        for(int j=0; j<COLUMNS; j++){
            tile(n, hanoi[i][j]);
        }
        printf("\n");
    }
}

void changeTiles(int o, int d, int n, int (*hanoi)[COLUMNS], int *m){

    // this function changes the 2-dimensional array 'hanoi'if:
    // - the origin and destination of tiles are between the range (1 - 3)
    // - the tile of origin is smaller than the tile of destination when above
    // - in case the whole column is made with 0's, the tile will be in the bottom

    // VARIABLES
    // 'o' and 'd' origin and destination
    // i and j are used in for loops
    // m is the number of moves
    // hanoi is the 2-dimensional array that contain the tiles

    //every 'goto end' means to stop the function, whether the inputs are right or not
    if (o > COLUMNS || o < 1 || d > COLUMNS || d < 1){
        goto end;
    }

    o--;
    d--;
    //these decreases in o and d is for the index being read corectly

    for(int i=0; i<n; i++){
        if(hanoi[i][o] !=0){
            for(int j=0; j<n; j++){
                if(j < n-1 && hanoi[j+1][d] < hanoi[i][o] && hanoi[j+1][d] != 0){
                    goto end;
                }
                if((hanoi[j+1][d] != 0) || (j == n-1 && hanoi[j][d] == 0)){
                    hanoi[j][d] = hanoi[i][o];
                    hanoi[i][o] = 0;
                    *m =*m +1;
                    goto end;
                }
            }
        }
    }
    end:
}

int main() {

    int n, i, j, ori, desti;
    int move =0;

    printf("How many tiles you want for the Tower of Hanoi: ");
    scanf("%d", &n);

    int hanoi[n][COLUMNS];

    // this for(for) creates a 2-dimensional array with only 0's
    for(i=0; i<n; i++){
        for(j=0; j<COLUMNS; j++){
            hanoi[i][j] = 0;
        }
    }

    // this for sets the first column to 1, 2, 3, ..., n
    for(i=0; i<n; i++){
        hanoi[i][0] = i+1;
    }

restart:

    system("cls");
    plot(hanoi, n);
    printf("\nNumber of moves: %d\nChange the tiles (input: origin of tile, destination of tile): ", move);
    scanf("%d %d", &ori, &desti);

    changeTiles(ori, desti, n, &hanoi, &move);

    while(check(&hanoi, n)){
        goto restart;
    }

    // i cleared and plotted the game again because i couldnt replot the game
    // since the while loop returns to the 'restart' part
    system("cls");
    plot(hanoi, n);

    printf("\nCongratulations! You completed the Tower of Hanoi puzzle in %d moves!\n", move);

    return 0;
}
