#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <Windows.h>
#include <time.h>

/* Change these constants behind if you want a different size of canvas */
#define WIDTH 13  /*the canvas WIDTH*/  /*recommended an odd number*/
#define HEIGHT 16 /*the canvas HEIGHT*/

/* Don't change these constants behind never */
#define MAXWIDTHRIGHT (WIDTH - 1) /*the canvas max WIDTH at right.  !!!Used for the piece not get out of the board!!! */
#define MAXWIDTHLEFT 0   /*the canvas max WIDTH at right.           !!!Used for the piece not get out of the board!!! */

char mtzCanvas[WIDTH][HEIGHT];

int difficult = 0, timeLength = 0, pieceAlreadyInGame = 0,
    vPiece = 1, playerCommand, userScore = 0,filledLinesCounter = 0,
    xMidPosition = 0, yMidPosition = 0;

const int MIDBLOCK = (WIDTH/2)-1;

char* vDifficult = "(nao escolhida)";
char* vTimeLenght = "(nao escolhido)";

void piece1(int x, int y, char value) {
    mtzCanvas[x][y] = value;
    mtzCanvas[x + 1][y] = value;
    mtzCanvas[x + 2][y] = value;
    mtzCanvas[x + 3][y] = value;
}

void piece190(int x, int y, char value) {
    mtzCanvas[x][y] = value;
    mtzCanvas[x][y + 1] = value;
    mtzCanvas[x][y + 2] = value;
    mtzCanvas[x][y + 3] = value;
}

void piece2(int x, int y, char value) {
    mtzCanvas[x][y] = value;
    mtzCanvas[x + 1][y] = value;
    mtzCanvas[x + 2][y] = value;
    mtzCanvas[x + 2][y + 1] = value;
}

void piece290() {

}

void piece218() {

}

void piece227() {

}

int isPieceDownOtherPiece() {
    switch(vPiece){
        case 1:
            if(mtzCanvas[xMidPosition][yMidPosition + 1] != 'X' &&
                mtzCanvas[xMidPosition + 1][yMidPosition + 1] != 'X' &&
                mtzCanvas[xMidPosition + 2][yMidPosition + 1] != 'X' &&
                mtzCanvas[xMidPosition + 3][yMidPosition + 1] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
        case 190:
            if(mtzCanvas[xMidPosition][yMidPosition + 4] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
        case 2:
            if(mtzCanvas[xMidPosition][yMidPosition + 1] != 'X' &&
               mtzCanvas[xMidPosition + 1][yMidPosition + 1] != 'X' &&
                mtzCanvas[xMidPosition + 2][yMidPosition + 1] != 'X' &&
                mtzCanvas[xMidPosition + 2][yMidPosition + 2] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
    }
}

int isPieceNextToOtherPiece(int direction) { // -1 == left && 1 == right
    switch(vPiece){
        case 1:
            if(mtzCanvas[xMidPosition + direction][yMidPosition] != 'X' &&
               mtzCanvas[(xMidPosition + 3) + direction][yMidPosition] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
        case 190:
            if(mtzCanvas[xMidPosition + direction][yMidPosition] != 'X' &&
               mtzCanvas[xMidPosition + direction][yMidPosition + 1] != 'X' &&
               mtzCanvas[xMidPosition + direction][yMidPosition + 2] != 'X' &&
               mtzCanvas[xMidPosition + direction][yMidPosition + 3] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
        case 2:
            if(mtzCanvas[xMidPosition + direction][yMidPosition] != 'X' &&
               mtzCanvas[(xMidPosition + 2) + direction][yMidPosition] != 'X' &&
               mtzCanvas[(xMidPosition + 2) + direction][yMidPosition + 1] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
    }
}

void cleanMtz() {
    int i = 0;
    int j = 0;
    for(i = 0;i < HEIGHT; i++) {
        for(j = 0;j < WIDTH;j++) {
            if(mtzCanvas[j][i] == 'x') {
                mtzCanvas[j][i] = '.';
            }
        }
    }
}

void drawCanvas() {
    int i;
    int j;
    printf("  ");
    for(i = 0; i<WIDTH ; i++) printf("_ ");
    printf("\n");
    for(i = 0;i < HEIGHT; i++) {
        printf("|");
        for(j = 0;j < WIDTH;j++) {
            if(mtzCanvas[j][i] == 0) {
                mtzCanvas[j][i] = '.';
            }
            printf(" %c", mtzCanvas[j][i]);
        }
        printf(" |");
        printf("\n");
    }
    printf("  ");
    for(i = 0; i<WIDTH ; i++) printf("- ");
    printf("\n");
}

int setPiece() {
    if(pieceAlreadyInGame == 0) {
        vPiece = 1 + (rand() % 2);
        switch(vPiece) {
            case 1:
                xMidPosition = MIDBLOCK;
                yMidPosition = 0;
                piece1(MIDBLOCK, 0, 'x');
                pieceAlreadyInGame = 1;
                return 0;
            case 2:
                xMidPosition = MIDBLOCK;
                yMidPosition = 0;
                piece2(MIDBLOCK, 0, 'x');
                pieceAlreadyInGame = 1;
                return 0;
            default:
                return 1;

        }
    }
    return 0;
}

void doPlayerCommand() {
    playerCommand = getch();
    switch(playerCommand) {
        case 77: //77 == right
            if(isPieceNextToOtherPiece(1) != 1) {
                cleanMtz();
                switch(vPiece){
                    case 1:
                        if((xMidPosition + 3) != MAXWIDTHRIGHT) xMidPosition++;
                        piece1(xMidPosition, yMidPosition, 'x');
                        break;
                    case 190:
                        if(xMidPosition != MAXWIDTHRIGHT) xMidPosition++;
                        piece190(xMidPosition, yMidPosition, 'x');
                        break;
                    case 2:
                        if((xMidPosition + 2) != MAXWIDTHRIGHT) xMidPosition++;
                        piece2(xMidPosition, yMidPosition, 'x');
                        break;
                }
            }
            break;
        case 80: //80 == down
            if((isPieceOnTheGround(vPiece)) == 0) {
                cleanMtz();
                yMidPosition++;
                switch(vPiece){
                    case 1:
                        piece1(xMidPosition, yMidPosition, 'x');
                        break;
                    case 190:
                        piece190(xMidPosition, yMidPosition, 'x');
                        break;
                    case 2:
                        piece2(xMidPosition, yMidPosition, 'x');
                        break;
                }
            }
            break;
        case 75: //75 == left
            if((isPieceNextToOtherPiece(-1)) != 1) {
                cleanMtz();
                switch(vPiece){
                    case 1:
                        if(xMidPosition != MAXWIDTHLEFT) xMidPosition--;
                        piece1(xMidPosition, yMidPosition, 'x');
                        break;
                    case 190:
                        if(xMidPosition != MAXWIDTHLEFT) xMidPosition--;
                        piece190(xMidPosition, yMidPosition, 'x');
                        break;
                    case 2:
                        if(xMidPosition != MAXWIDTHLEFT) xMidPosition--;
                        piece2(xMidPosition, yMidPosition, 'x');
                        break;
                }
            }
            break;
        case 72: //72 == up
            cleanMtz();
            switch(vPiece){
                case 1:
                    piece190(xMidPosition, yMidPosition, 'x');
                    vPiece = 190;
                    break;
                case 190:
                    piece1(xMidPosition, yMidPosition, 'x');
                    vPiece = 1;
                    break;
            }
            break;
    }
}

int isPieceOnTheGround(int piece) {
    switch(piece) {
        case 1: //piece 1
            if(yMidPosition < (HEIGHT - 1)){
                    return isPieceDownOtherPiece();
            } else {
                return 1;
            }
            break;
        case 190: //piece 1 turned 90 degrees left
            if((yMidPosition + 3) < (HEIGHT - 1)) {
                return isPieceDownOtherPiece();
            } else {
                return 1;
            }
            break;
        case 2: //piece 2
            if((yMidPosition + 1) < (HEIGHT - 1)) {
                return isPieceDownOtherPiece();
            } else {
                return 1;
            }
            break;
        case 290: //piece 2 turned 90 degrees left
            break;
        case 218: //piece 2 turned 180 degrees left
            break;
        case 227: //piece 2 turned 270 degrees left
            break;
    }
}

void fallPiece() {
    if(isPieceOnTheGround(vPiece) == 0) {
        cleanMtz();
        yMidPosition++;
        switch(vPiece){
            case 1:
                piece1(xMidPosition, yMidPosition, 'x');
                break;
            case 190:
                piece190(xMidPosition, yMidPosition, 'x');
                break;
            case 2:
                piece2(xMidPosition, yMidPosition, 'x');
                break;
        }
    } else {
        switch(vPiece){
            case 1:
                piece1(xMidPosition, yMidPosition, 'X');
                break;
            case 190:
                piece190(xMidPosition, yMidPosition, 'X');
                break;
            case 2:
                piece2(xMidPosition, yMidPosition, 'X');
                break;
        }
        pieceAlreadyInGame = 0;
        checkFullLines();
    }
}

void checkFullLines(){
    int i;
    int j;
    int l;
    for(i=HEIGHT; i!=0; i--){
        if(mtzCanvas[0][i]=='X' && mtzCanvas[1][i]=='X' && mtzCanvas[2][i]=='X' && mtzCanvas[3][i]=='X' &&
           mtzCanvas[4][i]=='X' && mtzCanvas[5][i]=='X' && mtzCanvas[6][i]=='X' && mtzCanvas[7][i]=='X' &&
           mtzCanvas[8][i]=='X' && mtzCanvas[9][i]=='X' && mtzCanvas[10][i]=='X' && mtzCanvas[11][i]=='X'){

            filledLinesCounter++;
            userScore += (100 * filledLinesCounter);

        } else {
            while(filledLinesCounter > 0){
                i++;
                for(j=0; j<WIDTH; j++){
                    mtzCanvas[j][i] = '.';
                    for(l=i-1;l!=0;l--){
                        mtzCanvas[j][l+1] = mtzCanvas[j][l];
                    }
                }
                filledLinesCounter--;
            }
        }
    }
    filledLinesCounter = 0;
}

void startGame() {
    int gameOver = 0;
    int vErr = 0;
    time_t t = time(NULL);
    time_t plusDif = (time_t) difficult;

    do {
        drawCanvas();
        vErr = setPiece();
        if(kbhit()) {
            doPlayerCommand();
        }
        if((t + plusDif) <= time(NULL)) {
            t = time(NULL);
            fallPiece();
        }
        printf("%i", userScore);
        Sleep(16.66);
        system("CLS");
    } while(gameOver != 1 && vErr != 1);
}

void chooseDificult() {
    char *vError = "";
    while(1) {
        int usrChoose = 0;

        if(vError != "") {
            printf("\n\n");
            printf(vError);
            vError = "";
        }

        printf("\n\n\n\n\n\n");
        printf("\t\t 1 - Easy \n\n");
        printf("\t\t 2 - Medium \n\n");
        printf("\t\t 3 - Hard \n\n");
        printf("\t\t ESC - <- Voltar \n\n");

        usrChoose = getch();
        switch(usrChoose) {
            case 49:
                difficult = 3;
                vDifficult = "EASY";
                break;
            case 50:
                difficult = 2;
                vDifficult = "MEDIUM";
                break;
            case 51:
                difficult = 1;
                vDifficult = "HARD";
                break;
            default:
                vError = "\t\t ERRO: Escolha somente 1, 2, 3 ou ESC! \n\n\n";
                break;
        }
        system("CLS");
        if(usrChoose == 27 || usrChoose == 49 || usrChoose == 50 || usrChoose == 51) break;
    }
}
void choseTime() {
    char* vError = "";
    while(1) {
        int usrChoose = 0;

        if(vError != "") {
            printf("\n\n");
            printf(vError);
            vError = "";
        }

        printf("\n\n\n\n\n\n");
        printf("\t\t 1 - 1 Minuto \n\n");
        printf("\t\t 2 - 2 Minutos \n\n");
        printf("\t\t 3 - 3 Minutos \n\n");
        printf("\t\t ESC - <- Voltar \n\n");

        usrChoose = getch();
        switch(usrChoose) {
            case 49:
                timeLength = 1;
                vTimeLenght = "1 Minuto";
                break;
            case 50:
                timeLength = 2;
                vTimeLenght = "2 Minutos";
                break;
            case 51:
                timeLength = 3;
                vTimeLenght = "3 Minutos";
                break;
            default:
                vError = "\t\t ERRO: Escolha somente 1, 2, 3 ou ESC! \n\n\n";
                break;
        }
        system("CLS");
        if(usrChoose == 27 || usrChoose == 49 || usrChoose == 50 || usrChoose == 51) break;
    }
}

int main(){
    char* vError = "";
    while(1) {
        char usrChoose;

        if(vError != "") {
            printf("\n\n");
            printf(vError);
            vError = "";
        }

        printf("\n\n\n\n\n\n");
        printf("\t\t P - Inicia o game \n\n");
        printf("\t\t D - Escolhe a dificuldade \n\n");
        printf("\t\t T - Escolhe o tempo de jogo \n\n");
        printf("\t\t ESC - Sair \n\n\n\n\n\n");

        printf("\t DIFICULDADE -> %s\t",vDifficult);
        printf("\t TEMPO DE JOGO -> %s\n",vTimeLenght);

        usrChoose = getch();
        switch(usrChoose) {
            case 112: //112 == p
                system("CLS");
                if(1) { //difficult != 0 && timeLength != 0
                    startGame();
                } else {
                    vError = "\t\t ERRO: Escolha uma dificuldade e tempo de jogo!";
                }
                break;
            case 100: //100 == d
                system("CLS");
                chooseDificult();
                break;
            case 116: //116 == t
                system("CLS");
                choseTime();
                break;
            default:
                vError = "\t\t ERRO: Escolha somente P, D, T ou ESC! \n\n\n";
                break;
        }
        system("CLS");
        if(usrChoose == 27) break;
    }
    return 0;
}
