#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

/* Change these constants below if you want a different size of canvas */
#define WIDTH 13  /*the canvas WIDTH*/  /*recommended an odd number*/
#define HEIGHT 16 /*the canvas HEIGHT*/

/* Do never change these constants below */
#define MAXWIDTH (WIDTH - 1) /*the canvas max WIDTH at right.  !!!Used for the piece not get out of the board!!! */
#define MINWIDTH 0   /*the canvas max WIDTH at right.           !!!Used for the piece not get out of the board!!! */

char mtzCanvas[WIDTH][HEIGHT];

int difficult = 0, timeLength = 0, pieceAlreadyInGame = 0,
    vPiece = 1, playerCommand, userScore = 0,filledLinesCounter = 0,
    xMidPosition = 0, yMidPosition = 0, gameOver = 0, gameTurn = 1,
    playerOneScore = 0, playerTwoScore = 0;

const int MIDBLOCK = (WIDTH/2)-1;

char* vDifficult = "(nao escolhida)";
char* vTimeLenght = "(nao escolhido)";

char playerOneNick[20] = " ";
char playerTwoNick[20] = " ";

void piece1(int x, int y, char value) {
    cleanMtz();
    mtzCanvas[x][y] = value;
    mtzCanvas[x + 1][y] = value;
    mtzCanvas[x + 2][y] = value;
    mtzCanvas[x + 3][y] = value;
}

void piece190(int x, int y, char value) {
    cleanMtz();
    mtzCanvas[x][y] = value;
    mtzCanvas[x][y + 1] = value;
    mtzCanvas[x][y + 2] = value;
    mtzCanvas[x][y + 3] = value;
}

void piece2(int x, int y, char value) {
    cleanMtz();
    mtzCanvas[x][y] = value;
    mtzCanvas[x + 1][y] = value;
    mtzCanvas[x + 2][y] = value;
    mtzCanvas[x + 2][y + 1] = value;
}

void piece290(int x, int y, char value) {
    cleanMtz();
    mtzCanvas[x][y] = value;
    mtzCanvas[x][y - 1] = value;
    mtzCanvas[x][y - 2] = value;
    mtzCanvas[x + 1][y -2] = value;
}

void piece218(int x, int y, char value) {
    cleanMtz();
    mtzCanvas[x][y] = value;
    mtzCanvas[x - 1][y] = value;
    mtzCanvas[x - 2][y] = value;
    mtzCanvas[x - 2][y - 1] = value;

}

void piece227(int x, int y, char value) {
    cleanMtz();
    mtzCanvas[x][y] = value;
    mtzCanvas[x][y + 1] = value;
    mtzCanvas[x][y + 2] = value;
    mtzCanvas[x - 1][y + 2] = value;

}

void cleanMtz() {
    int i = 0;
    int j = 0;
    for(i = 0;i < HEIGHT; i++) {
        for(j = 0;j < WIDTH;j++) {
            if(mtzCanvas[j][i] == 'x') {
                mtzCanvas[j][i] = ' ';
            }
        }
    }
}

cleanAllMtz() {
    int i = 0;
    int j = 0;
    for(i = 0;i < HEIGHT; i++) {
        for(j = 0;j < WIDTH;j++) {
            mtzCanvas[j][i] = ' ';
        }
    }
}

void printMatriz() {
    int i;
    int j;

    for(i = 0;i < HEIGHT; i++) {
        printf("\t   |");
        for(j = 0;j < WIDTH;j++) {
            if(mtzCanvas[j][i] == 0) {
                mtzCanvas[j][i] = ' ';
            }
            if(j != 0) printf(" ");
            printf("%c", mtzCanvas[j][i]);
        }
        printf("|");
        printf("\n");
    }
}

void drawCanvas(char *nick, char *offset) {
    system("CLS");

    printf("\t   ###########################\n");
    printf("\t   #       SCORE: %i\t     #\n", userScore);
    printf("\t   #       JOGADOR %i: %s%s  #\n", gameTurn,nick,offset);
    printf("\t   ###########################\n");

    printf("\t    ");
    int i;
    for(i=0; i<WIDTH ; i++) printf("_ ");
    printf("\n");
    printMatriz();
    printf("\t    ");
    for(i=0; i<WIDTH ; i++) printf("- ");

    printf("\n\t\t   #TIMER: %d\t\n", timeLength);
}

int setPiece() {
    if(pieceAlreadyInGame == 0) {
        vPiece = 1 + (rand() % 2);
        switch(vPiece) {
            case 1:
                xMidPosition = MIDBLOCK;
                yMidPosition = 0;
                if(mtzCanvas[xMidPosition][yMidPosition]!='X' &&
                   mtzCanvas[xMidPosition + 1][yMidPosition]!='X' &&
                   mtzCanvas[xMidPosition + 2][yMidPosition]!='X' &&
                   mtzCanvas[xMidPosition + 3][yMidPosition]!='X') {
                    piece1(MIDBLOCK, 0, 'x');
                    pieceAlreadyInGame = 1;
                } else {
                    gameOver = 1;
                }
                break;
            case 2:
                xMidPosition = MIDBLOCK;
                yMidPosition = 0;
                if(mtzCanvas[xMidPosition][yMidPosition]!='X' &&
                   mtzCanvas[xMidPosition + 1][yMidPosition]!='X' &&
                   mtzCanvas[xMidPosition + 2][yMidPosition]!='X' &&
                   mtzCanvas[xMidPosition + 2][yMidPosition + 1]!='X'){
                    piece2(MIDBLOCK, 0, 'x');
                    pieceAlreadyInGame = 1;
                } else {
                    gameOver = 1;
                }

        }
        return 1;
    }
    return 0;
}

int isPieceDownOtherPiece() {
    switch(vPiece) {
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
                mtzCanvas[xMidPosition + 2][yMidPosition + 2] != 'X') {
                return 0;
            } else {
                return 1;
            }
        case 290:
            if(mtzCanvas[xMidPosition][yMidPosition + 1] != 'X' &&
                mtzCanvas[xMidPosition + 1][(yMidPosition - 2) + 1] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
        case 218:
            if(mtzCanvas[xMidPosition][yMidPosition + 1] != 'X' &&
               mtzCanvas[xMidPosition - 1][yMidPosition + 1] != 'X' &&
               mtzCanvas[xMidPosition - 2][yMidPosition + 1] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
        case 227:
            if(mtzCanvas[xMidPosition][(yMidPosition + 2) + 1] != 'X' &&
               mtzCanvas[xMidPosition - 1][(yMidPosition + 2) + 1] != 'X') {
                return 0;
            } else {
                return 1;
            }
    }
}

int isPieceNextToOtherPiece(int direction) { // -1 == left && 1 == right
    switch(vPiece) {
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
        case 290:
            if(mtzCanvas[xMidPosition + direction][yMidPosition] != 'X' &&
               mtzCanvas[xMidPosition + direction][yMidPosition - 1] != 'X' &&
               mtzCanvas[xMidPosition + direction][yMidPosition - 2] != 'X' &&
               mtzCanvas[(xMidPosition + 1) + direction][yMidPosition - 2] != 'X') {
                return 0;
            } else {
                return 1;
            }
            break;
        case 218:
            if(mtzCanvas[xMidPosition + direction][yMidPosition] != 'X' &&
               mtzCanvas[(xMidPosition - 2) + direction][yMidPosition] != 'X' &&
               mtzCanvas[(xMidPosition - 2) + direction][yMidPosition - 1] != 'X'){
                return 0;
            } else {
                return 1;
            }
            break;
        case 227:
            if(mtzCanvas[xMidPosition + direction][yMidPosition] != 'X' &&
               mtzCanvas[xMidPosition + direction][yMidPosition + 1] != 'X' &&
               mtzCanvas[xMidPosition + direction][yMidPosition + 2] != 'X' &&
               mtzCanvas[(xMidPosition - 1) + direction][yMidPosition + 2] != 'X') {
                return 0;
            } else {
                return 1;
            }
    }
}

int isPieceOnTheGround(int piece) {
    switch(piece) {
        case 1: //piece 1
            if(yMidPosition < (HEIGHT - 1)) {
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
            if(yMidPosition < (HEIGHT - 1)) {
                return isPieceDownOtherPiece();
            } else {
                return 1;
            }
            break;
        case 218: //piece 2 turned 180 degrees left
            if(yMidPosition < (HEIGHT - 1)) {
                return isPieceDownOtherPiece();
            } else {
                return 1;
            }
            break;
        case 227: //piece 2 turned 270 degrees left
            if((yMidPosition + 2) < (HEIGHT - 1)) {
                return isPieceDownOtherPiece();
            } else {
                return 1;
            }
    }
}

void doPlayerCommand() {
    playerCommand = getch();
    switch(playerCommand) {
        case 77: //77 == right
            if(isPieceNextToOtherPiece(1) != 1) {
                switch(vPiece) {
                    case 1:
                        if((xMidPosition + 3) != MAXWIDTH) xMidPosition++;
                        piece1(xMidPosition, yMidPosition, 'x');
                        break;
                    case 190:
                        if(xMidPosition != MAXWIDTH) xMidPosition++;
                        piece190(xMidPosition, yMidPosition, 'x');
                        break;
                    case 2:
                        if((xMidPosition + 2) != MAXWIDTH) xMidPosition++;
                        piece2(xMidPosition, yMidPosition, 'x');
                        break;
                    case 290:
                        if((xMidPosition + 1) != MAXWIDTH) xMidPosition++;
                        piece290(xMidPosition, yMidPosition, 'x');
                        break;
                    case 218:
                        if(xMidPosition != MAXWIDTH) xMidPosition++;
                        piece218(xMidPosition, yMidPosition, 'x');
                        break;
                    case 227:
                        if(xMidPosition != MAXWIDTH) xMidPosition++;
                        piece227(xMidPosition, yMidPosition, 'x');

                }
            }
            break;
        case 80: //80 == down
            if((isPieceOnTheGround(vPiece)) == 0) {
                yMidPosition++;
                switch(vPiece) {
                    case 1:
                        piece1(xMidPosition, yMidPosition, 'x');
                        break;
                    case 190:
                        piece190(xMidPosition, yMidPosition, 'x');
                        break;
                    case 2:
                        piece2(xMidPosition, yMidPosition, 'x');
                        break;
                    case 290:
                        piece290(xMidPosition, yMidPosition, 'x');
                        break;
                    case 218:
                        piece218(xMidPosition, yMidPosition, 'x');
                        break;
                    case 227:
                        piece227(xMidPosition, yMidPosition, 'x');
                }
            }
            break;
        case 75: //75 == left
            if((isPieceNextToOtherPiece(-1)) != 1) {
                switch(vPiece) {
                    case 1:
                        if(xMidPosition != MINWIDTH) xMidPosition--;
                        piece1(xMidPosition, yMidPosition, 'x');
                        break;
                    case 190:
                        if(xMidPosition != MINWIDTH) xMidPosition--;
                        piece190(xMidPosition, yMidPosition, 'x');
                        break;
                    case 2:
                        if(xMidPosition != MINWIDTH) xMidPosition--;
                        piece2(xMidPosition, yMidPosition, 'x');
                        break;
                    case 290:
                        if(xMidPosition != MINWIDTH) xMidPosition--;
                        piece290(xMidPosition, yMidPosition, 'x');
                        break;
                    case 218:
                        if((xMidPosition - 2) != MINWIDTH) xMidPosition--;
                        piece218(xMidPosition, yMidPosition, 'x');
                        break;
                    case 227:
                        if((xMidPosition - 1) != MINWIDTH) xMidPosition--;
                        piece227(xMidPosition, yMidPosition, 'x');
                }
            }
            break;
        case 72: //72 == up
            switch(vPiece) {
                case 1:
                    if(mtzCanvas[xMidPosition][yMidPosition + 1] != 'X' &&
                       mtzCanvas[xMidPosition][yMidPosition + 2] != 'X' &&
                       mtzCanvas[xMidPosition][yMidPosition + 3] != 'X' &&
                        (yMidPosition + 3) <= (HEIGHT - 1)) {
                        piece190(xMidPosition, yMidPosition, 'x');
                        vPiece = 190;
                    }
                    break;
                case 190:
                    if((xMidPosition + 2) <= MAXWIDTH) {
                        if(mtzCanvas[xMidPosition + 1][yMidPosition] != 'X' &&
                           mtzCanvas[xMidPosition + 2][yMidPosition] != 'X' &&
                           mtzCanvas[xMidPosition + 3][yMidPosition] != 'X') {
                            piece1(xMidPosition, yMidPosition, 'x');
                            vPiece = 1;
                        }
                    }
                    break;
                case 2:
                    if((yMidPosition - 2) >= 0) {
                        if(mtzCanvas[xMidPosition][yMidPosition - 1] != 'X' &&
                           mtzCanvas[xMidPosition][yMidPosition - 2] != 'X' &&
                           mtzCanvas[xMidPosition + 1][yMidPosition - 2] != 'X') {
                            piece290(xMidPosition, yMidPosition, 'x');
                            vPiece = 290;
                        }
                    }
                    break;
                case 290:
                    if((xMidPosition - 2) >= 0) {
                        if(mtzCanvas[xMidPosition - 1][yMidPosition] != 'X' &&
                           mtzCanvas[xMidPosition - 2][yMidPosition] != 'X' &&
                           mtzCanvas[xMidPosition - 2][yMidPosition - 1] != 'X') {
                            piece218(xMidPosition, yMidPosition, 'x');
                            vPiece = 218;
                        }
                    }
                    break;
                case 218:
                    if((yMidPosition + 2) <= (HEIGHT - 1)) {
                        if(mtzCanvas[xMidPosition][yMidPosition + 1] != 'X' &&
                           mtzCanvas[xMidPosition][yMidPosition + 2] != 'X' &&
                           mtzCanvas[xMidPosition - 1][yMidPosition + 2] != 'X') {
                            piece227(xMidPosition, yMidPosition, 'x');
                            vPiece = 227;
                        }
                    }
                    break;
                case 227:
                    if((xMidPosition + 2) <= MAXWIDTH) {
                        if(mtzCanvas[xMidPosition + 1][yMidPosition] != 'X' &&
                           mtzCanvas[xMidPosition + 2][yMidPosition] != 'X' &&
                           mtzCanvas[xMidPosition + 2][yMidPosition + 1] != 'X') {
                            piece2(xMidPosition, yMidPosition, 'x');
                            vPiece = 2;
                        }
                    }
        }
    }
}

void fallPiece() {
    if(isPieceOnTheGround(vPiece) == 0) {
        yMidPosition++;
        switch(vPiece) {
            case 1:
                piece1(xMidPosition, yMidPosition, 'x');
                break;
            case 190:
                piece190(xMidPosition, yMidPosition, 'x');
                break;
            case 2:
                piece2(xMidPosition, yMidPosition, 'x');
                break;
            case 290:
                piece290(xMidPosition, yMidPosition, 'x');
                break;
            case 218:
                piece218(xMidPosition, yMidPosition, 'x');
                break;
            case 227:
                piece227(xMidPosition, yMidPosition, 'x');
        }
    } else {
        switch(vPiece) {
            case 1:
                piece1(xMidPosition, yMidPosition, 'X');
                break;
            case 190:
                piece190(xMidPosition, yMidPosition, 'X');
                break;
            case 2:
                piece2(xMidPosition, yMidPosition, 'X');
                break;
            case 290:
                piece290(xMidPosition, yMidPosition, 'X');
                break;
            case 218:
                piece218(xMidPosition, yMidPosition, 'X');
                break;
            case 227:
                piece227(xMidPosition, yMidPosition, 'X');
        }
        pieceAlreadyInGame = 0;
        checkFullLines();
    }
}

void checkFullLines() {
    int i;
    int j;
    int l;
    for(i=HEIGHT; i!=0; i--) {
        if(mtzCanvas[0][i]=='X' && mtzCanvas[1][i]=='X' && mtzCanvas[2][i]=='X' && mtzCanvas[3][i]=='X' &&
           mtzCanvas[4][i]=='X' && mtzCanvas[5][i]=='X' && mtzCanvas[6][i]=='X' && mtzCanvas[7][i]=='X' &&
           mtzCanvas[8][i]=='X' && mtzCanvas[9][i]=='X' && mtzCanvas[10][i]=='X' && mtzCanvas[11][i]=='X' &&
           mtzCanvas[12][i]=='X') {

            filledLinesCounter++;
            userScore += (100 * filledLinesCounter);

        } else {
            while(filledLinesCounter > 0) {
                i++;
                for(j=0; j<WIDTH + 1; j++) {
                    mtzCanvas[j][i] = ' ';
                    for(l=i-1;l!=-1;l--) {
                        mtzCanvas[j][l+1] = mtzCanvas[j][l];
                        mtzCanvas[j][l] = ' ';
                    }
                }
                filledLinesCounter--;
            }
        }
    }
    filledLinesCounter = 0;
}

void showGameOver() {
    printf("\t  GGGGGGGGGGG     GGGGGGGGGGG\n");
    printf("\t  GGGGGGGGGGG     GGGGGGGGGGG\n");
    printf("\t  GGGG            GGGG       \n");
    printf("\t  GGGG  GGGGG     GGGG  GGGGG\n");
    printf("\t  GGGG  GGGGG     GGGG  GGGGG\n");
    printf("\t  GGGG    GGG     GGGG    GGG\n");
    printf("\t  GGGGGGGGGGG     GGGGGGGGGGG\n");
    printf("\t  GGGGGGGGGGG     GGGGGGGGGGG\n");
}

void choosePlayerNames() {
    int segundos = 10, i;
    do {
        system("CLS");
        if(strlen(playerOneNick) > 5 || strlen(playerTwoNick) > 5){
            printf("ERRO: Um dos nicks possui mais de 5 carateres!\n");
        }

        printf("\n\n\n\n\n");
        printf("Escolha de nomes (5 caracteres): ");
        printf("\n\n");

        printf("\t -- Jogador 1 --> ");
        fflush(stdin);
        gets(playerOneNick);

        printf("\n\n");

        printf("\t -- Jogador 2 --> ");
        fflush(stdin);
        gets(playerTwoNick);

        printf("\n\n\n\n\n\n");
    } while(strlen(playerOneNick) > 5 || strlen(playerTwoNick) > 5);
    system("pause");
    system("CLS");

    for(i=10; i!=0; i--) {
        printf("\n\n\n\n\n");
        printf("\tPrepare - se PLAYER 1 !!!  :D");
        printf("\n\n\n\n\n");
        printf("\tIniciando jogo em %i segundos", i);
        Sleep(1*1000);
        system("cls");
    }
}

void startGame() {
    if(gameTurn != 2){
        choosePlayerNames();
    } else {
        int i;
        for(i=10; i!=0; i--) {
            printf("\n\n\n\n\n");
            printf("\tPrepare - se PLAYER 2 !!!  :D");
            printf("\n\n\n\n\n");
            printf("\tIniciando jogo em %i segundos", i);
            Sleep(1*1000);
            system("cls");
        }
    }
    char *playerNick = gameTurn == 1 ? playerOneNick : playerTwoNick;
    char *offset = "";
    switch(strlen(playerNick)) {
        case 4:
            offset = " ";
            break;
        case 3:
            offset = "  ";
            break;
        case 2:
            offset = "   ";
            break;
        case 1:
            offset = "    ";
        break;
        case 0:
            offset = "     ";

    }

    int reDraw = 1; //controls the reDraws of the board
    int timeLengthSave = timeLength; //save the time length for the next turn
    time_t timeController_FallPiece = time(NULL); //used for control the speed's falling of the piece
    time_t timeController_Game = time(NULL); //used for control the time of the game
    time_t plusDif = (time_t) difficult; //used for control the speed's falling of the piece

    int isTimeInfinity = timeLengthSave == 1 ? 1 : 0;

    do {
        /*controls the time of the game*/
        if(isTimeInfinity != 1) {
            if(timeController_Game != time(NULL)) {
                timeController_Game = time(NULL);
                timeLength--;
                reDraw++;
            }
        }

        /*make it draw only if necessary*/
        if(reDraw > 0) {
            drawCanvas(playerNick, offset); //1 - draw the canvas on screen
            reDraw--;
        }
        reDraw += setPiece(); //2 - put a new piece in the game
        if(kbhit()) {
            reDraw++;
            fflush(stdin);
            doPlayerCommand(); //3 - get and execute the player command
        }
        /*piece speed's falling*/
        if((timeController_FallPiece + plusDif) <= time(NULL)) {
            timeController_FallPiece = time(NULL);
            fallPiece(); //4 - make the piece fall
            reDraw++;
        }
    } while(gameOver != 1 && timeLength > 0);

    system("CLS");
    printf("\n\n\n\n\n");
    showGameOver();
    printf("\n\n\n\n\n\n\n\n\n\n");

    if(gameTurn == 1) {
        gameOver = 0;
        gameTurn = 2;
        timeLength = timeLengthSave;

        playerOneScore = userScore;
        userScore = 0;

        Sleep(5*1000);
        fflush(stdin);
        system("pause");
        system("CLS");

        cleanAllMtz();

        pieceAlreadyInGame = 0;
        startGame();
    } else {
        gameOver = 0;
        gameTurn = 1;
        timeLength = timeLengthSave;

        playerTwoScore = userScore;
        userScore = 0;

        if(playerOneScore > playerTwoScore) {
            printf("PLAYER 1 PARABENS!!!  :D");
            printf("\n\n\n\n");
        } else if (playerTwoScore > playerOneScore) {
            printf("PLAYER 2 PARABENS!!!  :D");
            printf("\n\n\n\n");
        } else {
            printf("EMPATE!!! lol");
            printf("\n\n\n\n");
        }

        cleanAllMtz();
        Sleep(5*1000);
        fflush(stdin);
        system("pause");
        system("CLS");

        pieceAlreadyInGame = 0;
    }

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
        printf("\t 1 - Easy \n\n");
        printf("\t 2 - Medium \n\n");
        printf("\t 3 - Hard \n\n");
        printf("\t ESC - <- Voltar \n\n");

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
void chooseTime() {
    int escape = 0;
    char* vError = "";
    do {
        int usrChoose = 0;

        if(vError != "") {
            printf("\n\n");
            printf(vError);
            vError = "";
        }

        printf("\n\n\n\n\n\n");
        printf("\t 1 - 1 Min     \t 4 - 10 Min    \n\n");
        printf("\t 2 - 2 Min     \t 5 - 15 Min    \n\n");
        printf("\t 3 - 3 Min     \t 6 -  INFINITO \n\n");

        printf("\n\n");
        printf("\t ESC - <- Voltar \n\n");

        usrChoose = getch();
        switch(usrChoose) {
            case 49:
                timeLength = 1 * 60;
                vTimeLenght = "1 Minuto";
                escape = 1;
                break;
            case 50:
                timeLength = 2 * 60;
                vTimeLenght = "2 Minutos";
                escape = 1;
                break;
            case 51:
                timeLength = 3 * 60;
                vTimeLenght = "3 Minutos";
                escape = 1;
                break;
            case 52:
                timeLength = 10 * 60;
                vTimeLenght = "10 Minutos";
                escape = 1;
                break;
            case 53:
                timeLength = 15 * 60;
                vTimeLenght = "15 Minutos";
                escape = 1;
                break;
            case 54:
                timeLength = 1;
                vTimeLenght = "INFINITO";
                escape = 1;
                break;
            default:
                vError = "\t\t ERRO: Escolha somente 1, 2, 3 ou ESC! \n\n\n";
                break;
        }
        system("CLS");

    } while(escape != 1);
}

int main() {
    system("mode 50,30");
    char* vError = "";
    while(1) {
        char usrChoose;

        if(vError != "") {
            printf("\n\n");
            printf(vError);
            vError = "";
        }

        printf("\n\n\n\n\n\n");
        printf("\t P - Inicia o game \n\n");
        printf("\t D - Escolhe a dificuldade \n\n");
        printf("\t T - Escolhe o tempo de jogo \n\n");
        printf("\t ESC - Sair \n\n\n\n\n\n");

        printf("\t DIFICULDADE -> %s\n",vDifficult);
        printf("\t TEMPO DE JOGO -> %s\n",vTimeLenght);

        usrChoose = getch();
        switch(usrChoose) {
            case 112: //112 == p
                system("CLS");
                if(difficult != 0 && timeLength != 0) {
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
                chooseTime();
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
