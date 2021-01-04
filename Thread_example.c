#include<stdio.h>
#include <pthread.h>
#include<unistd.h>
void *thread_1(void *p)
{
while(1)
{
	printf("1\n");
	sleep(1);
	}
}
void *thread_2(void *p)
{
while(1)
{
	printf("2\n");
	sleep(1);
	}
}
void main()
{
pthread_t t1,t2;
pthread_create(&t1,0,thread_1,0);
pthread_create(&t2,0,thread_2,0);
pthread_exit(0);
}
