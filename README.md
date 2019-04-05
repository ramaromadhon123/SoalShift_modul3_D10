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
# Soal5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
- Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
- Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
- Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
- Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
- Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
- Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
	- Pembeli (terintegrasi dengan game)
		- Dapat mengecek stok makanan yang ada di toko.
		- Jika stok ada, pembeli dapat membeli makanan.
	- Penjual (terpisah)
		- Bisa mengecek stok makanan yang ada di toko
		- Penjual dapat menambah stok makanan.
	Spesifikasi program:
- Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
- Program terdiri dari 3 scene yaitu standby, battle, dan shop.
- Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan - juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain -itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode
Health : [health status]
Hunger : [hunger status]
Hygiene : [hygiene status]
Food left : [your food stock]
Bath will be ready in [cooldown]s
Choices
Eat
Bath
Battle
Shop
Exit

Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode
Monster’s Health : [health status]
Enemy’s Health : [enemy health status]
Choices
Attack
Run

Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

		Shop Mode
		Shop food stock : [shop food stock]
		Your food stock : [your food stock]
		Choices
Buy
Back

Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop
Food stock : [shop food stock]
Choices
Restock
Exit

Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))</br>

penjelasan soal :</br>
pada soal ini kita diminta untuk membuat program c berupa game dengan syarat yang telah ditentukan seperti disoal</br>

penjelasan jawaban  : </br>
pada program pemain/pembeli kami menggunakan 2 thread untuk display game dan input
```
	iret1 = pthread_create( &thread1, NULL, display, NULL); //membuat thread pertama
    if(iret1) //jika eror
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        exit(EXIT_FAILURE);
    }

	iret2 = pthread_create( &thread2, NULL, inputgame, NULL);//membuat thread kedua
    if(iret2)//jika gagal
    {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        exit(EXIT_FAILURE);
    }
```
- untuk mengurangi hunger_status tiap 10 detik kami menggunaka :
```
if(time_hunger == 10){
			time_hunger = 0;
			hunger_status -= 5;
			if(hunger_status < 1){
				lose = 1;
				printf("game over\n%s mati kelaparan\n", nama_monster);
				
				return 0;
			}
		}
```
- untuk mengurangi hygiene_status tiap 30 detik kami menggunakan :
```
if(time_hygiene == 30){
			time_hygiene = 0;
			hygiene_status -= 10;
			if(hunger_status < 1){
				lose = 1;
				printf("game over\n%s mati membusuk karena tidak pernah mandi\n", nama_monster);
			
				return 0;
			}
		}
```
- untuk menambah health_status tiap 10 detik kami menggunakan :
```
if(time_health == 10){
			time_health = 0;
			if(st == 1){
				health_status += 5;
			}
			if(health_status > 300){health_status = 300;}
		}
```
-agar ketika battle hygiene_status dan hunger_status tidak berkurang maka kami menggunakan :
```
if(ba == 1){
			time_hunger = 0;time_hygiene = 0;time_health = 0;
		}
```
dimana ba merupakan variable yang digunakan untuk menandai battle. ba = 1 ketika sedang scene battle</br>

-untuk menampilkan Stanby mode :
```
	printf("Standby Mode\n");
			printf("Health : %d\n", health_status);
			printf("Hunger : %d\n", hunger_status);
			printf("Hygiene : %d\n", hygiene_status);
			printf("Food left : %d\n", food); 
			if(bath == 0){
				printf("Bath is ready\n");
			}else{
				printf("Bath will be ready in %ds\n",bath);
				bath--;
			}
			printf("Choices\n");
			printf("1. Eat\n");
			printf("2. Bath\n");
			printf("3. Battle\n");
			printf("4. Shop\n");
			printf("5. Exit\n");
```
- program akan berjalan sesuai input :
```
if(input == '1'){
				if(food>0){
					food--;
					hunger_status += 15;
					if(hunger_status > 200){hunger_status = 200;}
				}
			}else if(input == '2'){
				if(bath == 0){
					hygiene_status += 30;
					bath = 20;
					if(hygiene_status > 100){hygiene_status = 100;}
				}
			}else if(input =='3'){
				sh = 0;
				st = 0;
				ba = 1;
				lawan = 100;
			}else if(input == '4'){
				sh = 1;
				st = 0;
				ba = 0;
			}else if(input == '5'){
				keluar =1;
				return 0;
			}
```
- untuk tampilan scene battle dan tugas berdaasarkan input
```
printf("Battle Mode");
			printf("Monster's Health : %d\n", health_status);
			printf("Enemy's Health : %d\n", lawan);
			printf("Choices\n");
			printf("1. Attack\n");
			printf("2. Run\n");
			if(input == '1'){
				health_status -= 20;
				lawan -= 20;
				if(health_status < 1){
					//("game over\n%s mati pada saat tawuran\n", nama_monster);
					sh = 0; st = 1; ba = 0;
					health_status =0 ;
				}
				if(lawan < 1){
					sh = 0; st = 1; ba = 0;
				}
			}else if(input == '2'){
				sh = 0; st = 1; ba = 0;
			}
```
- untuk tampilan scene shop dan tugas berdaasarkan input
```
if(sh == 1){
			printf("Shop Mode\n");
			printf("Shop food stock : %d\n", *food_stock);
			printf("Your food stock : %d\n", food);
			printf("Choices\n");
			printf("1. Buy\n");
			printf("2. Back\n");
			if(input == '1'){
				if(*food_stock > 0){
					food++;
					*food_stock = *food_stock - 1;
				}
			}else if(input == '2'){
				sh = 0; st = 1; ba = 0;
			}
		}
```
- untk shop food stock kami menggunakan shared memory agar dapat di akses pada program penjual juga
```
int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	food_stock = shmat(shmid, NULL, 0);
```
- thread untuk input
```
void *inputgame(void *ptr){
	while(1){
		if(lose || keluar ){break;}
		input = getch();		
	}
}
```
- pada program penjual sama seperti program pembeli/pemain menggunak 2 thread yaitu display dan input
- yang membedakan hanya isi dari thread displaynya yang hanya berisi fitur restock food shoop
```
system("clear");
		printf("Shop\n");
		printf("Food stock : %d\n", *food_stock);
		printf("Choices\n");
		printf("1. Restock\n");
		printf("2. Exit\n");
		if(input == '1'){
			*food_stock = *food_stock + 1;
		}else if(input == '2'){
			keluar =1;
			return 0;
		}
		input = '0';
		sleep(1);
```

