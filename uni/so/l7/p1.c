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

int decrease_count(int count, pthread_mutex_t *mutex, int *resources)
{
	pthread_mutex_lock(mutex);

	if(*resources < count)
	{
		pthread_mutex_unlock(mutex);
		return -1;
	}
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

int main(int argc, char **argv)
{
	int itr;
	pthread_t thread_pool[5];

	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	int max_resources = 5;
	struct pair data[5] = {{0, &mutex, &max_resources}, {0, &mutex, &max_resources}, {0, &mutex, &max_resources}, {0, &mutex, &max_resources}, {0, &mutex, &max_resources}}; //glob scope so the stack doesnt get re written while a thread is still doing its thing...
	for(itr = 0; itr < 5; ++itr)
	{
		data[itr].count = 1;
		pthread_create(&thread_pool[itr], NULL, instance, &data[itr]);
	}

	for(itr = 0; itr < 5; ++itr)
	{
		pthread_join(thread_pool[itr], NULL);
	}

	pthread_mutex_destroy(&mutex);

	return 0;
}