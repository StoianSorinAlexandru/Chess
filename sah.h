#ifndef SAH_H_INCLUDED
#define SAH_H_INCLUDED

typedef struct{
	char c1, c2;
	int r1, r2;
}move;


///1) functia de initializare a tablei de sah
void init(char table[][8]);

///2) functia de afisare a tablei de sah
void print(char table[][8]);

///3) functia ce executa parcurgerea table si returneaza numarul de patrate parcurse
int getline(char table[][8], char col, int row, int dc, int dr, char line[]);

///4) functia codifica tabla sub forma ceruta
void encode(char table[][8], char* fen);

///5) functia decodeaza tabla
void decode(char table[][8], char* fen);

///6)
move* all_moves(char table[][8], char tomove);

#endif // SAH_H_INCLUDED
