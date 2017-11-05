#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Checks the longest pattern in each of the text lines and computes the score
void compare(char *pquery, char *ptext,int line);

// Gets the score of the line and checks in the struct if the score is greater
//				than the score of the other lines or if there is no score yet
void ranked_summary(rank_l *rank,double score_t, int line_t,char *ptext);

// Computes the more sofisticated scoring computation
double better_ranking(rank_l *rank,int line);
