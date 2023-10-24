#include <stdio.h>
#include <assert.h>

enum {
    EMPTY = 0,
    RED = 1,
    BLUE = 2,
};

typedef char board_t[4][5];
typedef char player_t;

player_t other_player(player_t player) {
    if (player == RED) {
        return BLUE;
    } else if (player == BLUE) {
        return RED;
    }
}

void initialize_board(board_t board) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            board[row][col] = EMPTY;
        }
    }
}

int has_won(board_t board, player_t player) {
    // horizontal win
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 2; col++) {
            if (board[row][col] == player && board[row][col + 1] == player &&
                board[row][col + 2] == player && board[row][col + 3] == player) {
                return 1;
            }
        }
    }

    // vert win
    for (int row = 0; row < 1; row++) {
        for (int col = 0; col < 5; col++) {
            if (board[row][col] == player && board[row + 1][col] == player &&
                board[row + 2][col] == player && board[row + 3][col] == player) {
                return 1;
            }
        }
    }

    // diag win
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            if (row + 3 < 4 && col + 3 < 5) {
                if (board[row][col] == player && board[row + 1][col + 1] == player &&
                    board[row + 2][col + 2] == player && board[row + 3][col + 3] == player) {
                    return 1;
                }
            }
            if (row + 3 < 4 && col - 3 >= 0) {
                if (board[row][col] == player && board[row + 1][col - 1] == player &&
                    board[row + 2][col - 2] == player && board[row + 3][col - 3] == player) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int is_full(board_t board) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            if (board[row][col] == EMPTY) {
                return 0;
            }
        }
    }
    return 1;
}

int drop_piece(board_t board, int col, player_t player) {
    for (int row = 3; row >= 0; row--) {
        if (board[row][col] == EMPTY) {
            board[row][col] = player;
            return row;
        }
    }
    return -1; // Invalid move
}

typedef struct {
    int col;
    int score;
} move_t;

move_t best_move(board_t board, player_t player) {
    move_t result, temp;
    int no_temp = 1;
    for (int col = 0; col < 5; col++) {
        if (board[0][col] == EMPTY) {
            int row = drop_piece(board, col, player);
            board[row][col] = player;
            if (has_won(board, player)) {
                board[row][col] = EMPTY;
                return (move_t){col, 1};
            }
            board[row][col] = EMPTY;
        }
    }
    player_t opponent = other_player(player);
    for (int col = 0; col < 5; col++) {
        if (board[0][col] == EMPTY) {
            int row = drop_piece(board, col, opponent);
            if (has_won(board, opponent)) {
                board[row][col] = EMPTY;
                return (move_t){col, 1};
            }
            board[row][col] = EMPTY;
        }
    }
    for (int col = 0; col < 5; col++) {
        if (board[0][col] == EMPTY) {
            int row = drop_piece(board, col, player);
            board[row][col] = player;
            if (is_full(board)) {
                board[row][col] = EMPTY;
                return (move_t){col, 0};
            }
            result = best_move(board, other_player(player));
            board[row][col] = EMPTY;
            if (result.score == -1) {
                return (move_t){col, 1};
            } else if (result.score == 0) {
                temp = (move_t){col, 0};
                no_temp = 0;
            } else {
                if (no_temp) {
                    temp = (move_t){col, -1};
                    no_temp = 0;
                }
            }
        }
    }
    return temp;
}

void print_board(board_t board,int choice) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 5; col++) {
            switch (board[row][col]) {
                case EMPTY:
                    printf("0  ");
                    break;
                case RED:
                    if (choice == 2) {
                        printf("B  "); // Change Red to Blue if choice is 2
                    } else {
                        printf("R  "); // Keep it as Red for choice 1
                    }
                    break;
                case BLUE:
                    if (choice == 2) {
                        printf("R  "); 
                    } else {
                        printf("B  "); 
                    }
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int move, col;
    board_t board;
    move_t result;
    int choice;
    printf("Choose your color:\n");
    printf("1. Red\n");
    printf("2. Blue\n");
    printf("Enter 1 or 2 to select your color: ");
    scanf("%d", &choice);
    player_t current;
    if (choice == 1) {
        current = RED;
    } else if (choice == 2) {
        current = BLUE;
    } else {
        printf("Invalid choice. Please select 1 or 2.\n");
        return 1;
    }
    initialize_board(board);
    while (1) {
        if (choice != 1 && choice != 2) {
            printf("Invalid choice. Please select 1 or 2.\n");
            break;
        }
        print_board(board, choice);
        printf("\n\n");
        if (current == RED) {
            printf("0  1  2  3  4\n");
            printf("Enter your move: ");
            scanf("%d", &move);
            col = move;
            if (col >= 0 && col < 5 && board[0][col] == EMPTY) {
                drop_piece(board, col, current);
            } else {
                printf("Invalid move. Please try again.\n");
                continue;
            }
        } else {
            result = best_move(board, current);
            col = result.col;
            if (col >= 0 && col < 5 && board[0][col] == EMPTY) {
                int row = drop_piece(board, col, current);
            }
        }
        if (has_won(board, current)) {
            print_board;
            printf("%c has won!\n", (current == RED) ? 'R' : 'B');
            break;
        } else if (is_full(board)) {
            printf("Draw.\n");
            break;
        }
        current = other_player(current);
    }
    return 0;
}
