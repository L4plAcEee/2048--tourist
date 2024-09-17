#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct game_play {
    int game_grid[4][4];
    long current_score;
    int game_status;
    int available;
} game_play;

game_play game;

int initalize_game() {
    srand((unsigned)time(NULL));
    for (size_t row = 0; row < 4; ++row){
        for (size_t col = 0; col < 4; ++col)
        {
            game.game_grid[row][col] = 0;
        }
    }
    game.current_score = 0;
    game.game_status = 1;
    game.available = 16;
    return 1;
}

void print_game_grid() {
    printf("gird:\n");
    for (size_t row = 0; row < 4; ++row){
        for (size_t col = 0; col < 4; ++col)
        {
            printf("%4d",game.game_grid[row][col]);
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
            if(game.game_grid[row][col] == 0) {
                game.game_grid[row][col] = (rand()%2 + 1) *2;
                game.available--;
                break;
            }
        }while(i);
    }
}

int main(){
    if(initalize_game()) printf("Initalize game success!\n");
    add_random_tile();
    print_game_grid();
    return 1;
}
