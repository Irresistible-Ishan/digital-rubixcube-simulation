#include <stdio.h>
#include <ctype.h>
#include <time.h>

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
    case 0:
        printf(WHITE RESET);
        break;
    case 1:
        printf(RED RESET);
        break;
    case 2:
        printf(GREEN RESET);
        break;
    case 3:
        printf(ORANGE RESET);
        break;
    case 4:
        printf(BLUE RESET);
        break;
    case 5:
        printf(YELLOW RESET);
        break;
    default:
        printf("  ");
    }
}

void visualizeCube(int cube[6][9])
{
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
        for (int j = 0; j < 3; j++)
            printColor(cube[4][i * 3 + j]);

        // Front Face (White - Index 0)
        for (int j = 0; j < 3; j++)
            printColor(cube[0][i * 3 + j]);

        // Right Face (Green - Index 2)
        for (int j = 0; j < 3; j++)
            printColor(cube[2][i * 3 + j]);

        // Back Face (Yellow - Index 5)
        for (int j = 0; j < 3; j++)
            printColor(cube[5][i * 3 + j]);
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
}

int face(int cube[6][9], int face, int dir)
{
    int temp;
    if (dir)
    {
        temp = cube[face][0];
        cube[face][0] = cube[face][6];
        cube[face][6] = cube[face][8];
        cube[face][8] = cube[face][2];
        cube[face][2] = temp;
        temp = cube[face][1];
        cube[face][1] = cube[face][3];
        cube[face][3] = cube[face][7];
        cube[face][7] = cube[face][5];
        cube[face][5] = temp;
    }
    else
    {
        temp = cube[face][0];
        cube[face][0] = cube[face][2];
        cube[face][2] = cube[face][8];
        cube[face][8] = cube[face][6];
        cube[face][6] = temp;
        temp = cube[face][1];
        cube[face][1] = cube[face][5];
        cube[face][5] = cube[face][7];
        cube[face][7] = cube[face][3];
        cube[face][3] = temp;
    }
    return 0;
}


{

    char move;
    int dir;
    int temp;
    move = tolower(command[0]);
    dir = 1;
    if (command[1] == '\'')
    {
        dir = 0;
    }

    if (move == 'r')
    {
        if (dir)
        {
            for (int i = 2; i < 9; i += 3)
            {
                temp = cube[0][i];
                cube[0][i] = cube[3][i];
                cube[3][i] = cube[5][i - 2];
                cube[5][i - 2] = cube[1][i];
                cube[1][i] = temp;
            }
        }
        else
        {
            for (int i = 2; i < 9; i += 3)
            {
                temp = cube[0][i];
                cube[0][i] = cube[1][i];
                cube[1][i] = cube[5][i - 2];
                cube[5][i - 2] = cube[3][i];
                cube[3][i] = temp;
            }
        }
        face(cube, 2, 1);
    }

    else if (move == 'l')
    {
        if (dir)
        {
            for (int i = 0; i < 7; i += 3)
            {
                temp = cube[0][i];
                cube[0][i] = cube[1][i];
                cube[1][i] = cube[5][i + 2];
                cube[5][i + 2] = cube[3][i];
                cube[3][i] = temp;
            }
        }
        else
        {
            for (int i = 0; i < 7; i += 3)
            {
                temp = cube[0][i];
                cube[0][i] = cube[3][i];
                cube[3][i] = cube[5][i + 2];
                cube[5][i + 2] = cube[1][i];
                cube[1][i] = temp;
            }
        }
        face(cube, 2, 1);
    }

    else if (move == 'u')
    {
        int faces[] = {0, 4, 5, 2};
        int indx[] = {0, 1, 2};
        if (dir)
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[faces[3]][indx[i]];
                cube[faces[3]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = temp;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[3]][indx[i]];
                cube[faces[3]][indx[i]] = temp;
            }
        }
        face(cube, 1, dir);
    }

    else if (move == 'd')
    {
        int faces[] = {0, 2, 5, 4};
        int indx[] = {6, 7, 8};
        if (dir)
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[faces[3]][indx[i]];
                cube[faces[3]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = temp;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[3]][indx[i]];
                cube[faces[3]][indx[i]] = temp;
            }
        }
        face(cube, 3, dir);
    }

    else if (move == 'f')
    {
        if (dir)
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[1][6 + i];
                cube[1][6 + i] = cube[4][8 - i * 3];
                cube[4][8 - i * 3] = cube[3][2 - i];
                cube[3][2 - i] = cube[2][i * 3];
                cube[2][i * 3] = temp;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[1][6 + i];
                cube[1][6 + i] = cube[2][i * 3];
                cube[2][i * 3] = cube[3][2 - i];
                cube[3][2 - i] = cube[4][8 - i * 3];
                cube[4][8 - i * 3] = temp;
            }
        }
        face(cube, 0, dir);
    }
    else if (move == 'b')
    {
        if (dir)
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[1][i];
                cube[1][i] = cube[2][8 - i * 3];
                cube[2][8 - i * 3] = cube[3][6 + i];
                cube[3][6 + i] = cube[4][i * 3];
                cube[4][i * 3] = temp;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[1][i];
                cube[1][i] = cube[4][i * 3];
                cube[4][i * 3] = cube[3][6 + i];
                cube[3][6 + i] = cube[2][8 - i * 3];
                cube[2][8 - i * 3] = temp;
            }
        }
        face(cube, 5, dir);
    }

    return 0;

int simulateCubeMove(int cube[6][9], int command)
{
    int move = command % 10;
    int dir = (command >= 10) ? 0 : 1;
    int temp;

    /* ---------- OUTER MOVES (unchanged logic) ---------- */

    if (move == 1) /* F */
    {
        if (dir)
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[1][6 + i];
                cube[1][6 + i] = cube[4][8 - i * 3];
                cube[4][8 - i * 3] = cube[3][2 - i];
                cube[3][2 - i] = cube[2][i * 3];
                cube[2][i * 3] = temp;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
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
        if (dir)
        {
            for (int i = 0; i < 3; i++)
            {
                temp = cube[1][i];
                cube[1][i] = cube[2][8 - i * 3];
                cube[2][8 - i * 3] = cube[3][6 + i];
                cube[3][6 + i] = cube[4][i * 3];
                cube[4][i * 3] = temp;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
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
        if (dir)
        {
            for (int i = 0; i < 7; i += 3)
            {
                temp = cube[0][i];
                cube[0][i] = cube[1][i];
                cube[1][i] = cube[5][i + 2];
                cube[5][i + 2] = cube[3][i];
                cube[3][i] = temp;
            }
        }
        else
        {
            for (int i = 0; i < 7; i += 3)
            {
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
        if (dir)
        {
            for (int i = 2; i < 9; i += 3)
            {
                temp = cube[0][i];
                cube[0][i] = cube[3][i];
                cube[3][i] = cube[5][i - 2];
                cube[5][i - 2] = cube[1][i];
                cube[1][i] = temp;
            }
        }
        else
        {
            for (int i = 2; i < 9; i += 3)
            {
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

        for (int i = 0; i < 3; i++)
        {
            temp = dir ? cube[faces[3]][indx[i]] : cube[faces[0]][indx[i]];

            if (dir)
            {
                cube[faces[3]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = temp;
            }
            else
            {
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

        for (int i = 0; i < 3; i++)
        {
            temp = dir ? cube[faces[3]][indx[i]] : cube[faces[0]][indx[i]];

            if (dir)
            {
                cube[faces[3]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = temp;
            }
            else
            {
                cube[faces[0]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[3]][indx[i]];
                cube[faces[3]][indx[i]] = temp;
            }
        }
        face(cube, 3, dir);
    }

    /* ---------- MIDDLE MOVES ---------- */

    else if (move == 7) /* M (between L and R) */
    {
        for (int i = 1; i < 8; i += 3)
        {
            temp = dir ? cube[0][i] : cube[0][i];

            if (dir)
            {
                cube[0][i] = cube[1][i];
                cube[1][i] = cube[5][i + 2];
                cube[5][i + 2] = cube[3][i];
                cube[3][i] = temp;
            }
            else
            {
                cube[0][i] = cube[3][i];
                cube[3][i] = cube[5][i + 2];
                cube[5][i + 2] = cube[1][i];
                cube[1][i] = temp;
            }
        }
    }

    else if (move == 8) /* E (between U and D) */
    {
        int faces[] = {0, 4, 5, 2};
        int indx[] = {3, 4, 5};

        for (int i = 0; i < 3; i++)
        {
            temp = cube[faces[3]][indx[i]];

            if (dir)
            {
                cube[faces[3]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[0]][indx[i]];
                cube[faces[0]][indx[i]] = temp;
            }
            else
            {
                cube[faces[0]][indx[i]] = cube[faces[1]][indx[i]];
                cube[faces[1]][indx[i]] = cube[faces[2]][indx[i]];
                cube[faces[2]][indx[i]] = cube[faces[3]][indx[i]];
                cube[faces[3]][indx[i]] = temp;
            }
        }
    }

    else if (move == 9) /* S (between F and B) */
    {
        for (int i = 0; i < 3; i++)
        {
            temp = cube[1][3 + i];

            if (dir)
            {
                cube[1][3 + i] = cube[4][7 - i * 3];
                cube[4][7 - i * 3] = cube[3][5 - i];
                cube[3][5 - i] = cube[2][1 + i * 3];
                cube[2][1 + i * 3] = temp;
            }
            else
            {
                cube[1][3 + i] = cube[2][1 + i * 3];
                cube[2][1 + i * 3] = cube[3][5 - i];
                cube[3][5 - i] = cube[4][7 - i * 3];
                cube[4][7 - i * 3] = temp;
            }
        }
    }

    return 0;
}


int main()
{
    int cube[6][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},  // White
                      {1, 1, 1, 1, 1, 1, 1, 1, 1},  // Red
                      {2, 2, 2, 2, 2, 2, 2, 2, 2},  // Green
                      {3, 3, 3, 3, 3, 3, 3, 3, 3},  // Orange
                      {4, 4, 4, 4, 4, 4, 4, 4, 4},  // blue
                      {5, 5, 5, 5, 5, 5, 5, 5, 5}}; // Yellow

    char command[3];
    while (1)
    {
        printf("> ");
        scanf("%s", &command);

        if (command[0] == 'q')
        {
            break;
        }
        simulateCubeMove(cube, command);
        visualizeCube(cube);
    }

    // Benchmarking the solver with a simple algorithm
    // clock_t start = clock();
    // int m = 0;
    // while (m < 100000000)
    // {
    //     simulateCubeMove(cube, "R");
    //     simulateCubeMove(cube, "U");
    //     simulateCubeMove(cube, "R'");
    //     simulateCubeMove(cube, "U'");
    //     m += 4;
    // }

    // clock_t end = clock();
    // double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    // printf("Elapsed time: %.6f seconds\n", elapsed);
    // return 0;
}