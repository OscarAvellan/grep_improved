#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "grep_helper.h"
#include "grep_ranking.h"

#define DEBUG 0

void compare(char *pquery, char *ptext, int line)
{
	double max_score = 0.0, score = 0.0;
	char *pt,*pt2,*pq;

	for (pt = ptext ; pt < pt+COL; pt++)
	{
		pt2 = pt;
		if (*pt != '\0')
		{
			for (pq = pquery; pq < pq+QUERY; pq++)
			{
				if ((*pq == '\0') || (*pt2 == '\0'))
				{
					break;
				}
				else if (*pq == *pt2)
				{
					score++;
					pt2++;
				}
				else
				{
					if (score > max_score)
					{
						max_score = score;
					}
					score = 0.0;
				}
			}
		}
		else
		{
			break;
		}
	}
	printf("S2: line\t%d, score = %.3f\n",line,max_score);

}

//------------------------------------------------------------------------------

void ranked_summary(rank_l *rank,double score_t, int line_t,char *ptext)
{
	int i;

	for (i = 0; i < MAX_LINES;i++)
	{
		if (score_t > rank->score[i])
		{
			if (rank->score[i] == 0.0)
			{
				rank->score[i] = score_t;
				rank->line[i] = line_t;
				strncpy(rank->A[i],ptext,COL);
				break;
			}
			else
			{
				swap(rank,&score_t,&line_t,ptext,i);
			}
		}
		else if (score_t == rank->score[i])
		{
			if (line_t < rank->line[i])
			{
				swap(rank,&score_t,&line_t,ptext,i);
			}
		}
	}
}

//------------------------------------------------------------------------------

double better_ranking(rank_l *rank,int line)
{
	int index_q, index_t, char_cmp = 1,count = 0,lenght_q, lenght_q2, lenght_t;
	double score = 0.0, i = 0.0, j = i + 2.0, result=0.0, x1;

	#if DEBUG
	int sp = 1,lin = 1,k;
	#endif

	lenght_q = strlen(rank->alquery);
	lenght_t = strlen(rank->low_text);
	lenght_q2 = lenght_q;

	#if DEBUG
	printf("DB:  ");
	for (k = 0; k <= lenght_q ; k++)
	{
		printf("%c  ",rank->alquery[k]);
	}
	printf("\n");
	#endif

	/*Starts the alphanumeric query stored in the struct*/
	for (index_q = 0; index_q < lenght_q2; index_q++)
	{
		#if DEBUG
		printf("DB:  ");
		while(sp < lin)
		{
			printf("   ");
			sp += 1;
		}
		sp=1;
		lin+=1;
		#endif

		/*Checks that the # of characters used in strncmp is less or equal to
											the lenght of the query*/
		while(char_cmp <= lenght_q)
		{
			if(index_t >= lenght_t)
			{
				/*Computes the score when i = # of row, and j = i + 2 */
				if (char_cmp >= 3)
				{
					if (count != 0)
					{
						x1 = j - i - 1.0;
						score = score + ((pow(x1,2))*(log_2(2 + count)));
						j += 1.0;
					}
					else
					{
						j += 1.0;
					}
				}
				index_t = 0;
				char_cmp += 1;

				#if DEBUG
				printf("%d  ",count);
				#endif

				count = 0;
			}
			else if(strncmp(&rank->alquery[index_q],&rank->low_text[index_t]
															,char_cmp) == 0)
			{
				count += 1;
				index_t += 1;
			}
			else
			{
				index_t += 1;
			}
		}
		lenght_q = lenght_q - 1;
		char_cmp = 1;
		i += 1.0;
		j = i + 2.0;
		count = 0;

		#if DEBUG
		printf("\n");
		#endif
	}

	result = score / log_2(30 + lenght_t);
	printf("S4: line\t%d, score = %.3f\n",line,result);
	printf("---\n");

	return result;
}
