#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int					count = 0;
sem_t				semaphore;

int num = 2;

void *threadF1(void *arg)
{
    int i;
    if(num != 0)
    {
        num--;
        sem_wait(&semaphore);
        printf("스레드 1이 화장실을 이용하기 시작합니다.\n");

        // 화장실 이용하는 시간이라 가정
        for(i = 0 ; i < 1000000 ; i++){}

        printf("스레드 1이 화장실 이용을 마쳤습니다.\n");
        num++;
        sem_post(&semaphore);
    }

    else if(num == 0)
    {
        printf("화장실이 꽉 차 스레드 1이 기다리고 있습니다.\n");

        while(num == 0){}

        printf("스레드 1이 화장실 이용을 하고 마쳤습니다.\n");
        num++;
        sem_post(&semaphore);
    }

    return NULL;
}

void *threadF2(void *arg)
{
    int i;
    if(num != 0)
    {
        num--;
        sem_wait(&semaphore);
        printf("스레드 2가 화장실을 이용하기 시작합니다.\n");

        // 화장실 이용하는 시간이라 가정
        for(i = 0 ; i < 1000000 ; i++){}

        printf("스레드 2가 화장실 이용을 마쳤습니다.\n");
        num++;
        sem_post(&semaphore);
    }

    else if(num == 0)
    {
        printf("화장실이 꽉 차 스레드 2가 기다리고 있습니다.\n");
        while(num == 0){}

        printf("스레드 2가 화장실 이용을 하고 마쳤습니다.\n");
        num++;
        sem_post(&semaphore);
    }


    return NULL;
}

void *threadF3(void *arg)
{
    int i;
    if(num != 0)
    {
        num--;
        sem_wait(&semaphore);
        printf("스레드 3이 화장실을 이용하기 시작합니다.\n");

        // 화장실 이용하는 시간이라 가정
        for(i = 0 ; i < 1000000 ; i++){}

        printf("스레드 3이 화장실 이용을 마쳤습니다.\n");
        num++;
        sem_post(&semaphore);
    }

    else if(num == 0)
    {
        printf("화장실이 꽉 차 스레드 3이 기다리고 있습니다.\n");
        while(num == 0){}

        printf("스레드 3이 화장실 이용을 하고 마쳤습니다.\n");
        sem_post(&semaphore);
        num++;
    }


    return NULL;
}

void				fork_test5()
{
	pid_t			pid[3];
	int				idx;
	int				status;

	printf("branch0\n");
	idx = 1;
	while (idx < 3)
	{
		if ((pid[idx] = fork()) == 0)
		{
			printf("branch%d\n", idx);
			if (idx == 1)
				threadF1((void *)NULL);
			else if (idx == 2)
				threadF2((void *)NULL);
			count++;
			exit(0);
		}
		idx++;
	}
	printf("Bye\n");
	waitpid(pid[idx], &status, WCONTINUED);
}

// void				fork_test4()
// {
// 	pid_t			pid[3];

// 	printf("branch0\n");
// 	if ((pid[0] = fork()) == 0)
// 	{
// 		printf("branch1\n");
// 		if ((pid[1] = fork()) == 0)
// 		{
// 			printf("branch2\n");
// 			pid[2] = fork();
// 		}
// 	}
// 	printf("Bye\n");
// 	sleep(2);
// }

// void				fork_test3()
// {
// 	pid_t			pid[3];

// 	printf("branch0\n");
// 	if ((pid[0] = fork()) != 0)
// 	{
// 		printf("branch1\n");
// 		if ((pid[1] = fork()) != 0)
// 		{
// 			printf("branch2\n");
// 			pid[2] = fork();
// 		}
// 	}
// 	printf("Bye\n");
// 	sleep(2);
// }

// void				fork_test2()
// {
// 	printf("branch0\n");
// 	fork();
// 	printf("branch1\n");
// 	fork();
// 	printf("branch2\n");
// 	fork();
// 	printf("Bye\n");
// 	sleep(2);
// }

// void				fork_test1()
// {
// 	printf("branch0\n");
// 	fork();
// 	printf("branch1\n");
// 	fork();
// 	printf("Bye\n");
// 	sleep(2);
// }

int					main(void)
{
	pthread_t thread1, thread2, thread3;


    sem_init(&semaphore, 0, 1); // return :: 0 -> success , others -> fail


    printf("Semaphore test Start!\n");
    // 스레드 조인
	fork_test5();
    printf("모든 스레드가 화장실 이용을 끝냈습니다.\n");

    // 세마포어 객체 소멸
    sem_destroy(&semaphore);
}
