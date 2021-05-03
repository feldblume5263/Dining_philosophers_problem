#include <stdio.h>
#include <unistd.h>

int main( void)
{
	while(1)
	{
		printf( "1초(1백만마이크로초) 마다 문자열 출력\n");
		usleep(1000 * 1000);
		//지정한 마이크로 초 동안 대기 상태가 된다.
		// 1마이크로초는 1백만분의 1초에 해당.
	}
}
