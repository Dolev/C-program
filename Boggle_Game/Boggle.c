/**(boggle)
* Program:
finding all words that can be created from given matrix.
* Rules:
1. if the char[][] used u cant use use it again
2. you can go only : up , down , left , right.
*/


#include<stdio.h>
#include<string.h>
#include<stdbool.h>

//define 
bool isWord(char *s);
void printWords(char mat[4][4], int i, int j, char word[], bool checker[4][4]);
void shortenByOne(char* s);
void append(char* s, char c);
void check(char mat[4][4]);


#define MATRIX_SIZE 4;

/*void Print_Mat(char mat[4][4]) {
for (int i = 0; i < 4; i++)
{
for (int j = 0; j < 4; j++)
{
printf("%c ", mat[i][j]);
}
printf("\n");
}
}
*/


int counter()
{
	static int counter = 0;
	counter++;
	return counter;
}

// function to add character to array (represent string)
void append(char* s, char c)
{
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
}


// Taking down the '\0' after recursion.
void shortenByOne(char* s)
{
	int len = strlen(s);
	if (len == 0) return;
	s[len - 1] = '\0';
}

//1.I added the word - start
//2.I added the word - mat
//3.I added the word - tramp
//4.and delete the word - cars (this word is  not exist)

// Given funtion - checking if it vaild word.
bool isWord(char* s) {
	return (!strcmp(s, "CAT") |
		!strcmp(s, "CATS") |
		!strcmp(s, "TRAM") |
		!strcmp(s, "TRAMS") |
		!strcmp(s, "TRAMP") |//3.
		!strcmp(s, "TAME") |
		!strcmp(s, "CAR") |
		//4.
		!strcmp(s, "RAT") |
		!strcmp(s, "RATS") |
		!strcmp(s, "RAMP") |
		!strcmp(s, "ART") |
		!strcmp(s, "CART") |
		!strcmp(s, "STAMP") |
		!strcmp(s, "TAKEN") |
		!strcmp(s, "MEN") |
		!strcmp(s, "MAKE") |
		!strcmp(s, "TAKE") |
		!strcmp(s, "ATE") |
		!strcmp(s, "SELL") |
		!strcmp(s, "STEEL") |
		!strcmp(s, "RAKE") |
		!strcmp(s, "START") |//1.
		!strcmp(s, "MAT"));//2.
}

void printWords(char mat[4][4], int i, int j, char word[], bool checker[4][4])
{
	if (i >= 0 && i<4 && j >= 0 && j < 4)
	{
		if (!checker[i][j])
		{
			checker[i][j] = true; // mark as seen.
			append(word, mat[i][j]); // adding letter
			if (isWord(word)) // checking if its vaild word
			{
				printf("Found word: %s\n", word);
				count();
			}
			// Continuting with recursion.     
			printWords(mat, i + 1, j, word, checker);
			printWords(mat, i, j + 1, word, checker);
			printWords(mat, i, j - 1, word, checker);
			printWords(mat, i - 1, j, word, checker);
			checker[i][j] = false; // clear path for other paths
			shortenByOne(word);
		}

	}
}
// Starting function. every letter has been checked here.
void check(char mat[4][4]) {
	int i, j;
	int counter = 0;
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			char str[12] = "";
			//append(str, mat[i][j]);
			bool checker[4][4] = { { false } };
			//printf("mat[%d][%d]: %s\n", i, j, str);
			printWords(mat, i, j, str, checker);
			counter++;
			fflush(stdout);
		}
	}
}
//main
int main() {

	char matrix[4][4] = { { 'C','A','R','T' },
	{ 'E','T','A','K' },
	{ 'E','S','M','E' },
	{ 'L','L','P','N' } };
	check(matrix);
	printf("There are: %d words\n", count() - 5); // Minus 5 because of duplicates.


	getch();

	return 0;
}
