#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 4
#define MAX_NUM 40000000

int arr[MAX_NUM];
int tmp[MAX_NUM];

int check_sorted(int n)
{
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] != i)
            return 0;
    return 1;
}

// Implement your solution here
void merge(int l,int r){
	int m=(l+r)>>1;
	int n1=l,n2=m+1;
	int k=l;
	while(n1<=m && n2<=r){
		if(arr[n1]<=arr[n2])
			tmp[k++] = arr[n1++];
		else
			tmp[k++] = arr[n2++];
	}

	while(n2<=r) tmp[k++]=arr[n2++];
	while(n1<=m) tmp[k++]=arr[n1++];

	for(int i=l;i<=r;i++) arr[i]=tmp[i];
}

void merge_sort(int l, int r){
	if(l >= r) return;
	int m = (l+r)>>1;
	merge_sort(l, m);
	merge_sort(m+1, r);
	merge(l,r);
}


///////////////////////////////

int main(void)
{
    srand((unsigned int)time(NULL));
    const int n = MAX_NUM;
    int i;

    for (i = 0; i < n; i++)
        arr[i] = i;
    for (i = n - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }

    printf("Sorting %d elements...\n", n);

    // Create threads and execute.

		merge_sort(0, MAX_NUM-1);


    //////////////////////////////

    if (!check_sorted(n))
    {
        printf("Sort failed!\n");
        return 0;
    }

    printf("Ok %d elements sorted\n", n);
    return 0;
}
