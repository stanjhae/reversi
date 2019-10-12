#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int playerRow = 0, playerCol = 0, occupied = 0, foundByAi = 0, flips = 0, maxFlips = 0, flipRow, flipCol, flip = 0, edge = 0;

void *levels[5][2] = { //levels for the game
        {"1", "Human"},
        {"2", "AI (Easy)"},
        {"3", "AI (Medium)"},
        {"4", "AI (Hard)"},
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

int checkExtSpot(r, c, row, col, player, direction) { //checks the direction we're searching.
    char x = 'x', o = 'o';
    int rowTwo = 2, rowOne = 1, colTwo = 2, colOne = 1;
    if (player == 2) {
        x = 'o', o = 'x';
    }
    if (direction == 1) { //negate values if direction 1.
//        rowTwo = -rowTwo;
        rowOne = -rowOne;
    } else if (direction == 2) {
        colOne = -colOne;
    }
//    if(row-2<1 || row+2>8 || col-2<1 || col+2>8){
//        printf("row:%d, col:%d is outside the board\n", r, c);
//        return 5;
//    }
    printf("%d %d %d %d\n", r, c, row, col);
    int rowDiff = r - row; //finds row difference between possible flip and actual move
    int colDiff = c - col; //finds col difference between possible flip and actual move

    if (rowDiff == 0 && colDiff > 0) {//if same row but checking right col [0,2]
        printf("rowDiff: %d colDiff: %d\n", rowDiff, colDiff);

        if (board[row][col + colTwo] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row, col + colTwo);
            int reverseCol = col + colTwo;
            while (reverseCol != playerCol) {
                flips++;
                flip ? board[row][reverseCol - 1] = x : NULL;
                reverseCol--;
            }
            foundByAi++;
        } else if (board[row][col + colTwo] == o) {
            printf("Found o at row:%d, col:%d\n", row, col + colTwo);
            if (direction == 2) {
                colOne = -colOne;
            }
            printf("%d\n", colOne);
            checkExtSpot(r, c + colOne, row, col + colOne, player, direction);
        } else {
            printf("No X at row:%d, col:%d\n", row, col + colTwo);
        }
    } else if (rowDiff == 0 && colDiff < 0) { //if same row but checking left col [0,-2]
        printf("rowDiff: %d colDiff: %d\n", rowDiff, colDiff);
        if (board[row][col - colTwo] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row, col - colTwo);
            int reverseCol = col - colTwo;
            while (reverseCol != playerCol) {
                flips++;
                flip ? board[row][reverseCol + 1] = x : NULL;
                reverseCol++;
            }
            foundByAi++;
        } else if (board[row][col - colTwo] == o) {
            printf("Found o at row:%d, col:%d\n", row, col - colTwo);
            checkExtSpot(r, c - colOne, row, col - colOne, player, direction);
        } else {
            printf("No X at row:%d, col:%d\n", row, col - colTwo);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff < 0 && colDiff == 0) { //if same col but checking top row [-2,0]
        printf("rowDiff: %d colDiff: %d\n", rowDiff, colDiff);
        if (board[row - rowTwo][col] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row - rowTwo, col);
            int reverseRow = row - rowTwo;
            while (reverseRow != playerRow) {
                flips++;
                flip ? board[reverseRow + 1][col] = x : NULL;
                reverseRow++;
            }
            foundByAi++;
        } else if (board[row - rowTwo][col] == o) {
            printf("Found o at row:%d, col:%d\n", row - rowTwo, col);
            checkExtSpot(r - rowOne, c, row - rowOne, col, player, direction);
        } else {
            printf("No X at row:%d, col:%d\n", row - rowTwo, col);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff < 0 && colDiff < 0) { //if same col but checking top row [-2,-2]
        printf("rowDiff: %d colDiff: %d\n", rowDiff, colDiff);
        if (board[row - rowTwo][col - colTwo] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row - rowTwo, col - colOne);
            int reverseRow = row - rowTwo; //Get row where X or O is found
            int reverseCol = col - colTwo; //Get col where X or O is found
            while (reverseCol != playerCol) { //we loop until we get to initial play
                flips++;
                flip ? board[reverseRow + 1][reverseCol + 1] = x : NULL; //change every character
                reverseRow++; //increase or reduce row
                reverseCol++; //increase or reduce col
            }
            foundByAi++;
        } else if (board[row - rowTwo][col - colTwo] == o) {
            printf("Found o at row:%d, col:%d\n", row - rowTwo, col - colTwo);
            checkExtSpot(r - rowOne, c - colOne, row - rowOne, col - colOne, player, direction);
        } else {
            printf("No X at row:%d, col:%d\n", row - rowTwo, col - colTwo);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff < 0 && colDiff > 0) { //[-2,+2]
        printf("rowDiff: %d colDiff: %d\n", rowDiff, colDiff);
        if (board[row - rowTwo][col + colTwo] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row - rowTwo, col + colTwo);
            int reverseRow = row - rowTwo;
            int reverseCol = col + colTwo;
            while (reverseCol != playerCol) {
                flips++;
                flip ? board[reverseRow + 1][reverseCol - 1] = x : NULL;
                reverseRow++;
                reverseCol--;
            }
            foundByAi++;
        } else if (board[row - rowTwo][col + rowTwo] == o) {
            printf("Found o at row:%d, col:%d\n", row - rowTwo, col + colTwo);
            if (direction == 1) {
                rowOne = -rowOne;
            }
            if (direction == 2) {
                colOne = -colOne;
            }
            checkExtSpot(r - rowOne, c + colOne, row - rowOne, col + colOne, player, direction);
        } else {
            printf("No X at row:%d, col:%d\n", row - rowTwo, col + colTwo);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff > 0 && colDiff < 0) { //[2,-2]
        printf("rowDiff: %d colDiff: %d\n", rowDiff, colDiff);
        if (board[row + rowTwo][col - colTwo] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row + rowTwo, col - colTwo);
            int reverseRow = row + rowTwo;
            int reverseCol = col - colTwo;
            while (reverseCol != playerCol) {
                flips++;
                flip ? board[reverseRow - 1][reverseCol + 1] = x : NULL;
                reverseRow--;
                reverseCol++;
            }
            foundByAi++;
        } else if (board[row + rowTwo][col - colTwo] == o) {
            printf("Found o at row:%d, col:%d\n", row + rowTwo, col - colTwo);
            if (direction == 1) {
                rowOne = -rowOne;
            }
            checkExtSpot(r + rowOne, c - colOne, row + rowOne, col - colOne, player, direction);
//            checkExtSpot(r + 1, c - 1, row + 1, col + 1, player, direction);
        } else {
            printf("No X at row:%d, col:%d\n", row + rowTwo, col - colTwo);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff > 0 && colDiff > 0) { //[2,2]
        printf("rowDiff: %d colDiff: %d\n", rowDiff, colDiff);
        if (board[row + rowTwo][col + colTwo] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row + rowTwo, col + colTwo);
            int reverseRow = row + rowTwo;
            int reverseCol = col + colTwo;
            while (reverseCol != playerCol) {
                printf("Flippppping!!!!!\n");
                flips++;
                flip ? board[reverseRow - 1][reverseCol - 1] = x : NULL;
                reverseRow--;
                reverseCol--;
            }
            foundByAi++;
        } else if (board[row + rowTwo][col + colTwo] == o) {
            printf("Found o at row:%d, col:%d\n", row - rowTwo, col + colTwo);
            if (direction == 1) {
                rowOne = -rowOne;
            }
            if (direction == 2) {
                colOne = -colOne;
            }
            checkExtSpot(r + rowOne, c + colOne, row + rowOne, col + colOne, player, direction);
        } else {
            printf("No X at row:%d, col:%d\n", row + rowTwo, col + colTwo);
//                                    return 5; //throws a no flip possible error
        }
    } else if (rowDiff > 0 && colDiff == 0) { //if same col but checking bottom row [2,0]
        printf("rowDiff: %d colDiff: %d\n", rowDiff, colDiff);
        if (board[row + rowTwo][col] == x) { //if spot contains opposite disc (x)
            printf("Found X at row:%d, col:%d\n", row + rowTwo, col);
            int reverseRow = row + rowTwo;
            while (reverseRow != playerRow) {
                flips++;
                flip ? board[reverseRow - 1][col] = x : NULL;
                reverseRow--;
            }
            foundByAi++;
        } else if (board[row + rowTwo][col] == o) {
            printf("Found Oo at row:%d, col:%d\n", row + rowTwo, col);
            if (direction == 1) {
                rowOne = -rowOne;
            }
            checkExtSpot(r + rowOne, c, row + rowOne, col, player, direction);
        } else {
            printf("No X at row:%d, col:%d\n", row + rowTwo, col);
//                                    return 5; //throws a no flip possible error
        }
    }
}

int checkOccupied(row, col, player, direction) {
    char x = 'x', o = 'o';
    if (player == 2) {
        x = 'o', o = 'x';
    }

    if (board[row][col] == x || board[row][col] == o) { //if spot is occupied
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
                        checkExtSpot(r, c, row, col, player, direction);
                        rounds++;
                    }
                }
            }
            if (found == 0) { //at end of row, check if any spot is occupied
                if (r == row + 1) { //if it is the last row
                    return 3; //throws a no spot around given point is a occupied error
                }
            }
        }
        if (opposite == 0) { //if no neighbour of opposite disc
            return 4; //throws a no neighbour of opposite disc error
        }
    }
    return 0;
}

void humanMove(turn, shape){
    do {
        flips = 0;
        printf("\n");
        if (occupied == 2) printf("This spot is taken.\n");
        else if(occupied == 3) printf("No disc around this spot.\n");
        else if(occupied == 4) printf("No opposite disc around this spot.\n");

        printf("Player %d move: ", turn);
        scanf("%d, %d", &playerRow, &playerCol); //getting the player's move (row,col)

        occupied = checkOccupied(playerRow, playerCol, turn);

        flip = 1;
        checkOccupied(playerRow, playerCol, turn, 0);
        flip = 0;
        board[playerRow][playerCol] = shape; //assign x to player's move

        printBoard(); //print updated board

    } while (occupied !=0);
}

int levelChooser(turn){
    int player = 1;
    do {
        printf("\n");
        if (player < 1 || player > 4) printf("Level must be between 1 and 4.\n");
        printf("Choose Level for player %d: ", turn);
        scanf("%d", &player);
    } while (player < 1 || player > 4);

    return player;
}

void initialization(){
    board[4][4] = 'o';
    board[4][5] = 'x';
    board[5][4] = 'x';
    board[5][5] = 'o';

    printf("\nWelcome To Reversi\n\n");

    for (int i = 0; i < 4; i++) { //printing the levels
        printf("%s: %s \n", levels[i][0], levels[i][1]);
    }

}

int main() {
    srand(time(0));   // Initialization, should only be called once.

    int play = 20;

    initialization();

    int player1 = levelChooser(1);
    int player2 = levelChooser(2);


    printf("\n%s vs %s\n\n", levels[player1 - 1][1], levels[player2 - 1][1]); //displays who vs who

    printBoard();

    while (play) { //Continue playing until play becomes false.
        flip = 0;
        maxFlips = 0;

        if (player1 == 1) {
            humanMove(1, 'x');
        } else if (player1 == 2) {
            flips = 0;
            int random = rand() % 4;
//            int random = 3;
            printf("random:%d\n", random);

            flip = 1;
            if (random < 2) {
                for (int r = 1; r < 9; r++) {
                    for (int c = 1; c < 9; c++) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 0 ? r : c;
                        playerCol = random == 0 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 0 ? r : c, random == 0 ? c : r);
                        checkOccupied(random == 0 ? r : c, random == 0 ? c : r, 1, 0);
                        if (foundByAi > 0) {
                            board[playerRow][playerCol] = 'x';
                            printBoard(); //print updated board
                            break;
                        }
                    }
                    if (foundByAi != 0) {
                        break;
                    }
                }
            } else {
                for (int r = 8; r > 0; r--) {
                    for (int c = 8; c > 0; c--) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 2 ? r : c;
                        playerCol = random == 2 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 2 ? r : c, random == 2 ? c : r);
                        checkOccupied(random == 2 ? r : c, random == 2 ? c : r, 1, random == 2 ? 2 : 1);
                        if (foundByAi > 0) {
                            printf("playerRow:%d, playerCol:%d\n", playerRow, playerCol);
                            board[playerRow][playerCol] = 'x';
                            printBoard(); //print updated board
                            break;
                        }
                    }
                    if (foundByAi != 0) {
                        break;
                    }
                }
            }
        } else if (player1 == 3) {
            flips = 0;
            int random = rand() % 4;
//            int random = 3;
            printf("random:%d\n", random);

            if (random < 2) {
                for (int r = 1; r < 9; r++) {
                    for (int c = 1; c < 9; c++) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 0 ? r : c;
                        playerCol = random == 0 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 0 ? r : c, random == 0 ? c : r);
                        checkOccupied(random == 0 ? r : c, random == 0 ? c : r, 1, 0);
                        printf("flips:%d\n", flips);
                        if (flips > maxFlips) {
                            maxFlips = flips;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        }
                        flips = 0;
                    }
                }
            } else {
                for (int r = 8; r > 0; r--) {
                    for (int c = 8; c > 0; c--) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 2 ? r : c;
                        playerCol = random == 2 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 2 ? r : c, random == 2 ? c : r);
                        checkOccupied(random == 2 ? r : c, random == 2 ? c : r, 1, random == 2 ? 2 : 1);
                        if (flips > maxFlips) {
                            maxFlips = flips;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        }
                        flips = 0;
                    }
                }
            }

            printf("max flips:%d row:%d col:%d\n", maxFlips, flipRow, flipCol);
            if (maxFlips > 0) {
                flip = 1;
                playerRow = flipRow;
                playerCol = flipCol;
                checkOccupied(flipRow, flipCol, 1, 0);
            }
            printBoard(); //print updated board
        } else if (player1 == 4) {
            flips = 0;
            int random = rand() % 4;
//            int random = 1;
            printf("random:%d\n", random);

            if (random < 2) {
                for (int r = 1; r < 9; r++) {
                    for (int c = 1; c < 9; c++) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 0 ? r : c;
                        playerCol = random == 0 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 0 ? r : c, random == 0 ? c : r);
                        checkOccupied(random == 0 ? r : c, random == 0 ? c : r, 1, 0);
                        printf("flips:%d\n", flips);
                        if (flips &&
                            ((r == 1 && c == 1) || (r == 8 && c == 1) || (r == 1 && c == 8) || (r == 8 && c == 8))) {
                            printf("edge!!!!!!!!!!!!!!!!!!!!!!!!!!:%d\n");
                            edge++;
                            maxFlips++;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        } else if (!edge && flips > maxFlips) {
                            maxFlips = flips;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        }
                        flips = 0;
                    }
                }
            } else {
                for (int r = 8; r > 0; r--) {
                    for (int c = 8; c > 0; c--) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 2 ? r : c;
                        playerCol = random == 2 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 2 ? r : c, random == 2 ? c : r);
                        checkOccupied(random == 2 ? r : c, random == 2 ? c : r, 1, random == 2 ? 2 : 1);
                        printf("flips!!!!!!!!!!!!!!!!!!!!!!!!!!:%d\n", flips);
                        if (flips &&
                            ((r == 1 && c == 1) || (r == 8 && c == 1) || (r == 1 && c == 8) || (r == 8 && c == 8))) {
                            printf("edge!!!!!!!!!!!!!!!!!!!!!!!!!!:\n");
                            edge++;
                            maxFlips++;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        } else if (!edge && flips > maxFlips) {
                            maxFlips = flips;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        }
                        flips = 0;
                    }
                }
            }

            printf("max flips:%d row:%d col:%d\n", maxFlips, flipRow, flipCol);
            if (maxFlips > 0) {
                flip = 1;
                playerRow = flipRow;
                playerCol = flipCol;
                checkOccupied(flipRow, flipCol, 1, 0);
            }
            printBoard(); //print updated board
        }

        foundByAi = 0;

        if (player2 == 1) {
            humanMove(2, 'o');
        } else if (player2 == 2) {
            flips = 0;
            int random = rand() % 4;
//            int random = 3;
            printf("random:%d\n", random);

            flip = 1;
            if (random < 2) {
                for (int r = 1; r < 9; r++) {
                    for (int c = 1; c < 9; c++) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 0 ? r : c;
                        playerCol = random == 0 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 0 ? r : c, random == 0 ? c : r);
                        checkOccupied(random == 0 ? r : c, random == 0 ? c : r, 2, 0);
                        if (foundByAi > 0) {
                            board[playerRow][playerCol] = 'o';
                            printBoard(); //print updated board
                            break;
                        }
                    }
                    if (foundByAi != 0) {
                        break;
                    }
                }
            } else {
                for (int r = 8; r > 0; r--) {
                    for (int c = 8; c > 0; c--) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 2 ? r : c;
                        playerCol = random == 2 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 2 ? r : c, random == 2 ? c : r);
                        checkOccupied(random == 2 ? r : c, random == 2 ? c : r, 2, random == 2 ? 2 : 1);
                        if (foundByAi > 0) {
                            printf("playerRow:%d, playerCol:%d\n", playerRow, playerCol);
                            board[playerRow][playerCol] = 'o';
                            printBoard(); //print updated board
                            break;
                        }
                    }
                    if (foundByAi != 0) {
                        break;
                    }
                }
            }
        } else if (player2 == 3) {
            flips = 0;
            int random = rand() % 4;
//            int random = 3;
            printf("random:%d\n", random);

            if (random < 2) {
                for (int r = 1; r < 9; r++) {
                    for (int c = 1; c < 9; c++) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 0 ? r : c;
                        playerCol = random == 0 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 0 ? r : c, random == 0 ? c : r);
                        checkOccupied(random == 0 ? r : c, random == 0 ? c : r, 2, 0);
                        printf("flips:%d\n", flips);
                        if (flips > maxFlips) {
                            maxFlips = flips;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        }
                        flips = 0;
                    }
                }
            } else {
                for (int r = 8; r > 0; r--) {
                    for (int c = 8; c > 0; c--) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 2 ? r : c;
                        playerCol = random == 2 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 2 ? r : c, random == 2 ? c : r);
                        checkOccupied(random == 2 ? r : c, random == 2 ? c : r, 2, random == 2 ? 2 : 1);
                        if (flips > maxFlips) {
                            maxFlips = flips;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        }
                        flips = 0;
                    }
                }
            }

            printf("max flips:%d row:%d col:%d\n", maxFlips, flipRow, flipCol);
            if (maxFlips > 0) {
                flip = 1;
                playerRow = flipRow;
                playerCol = flipCol;
                checkOccupied(flipRow, flipCol, 2, 0);
            }
            printBoard(); //print updated board
        } else if (player2 == 4) {
            flips = 0;
            int random = rand() % 4;
//            int random = 1;
            printf("random:%d\n", random);

            if (random < 2) {
                for (int r = 1; r < 9; r++) {
                    for (int c = 1; c < 9; c++) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 0 ? r : c;
                        playerCol = random == 0 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 0 ? r : c, random == 0 ? c : r);
                        checkOccupied(random == 0 ? r : c, random == 0 ? c : r, 2, 0);
                        printf("flips:%d\n", flips);
                        if (flips &&
                            ((r == 1 && c == 1) || (r == 8 && c == 1) || (r == 1 && c == 8) || (r == 8 && c == 8))) {
                            printf("edge!!!!!!!!!!!!!!!!!!!!!!!!!!:%d\n");
                            edge++;
                            maxFlips++;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        } else if (!edge && flips > maxFlips) {
                            maxFlips = flips;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        }
                        flips = 0;
                    }
                }
            } else {
                for (int r = 8; r > 0; r--) {
                    for (int c = 8; c > 0; c--) {
                        printf("before flip: row:%d. col:%d.\n", r, c);
                        playerRow = random == 2 ? r : c;
                        playerCol = random == 2 ? c : r;
                        printf("after flip: row:%d. col:%d.\n\n", random == 2 ? r : c, random == 2 ? c : r);
                        checkOccupied(random == 2 ? r : c, random == 2 ? c : r, 2, random == 2 ? 2 : 1);
                        printf("flips!!!!!!!!!!!!!!!!!!!!!!!!!!:%d\n", flips);
                        if (flips &&
                            ((r == 1 && c == 1) || (r == 8 && c == 1) || (r == 1 && c == 8) || (r == 8 && c == 8))) {
                            printf("edge!!!!!!!!!!!!!!!!!!!!!!!!!!:\n");
                            edge++;
                            maxFlips++;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        } else if (!edge && flips > maxFlips) {
                            maxFlips = flips;
                            flipRow = playerRow;
                            flipCol = playerCol;
                        }
                        flips = 0;
                    }
                }
            }

            printf("max flips:%d row:%d col:%d\n", maxFlips, flipRow, flipCol);
            if (maxFlips > 0) {
                flip = 1;
                playerRow = flipRow;
                playerCol = flipCol;
                checkOccupied(flipRow, flipCol, 2, 0);
            }
            printBoard(); //print updated board
        }


        foundByAi = 0;
        play--;
    }
    printf("GAME OVER!!");

    return 0;
}