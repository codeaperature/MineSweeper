//
//  https://www.codeeval.com/open_challenges/79/
//  minesweeper
//
//  Created by Stephan Warren on 12/10/14.
//  Copyright (c) 2014 Arxan. All rights reserved.
//


/* 
 CHALLENGE DESCRIPTION:

You will be given an M*N matrix. Each item in this matrix is either a '*' or a '.'.
A '*' indicates a mine whereas a '.' does not. The objective of the challenge is to
output a M*N matrix where each element contains a number (except the positions which
                                                          actually contain a mine which will remain as '*') which indicates the number of
mines adjacent to it. Notice that each position has at most 8 adjacent positions
e.g. left, top left, top, top right, right, ...

INPUT SAMPLE:

Your program should accept as its first argument a path to a filename. Each line in this
file contains M,N, a semicolon and the M*N matrix in row major form. E.g.

3,5;**.........*...
4,4;*........*......
OUTPUT SAMPLE:

Print out the new M*N matrix (in row major form) with each position(except the ones with the mines) indicating how many adjacent mines are there. E.g.

**100332001*100
*10022101*101110


*/
/*
 test data in matrix form
 
in #1 (3,5):
**...
.....
.*...

out #1:
**100
33200
1*100
 
in #2 (4,4):
*...
....
.*..
....

 out #2:
*100
2210
1*10
1110
 
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    FILE *file = fopen(argv[1], "r");
    
    char line[1024];
//    char * ptr;
    char out;
    unsigned char * uptr;
    unsigned char n, m, r, c;
    unsigned short i;
    
    typedef struct { char r; char c; } neighbors_t;
    const neighbors_t delta[8] = {
        { -1,  -1}, // top left
        {  0,  -1},
        {  1,  -1},
        { -1,   0},
//      {  0,   0},
        {  1,   0},
        { -1,   1},
        {  0,   1},
        {  1,   1}  // bottom right
    };
    
    while (fgets(line, 1024, file)) {
        // get the row & col dims
        i = 0;
        n = m = 0;
        while(line[i] != ',') {
            n = 10 * n + line[i++] - '0';
        }
//        *(ptr = line + i++) = '\0';
//        n = atoi(line);
        i++;
        while(line[i] != ';') {
            m = m * 10 + line[i++] - '0';
        }
//        m = atoi(ptr+1);
//        printf("rows = %d, cols = %d\n", (int) n, (int) m);
        i++;
        
        uptr = (unsigned char *) &line[i];
        unsigned char ** matrix = (unsigned char**) malloc((n + 2) * sizeof(unsigned char*));
        for(r = 0; r < n + 2; r++) {
            matrix[r] = (unsigned char *) malloc((m + 2) * sizeof(char));
            if((r != 0) && (r != (n + 1))) {
                matrix[r][0] = matrix[r][m+1] = (unsigned char) '.';
                for(c = 1; c <= m; c++) {
                    matrix[r][c] = *(uptr++);
                }
            }
            else {
                for(c = 0; c < m + 2; c++) {
                    matrix[r][c] = matrix[r][n+1] = (unsigned char) '.';
                }
            }
        }
/*
        // print in matrix
        printf("   0123456789\n");
        for(r = 0; r < n + 2; r++) {
            printf("%d: ", (int) r);
            for(c = 0; c < m + 2; c++) {
                printf("%c%s", (char) matrix[r][c], ((c != (m + 1)) ? "":"\n"));
            }
        }

        // print out matrix
        printf("   0123456789\n");
        for(r = 1; r <= n ; r++) {
            printf("%d: ", (int) r);
            for(c = 1; c <= m; c++) {
                if(matrix[r][c] == (unsigned char) '*') {
                    printf("%c%s", '*', (c != m) ? "":"\n");
                }
                else {
                    char cnt = '0';
                    for(i = 0; i < 8; i++) {
                        if(matrix[((char) r) + delta[i].r]
                                 [((char) c) + delta[i].c] == (unsigned char) '*') cnt++;
                    }
                    printf("%c%s", (char) cnt, ((c != m)) ? "":"\n");
                }
            }
        }
*/
        for(r = 1; r <= n ; r++) {
            for(c = 1; c <= m; c++) {
                if(matrix[r][c] == (unsigned char) '*') {
                    out = '*';
                }
                else {
                    out = '0';
                    for(i = 0; i < 8; i++) {
                        if(matrix[((char) r) + delta[i].r]
                           [((char) c) + delta[i].c] == (unsigned char) '*') out++;
                    }
                }
                putchar(out);
            }
        }
        putchar('\n');
        
        for(r = 0; r < n + 2; r++)
            free(matrix[r]);
        free(matrix);
        
        
    }
    return 0;
}