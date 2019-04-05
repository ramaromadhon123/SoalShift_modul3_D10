#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

long long int hasil[1000];

void sort_swap (int *min1, int *min2)
{
	int temp = *min1;
	*min1 = *min2;
	*min2  = temp;
}

void selectionsort(int a[], int n)
{
	int i, j, minimum;
	for (i = 1; i < n-1; i++)
	{
		minimum = i;

        	for (j = i+1; j < n; j++)
          		if (a[j] < a[minimum])
            			minimum = j;

		sort_swap(&a[minimum], &a[i]);
	}
}

void* faktorial (void* n)
{
	int* a;
	a = (int*) n;
	int i, num =  *a;
	long long temp = 1;

	for(i = 1; i <= num; i++)
	{
		temp = temp * i;
	}

	hasil[num] = temp;
}

int main(int argc, char *argv[])
{
	int panjang = argc-1;
	int arr[panjang];
	int n;

	pthread_t tid[panjang];

	for(n = 1; n <= panjang; n++)
    	{
		arr[n] = atoi (argv[n]); 
	}

    	for(n = 1; n <= panjang; n++)
    	{
        	pthread_create(&(tid[n]), NULL, &faktorial, &arr[n]);
	}

    	for(n = 1; n <= panjang; n++)
	{
		pthread_join(tid[n],NULL);
	}

	selectionsort(arr, argc);

	for(n = 1; n <= panjang; n++)
	{
		printf("%d! = %lld\n", arr[n], hasil[arr[n]]);
	}
}
