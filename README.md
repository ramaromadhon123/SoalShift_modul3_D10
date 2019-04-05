# SoalShift_modul3_D10</br>
# Soal4</br>
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip </br>
Dengan Syarat : </br>
1. Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama</br>
2. Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama</br>
3. Ketika Mengekstrak file .zip juga harus secara bersama-sama</br>
4. Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”</br>
5. Wajib Menggunakan Multithreading</br>
6. Boleh menggunakan system</br>
penjelasan soal: </br>
pada soal ini kita diminta untuk membuat program c yang dapat menyimpan list proses yang sedang berjalan maksimal 10 list proses. lalu list disimpan pada 2 file ekstensi .txt yang telah ditentukan pada direktori yang telah ditentukan juga pada soal. setelah menyimpan list pada file yang telah ditentukan maka kompres zip file tersebut lalu menghapus file ekstensi .txt  setelah itu program akan  memberi pesan yang telah ditentukan dan menunggu selama 15 detik lalu mengekstrak kembali file zip. program juga harus dapat menyimpan list bersamaan, mengkompres bersamaan, mengekstrak bersamaan dan wajib menggunakan Multithreading.</br>
penjelasan jawaban : </br>

-kami menggunakan fork() agar process dapat berjalan diwaktu yang sama.</br>
-untuk menyimpan list kami menggunakan 2 thread
```
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
```
  isi dari thread1 digunakan untuk  SimpanProses1.txt</br>
  ```
  void *get_ps1(void *ptr){
	//printf("1a\n");
	system("ps -aux | tail -10 > /home/ramrom/Documents/FolderProses1/SimpanProses1.txt");
}
  ```
  isi dari thread2 untuk SimpanProses2.txt</br>
  ```
  void *get_ps2(void *ptr){
	//printf("2a\n");
	system("ps -aux | tail -10 > /home/ramrom/Documents/FolderProses2/SimpanProses2.txt");
}
  ```
- lalu untuk kompres juga kami menggunakan 2 thread lalu menggunakan fork() agar kedua thread berjalan bersama
```
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
```
- diman thread pertama untuk mengkompres SimpanProses1.txt</br>
```
 void *kompres1(void *ptr){
	system("zip /home/ramrom/Documents/FolderProses1/KompresProses1 /home/ramrom/Documents/FolderProses1/SimpanProses1.txt");
	system("rm /home/ramrom/Documents/FolderProses1/SimpanProses1.txt");
}
```
- dimana thread kedua untuk mengkompres SimpanProses2.txt</br>
```
void *kompres2(void *ptr){
	system("zip /home/ramrom/Documents/FolderProses2/KompresProses2 /home/ramrom/Documents/FolderProses2/SimpanProses2.txt");
	system("rm /home/ramrom/Documents/FolderProses2/SimpanProses2.txt");
}	
```
- lalu untuk mengekstrak kembali kami menggunakan 2 thread lalu menggunakan fork() agar kedua thread berjalan bersama
```
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
```
- untuk thread pertama untuk mengekstrak zip yg pertama
```
  void *ekstrak1(void *ptr){
	system("unzip -j /home/ramrom/Documents/FolderProses1/KompresProses1.zip -d /home/ramrom/Documents/FolderProses1");
}
```
- untuk thread pertama untuk mengekstrak zip yg pertama
```
void *ekstrak2(void *ptr){
	system("unzip -j /home/ramrom/Documents/FolderProses2/KompresProses2.zip -d /home/ramrom/Documents/FolderProses2");
}
```
