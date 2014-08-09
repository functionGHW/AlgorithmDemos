/* File:            bucket_sort.c
 * Coder:           FunctionGHW
 * Last Modified:   2014-08-09 12:31:04
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_sorted(int arr[], int length)
{
    int i;
    for (i = 1; i < length; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return 0;
        }
    }
    return 1;
}

void print_arr(int arr[], int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%3d, ", arr[i]);
    }
    puts("");
}

/*
 * range of every value in array: [range_start, range_end)
 */
void bucket_sort(int arr[], int length, int range_start, int range_end)
{
    if (range_end < range_start)
    {
        return;
    }
    int i;
    int buckets_size = range_end - range_start;
    int* buckets = (int*)malloc(sizeof(int) * buckets_size);

    //Initialize buckets
    for (i = 0; i < buckets_size; i++)
    {
        buckets[i] = 0;
    }

    // push all value into buckets, O(n)
    for (i = 0; i < length; i++)
    {
        //index = value - range_start
        buckets[arr[i] - range_start] += 1;
    }

    // pop the value back to the array in order, O(n)
    int j = 0;
    for (i = 0; i < buckets_size; i++)
    {
        while (buckets[i] > 0)
        {
            //value = index + range_start
            arr[j] = i + range_start;
            j++;
            buckets[i]--;
        }
    }

    free(buckets);
}

int main()
{
    const int LEN = 100000;
    int i;
    int* arr = (int*)malloc(sizeof(int) * LEN);
    int input_range_start = 0;
    int input_range_end = 1333;

    srand(time(NULL));
    for (i = 0; i < LEN; i++)
    {
        arr[i] = input_range_start + rand() % (input_range_end - input_range_start);
    }
    time_t start, stop;

    start = clock();
    bucket_sort(arr, LEN, input_range_start, input_range_end);
    stop = clock();

    printf("bucket sort time: %fs\n", (double)(stop - start) / CLOCKS_PER_SEC);
    printf("is sorted? %d\n", is_sorted(arr, LEN));

    return 0;
}
