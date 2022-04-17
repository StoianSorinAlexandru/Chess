#include <stdio.h>
#include "sah.h"

void init(char table[][8])
{

    ///completam linia 7 cu pioni negri
    for(int i=0; i<8; ++i)
        table[6][i]='p';

    ///completam linia 2 cu pioni albi
    for(int i=0; i<8; ++i)
        table[1][i]='P';

    ///atribuim caraterul R pt turele albe
    table[0][0]=table[0][7]='R';

    ///atribuim caraterul r pt turele negre
    table[7][0]=table[7][7]='r';


    ///atribuim caraterul N pt caii albi
    table[0][1]=table[0][6]='N';


    ///atribuim caraterul n pt caii negri
    table[7][1]=table[7][6]='n';


    ///atribuim caraterul B pt nebunii albi
    table[0][2]=table[0][5]='B';


    ///atribuim caraterul b pt nebunii negri
    table[7][2]=table[7][5]='b';

    ///regina si regele alb
    table[0][3]='Q';
    table[0][4]='K';

    ///regina si regele negru
    table[7][3]='q';
    table[7][4]='k';


    ///completam tabla cu zone goale cu caracterele ' '
    for(int i=2; i<6; ++i)
        for(int j=0; j<8; ++j)
            table[i][j]=' ';

}

void print(char table[][8])
{

    ///afisarea coordonata coloana: a b c d e f g h de la inceputul tablei
    printf("  ");
    for(int i=0; i<8; ++i)
        printf("%c ", i+'a');
    printf("\n");


    for(int i=7; i>=0; --i)
    {

        printf("%d ", i+1);///afisam cifra corespunsazatoare coordonatei liniei

        for(int j=0; j<8; ++j)
            printf("%c ", table[i][j]);///afisam caraterul de pe pozitia i+1, j+1

        printf("%d\n", i+1);///afisam cifra corespunsazatoare coordonatei liniei + caracterul \n pt separarea liniilor
    }

    ///afisarea coordonata coloana: a b c d e f g h de la sfarsitul tablei
    printf("  ");
    for(int i=0; i<8; ++i)
        printf("%c ", i+'a');

    printf("\n\n");
}

int getline(char table[][8], char col, int row, int dc, int dr, char line[])
{

    int x, y;

    ///initializam linia si coloana pentru matricea indexata de la 0 si 0 pana la 7 7

    x=col-'a';
    y=row-1;

    int ok=1, nr=0;

    if(dc!=0 || dr!=0)
    {
        ///daca se poate executa parcurgerea matricei
        while(ok)
        {
            ///parcurgem pana cand ajungem la capetele matricei inclusiv
            x+=dr;
            y+=dc;
            line[nr++]=table[x][y];
            if(x<0 || 7<x)///conditia de oprire se atinge cand linia depaseste
                ok=0;
            if(y<0 || 7<y)///conditia de oprire se atinge cand coloana depaseste
                ok=0;
        }
        --nr;
    }
    else
        return 0;
    ///EXISTA CAZUL CAND dc=0 si dr=0 astfel programul returneaza 0


    return nr;
}

void encode(char table[][8], char* fen)
{
    int k, nr=0;
    for(int i=7; i>=0; --i)
    {
        for(int j=0; j<8; ++j)
        {
            while(j<8)
            {
                if(table[i][j] == ' ')
                {
                    k=0;
                    while(j<8 && table[i][j]==32)
                    {
                        ++j;
                        ++k;
                    }
                    fen[nr]=k+'0';
                    ++nr;
                }
                if(j<8 && table[i][j] != ' ')
                {
                    fen[nr]=table[i][j];
                    ++nr;
                    ++j;
                }

            }

        }
        if(i!=0){
            fen[nr]='/';
            ++nr;
        }
    }

}

void decode(char table[][8], char* fen)
{
    int i=7, j=0,
    k=0, c;
    while(fen[k]){
        if(fen[k]=='/')
        {
            ++k;
            --i;
            j=0;
        }
        if('1' <= fen[k] && fen[k] <= '8')
        {
            c=fen[k]-'0';
            for(int pas=0; pas<c; ++pas)
            {
                table[i][j]=' ';
                ++j;
            }
            ++k;
        }
        if('a'<= fen[k] && fen[k] <= 'z')
        {
            table[i][j]=fen[k];
            ++k;
            ++j;
        }
        if('A'<= fen[k] && fen[k] <= 'Z')
        {
            table[i][j]=fen[k];
            ++k;
            ++j;
        }
    }
}

int isupper(char x)
{
    if('A'<=x && x<='Z')
        return 1;
    return 0;
}

int islower(char x)
{
    if('a'<=x && x<='z')
        return 1;
    return 0;
}

void print_move(move x)
{
    printf("%c%d-%c%d ",x.c1,x.r1,x.c2,x.r2);
}
int colide(char table[][8], int p1, int p2, int x, int y, int cul)
{
    if(-1<x && x<8 && -1<y && y<8)
    {

        if(cul)
        {
            if(islower(table[x][y]))
                return 1;
        }
        else
        {
            if(isupper(table[x][y]))
                return 1;
        }
    }
    return 0;
}

int add_move_line(int n, char table[][8], move* a, int p1, int p2, int cul)
{
    int x, y;
    x=p1+1;
    while(x<8 && table[x][p2]==' ')///SUS
    {
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=p2+'a';
        ++n;
        ++x;
    }

    if(colide(table, p1, p2, x, p2, cul)){
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=p2+'a';
        ++n;
    }
    x=p1-1;
    while(x>-1 && table[x][p2]==' ')///JOS
    {
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=p2+'a';
        ++n;
        --x;
    }

    if(colide(table, p1, p2, x, p2, cul)){
                a[n].r1=p1+1;
                a[n].c1=p2+'a';
                a[n].r2=x+1;
                a[n].c2=p2+'a';
                ++n;
    }
    y=p2+1;
    while(y<8 && table[p1][y]==' ')///DREAPTA
    {
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=p1+1;
        a[n].c2=y+'a';
        ++n;
        ++y;
    }

    if(colide(table, p1, p2, p1, y, cul)){
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=p1+1;
        a[n].c2=y+'a';
        ++n;
    }
    y=p2-1;
    while(y>-1 && table[p1][y]==' ')///STANGA
    {
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=p1+1;
        a[n].c2=y+'a';
        ++n;
        --y;
    }

    if(colide(table, p1, p2, p1, y, cul)){
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=p1+1;
        a[n].c2=y+'a';
        ++n;
    }
    return n;
}


int add_move_diag(int n, char table[][8], move* a, int p1, int p2, int cul)
{
    int x, y;
    x=p1+1;
    y=p2+1;
    while(x<8 && y<8 && table[x][y]==' ')///DREAPTA-SUS
    {
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=y+'a';
        ++n;
        ++x;
        ++y;
    }
    if(colide(table, p1, p2, x, y, cul)){
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=y+'a';
        ++n;
    }
    x=p1+1;
    y=p2-1;
    while(x<8 && y>-1 && table[x][y]==' ')///STANGA-SUS
    {
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=y+'a';
        ++n;
        ++x;
        --y;
    }
    if(colide(table, p1, p2, x, y, cul)){
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=p2+'a';
        ++n;
    }
    x=p1-1;
    y=p2+1;
    while(x>-1 && y<8 && table[x][y]==' ')///DREAPTA-JOS
    {
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=y+'a';
        ++n;
        --x;
        ++y;
    }
    if(colide(table, p1, p2, x, y, cul)){
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=y+'a';
        ++n;
    }
    x=p1-1;
    y=p2-1;
    while(x>-1 && y>-1 && table[x][y]==' ')///STANGA-JOS
    {
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=y+'a';
        ++n;
        --x;
        --y;
    }

    if(colide(table, p1, p2, x, y, cul)){
        a[n].r1=p1+1;
        a[n].c1=p2+'a';
        a[n].r2=x+1;
        a[n].c2=y+'a';
        ++n;
    }

    return n;
}

move* all_moves(char table[][8], char tomove)
{
    int number_moves=0;
    move* a=calloc(256, sizeof(move));

    ///ALBE
    if(tomove=='w')
    {
        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<8; ++j)
            {
                if(table[i][j]=='Q' || table[i][j]=='R')
                {
                    number_moves=add_move_line(number_moves, table, a, i , j, 1);
                }
                if(table[i][j]=='Q' || table[i][j]=='B')
                {
                    number_moves=add_move_diag(number_moves, table, a, i , j, 1);
                }
            }
        }
    }

    ///NEGRE
    if(tomove=='b')
    {
        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<8; ++j)
            {
                if(table[i][j]=='q' || table[i][j]=='r')
                {
                    number_moves=add_move_line(number_moves, table, a, i , j, 0);
                }
                if(table[i][j]=='q' || table[i][j]=='b')
                {
                    number_moves=add_move_diag(number_moves, table, a, i , j, 0);
                }
            }
        }
    }

    return a;
}
