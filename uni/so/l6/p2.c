#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct m_pair
{
	int m1_l, m2_l, m1_c, m2_c; //m1_c == m2_l
	int **m1;
	int **m2;
}m_pair;

typedef struct m_instance
{
	m_pair *pair;
	int l, c;
}m_instance;

void* prod(void *a)
{
	m_instance *x = (m_instance*) a;

	int n = x->pair->m1_c;
	int *res = (int*) malloc(sizeof(int));
	*res = 0;
	
	int i;
	for(i = 0; i < n; ++i)
		*res += x->pair->m1[x->l][i] * x->pair->m2[i][x->c];

	return res;
}

int main(int argc, char **argv)
{
	//BEWARE, this code is an absolute mess XD

	//testing it against the following, the functions should work just fine for any scenario
	int **m1 = (int**) malloc (3*sizeof(int*));
	int **m2 = (int**) malloc (3*sizeof(int*));
	int k,p;
	for(k = 0; k < 3; ++k)
	{
		m1[k] = (int*) malloc(3*sizeof(int));
		m2[k] = (int*) malloc(3*sizeof(int));
	}

	for(k = 0; k < 3; ++k)
	{
		for(p = 0; p < 3; ++p)
		{
			m1[k][p] = 1;
			m2[k][p] = 2;
		}
	}

	m_pair y = {3, 3, 3, 3, m1, m2};

	pthread_t **thread_pool = (pthread_t**) malloc(y.m1_l * sizeof(pthread_t*));
	int i,j;
	m_instance **inst = (m_instance**) malloc(y.m1_l * sizeof(m_instance*));
	for(i = 0; i < y.m1_l; ++i)
	{	
		thread_pool[i] = (pthread_t*) malloc(y.m2_c * sizeof(pthread_t));
		inst[i] = (m_instance*) malloc(y.m2_c * sizeof(m_instance));
		for(j = 0; j < y.m2_c; ++j)
		{
			inst[i][j].pair = &y;
			inst[i][j].l = i;
			inst[i][j].c = j;
			pthread_create(&thread_pool[i][j], NULL, prod, &(inst[i][j]));
		}
	}

	for(i = 0; i < y.m1_l; ++i)
	{
		for(j = 0; j < y.m2_c; ++j)
		{
			void *curr;
			pthread_join(thread_pool[i][j], &curr);
			printf("%d ", *(int*)curr);
		}
		printf("\n");
	}

	return 0;
}