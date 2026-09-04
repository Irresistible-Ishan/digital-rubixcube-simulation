#include <stdio.h>
#include <ctype.h>

#define RESET "\x1B[0m"
#define WHITE "\x1B[47m  "
#define RED "\x1B[41m  "
#define GREEN "\x1B[42m  "
#define ORANGE "\x1B[48;5;208m  "
#define BLUE "\x1B[44m  "
#define YELLOW "\x1B[103m  "

void printColor(int colorCode)
{
    switch (colorCode)
    {
    case 0: printf(WHITE RESET); break;
    case 1: printf(RED RESET); break;
    case 2: printf(GREEN RESET); break;
    case 3: printf(ORANGE RESET); break;
    case 4: printf(BLUE RESET); break;
    case 5: printf(YELLOW RESET); break;
    default: printf("  ");
    }
}

void visualizeCube(int cube[6][9])
{
    printf("\n--- Cube State ---\n");
    // 1. Print TOP Face (Red - Index 1)
    for (int i = 0; i < 3; i++)
    {
        printf("      ");
        for (int j = 0; j < 3; j++)
            printColor(cube[1][i * 3 + j]);
        printf("\n");
    }

    // 2. Print MIDDLE Row (Left, Front, Right, Back)
    for (int i = 0; i < 3; i++)
    {
        // Left Face (Blue - Index 4)
        for (int j = 0; j < 3; j++) printColor(cube[4][i * 3 + j]);
        // Front Face (White - Index 0)
        for (int j = 0; j < 3; j++) printColor(cube[0][i * 3 + j]);
        // Right Face (Green - Index 2)
        for (int j = 0; j < 3; j++) printColor(cube[2][i * 3 + j]);
        // Back Face (Yellow - Index 5)
        for (int j = 0; j < 3; j++) printColor(cube[5][i * 3 + j]);
        printf("\n");
    }

    // 3. Print BOTTOM Face (Orange - Index 3)
    for (int i = 0; i < 3; i++)
    {
        printf("      ");
        for (int j = 0; j < 3; j++)
            printColor(cube[3][i * 3 + j]);
        printf("\n");
    }
    printf("------------------\n");
}

int face(int cube[6][9], int faceIdx, int dir)
{
    int temp;
    if (dir)
    {
        temp = cube[faceIdx][0];
        cube[faceIdx][0] = cube[faceIdx][6];
        cube[faceIdx][6] = cube[faceIdx][8];
        cube[faceIdx][8] = cube[faceIdx][2];
        cube[faceIdx][2] = temp;
        temp = cube[faceIdx][1];
        cube[faceIdx][1] = cube[faceIdx][3];
        cube[faceIdx][3] = cube[faceIdx][7];
        cube[faceIdx][7] = cube[faceIdx][5];
        cube[faceIdx][5] = temp;
    }
    else
    {
        temp = cube[faceIdx][0];
        cube[faceIdx][0] = cube[faceIdx][2];
        cube[faceIdx][2] = cube[faceIdx][8];
        cube[faceIdx][8] = cube[faceIdx][6];
        cube[faceIdx][6] = temp;
        temp = cube[faceIdx][1];
        cube[faceIdx][1] = cube[faceIdx][5];
        cube[faceIdx][5] = cube[faceIdx][7];
        cube[faceIdx][7] = cube[faceIdx][3];
        cube[faceIdx][3] = temp;
    }
    return 0;
}

int simulateCubeMove(int cube[6][9], int input)
{
    if (input == 0) return 0;

    int move;
    int dir;
    
    // Properly map 10-90 to CCW, and 1-9 to CW
    if (input >= 10) {
        move = input / 10;
        dir = 0; 
    } else {
        move = input;
        dir = 1; 
    }

    int temp;

    if (move == 1) /* F */
    {
        if (dir) {
            for (int i = 0; i < 3; i++) {
                temp = cube[1][6 + i];
                cube[1][6 + i] = cube[4][8 - i * 3];
                cube[4][8 - i * 3] = cube[3][2 - i];
                cube[3][2 - i] = cube[2][i * 3];
                cube[2][i * 3] = temp;
            }
        } else {
            for (int i = 0; i < 3; i++) {
                temp = cube[1][6 + i];
                cube[1][6 + i] = cube[2][i * 3];
                cube[2][i * 3] = cube[3][2 - i];
                cube[3][2 - i] = cube[4][8 - i * 3];
                cube[4][8 - i * 3] = temp;
            }
        }
        face(cube, 0, dir);
    }
    else if (move == 2) /* B */
    {
        if (dir) {
            for (int i = 0; i < 3; i++) {
                temp = cube[1][i];
                cube[1][i] = cube[2][8 - i * 3];
                cube[2][8 - i * 3] = cube[3][6 + i];
                cube[3][6 + i] = cube[4][i * 3];
                cube[4][i * 3] = temp;
            }
        } else {
            for (int i = 0; i < 3; i++) {
                temp = cube[1][i];
                cube[1][i] = cube[4][i * 3];
                cube[4][i * 3] = cube[3][6 + i];
                cube[3][6 + i] = cube[2][8 - i * 3];
                cube[2][8 - i * 3] = temp;
            }
        }
        face(cube, 5, dir);
    }
    else if (move == 3) /* L */
    {
        if (dir) {
            for (int i = 0; i < 7; i += 3) {
                temp = cube[0][i];
                cube[0][i] = cube[1][i];
                cube[1][i] = cube[5][i + 2];
                cube[5][i + 2] = cube[3][i];
                cube[3][i] = temp;
            }
        } else {
            for (int i = 0; i < 7; i += 3) {
                temp = cube[0][i];
                cube[0][i] = cube[3][i];
                cube[3][i] = cube[5][i + 2];
                cube[5][i + 2] = cube[1][i];
                cube[1][i] = temp;
            }
        }
        face(cube, 4, dir);
    }
    else if (move == 4) /* R */
    {
        if (dir) {
            for (int i = 2; i < 9; i += 3) {
                temp = cube[0][i];
                cube[0][i] = cube[3][i];
                cube[3][i] = cube[5][i - 2];
                cube[5][i - 2] = cube[1][i];
                cube[1][i] = temp;
            }
        } else {
            for (int i = 2; i < 9; i += 3) {
                temp = cube[0][i];
                cube[0][i] = cube[1][i];
                cube[1][i] = cube[5][i - 2];
                cube[5][i - 2] = cube[3][i];
                cube[3][i] = temp;
            }
        }
        face(cube, 2, dir);
    }
    else if (move == 5) /* U */
    {
        int faces[] = {0, 4, 5, 2};
        int indx[] = {0, 1, 2};
        for (int i = 0; i < 3; i++) {
            temp = dir ? cube[faces[3]][indx[i]] : cube[faces[0]][indx[i]];
            if (dir) {
                cube[faces[3]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = temp;
            } else {
                cube[faces[0]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[3]][indx[i]];
                cube[faces[3]][indx[i]] = temp;
            }
        }
        face(cube, 1, dir);
    }
    else if (move == 6) /* D */
    {
        int faces[] = {0, 2, 5, 4};
        int indx[] = {6, 7, 8};
        for (int i = 0; i < 3; i++) {
            temp = dir ? cube[faces[3]][indx[i]] : cube[faces[0]][indx[i]];
            if (dir) {
                cube[faces[3]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = temp;
            } else {
                cube[faces[0]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[3]][indx[i]];
                cube[faces[3]][indx[i]] = temp;
            }
        }
        face(cube, 3, dir);
    }
    else if (move == 7) /* M (between L and R) */
    {
        // Hardcoding indices prevents out-of-bounds math errors on the Back face
        int idxFUD[] = {1, 4, 7};
        int idxB[]   = {7, 4, 1}; 
        for (int i = 0; i < 3; i++) {
            temp = cube[0][idxFUD[i]];
            if (dir) {
                cube[0][idxFUD[i]] = cube[1][idxFUD[i]];
                cube[1][idxFUD[i]] = cube[5][idxB[i]];
                cube[5][idxB[i]]   = cube[3][idxFUD[i]];
                cube[3][idxFUD[i]] = temp;
            } else {
                cube[0][idxFUD[i]] = cube[3][idxFUD[i]];
                cube[3][idxFUD[i]] = cube[5][idxB[i]];
                cube[5][idxB[i]]   = cube[1][idxFUD[i]];
                cube[1][idxFUD[i]] = temp;
            }
        }
    }
    else if (move == 8) /* E (between U and D) */
    {
        int faces[] = {0, 2, 5, 4}; 
        int idx[] = {3, 4, 5};
        for (int i = 0; i < 3; i++) {
            temp = dir ? cube[faces[3]][idx[i]] : cube[faces[0]][idx[i]];
            if (dir) {
                cube[faces[3]][idx[i]] = cube[faces[2]][idx[i]];
                cube[faces[2]][idx[i]] = cube[faces[1]][idx[i]];
                cube[faces[1]][idx[i]] = cube[faces[0]][idx[i]];
                cube[faces[0]][idx[i]] = temp;
            } else {
                cube[faces[0]][idx[i]] = cube[faces[1]][idx[i]];
                cube[faces[1]][idx[i]] = cube[faces[2]][idx[i]];
                cube[faces[2]][idx[i]] = cube[faces[3]][idx[i]];
                cube[faces[3]][idx[i]] = temp;
            }
        }
    }
    else if (move == 9) /* S (between F and B) */
    {
        int idxU[] = {3, 4, 5};
        int idxL[] = {7, 4, 1};
        int idxD[] = {5, 4, 3};
        int idxR[] = {1, 4, 7};
        for (int i = 0; i < 3; i++) {
            temp = cube[1][idxU[i]];
            if (dir) {
                cube[1][idxU[i]] = cube[4][idxL[i]];
                cube[4][idxL[i]] = cube[3][idxD[i]];
                cube[3][idxD[i]] = cube[2][idxR[i]];
                cube[2][idxR[i]] = temp;
            } else {
                cube[1][idxU[i]] = cube[2][idxR[i]];
                cube[2][idxR[i]] = cube[3][idxD[i]];
                cube[3][idxD[i]] = cube[4][idxL[i]];
                cube[4][idxL[i]] = temp;
            }
        }
    }
    return 0;
}

int main()
{
    int cube[6][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},  // White (Front)
        {1, 1, 1, 1, 1, 1, 1, 1, 1},  // Red (Top)
        {2, 2, 2, 2, 2, 2, 2, 2, 2},  // Green (Right)
        {3, 3, 3, 3, 3, 3, 3, 3, 3},  // Orange (Bottom)
        {4, 4, 4, 4, 4, 4, 4, 4, 4},  // Blue (Left)
        {5, 5, 5, 5, 5, 5, 5, 5, 5}   // Yellow (Back)
    };

    int input;
    visualizeCube(cube);

    printf("Ready! Enter a number (0 to quit)\n");
    while (1)
    {
        printf("> ");
        if (scanf("%d", &input) != 1) break;
        if (input == 0) break;

        simulateCubeMove(cube, input);
        visualizeCube(cube);
    }

    return 0;
}