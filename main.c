#include <stdio.h>


int playerRow = 0, playerCol = 0, occupied;
void *levels[5][2] = { //levels for the game
        {"1", "Human"},
        {"2", "AI (Easy)"},
        {"3", "AI (Medium)"},
        {"4", "AI (Hard)"},
        {"5", "AI (Very Hard)"},
};

char board[8][8];

void printBoard() {
    int x = 0, o = 0; //number of x and o

    for (int row = 0; row < 9; row++) {
        if (row != 0) { //if first row do not print number of row.
            printf("%d", row);
        }
        for (int col = 0; col < 9; col++) {
            if (board[row + 1][col + 1] == 'x') { //if X, increase x.
                x++;
            }
            if (board[row + 1][col + 1] == 'o') { //if O, increase o.
                o++;
            }
            if (row == 0) { //if first row
                if (col != 0) { //and not first column
                    printf("%d\t", col); //print number of column
                } else {
                    printf("\t"); //if firs[t column, print space
                }
            } else { //if second to ninth row
                if (col != 0) { //if not the first column
                    if (board[row][col] == 'x') { //if point in board is equal to x
                        printf("x\t"); //print x
                    } else if (board[row][col] == 'o') { //if point in board is equal to o
                        printf("o\t"); //print o
                    } else {
                        printf(".\t"); //print .
                    }
                } else { //if first column
                    printf("\t"); //print space
                }
            }
        }
        printf("\n\n");
    }
    printf("X: %d,\t O: %d\n", x, o); //print result
}

int checkExtSpot(r, c, row, col, player) {
    char x = 'x', o = 'o';
    if (player == 2) {
        x = 'o', o = 'x';
    }

//    if(row-2<1 || row+2>8 || col-2<1 || col+2>8){
//        printf("row:%d, col:%d is outside the board\n", r, c);
//        return 5;
//    }
    printf("%d %d %d %d\n", r, c, row, col);
    int rowDiff = r - row; //finds row difference between possible flip and actual move
    int colDiff = c - col; //finds col difference between possible flip and actual move

    if (rowDiff == 0 && colDiff > 0) { //if same row but checking right col [0,2]
        if (board[row][col + 2] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row, col + 2);
            int reverseCol = col + 2;
            while (reverseCol != playerCol) {
                board[row][reverseCol - 1] = x;
                reverseCol--;
            }
        } else if (board[row][col + 2] == o) {
            printf("Found o at row:%d, col:%d\n", row, col + 2);
            checkExtSpot(r, c + 1, row, col + 1, player);
        } else {
            printf("No X at row:%d, col:%d\n", row, col + 2);
        }
    } else if (rowDiff == 0 && colDiff < 0) { //if same row but checking left col [0,-2]
        if (board[row][col - 2] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row, col - 2);
            int reverseCol = col - 2;
            while (reverseCol != playerCol) {
                board[row][reverseCol + 1] = x;
                reverseCol++;
            }
        } else if (board[row][col - 2] == o) {
            printf("Found o at row:%d, col:%d\n", row, col - 2);
            checkExtSpot(r, c - 1, row, col - 1, player);
        } else {
            printf("No X at row:%d, col:%d\n", row, col - 2);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff < 0 && colDiff == 0) { //if same col but checking top row [-2,0]
        if (board[row - 2][col] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row - 2, col);
            int reverseRow = row - 2;
            while (reverseRow != playerRow) {
                board[reverseRow + 1][col] = x;
                reverseRow++;
            }

        } else if (board[row - 2][col] == o) {
            printf("Found o at row:%d, col:%d\n", row - 2, col);
            checkExtSpot(r - 1, c, row - 1, col, player);
        } else {
            printf("No X at row:%d, col:%d\n", row - 2, col);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff < 0 && colDiff < 0) { //if same col but checking top row [-2,-2]
        if (board[row - 2][col - 2] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row - 2, col - 2);
            int reverseRow = row - 2; //Get row where X or O is found
            int reverseCol = col - 2; //Get col where X or O is found
            while (reverseCol != playerCol) { //we loop until we get to initial play
                board[reverseRow + 1][reverseCol + 1] = x; //change every character
                reverseRow++; //increase or reduce row
                reverseCol++; //increase or reduce col
            }
        } else if (board[row - 2][col - 2] == o) {
            printf("Found o at row:%d, col:%d\n", row - 2, col - 2);
            checkExtSpot(r - 1, c - 1, row - 1, col - 1, player);
        } else {
            printf("No X at row:%d, col:%d\n", row - 2, col - 2);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff < 0 && colDiff > 0) { //[-2,+2]
        if (board[row - 2][col + 2] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row - 2, col + 2);
            int reverseRow = row - 2;
            int reverseCol = col + 2;
            while (reverseCol != playerCol) {
                board[reverseRow + 1][reverseCol - 1] = x;
                reverseRow++;
                reverseCol--;
            }
        } else if (board[row - 2][col + 2] == o) {
            printf("Found o at row:%d, col:%d\n", row - 2, col + 2);
            checkExtSpot(r - 1, c + 1, row - 1, col + 1, player);
        } else {
            printf("No X at row:%d, col:%d\n", row - 2, col + 2);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff > 0 && colDiff < 0) { //[2,-2]
        if (board[row + 2][col - 2] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row + 2, col - 2);
            int reverseRow = row + 2;
            int reverseCol = col - 2;
            while (reverseCol != playerCol) {
                board[reverseRow - 1][reverseCol + 1] = x;
                reverseRow--;
                reverseCol++;
            }
        } else if (board[row + 2][col - 2] == o) {
            printf("Found o at row:%d, col:%d\n", row + 2, col - 2);
            checkExtSpot(r + 1, c - 1, row + 1, col + 1, player);
        } else {
            printf("No X at row:%d, col:%d\n", row + 2, col - 2);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff > 0 && colDiff > 0) { //[2,2]
        if (board[row + 2][col + 2] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row + 2, col + 2);
            int reverseRow = row + 2;
            int reverseCol = col + 2;
            while (reverseCol != playerCol) {
                board[reverseRow - 1][reverseCol - 1] = x;
                reverseRow--;
                reverseCol--;
            }
        } else if (board[row + 2][col + 2] == o) {
            printf("Found o at row:%d, col:%d\n", row - 2, col + 2);
            checkExtSpot(r + 1, c + 1, row + 1, col + 1, player);
        } else {
            printf("No X at row:%d, col:%d\n", row + 2, col + 2);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff > 0 && colDiff == 0) { //if same col but checking bottom row [2,0]
        if (board[row + 2][col] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row + 2, col);
            int reverseRow = row + 2;
            while (reverseRow != playerRow) {
                board[reverseRow - 1][col] = x;
                reverseRow--;
            }
        } else if (board[row + 2][col] == o) {
            printf("Found o at row:%d, col:%d\n", row + 2, col);
            checkExtSpot(r + 1, c, row + 1, col, player);
        } else {
            printf("No X at row:%d, col:%d\n", row + 2, col);
//                                    return 5; //throws a no flip possible error
        }
    }

}

int checkOccupied(row, col, player) {
    char x = 'x', o = 'o';
    if (player == 2) {
        x = 'o', o = 'x';
    }

    if (board[row][col] == x || board[row][col] == o) { //if spot is occupied
        printf("This spot is occupied");
        return 2; //throws an occupied error
    } else {
        int found = 0;
        int opposite = 0;
        int rounds = 2;
        for (int r = row - 1; r <= row + 1; r++) { //if spot is not occupied

            for (int c = col - 1; c <= col + 1; c++) { //check the spots around a given point

                if ((board[r][c] == x) || (board[r][c] == o)) { //if any spot around the given point is occupied
                    found++; //increment found
                    printf("%c\n", board[r][c]);
                    if (board[r][c] == o) { //for player x, check if neighbour is opposite o
                        opposite++; //increment opposite

                        checkExtSpot(r, c, row, col, player);
                        rounds++;
//                        if(board[r][c+1] == x){
//                            printf("Found X at row:%d, col:%d\n", r, c+1);
//                        }else if(board[r+1][c+1] == x){
//                            printf("Found X at row:%d, col:%d\n", r+1, c+1);
//                        }else
//                            printf("No X found");
                    }
                } else { //if no spot around is occupied
                    continue; //continue to next column
                }
            }
            if (found == 0) { //at end of row, check if any spot is occupied
                if (r == row + 1) { //if it is the last row
                    printf("No characters around this spot.");
                    return 3; //throws a no spot around given point is a occupied error
                }
            }
        }
        printf("\nopposite: %d\n", opposite);
        if (opposite == 0) { //if no neighbour of opposite disc
            printf("No opposite disc around this spot");
            return 4; //throws a no neighbour of opposite disc error
        }
    }

    return 0;
}

int main() {
    int play = 1;

    board[4][4] = 'x';
    board[4][5] = 'o';
    board[5][4] = 'o';
    board[5][5] = 'x';

    int player1 = 1, player2 = 1; //define players

    printf("\nWelcome To Reversi\n\n");

    for (int i = 0; i < 5; i++) { //printing the levels
        printf("%s: %s \n", levels[i][0], levels[i][1]);
    }

    do {
        printf("\n");
        if (player1 < 1 || player1 > 5) printf("Level must be between 1 and 5.\n");
        printf("Choose Level for player 1: ");
        scanf("%d", &player1);
    } while (player1 < 1 || player1 > 5);

    do {
        printf("\n");
        if (player2 < 1 || player2 > 5) printf("Level must be between 1 and 5.\n");
        printf("Choose Level for player 2: ");
        scanf("%d", &player2);
    } while (player2 < 1 || player2 > 5);


//    Logic for selecting player level
//    printf("Choose Level for player 2: ");
//    scanf("%d", &player2);
//    while(player2 < 1 || player2 > 5){
//        printf("Level must be between 1 and 5.\n");
//        printf("Choose Level for player 2: ");
//        scanf("%d", &player2);
//    }

    printf("\n%s vs %s\n\n", levels[player1 - 1][1], levels[player2 - 1][1]); //displays who vs who

    printBoard();

//    while(maxMoves){
//        printf("Player 1 move: ");
//        scanf("%d, %d", &row, &col); //getting the player's move (row,col)
//
//        board[row][col] = 'x'; //assign x to player's move
//
//        printBoard(); //print updated board
//
//        printf("Player 2 move: ");
//        scanf("%d, %d", &row, &col);
//
//        board[row][col] = 'o';
//
//        printBoard();
//
//        maxMoves -= 2; //decrements mmaxMoves by 2 on each play.
//
//    }

    while (play) { //Continue playing until play becomes false.
        printf("Player 1 move: ");
        scanf("%d, %d", &playerRow, &playerCol); //getting the player's move (row,col)

        if (playerRow == '9') {
            break;
        }
        occupied = checkOccupied(playerRow, playerCol, 1);

        if (occupied != 0) {
            return occupied;
        }

        board[playerRow][playerCol] = 'x'; //assign x to player's move

        printBoard(); //print updated board

        printf("Player 2 move: ");
        scanf("%d, %d", &playerRow, &playerCol); //getting the player's move (row,col)

        occupied = checkOccupied(playerRow, playerCol, 2);

        if (occupied != 0) {
            return occupied;
        }

        board[playerRow][playerCol] = 'o'; //assign x to player's move

        printBoard(); //print updated board

    }
    printf("GAME OVER!!");

    return 0;
}