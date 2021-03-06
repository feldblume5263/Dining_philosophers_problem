#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 쓰레드 함수
// 5초간 머뭄뒤에 종료
void					*t_function(void *data)
{
	char				a[100000];// 자원 점유!
	static int			num = 0;

	num = *((int *)data);
	printf("Thread Start\n");
	sleep(5);
	printf("Thread end\n");
	return (void*)&num;
}

int						main()
{
	pthread_t			p_thread;
	int					thr_id;
	int					status;
	int					a = 100;

	printf("Before Thread\n");
	thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	// pthread_detach(p_thread); //없이 pause 상태 진입하면?
	// join으로 끝날때까지 기다리지 않아도, detach로 완전히 해제가 가능하다고 한다.
	// 생성된 스레드가 종료된 후에도, 계속 남아있는다. leaks가 생긴다고 함.. 근데 나는 왜 안생기지????

	pause();
	return (0);
}
