
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>

#define UP 1
#define DOWN 0

#define BUFF_SIZE 9

uint32_t *status;
#if 0 // MJN

void *thread_1(void *k)
{
		uint32_t iter,button, id, semId, *p;
		int  iter1=1, iter2,counter = 0,i,val,doorFlag = 0,floor;
		int direction,j,doorOpen = 0;
		struct sembuf v;

		memset((uint32_t *)status, 0, BUFF_SIZE);

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

		p = shmat(id, 0, 0);

		v.sem_num = 3;
		v.sem_op = 0;
		v.sem_flg = 0;

		while(1)
		{
				semop(semId, &v, 1);
				semctl(semId,2,SETVAL,1);
				printf("rece;%d\n",*p);
				status[*p] = 1;
				*p = 0;
				semctl(semId,3,SETVAL,1);
				semctl(semId,2,SETVAL,0);

		}	
}
#endif


void inititialize(void)
{

		uint32_t id; 
		id = shmget(2, 50, IPC_CREAT|0664);

		if(id < 0)
		{
				perror("shmget");
				exit(0);
		}
		status = shmat(id, 0, 0);

}

void *thread_2(void *p)
{
		int iter=8, iter1=1, iter2,counter = 0,i,val,doorFlag = 0,floor;
		int direction,j,doorOpen = 0;
		while(1)
		{
				for(j=1;j<9;j++)
				{
						if(status[j] == 1)
						{
								floor = j;
								if(floor>counter)
								{
										direction = UP;
								}
								else
								{
										direction = DOWN;
								}
								if(direction == UP)
								{
										while(counter < floor)
										{
												counter++;
												system("clear");
												printf("\t------------------\n");
												for(iter1 = 8 ; iter1 > 0 ; iter1-- )
												{
														if(counter != iter1)
														{
																for(iter2 = 0 ; iter2 < 5 ; iter2++)
																		printf("\t|               |\n");
														}
														else if(counter == floor)
														{
																status[j] = 0;
																printf("\t|    -------    |\n");
																printf("\t|    |           \n");
																printf("\t|    |  %d        \n",iter1);
																printf("\t|    |           \n");
																printf("\t|    -------    |\n");
																doorOpen = 1;
														}
														else
														{
																printf("\t|    -------    |\n");
																printf("\t|    |     |    |\n");
																printf("\t|    |  %d  |    |\n",iter1);
																printf("\t|    |     |    |\n");
																printf("\t|    -------    |\n");
														}
												}
												printf("\t------------------\n");
												if(doorOpen)
												{
														sleep(5);
														doorOpen=0;
												}
												sleep(1);
										}
								}
								else if(direction == DOWN)
								{
										while(counter > floor)
										{
												counter--;
												system("clear");
												printf("\t------------------\n");
												for(iter1 = 8 ; iter1 > 0 ; iter1-- )
												{
														if(counter != iter1)
														{
																for(iter2 = 0 ; iter2 < 5 ; iter2++)
																		printf("\t|               |\n");
														}
														else if(counter == floor)
														{
																status[j] = 0;
																printf("\t|    -------    |\n");
																printf("\t|    |           \n");
																printf("\t|    |  %d        \n",iter1);
																printf("\t|    |           \n");
																printf("\t|    -------    |\n");
																doorOpen = 1;
														}
														else
														{
																printf("\t|    -------    |\n");
																printf("\t|    |     |    |\n");
																printf("\t|    |  %d  |    |\n",iter1);
																printf("\t|    |     |    |\n");
																printf("\t|    -------    |\n");
														}
												}
												printf("\t------------------\n");
												if(doorOpen)
												{
														sleep(5);
														doorOpen=0;
												}
												sleep(1);
										}
								}
						}
				}
		}
}
int32_t main()
{
pthread_t t1,t2;
//pthread_create(&t1,0,thread_1,0);
inititialize();
pthread_create(&t2,0,thread_2,0);
pthread_exit(0);
}
