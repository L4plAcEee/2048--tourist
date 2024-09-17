#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void print_grid();
void add_random_tile();
void move_elements(int* elem_0, int* elem_1, int* elem_2, int* elem_3);
void merge_elements(int* elem_0, int* elem_1, int* elem_2, int* elem_3);
void move_left();
void move_right();
void move_up();
void move_down();
void handle_user_input();
int check_game_over();
int initalize_game();

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
        for (size_t col = 0; col < 4; ++col) {
            game.grid[row][col] = 0;
        }
    }
    game.current_score = 0;
    game.game_status = 1;
    game.available = 16;
    game.has_moved = 0;
    
    add_random_tile();
    add_random_tile();  // 初始状态生成两个随机 tile
    return 1;
}

void print_grid() {
    printf("Current score: %ld\n", game.current_score);
    printf("Grid:\n");
    for (size_t row = 0; row < 4; ++row) {
        for (size_t col = 0; col < 4; ++col) {
            printf("%4d", game.grid[row][col]);
        }
        printf("\n");
    }
}

void add_random_tile() {
    if(game.available == 0) return;
    while(1) {
        int row = rand() % 4;
        int col = rand() % 4;
        if (game.grid[row][col] == 0) {
            game.grid[row][col] = (rand() % 2 + 1) * 2;
            game.available--;
            break;
        }
    }
}

void move_elements(int* elem_0, int* elem_1, int* elem_2, int* elem_3){
    int* elements[4] = {elem_0, elem_1, elem_2, elem_3};
    int target_index = 0;
    for (int i = 0; i < 4; ++i) {
        if (*elements[i] != 0) {
            if (target_index != i) {
                game.has_moved = 1;
            }
            int temp = *elements[i];
            *elements[i] = 0;
            *elements[target_index] = temp;
            target_index++;
        }
    }
}

void merge_elements(int* elem_0, int* elem_1, int* elem_2, int* elem_3) {
    int* elements[4] = {elem_0, elem_1, elem_2, elem_3};
    for (int i = 0; i < 3; ++i) {
        if (*elements[i] != 0 && *elements[i] == *elements[i + 1]) {
            *elements[i] *= 2;
            game.current_score += *elements[i];
            *elements[i + 1] = 0;
            game.available++;
            game.has_moved = 1;
        }
    }
}

void move_left() {
    for (int row = 0; row < 4; ++row) {
        move_elements(&game.grid[row][0], &game.grid[row][1], &game.grid[row][2], &game.grid[row][3]);
        merge_elements(&game.grid[row][0], &game.grid[row][1], &game.grid[row][2], &game.grid[row][3]);
        move_elements(&game.grid[row][0], &game.grid[row][1], &game.grid[row][2], &game.grid[row][3]);
    }
}

void move_right() {
    for (int row = 0; row < 4; ++row) {
        move_elements(&game.grid[row][3], &game.grid[row][2], &game.grid[row][1], &game.grid[row][0]);
        merge_elements(&game.grid[row][3], &game.grid[row][2], &game.grid[row][1], &game.grid[row][0]);
        move_elements(&game.grid[row][3], &game.grid[row][2], &game.grid[row][1], &game.grid[row][0]);
    }
}

void move_up() {
    for (int col = 0; col < 4; ++col) {
        move_elements(&game.grid[0][col], &game.grid[1][col], &game.grid[2][col], &game.grid[3][col]);
        merge_elements(&game.grid[0][col], &game.grid[1][col], &game.grid[2][col], &game.grid[3][col]);
        move_elements(&game.grid[0][col], &game.grid[1][col], &game.grid[2][col], &game.grid[3][col]);
    }
}

void move_down() {
    for (int col = 0; col < 4; ++col) {
        move_elements(&game.grid[3][col], &game.grid[2][col], &game.grid[1][col], &game.grid[0][col]);
        merge_elements(&game.grid[3][col], &game.grid[2][col], &game.grid[1][col], &game.grid[0][col]);
        move_elements(&game.grid[3][col], &game.grid[2][col], &game.grid[1][col], &game.grid[0][col]);
    }
}

void handle_user_input() {
    char input;
    printf("Use WASD to move, press Q to exit.\n");
    while (1) {
        input = _getch();
        game.has_moved = 0;  // 重置移动标志
        
        if (input == 'q') { break; }
        switch (input) {
            case 'a':
                move_left();
                break;
            case 's':
                move_down();
                break;
            case 'd':
                move_right();
                break;
            case 'w':
                move_up();
                break;
        }
        
        if (game.has_moved) {
            add_random_tile();
            print_grid();
        }
        
        if (check_game_over()) {
            printf("Game Over!\n");
            break;
        }
    }
}

int check_game_over() {
    if (game.available > 0) return 0;
    
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if ((col < 3 && game.grid[row][col] == game.grid[row][col + 1]) || 
                (row < 3 && game.grid[row][col] == game.grid[row + 1][col])) {
                return 0; // 还有可合并的元素，游戏未结束
            }
        }
    }
    
    game.game_status = 0;
    return 1; // 游戏结束
}

int main() {
    if (initalize_game()) 
        printf("Initialize game success!\n");
    print_grid();
    handle_user_input();
    return 0;
}
