#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>

#define BUFF_SIZE 9
uint32_t button,*status;
void *thread_1(void *k)
{
		uint32_t iter, id, semId;
		//uint8_t status[BUFF_SIZE];
		struct sembuf v;


		semId = semget(7,5,IPC_CREAT|0664);
		id = shmget(2, 50, IPC_CREAT|0664);

		if(id < 0)
		{
				perror("shmget");
				exit(0);
		}
		if(semId < 0)
		{
				perror("Semaphore");
				exit(0);
		}

		status = shmat(id, 0, 0);
		memset(status, 0, BUFF_SIZE);

		v.sem_num = 2;
		v.sem_op = 0;
		v.sem_flg = 0;

		while(1)
		{
				system("clear");
				for(iter = 1 ; iter < 9 ; iter ++)
				{
						if(iter == 1)
						{
								printf("\n\t------------------------------------------\n");
								printf("\t|               LIFT PANNEL              |\n");
								printf("\t|                                        |\n");
								printf("\t|    ---------------  ---------------    |\n");
						}
						if( (status[iter] == 1) && ( (iter%2) == 1) ) 
						{
								printf("\t|    |             |  |             |    |\n");
								printf("\t|    |      %d \u263A    |  ",iter);
						}
						else if( (status[iter] == 1) && ( (iter%2) == 0) ) 
						{
								printf("|      %d \u263A    |    |\n",iter);
								printf("\t|    |             |  |             |    |\n");
								printf("\t|    ---------------  ---------------    |\n");
						}
						else if( (iter%2) == 1 ) 
						{
								printf("\t|    |             |  |             |    |\n");
								printf("\t|    |      %d      |  ",iter);
						}
						else if( (iter%2) == 0 ) 
						{
								printf("|      %d      |    |\n",iter);
								printf("\t|    |             |  |             |    |\n");
								printf("\t|    ---------------  ---------------    |\n");
						}
						if(iter == 8)
						{
								printf("\t|                                        |\n");
								printf("\t------------------------------------------\n");
						}
				}
						sleep(1);

#if 0 //MJN
				semop(semId, &v, 1);
				semctl(semId,3,SETVAL,1);

#endif
				//	*p = button;

#if 0 //MJN
				semctl(semId,2,SETVAL,1);
				semctl(semId,3,SETVAL,0);
#endif
		}
}
void *thread_2(void *k)
{
		while(1)
		{
				scanf("%d",&button);
				status[button] = 1;
		}
}

int32_t main()
{
pthread_t t1,t2;
pthread_create(&t1,0,thread_1,0);
pthread_create(&t1,0,thread_2,0);
pthread_exit(0);
}
