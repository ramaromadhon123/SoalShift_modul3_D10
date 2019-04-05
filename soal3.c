#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int WakeUp_Status = 0;
int Spirit_Status = 100;
int countbangun = 0;
int counttidur = 0;
int agmal_disable = 0;
int iraj_disable = 0;

void *WakeUp_stun(void *argv)
{
	agmal_disable = 1;
    	sleep(10);
    	agmal_disable = 0;
}

void *Spirit_stun(void *argv)
{
    	iraj_disable = 1;
    	sleep(10);
    	iraj_disable = 0;
}

int main()
{
    	pthread_t tid[2];

    	while(1)
	{
        	char pesan[100];
        	scanf("%[^\n]s", pesan);
        	getchar();

       		if (strcmp(pesan, "All Status") == 0)
		{
            		printf ("Agmal WakeUp_Status = %d\n", WakeUp_Status);
            		printf ("Iraj Spirit_Status = %d\n", Spirit_Status);
            		printf ("\n");
        	}

        	else if (strcmp(pesan, "Agmal Ayo Bangun") == 0 && agmal_disable == 0)
		{
            		WakeUp_Status += 15;
            		countbangun++;

			if (countbangun == 3)
			{
                		countbangun == 0;
                		pthread_create(&(tid[0]), NULL, Spirit_stun, NULL);
            		}

			printf ("Agmal hampir bangun.\n");
        	}

        	else if (strcmp(pesan, "Iraj Ayo Tidur") == 0 && iraj_disable == 0)
		{
            		Spirit_Status -= 20;
           	 	counttidur++;

			if (counttidur == 3)
			{
                		counttidur == 0;
                		pthread_create(&(tid[1]), NULL, WakeUp_stun, NULL);
            		}

			printf ("Iraj hampir tidur.\n");
        	}


		if (agmal_disable == 1)
			printf ("Fitur Agmal Ayo Bangun disabled 10 s.\n");

		if (iraj_disable == 1)
			printf ("Fitur Iraj Ayo Tidur disabled 10 s.\n");

		if (WakeUp_Status >= 100)
		{
			printf ("Agmal terbangun, mereka bangun pagi dan berolahraga.\n");
			break;
        	}

		if (Spirit_Status <= 0)
		{
			printf ("Iraj ikut tidur, dan bangun kesiangan bersama Agmal.\n");
			break;
        	}
    	}
	return 0;
}

