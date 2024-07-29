#include <bits/stdc++.h>
using namespace std;
const char nl = '\n';

char mapValueToSymbol(int value) {
    return (value > 0) ? (value == 1) ? 'X' : 'O' : ' ';
}

bool isWinning(const int* gameBoard, int pos1, int pos2, int pos3) {
    return (gameBoard[pos1] == gameBoard[pos2] && gameBoard[pos2] == gameBoard[pos3] && gameBoard[pos1] != 0);
}

int determineWinner(const int* gameBoard) {
    int winner = 0;
    for (int i = 0; i < 3; i++) {
        if (isWinning(gameBoard, 3 * i, 3 * i + 1, 3 * i + 2)) {
            winner = gameBoard[3 * i];
            break;
        } else if (isWinning(gameBoard, i, i + 3, i + 6)) {
            winner = gameBoard[i];
            break;
        } else if (isWinning(gameBoard, 2 * i, 4, 8 - 2 * i) && (i < 2)) {
            winner = gameBoard[4];
            break;
        }
    }
    return winner;
}

int isGameOver(const int* gameBoard) {
    int winner = determineWinner(gameBoard);
    if (winner > 0) {
        cout << mapValueToSymbol(winner) << " wins!" << nl;
        return 1;
    }
    for (int i = 0; i < 9; i++) {
        if (gameBoard[i] == 0) return 0;
    }
    cout << "Tie!\n\n";
    return 1;
}

int willWin(const int* gameBoard, int player) {
    for (int i = 0; i < 9; i++) {
        int tempBoard[9];
        memcpy(tempBoard, gameBoard, 36);
        if (gameBoard[i] > 0) continue;
        tempBoard[i] = player;
        if (determineWinner(tempBoard) == player) return i;
    }
    return -1;
}

int specialCase(const int* gameBoard) {
    int cases[2][9] = {{1, 0, 0, 0, 2, 0, 0, 0, 1}, {0, 1, 0, 1, 2, 0, 0, 0, 0}};
    int answers[2][4] = {{3, 3, 3, 3}, {2, 8, 6, 0}};
    int rotatedBoard[9] = {6, 3, 0, 7, 4, 1, 8, 5, 2};
    int newBoard[9];
    int tempBoard[9];
    for (int i = 0; i < 9; i++) {
        newBoard[i] = gameBoard[i];
    }
    for (int caseIndex = 0; caseIndex < 2; caseIndex++) {
        for (int rotation = 0; rotation < 4; rotation++) {
            for (int i = 0; i < 9; i++)
                tempBoard[i] = newBoard[i];
            int match = 0;
            for (int position = 0; position < 9; position++) {
                newBoard[position] = tempBoard[rotatedBoard[position]];
            }
            for (int i = 0; i < 9; i++) {
                if (newBoard[i] == cases[caseIndex][i]) match++;
                else break;
            }
            if (match == 9) return answers[caseIndex][rotation];
        }
    }
    return -1;
}

int getRandomMove(const int* gameBoard, int positions[4]) {
    bool isEmpty = false;
    int randomPosition;
    for (int i = 0; i < 4; i++) {
        if (gameBoard[positions[i]] == 0) {
            isEmpty = true;
            break;
        }
    }
    if (isEmpty) {
        do {
            randomPosition = rand() % 4;
        } while (gameBoard[positions[randomPosition]] != 0);
        return positions[randomPosition];
    }
    return -1;
}

void displayBoard(const int* gameBoard) {
    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++) {
            cout << mapValueToSymbol(gameBoard[3 * row + col]) << ((col < 2) ? '|' : '\n');
        }
        cout << ((row < 2) ? "-----\n" : "\n");
    }
}

int main(){
    int gameBoard[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int potentialWinner;
    int move;
    bool isInvalid;
    string moveString;
    srand(static_cast<int>(time(0)));
    int corners[4] = {0, 2, 6, 8};
    int sides[4] = {1, 3, 5, 7};

    cout << "1|2|3\n-----\n4|5|6\n-----\n7|8|9\n\n";

    while (true) {
        do {
            cout << "X: ";
            getline(cin, moveString);
            move = moveString[0] - '1';
            if (move > 8 || move < 0 || gameBoard[move] != 0) {
                cout << "Invalid input" << nl;
                isInvalid = true;
            } else {
                gameBoard[move] = 1;
                isInvalid = false;
                cout << nl;
            }
        } while (isInvalid);

        if (isGameOver(gameBoard)) {
            displayBoard(gameBoard);
            break;
        }

        bool good = false;
        for (int i = 2; i > 0; i--){
            potentialWinner = willWin(gameBoard, i);
            if (potentialWinner != -1) {
                gameBoard[potentialWinner] = 2;
                good = true;
                break;
            }
        }
        if (good);
        else if (gameBoard[4] == 0) gameBoard[4] = 2;
        else if (specialCase(gameBoard) > -1) gameBoard[specialCase(gameBoard)] = 2;
        else if (getRandomMove(gameBoard, corners) != -1) gameBoard[getRandomMove(gameBoard, corners)] = 2;
        else gameBoard[getRandomMove(gameBoard, sides)] = 2;

        displayBoard(gameBoard);

        if (isGameOver(gameBoard)) break;
    }
    return 0;
}
