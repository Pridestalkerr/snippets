#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct pair_s
{
	sem_t *sem;
	pthread_mutex_t *mut;
	int id;
	int *count;
}pair_s;

void barrier_point(sem_t *sem, pthread_mutex_t *mut, int *count)
{
	pthread_mutex_lock(mut);
	(*count)--;
	int tmp = *count; //use a temp variable for the upcoming check
	pthread_mutex_unlock(mut);

	if(tmp == 0)
	{
		int itr;
		for(itr = 0; itr < 4; ++itr)
		{
			sem_post(sem);
		}
	}
	else
		sem_wait(sem);
}

void *tfun(void *data)
{
	printf("%d reached barrier\n", ((pair_s*)data)->id);
	barrier_point(((pair_s*)data)->sem, ((pair_s*)data)->mut, ((pair_s*)data)->count);
	printf("%d passed barrier\n", ((pair_s*)data)->id);

	return NULL;
}

int main(int argc, char **argv)
{
	sem_t sem;
	sem_init(&sem, 0, 0);
	int total = 5;
	pthread_mutex_t mut;
	pthread_mutex_init(&mut, NULL);

	pthread_t thread_pool_s[5];
	struct pair_s data_s[5] = {{&sem, &mut, 0, &total}, {&sem, &mut, 0, &total}, {&sem, &mut, 0, &total}, {&sem, &mut, 0, &total}, {&sem, &mut, 0, &total}};

	int itr;
	for(itr = 0; itr < 5; ++itr)
	{
		data_s[itr].id = itr;
		pthread_create(&thread_pool_s[itr], NULL, tfun, &data_s[itr]);
	}

	for(itr = 0; itr < 5; ++itr)
	{
		pthread_join(thread_pool_s[itr], NULL);
	}

	sem_destroy(&sem);
	pthread_mutex_destroy(&mut);

	return 0;
}