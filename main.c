#include <stdio.h>
#include <stdlib.h>


typedef struct{
	char c1, c2;
	int r1, r2;
}move;


int main()
{
    char table[8][8];
    char linie[8];

    int col, row, dc, dr;

    init(table);

    //print(table);

    char* fen=calloc(128, sizeof(int));

    encode(table, fen);

    fen="rnbqkbnr/pp1pppp1/8/8/8/7b/PPPPPPPP/RNBQKBNR";
    int k=0;
    while(fen[k])
    {
        printf("%c", fen[k]);
        ++k;
    }
    printf("\n");
    decode(table, fen);
    print(table);

    char tomove;
    scanf("%c", &tomove);

    move* mutare=all_moves(table,  tomove);

    int i=0;
    while(mutare[i].r1)
    {
        print_move(mutare[i]);
        if(mutare[i].r1!=mutare[i+1].r1 || mutare[i].c1!=mutare[i+1].c1)
            printf("\n");
        ++i;
    }
    printf("00-00\n");

    free(mutare);
    free(fen);

    return 0;
}
///fen="7q/8/8/8/8/8/8/P7";
///fen="7q/2p5/3p4/4p3/5p2/6p1/7p/P7";
///fen="8/8/8/3QK3/8/8/8/8";
///fen="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
///fen="rnbqkbnr/pp1pppp1/8/8/8/7b/PPPPPPPP/RNBQKBNR";
