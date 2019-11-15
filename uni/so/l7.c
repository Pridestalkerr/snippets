#include <pthread.h>
#include <stdio.h>

typedef struct pair
{
	int count;
	pthread_mutex_t *mutex;
	int *available;
}pair;

void* decrease_count(void *data)
{
	int count = ((pair*) data)->count;
	pthread_mutex_t *mutex = ((pair*) data)->mutex;
	int *available = ((pair*) data)->available;

	//this breaks it for some reason
	pthread_mutex_lock(mutex);



	pthread_mutex_unlock(mutex);

	
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
		data[itr].count = itr;
		pthread_create(&thread_pool[itr], NULL, decrease_count, &data[itr]);
	}

	for(itr = 0; itr < 5; ++itr)
	{
		pthread_join(thread_pool[itr], NULL);
	}

	pthread_mutex_destroy(&mutex);	
	return 0;
}