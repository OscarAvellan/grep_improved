/*
*  Created by Oscar Avellan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define QUERY 100
#define COL 101
#define MAX_LINES 10

typedef struct
{
	double score[MAX_LINES];
	int line[MAX_LINES];
	char A[MAX_LINES][COL];
	char alquery[COL];
	char low_text[COL];
} rank_l;

// Prints query to stdout
void print_query(char *pquery);

void print_text(char *ptext,int line,int col);

// Copies the lower case line to the low_text array in the struct
void tolow_text(rank_l *rank, char *ptext);

// Computes the logarithm base 2
double log_2(int val);

// Copies the alphanumeric query to the struct
void alpha_query(rank_l *rank, char *pquery);

// Swaps the scores, line numbers and strings in the struct
void swap(rank_l *rank, double *score_t, int *line_t, char *ptext, int i);
