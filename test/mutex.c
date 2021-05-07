#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int					cnt = 0;
pthread_mutex_t		mutex;

void				*count(void *arg)
{
	int				i;
	char*			name = (char*)arg;

	pthread_mutex_lock(&mutex);
	//======== critical section =============
	cnt=0;
	for (i = 0; i < 10; i++)
	{
		printf("%s cnt: %d\n", name,cnt);
		cnt++;
		usleep(1);
	}
	//========= critical section ============
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int					main()
{
	pthread_t		thread1;
	pthread_t		thread2;
	pthread_t		thread3;

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread1, NULL, count, (void *)"thread1");
	pthread_create(&thread2, NULL, count, (void *)"thread2");
	pthread_create(&thread2, NULL, count, (void *)"thread3");


	count((void *)"pm");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_detach(thread1);
	pthread_detach(thread2);
	pthread_detach(thread3);
	pause();
}
