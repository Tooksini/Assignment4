#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++){
		 L[i] = arr[l + i];
	}
    for (j = 0; j < n2; j++){
		R[j] = arr[m + 1 + j];
	}
        
    // Merge the temporary arrays back into arr[l..r]
    i = 0; 
    j = 0;  
    k = l;  
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int pData[], int l, int r){
	 if (l < r) {
        // Find the middle point
        int mid = (l + r) / 2;

        // Sort first and second halves
        mergeSort(pData, l, mid);
        mergeSort(pData, mid + 1, r);

        // Merge the sorted halves
        merge(pData, l, mid, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n){
    int i, item, j;
    for (i = 1; i < n; i++){
        item = pData[i];
        for(j = i - 1; j >= 0; j--){
            if(pData[j] > item)
                pData[j + 1] = pData[j];
            else{
                break;
            }
        }
        pData[j+1] = item;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void swap(int *l, int *r){
    int tmp = *l;
    *l = *r;
    *r = tmp;
}

void bubbleSort(int* pData, int n){
	int i, j;
    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - i - 1; j++){
            if(pData[j] > pData[j + 1]){
                swap(&pData[j], &pData[j + 1]);
            }
        }
    }	
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz){
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n){
	int i, j, min_idx, temp;
    
    for (i = 0; i < n - 1; i++){
        printf("\nIteration# %d\n",i+1);
        min_idx = i;
        for (j = i + 1; j < n; j++){
            if (pData[j] < pData[min_idx]){
                min_idx = j;
			}
		}
        temp = pData[i];
        pData[i] = pData[min_idx];
        pData[min_idx] = temp;
        printArray(pData, n);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if(*ppData == NULL){
			fclose(inFile);
			return 0;
		}
		for(int i = 0; i < dataSz; ++i){
			fscanf(inFile, "%d", &(*ppData)[i]);
		}
		fclose(inFile);
	} else{
		return 0;
	}
	return dataSz;
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
}