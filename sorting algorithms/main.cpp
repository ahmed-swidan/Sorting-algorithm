#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <string.h>
using namespace std;

bool isHeap = false;
void merge_arrays(int *arr, int *left, int *right, int n)
{
    int i,j,index;
    for(i = 0, j = 0, index = 0; i < n/2 && j < n-n/2;)
    {
        arr[index++] = left[i] < right[j] ? left[i++] : right[j++];
    }

    while(i < n/2)
        arr[index++] = left[i++];
    while(j < n-n/2)
        arr[index++] = right[j++];
}

void MergeSort(int *arr, int n)
{
    if(n == 1)
        return;

    int left[n/2], right[n-n/2];

    for(int i = 0; i < n/2; i++)
        left[i] = arr[i];

    for(int i = n/2; i < n; i++)
        right[i-n/2] = arr[i];

    MergeSort(left,n/2);
    MergeSort(right,n-n/2);

    merge_arrays(arr,left,right,n);
}

int partition(int *arr, int start, int end)
{
    int pivot = start + rand()%(end-start+1);
    int i = start - 1;

    swap(arr[end], arr[pivot]);
    pivot = end;

    for(int j = start; j <= end; ++j)
    {
        if(arr[j] < arr[pivot])
            swap(arr[++i], arr[j]);
    }
    swap(arr[i+1], arr[pivot]);

    return i+1;
}

void QuickSort(int *arr, int start, int end)
{
    if(start < end)
    {
        int pivot = partition(arr, start, end);
        QuickSort(arr, start, pivot - 1);
        QuickSort(arr, pivot + 1, end);
    }
}

void SelectionSort(int a[], int n)
{
    for(int i = 0; i < n-1; i++)
    {
        int smallest = i;
        for(int j = i+1; j < n; j++)
        {
            if(a[j] < a[smallest])
                smallest = j;
        }
        swap(a[i], a[smallest]);
    }

}

void InsertionSort(int a[], int n)
{
    int temp, j;
    for(int i = 1; i < n ; i++)
    {
        temp = a[i];
        for (j = i; j > 0 && temp < a[j-1]; j--)
        {
            a[j] = a[j-1];
        }
        a[j] = temp;
    }
}

void BubbleSort(int a[], int n)
{
    bool sorted;
    for(int i = 0; i < n-1 && !sorted; i++)
    {
        sorted = true;
        for(int j = 0; j < n-i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                swap(a[j], a[j+1]);
                sorted = false;
            }
        }
    }
}

void max_heapify(int *arr, int i, int n)
{
    int parent = i;
    int left_child = 2*i;
    int right_child = 2*i + 1;

    int largest = parent;

    if(left_child < n && arr[left_child] > arr[parent])
        largest = left_child;
    if(right_child < n && arr[right_child] > arr[largest])
        largest = right_child;

    if(largest != parent)
    {
        swap(arr[parent], arr[largest]);
        max_heapify(arr, largest, n);
    }
}

void build_max_heap(int *arr, int n)
{
    for(int i = n/2; i >= 1; --i)
        max_heapify(arr,i,n);
}

void HeapSortR(int *arr, int n)
{
    build_max_heap(arr,n);
    for(int i = n - 1; i >= 1; --i)
    {
        swap(arr[1], arr[i]);
        max_heapify(arr,1,i);
    }
}

void HeapSortI(int a[], int n)
{
    bool swapDone = false;
    int heapIndex;
    for(int i = 1; i < n ; i++)
    {
        heapIndex = i+1;
        while(heapIndex != 1)
        {
            if(a[(heapIndex-1)] > a[(heapIndex/2)-1])
            {
                swap(a[(heapIndex-1)], a[(heapIndex/2)-1]);
                heapIndex = heapIndex/2;
            }
            else
                heapIndex = 1;
        }
    }

    while(n > 1)
    {
        heapIndex = 1;
        swap(a[0], a[n-1]);
        n--;
        while(heapIndex <= (n/2))
        {
            swapDone = false;
            int biggestChild = heapIndex;
            if(a[2*heapIndex-1] > a[heapIndex-1] && 2*heapIndex <= n)
            {
                biggestChild = 2*heapIndex;
                swapDone = true;
            }
            if(a[2*heapIndex] > a[biggestChild - 1] && 2*heapIndex+1 <= n)
            {
                biggestChild = 2*heapIndex+1;
                swapDone = true;
            }
            if(swapDone == false)
                break;
            swap(a[heapIndex-1], a[biggestChild-1]);
            heapIndex = biggestChild;
        }

    }

}

int* readFile(char* fileName, int *n, int mode)
{

    FILE *f = fopen(fileName, "r");

    int dummy;
    while(!feof(f))
    {
        fscanf(f,"%d\n", &dummy);
        ++(*n);
    }
    rewind(f);

    *n = mode == 5 ? *n+1 : *n; // for heapR
    int *arr = (int*)malloc(sizeof(int)*(*n));

    int i = mode == 5 ? 1: 0; // for heapR
    while(!feof(f))
    {
        fscanf(f, "%d\n", &arr[i++]);
    }
    fclose(f);

    return arr;
}

int* sortFile(char* filename, int* numberOfElements, int sortingMode){

    int *arr = readFile(filename, numberOfElements, sortingMode);
    int n = *numberOfElements;
    clock_t start, finish;
    start = clock();

        switch(sortingMode)
    {
    case 1:
        BubbleSort(arr, n);
        break;
    case 2:
        InsertionSort(arr, n);
        break;
    case 3:
        SelectionSort(arr, n);
        break;
    case 4:
        HeapSortI(arr, n);
        break;
    case 5:
        HeapSortR(arr, n);
        isHeap = true;
        break;
    case 6:
        MergeSort(arr, n);
        break;
    case 7:
        QuickSort(arr, 0, n-1);
        break;
    }
    finish = clock();

    double time_taken = ((double) (finish - start)) / CLOCKS_PER_SEC;

    printf("Running time for %s is %f\n", sortingMode > 3 ? "O(n log n)" : "O(n^2)", time_taken);

    return arr;

}
bool isIdentical(int *arr1, int *arr2, int n1, int n2)
{
    if(isHeap){
        if(n1 - 1 != n2)
        return false;

    for(int i = 0, j= 1; j < n1; ++i, ++j)
    {
        if (arr1[j] != arr2[i]){
            return false;}
    }
    return true;
    }

    if(n1 != n2)
        return false;
    for(int i = 0; i < n2; ++i)
    {
        if (arr1[i] != arr2[i]){
            return false;}
    }
    return true;
}
int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Usage: %s filename1 filename2\n", argv[0]);
        exit(1);
    }

    int mode1, mode2;

    do
    {
        cout << "Choose which sort to perform on file1(1-heapI, 2-heapR, 3-merge 4-quick):\n";
        cin >> mode1;
    }
    while(mode1 > 4 || mode1 < 0);

     do
    {
        cout << "Choose which sort to perform on file2(1-bubble, 2-insertion, 3-selection):\n";
        cin >> mode2;
    }
    while(mode2 > 3 || mode2 < 0);

    int n1 = 0, n2 = 0;
    int *arr1 = sortFile(argv[1], &n1, mode1 + 3);
    int *arr2 = sortFile(argv[2], &n2, mode2);


    printf("Files are %s", isIdentical(arr1, arr2, n1, n2)? "identical" : "not identical");
    return 0;
}
