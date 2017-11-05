/*
		Created By Oscar Avellan, 20/09/2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "grep_helper.h"
#include "grep_ranking.h"

#define MAX_LENGTH 99

int main(int argc, char *argv[])
{
	char c,text[COL];
	int col,line = 1,i;
	double score;
	rank_l rank1 = { {0.0},{0},{{'\0'}},{'\0'},{'\0'} };

	if(argc != 2){
		printf("Not enough arguments\n");
		printf("Bye Bye...\n");
		exit(0);
	}

	print_query(&argv[1][0]);
	alpha_query(&rank1,&argv[1][0]);

	// Reads and copies the file into an array
	for (col = 0; col < COL; col++)
	{
		if ( (c = getchar()) == EOF )	{
			break;
		}
		else if ((c == '\n') || (col > MAX_LENGTH)) {
			text[col] = '\0';
			print_text(text,line,col);
			tolow_text(&rank1,text);
			compare(&argv[1][0],text,line);
			score = better_ranking(&rank1,line);
			ranked_summary(&rank1,score,line,text);

			line++;
			col = -1;
		}
		else {
			text[col] = c;
		}
	}

	printf("-------------------------------------------------\n");

	/*Prints the lines in the struct from the ones with the highest score
	      								to the ones with the lowest score*/
	for (i = 0; i < MAX_LINES;i++)
	{
		if (rank1.line[i] != 0)
		{
			printf("S3: line\t%d, score = %.3f\n",rank1.line[i],rank1.score[i]);
			printf("%s\n---\n",rank1.A[i]);
		}
		else
		{
			break;
		}
	}

	printf("\n");

    return 0;
}
