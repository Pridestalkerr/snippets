#include <pthread.h>
#include <string.h>
#include <stdio.h>

typedef struct str_pair
{
	char *str;
	char *rev;
}str_pair;

void* revert(void *a)
{
	str_pair *x = (str_pair*) a;

	int i;
	for(i = 0; i < strlen(x->str); ++i)
		x->rev[strlen(x->str) - i - 1] = x->str[i];

	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t thr;
	char rev_str[50]; //char[] can decay to char*, i think...
	str_pair x = {argv[1], rev_str};

	pthread_create(&thr, NULL, revert, &x);
	pthread_join(thr, NULL);

	printf("%s\n", rev_str);

	return 0;
}