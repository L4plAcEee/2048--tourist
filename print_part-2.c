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

int main(){
    if(initalize_game()) printf("Initalize game success!\n");
    print_game_grid();
    return 1;
}
