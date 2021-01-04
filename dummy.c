#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define UP 1
#define DOWN 0
void main(void)
{
		int iter=8, iter1=1, iter2, status[10] = {1,0,0,1,0,0,1,0,0,0} ,counter = 0,i,val,doorFlag = 0,floor;
		int direction,j,doorOpen = 0;
		while(1)
		{
				for(j=1;j<9;j++)
				{
						if(status[j]==1)
						{
								//status[j] = 0;
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

