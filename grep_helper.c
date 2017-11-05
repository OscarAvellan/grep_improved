/*
*  Created by Oscar Avellan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "grep_helper.h"

#define COL 101

/*----------------------------------------------------------------------------*/
void print_query(char *pquery)
{
	char *pq;
	printf("S0: query = ");

	for (pq = pquery; pq < pq+COL; pq++)
	{
		if(*pq == '\0')
			break;
		else
			printf("%c", *pq);
	}
	printf("\n---\n");
}

/*----------------------------------------------------------------------------*/
void print_text(char *ptext,int line,int col)
{
	char *pt;

	for (pt = ptext ; pt < pt+COL; pt++)
	{
		if(*pt == '\0'){
			printf("\nS1: line\t%d, bytes = %d\n",line,col);
      break;
    }
		else
			printf("%c", *pt);
	}
}

/*----------------------------------------------------------------------------*/
double log_2(int val)
{
	double result,count;

	count = (double)val;
	result = log(count)/log(2);

	return result;
}

/*----------------------------------------------------------------------------*/


void tolow_text(rank_l *rank, char *ptext)
{
	int j;

	for(j = 0; j < COL; j++)
	{
		if (*ptext == '\0')
		{
			rank->low_text[j] = *ptext;
			break;
		}
		else
		{
			rank->low_text[j] = tolower(*ptext);
			ptext++;
		}
	}
}

/*----------------------------------------------------------------------------*/

void alpha_query(rank_l *rank, char *pquery)
{
	int i;

	for(i = 0; i < COL;i++)
	{
		if (*pquery == '\0')
		{
			rank->alquery[i] = *pquery;
			break;
		}
		else if(isalnum(*pquery))
		{
			rank->alquery[i] = *pquery;
			pquery++;
		}
		else
		{
			pquery++;
			i--;
		}
	}
}

/*----------------------------------------------------------------------------*/

void swap(rank_l *rank, double *score_t, int *line_t, char *ptext, int i)
{
	int tmp_line;
	double tmp_score;
	char tmp[COL];

	tmp_score = rank->score[i];
	tmp_line = rank->line[i];
	strncpy(tmp,rank->A[i],COL);

	rank->score[i] = *score_t;
	rank->line[i] = *line_t;
	strncpy(rank->A[i],ptext,COL);

	*score_t = tmp_score;
	*line_t = tmp_line;
	strncpy(ptext,tmp,COL);
}
