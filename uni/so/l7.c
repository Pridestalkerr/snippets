#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct pair
{
	int count;
	pthread_mutex_t *mutex;
	int *available;
}pair;

/*void* decrease_count(void *data)
{
	int count = ((pair*) data)->count;
	pthread_mutex_t *mutex = ((pair*) data)->mutex;
	int *available = ((pair*) data)->available;

	pthread_mutex_lock(mutex);



	pthread_mutex_unlock(mutex);
}*/

int decrease_count(int count, pthread_mutex_t *mutex, int *resources)
{
	pthread_mutex_lock(mutex);

	if(*resources < count)
		return -1;
	else
		*resources -= count;

	pthread_mutex_unlock(mutex);

	return 0;
}

int increase_count(int count, pthread_mutex_t *mutex, int *resources)
{
	pthread_mutex_lock(mutex);

	*resources += count;

	pthread_mutex_unlock(mutex);

	return 0;
}

void *instance(void *data)
{
	int count = ((pair*) data)->count;
	pthread_mutex_t *mutex = ((pair*) data)->mutex;
	int *available = ((pair*) data)->available;

	if(decrease_count(count, mutex, available) != -1)
		printf("-%d\n", count);

	increase_count(count, mutex, available);
	printf("%d\n", count);

	return NULL;
}

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
	pthread_mutex_unlock(mut);

	if(*count == 0)
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
	int itr;
	/*pthread_t thread_pool[5];

	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	int max_resources = 5;
	struct pair data[5] = {{0, &mutex, &max_resources}, {0, &mutex, &max_resources}, {0, &mutex, &max_resources}, {0, &mutex, &max_resources}, {0, &mutex, &max_resources}}; //glob scope so the stack doesnt get re written while a thread is still doing its thing...
	for(itr = 0; itr < 5; ++itr)
	{
		data[itr].count = itr;
		pthread_create(&thread_pool[itr], NULL, instance, &data[itr]);
	}

	for(itr = 0; itr < 5; ++itr)
	{
		pthread_join(thread_pool[itr], NULL);
	}

	pthread_mutex_destroy(&mutex);*/


	//2

	sem_t sem;
	sem_init(&sem, 0, 0);
	int total = 5;
	pthread_mutex_t mut;
	pthread_mutex_init(&mut, NULL);

	pthread_t thread_pool_s[5];
	struct pair_s data_s[5] = {{&sem, &mut, 0, &total}, {&sem, &mut, 0, &total}, {&sem, &mut, 0, &total}, {&sem, &mut, 0, &total}, {&sem, &mut, 0, &total}};
	for(itr = 0; itr < 5; ++itr)
	{
		data_s[itr].id = itr;
		pthread_create(&thread_pool_s[itr], NULL, tfun, &data_s[itr]);
	}

	for(itr = 0; itr < 5; ++itr)
	{
		pthread_join(thread_pool_s[itr], NULL);
	}

	return 0;
}