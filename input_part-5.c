#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

typedef struct game_play {
    int grid[4][4];
    long current_score;
    int game_status;
    int available;
    int has_moved;
} game_play;

game_play game;

int initalize_game() {
    srand((unsigned)time(NULL));
    for (size_t row = 0; row < 4; ++row){
        for (size_t col = 0; col < 4; ++col)
        {
            game.grid[row][col] = 0;
        }
    }
    game.current_score = 0;
    game.game_status = 1;
    game.available = 16;
    game.has_moved = 0;
    return 1;
}

void print_grid() {
    printf("gird:\n");
    for (size_t row = 0; row < 4; ++row){
        for (size_t col = 0; col < 4; ++col)
        {
            printf("%4d",game.grid[row][col]);
        }
        printf("\n");
    }
}

void add_random_tile(){
    for(size_t i = 0; i < 2; ++i) {
        if(game.available == 0) break;
        do{
            int row = rand()%4;
            int col = rand()%4;
            if(game.grid[row][col] == 0) {
                game.grid[row][col] = (rand()%2 + 1) *2;
                game.available--;
                break;
            }
        }while(i);
    }
}

void move_elements(int* elem_0,int* elem_1,int* elem_2,int* elem_3){
    int* elements[4]={elem_0,elem_1,elem_2,elem_3};
    int target_index = 0;
    for(int i = 0;i < 4;++i) {
        if(*elements[i] != 0) {
            if(target_index != i){
                game.has_moved = 1;
            }
            int temp = *elements[i];
            *elements[i] = 0;
            *elements[target_index] = temp;
            target_index++;
        }
    }
}

void move_left(){
    for(int row = 0; row < 4 ;++row){
        move_elements(&game.grid[row][0],&game.grid[row][1],&game.grid[row][2],&game.grid[row][3]);
    }
}

void handle_user_input(){
    char input;
    printf("use WASD to move, press Q to exit.\n");
    while(1){
        input = _getch();
        if(input == 'q') {break;}
        switch (input) {
            case 'a':
                move_left();
                break;
        }
        add_random_tile();
        print_grid();

    }
}

int main(){
    if(initalize_game()) 
        printf("Initalize game success!\n");
    add_random_tile();
    print_grid();
    move_left();
    handle_user_input();
    return 1;
}