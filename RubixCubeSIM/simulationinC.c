#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// perm states 
/*
void save_cube(const char *filename, char cube[6][7][7]) {
    FILE *f = fopen(filename, "wb");
    fwrite(cube, sizeof(char), 6*7*7, f);
    fclose(f);
}
void load_cube(const char *filename, char cube[6][7][7]) {
    FILE *f = fopen(filename, "rb");
    fread(cube, sizeof(char), 6*7*7, f);
    fclose(f);
}
*/

char updateW[4] = {'b','r','g','o'};
char updateO[4] = {'b','w','g','y'};
char updateB[4] = {'r','w','o','y'};
char updateR[4] = {'b','y','g','w'};
char updateG[4] = {'o','w','r','y'};
char updateY[4] = {'b','o','g','r'};


char default1[7][7] = {
      {'0','0','0','0','0','0','0'},
      {'0','0','0','0','0','0','0'},
      {'0','0','0','0','0','0','0'},
      {'0','0','0','0','0','0','0'},
      {'0','0','0','0','0','0','0'},
      {'0','0','0','0','0','0','0'},
      {'0','0','0','0','0','0','0'}
      };
char whiteface[7][7] = {
      {'0','0','b','b','b','0','0'},
      {'0','0','0','0','0','0','0'},
      {'o','0','w','w','w','0','r'},
      {'o','0','w','w','w','0','r'},
      {'o','0','w','w','w','0','r'},
      {'0','0','0','0','0','0','0'},
      {'0','0','g','g','g','0','0'}
};
char blueface[7][7] = {
      {'0','0','y','y','y','0','0'},
      {'0','0','0','0','0','0','0'},
      {'o','0','b','b','b','0','r'},
      {'o','0','b','b','b','0','r'},
      {'o','0','b','b','b','0','r'},
      {'0','0','0','0','0','0','0'},
      {'0','0','w','w','w','0','0'}
};
char redface[7][7] = {
      {'0','0','y','y','y','0','0'},
      {'0','0','0','0','0','0','0'},
      {'b','0','r','r','r','0','g'},
      {'b','0','r','r','r','0','g'},
      {'b','0','r','r','r','0','g'},
      {'0','0','0','0','0','0','0'},
      {'0','0','w','w','w','0','0'}
};
char greenface[7][7] = {
      {'0','0','y','y','y','0','0'},
      {'0','0','0','0','0','0','0'},
      {'r','0','g','g','g','0','o'},
      {'r','0','g','g','g','0','o'},
      {'r','0','g','g','g','0','o'},
      {'0','0','0','0','0','0','0'},
      {'0','0','w','w','w','0','0'}
};
char orangeface[7][7] = {
      {'0','0','y','y','y','0','0'},
      {'0','0','0','0','0','0','0'},
      {'g','0','o','o','o','0','b'},
      {'g','0','o','o','o','0','b'},
      {'g','0','o','o','o','0','b'},
      {'0','0','0','0','0','0','0'},
      {'0','0','w','w','w','0','0'}
};
char yellowface[7][7] = {
      {'0','0','b','b','b','0','0'},
      {'0','0','0','0','0','0','0'},
      {'o','0','w','w','w','0','r'},
      {'o','0','w','w','w','0','r'},
      {'o','0','w','w','w','0','r'},
      {'0','0','0','0','0','0','0'},
      {'0','0','g','g','g','0','0'}
};

void updatesides(char side){
      char updateW[4] = {'b','r','g','o'};
      char updateO[4] = {'b','w','g','y'};
      char updateB[4] = {'r','w','o','y'};
      char updateR[4] = {'b','y','g','w'};
      char updateG[4] = {'o','w','r','y'};
      char updateY[4] = {'b','o','g','r'};
      if (side == 'w'){
            for (int j = 0 ; j < 4; j++){
                  blueface[4][j+2] = whiteface[0][j+2];
                  blueface[7][j+2] = whiteface[2][j+2];
                  redface[j+2][0] = whiteface[j+2][4];
                  redface[j+2][2] = whiteface[j+2][6];
                  greenface[0][j+2]=whiteface[4][j+2];
                  greenface[2][j+2]=whiteface[6][j+2];
                  orangeface[j+2][4]=whiteface[j+2][0];
                  orangeface[j+2][6]=whiteface[j+2][2];
            }
      }
      if (side == 'y'){
            for (int j = 0 ; j < 4; j++){
                  blueface[4][j+2] = yellowface[0][j+2];
                  blueface[7][j+2] = yellowface[2][j+2];
                  orangeface[j+2][0] = yellowface[j+2][4];
                  orangeface[j+2][2] = yellowface[j+2][6];
                  greenface[0][j+2]= yellowface[4][j+2];
                  greenface[2][j+2]= yellowface[6][j+2];
                  redface[j+2][4]= yellowface[j+2][0];
                  redface[j+2][6]= yellowface[j+2][2];
            }
      }
      if (side == 'o'){
            for (int j = 0 ; j < 4; j++){
                  blueface[4][j+2] = orangeface[0][j+2];
                  blueface[7][j+2] = orangeface[2][j+2];
                  whiteface[j+2][0] = orangeface[j+2][4];
                  whiteface[j+2][2] = orangeface[j+2][6];
                  greenface[0][j+2] = orangeface[4][j+2];
                  greenface[2][j+2] = orangeface[6][j+2];
                  yellowface[j+2][4] = orangeface[j+2][0];
                  yellowface[j+2][6] = orangeface[j+2][2];
            }
      }
      if (side == 'r'){
            for (int j = 0 ; j < 4; j++){
                  blueface[4][j+2] = whiteface[0][j+2];
                  blueface[7][j+2] = whiteface[2][j+2];
                  redface[j+2][0] = whiteface[j+2][4];
                  redface[j+2][2] = whiteface[j+2][6];
                  greenface[0][j+2]=whiteface[4][j+2];
                  greenface[2][j+2]=whiteface[6][j+2];
                  orangeface[j+2][4]=whiteface[j+2][0];
                  orangeface[j+2][6]=whiteface[j+2][2];
            }
      }
      if (side == 'b'){
            for (int j = 0 ; j < 4; j++){
                  blueface[4][j+2] = whiteface[0][j+2];
                  blueface[7][j+2] = whiteface[2][j+2];
                  redface[j+2][0] = whiteface[j+2][4];
                  redface[j+2][2] = whiteface[j+2][6];
                  greenface[0][j+2]=whiteface[4][j+2];
                  greenface[2][j+2]=whiteface[6][j+2];
                  orangeface[j+2][4]=whiteface[j+2][0];
                  orangeface[j+2][6]=whiteface[j+2][2];
            }
      }
      if (side == 'g'){
            for (int j = 0 ; j < 4; j++){
                  blueface[4][j+2] = whiteface[0][j+2];
                  blueface[7][j+2] = whiteface[2][j+2];
                  redface[j+2][0] = whiteface[j+2][4];
                  redface[j+2][2] = whiteface[j+2][6];
                  greenface[0][j+2]=whiteface[4][j+2];
                  greenface[2][j+2]=whiteface[6][j+2];
                  orangeface[j+2][4]=whiteface[j+2][0];
                  orangeface[j+2][6]=whiteface[j+2][2];
            }
      }
      
}

int clockrota(int times , char arr[7][7], int arrresultant[7][7]){
      for (int i = 0 ; i <7 ; i++) {
            for (int j = 0 ; j < 7 ; j++) {
                  arrresultant[i][j] = arr[i][j];}}
      for (int i = 1 ; i <= times ; i++){
            for (int j = 6 ; j >= 0 ; j--){
                  for (int k = 0 ; k < 7 ; k++){
                        arrresultant[k][j] = arr[j][k];}}
            for (int p = 0 ; p <7 ; p++) {
                  int ar2[7];
                  for (int q = 0 ; q < 7 ; q++){
                        ar2[q] = arrresultant[p][6-q];}
                  for (int q = 0 ; q < 7 ; q++){
                        arrresultant[p][q] = ar2[q];}}}}

int main (){
      int arrresultant[7][7];
      clockrota(1 , whiteface ,  arrresultant);
      for (int i = 0 ; i <7 ; i++) {
            for (int j = 0 ; j < 7 ; j++) {
                  printf("%c ", arrresultant[i][j]);
            }
            printf("\n");
      }
    
      return 0;
}

/*

 // w 0  b 1 g 2 y 3 o 4 r 5 

make a rotation function for the side including the extra from the up down 
left right as the whole 2d array rotates , then store the last color side change made , 
then check for the closest colors -> oppposite , in a clockwise pattern 
up right down left back so for each
then start to update the closest - furthest sides's individual 2d arrays
then finally use all sides to update the 3d matrix 

-------
        red  orange
          |   |
w 0  -> b r g o | y
b 1  -> y r w o | g
g 2  -> w r y o | b
-------
      blue green
        |   |
y 3  -> b o g r | w
o 4  -> b w g y | r
r 5  -> b y g w | o

*/
// transformation : 
/*
right R , left L , up U , down D , front F , back B
R1 - face turn 90 degree
R2 - face turn 180 degree
R1' - anti clockwise 90 degree
R2' - anti clockwise 180 degree

M middle vertical slit , E horizontal slit , S the 3rd slit turn 
M1 , E1 , S1-- same logic 
for clockwise , LMR so M is closer to L then same positive rotation as the L 
similarly for E and S  , E - D , S - F 

R M E U ... any with : Rw - Rwide - 2 layers that and the behind one at same time

      b b b 
      b b b
      b b b
o o o w w w r r r y y y
o o o w w w r r r y y y
o o o w w w r r r y y y
      g g g
      g g g
      g g g

F1 ->
      b b b 
      b b b
      o o o 
o o g w w w b r r y y y
o o g w w w b r r y y y
o o g w w w b r r y y y
      r r r
      g g g
      g g g

*/
