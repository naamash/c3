#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MATRIX_ROW 6
#define MATRIX_COL 7

char matrix [MATRIX_ROW][MATRIX_COL];
char kelet[1100];
int tor[43];
int i,j,k; 
int a,b; 
int m;
int col;  
int helpkelet;
int indexTor=0;
int row;
int counter=0;
int counterpoint;
int playsome=0;
int num;
char player = 'X';
bool win=false;
bool keletcorrect=true;

void changeMatrix (char matrix[MATRIX_ROW][MATRIX_COL],int col);
void PlayPlayer (char matrix[MATRIX_ROW][MATRIX_COL]);

void PrintMatrix(char matrix[MATRIX_ROW][MATRIX_COL]){
    for (i=0 ; i < MATRIX_ROW ; i++){
        for (j=0 ; j<MATRIX_COL ; j++){
            printf("|%c",matrix[i][j]);
        }
        printf("|\n");
    }
    for (k=1 ; k<8 ; k++){
        printf(" %d" , k);
    }
    printf("\n");
}

bool winSlant2(char matrix[MATRIX_ROW][MATRIX_COL],int row,int col){
    counter=1;
    for (a=row-1 , b=col-1 ; a>=0 && b>=0  ; a-- && b--){
        if ((matrix[a][b])==player){
            counter++;
        }
        else{
            break;
        }
    }

    for (a=row+1 , b=col+1 ; a<MATRIX_ROW && b<MATRIX_COL  ; a++ && b++){
        if ((matrix[a][b])==player){
            counter++;
        }
        else{
            break;
        }
    }

    if (counter>=4){
        return true;
    }
    else{
    return false;
    }
}

bool winSlant(char matrix[MATRIX_ROW][MATRIX_COL],int row,int col){
    counter=1;
    for (a=row-1, b=col+1 ; a>=0 && b<MATRIX_COL  ; a-- && b++){
        if ((matrix[a][b])==player){
            counter++;
        }
        else{
            break;
        }
    }

    if (row<5 && col>0){
        for (a=row+1 , b=col-1 ; a<MATRIX_ROW && b>=0  ; a++ && b--){
            if ((matrix[a][b])==player){
                counter++;
            }
            else{
                break;
            }
        }
    }
    if (counter>=4){
        return true;
    }
    else{
        return false;
    }
}

bool winCol(char matrix[MATRIX_ROW][MATRIX_COL],int row,int col){
    counter=1;
    for (a=row+1 ; a<MATRIX_ROW ; a++){
        if ((matrix[a][col])==player){
            counter++;
        }
        else{
            break;
        }
    }
    if (counter>=4){
        return true;
    }
    else{
        return false;
    }
}

bool winRow(char matrix[MATRIX_ROW][MATRIX_COL],int row,int col){
    counter=1;
    for (a=col+1 ; a<MATRIX_COL ; a++){
        if ((matrix[row][a])==player){
            counter++;
        }
        else{
            break;
        }
    }
    for (b=col-1 ; b>=0 ; b--){
        if ((matrix[row][b])==player){
            counter++;
        }
        else{
            break;
        }
    }
    if (counter>=4){
        return true;
    }
    else{
        return false;
    }
}
int checkelet(char kelet[1100]){
    for (m=0 ; m<strlen(kelet) ; m++){
        if (kelet[0]=='-'||kelet[m]=='.' && counterpoint==0){
            counterpoint++;
            helpkelet = 1;
        }
        else if (kelet[0]=='.'||!isdigit(kelet[m]) && (kelet[m]!='.') || counterpoint>1){
            keletcorrect=false;
            helpkelet = 2;
            return helpkelet;
        }
    }
return helpkelet;
}      

void checkelet2(char kelet[1100]){
    num=atoi(kelet);
    if (strlen(kelet)==1){
        if (isdigit(kelet[0])){
            keletcorrect=true;
            col=num;
        }
        else{
            printf("Invalid input, bye-bye!\n");
            keletcorrect=false;
        }
    }

    if (strlen(kelet)>1){
        if(checkelet(kelet)==1){
            col=num;        
        }
        else if (checkelet(kelet)==2){
            printf("Invalid input, bye-bye!\n");
            keletcorrect=false;
        }
    }

    if(keletcorrect){
        while (col<0||col>7){
            PrintMatrix(matrix);
            printf("Invalid input, the number must be between 1 to 7:\n");
            memset(kelet,0,1100);
            scanf("%s",kelet);
            checkelet2(kelet);
        }

        if (col>0 && col<8){
            tor[indexTor]=col;
            indexTor=indexTor+1;
            changeMatrix (matrix,col);
        }
        else if (col==0){
            if (tor[indexTor-1]==0){
                printf("Board is empty - can't undo!\n");
                PlayPlayer(matrix);
            }
            else{
                changeMatrix (matrix,col);
            }
        }
    }
}

void changeMatrix (char matrix[MATRIX_ROW][MATRIX_COL],int col){
    bool stop = true;
    int row = MATRIX_ROW-1;
    if (col>0 && col<8){
        while (row>=0 && stop == true){
            if (matrix[row][col-1]==' '){
                matrix[row][col-1] = player; 
                playsome++;
                stop=false;
                if ((winCol(matrix,row,col-1)==true)||(winRow(matrix,row,col-1)==true)
                    ||(winSlant(matrix,row,col-1)==true)||(winSlant2(matrix,row,col-1)==true)){
                    win=true;
                    PrintMatrix(matrix);
                    printf("Player %c wins!\n",player);
                    break;
                }
            }
            else{
                row--;
            }
        }
    }
    if (row<0){
        PrintMatrix(matrix);
        printf("Invalid input, this column is full. Please choose another one:\n");
        memset(kelet,0,1100);
        scanf("%s",kelet);
        checkelet2(kelet);
    }
    
    if (col==0){
        col = tor[indexTor-1];
        if ((matrix[row][col-1]=='X')||(matrix[row][col-1]=='O')){
            matrix[row][col-1]=' ';
            indexTor=indexTor-1;
            playsome--;
        }
        else{
            row--;
        }
    }
    
    if (player == 'X'){
        player = 'O';
    }
    else {
        player = 'X';
    }
} 

void PlayPlayer (char matrix[MATRIX_ROW][MATRIX_COL]){
    PrintMatrix(matrix);
    printf ("Player %c, please enter a column number (or 0 to undo):\n",player);
    memset(kelet,0,1100);
    scanf("%s",kelet);
    checkelet2(kelet);
}

void Game (char matrix[MATRIX_ROW][MATRIX_COL]){
    while (!win && keletcorrect){
        if (playsome<42){
        PlayPlayer(matrix);
        }
        else{
            break;
        }
    }

    if (playsome==42){
        PrintMatrix(matrix);
        printf("It's a tie!\n");
    }
}