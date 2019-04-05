#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <pthread.h>
#include <sys/types.h>

void *get_ps1(void *ptr){
	//printf("1a\n");
	system("ps -aux | tail -10 > /home/ramrom/Documents/FolderProses1/SimpanProses1.txt");
}

void *get_ps2(void *ptr){
	//printf("2a\n");
	system("ps -aux | tail -10 > /home/ramrom/Documents/FolderProses2/SimpanProses2.txt");
}

void *kompres1(void *ptr){
	system("zip /home/ramrom/Documents/FolderProses1/KompresProses1 /home/ramrom/Documents/FolderProses1/SimpanProses1.txt");
	system("rm /home/ramrom/Documents/FolderProses1/SimpanProses1.txt");
}

void *kompres2(void *ptr){
	system("zip /home/ramrom/Documents/FolderProses2/KompresProses2 /home/ramrom/Documents/FolderProses2/SimpanProses2.txt");
	system("rm /home/ramrom/Documents/FolderProses2/SimpanProses2.txt");
}	

void *ekstrak1(void *ptr){
	system("unzip -j /home/ramrom/Documents/FolderProses1/KompresProses1.zip -d /home/ramrom/Documents/FolderProses1");
}

void *ekstrak2(void *ptr){
	system("unzip -j /home/ramrom/Documents/FolderProses2/KompresProses2.zip -d /home/ramrom/Documents/FolderProses2");
}
	

int main(){
	system("mkdir /home/ramrom/Documents/FolderProses1");
	system("mkdir /home/ramrom/Documents/FolderProses2");
	system("touch /home/ramrom/Documents/FolderProses1/SimpanProses1.txt");
	system("touch /home/ramrom/Documents/FolderProses2/SimpanProses2.txt");
	pthread_t thread1, thread2;
	int iret1, iret2, input;
	pid_t c;

	printf("ketik ""1"" untuk menyalin data ps -aux\n"); 
	scanf("%d", &input);
	while(input != 1){
		scanf("%d", &input);
	}

	c = fork();

	if (c < 0) {
	    exit(EXIT_FAILURE);
  	}	

	if(c == 0){
		iret1 = pthread_create(&thread1, NULL, get_ps1, NULL);
		if(iret1)//jika gagal
		{
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread1, NULL);
		//printf("a");
		return 0;
	}else{
		iret2 = pthread_create(&thread2, NULL, get_ps2, NULL);
		if(iret2)//jika gagal
		{
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread2, NULL);
		//printf("b");
	}
	printf("menyalin data telah selesai\n");	

	printf("ketik ""1"" untuk kompres\n"); 
	while(scanf("%d", &input) != 1);	

	c = fork();

	if (c < 0) {
	    exit(EXIT_FAILURE);
  	}	

	if(c == 0){
		iret1 = pthread_create(&thread1, NULL, kompres1, NULL);
		if(iret1)//jika gagal
		{
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread1, NULL);
		//printf("a");
		return 0;
	}else{
		iret2 = pthread_create(&thread2, NULL, kompres2, NULL);
		if(iret2)//jika gagal
		{
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread2, NULL);
		//printf("b");
	}
	printf("kompres file simpanproses dan hapus file simpanproses telah selesai\n");
	printf("Menunggu 15 detik untuk mengekstrak kembali\n");
	sleep(15);

	c = fork();

	if (c < 0) {
	    exit(EXIT_FAILURE);
  	}	

	if(c == 0){
		iret1 = pthread_create(&thread1, NULL, ekstrak1, NULL);
		if(iret1)//jika gagal
		{
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread1, NULL);
		//printf("a");
		return 0;
	}else{
		iret2 = pthread_create(&thread2, NULL, ekstrak2, NULL);
		if(iret2)//jika gagal
		{
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
			exit(EXIT_FAILURE);
		}
		pthread_join(thread2, NULL);
		//printf("b");
	}	
	printf("ekstrak telah selesai\n");

	return 0;
}
