#include <stdio.h>
//Define :
#define MAX_ROW 6
#define MAX_COLUMN 7
#define Space ' '
#define STACK_MAX 42 // 7*6 

int Push(int data);
int Pop();
int Peek();
int Isfull() ;
int Isempty() ;
void Print_Board(char board[MAX_ROW][MAX_COLUMN]);
int Row(char board[MAX_ROW][MAX_COLUMN],char User [] ,int player);
int Column(char board[MAX_ROW][MAX_COLUMN],char User [] ,int player);
int Trace1(char board[MAX_ROW][MAX_COLUMN],char User [] ,int player);
int Trace2(char board[MAX_ROW][MAX_COLUMN],char User [] ,int player);
int Full_Column(char board[MAX_ROW][MAX_COLUMN],int n);
void add(char board[MAX_ROW][MAX_COLUMN],int col,char[] ,int place);
void del(char board[MAX_ROW][MAX_COLUMN]);
