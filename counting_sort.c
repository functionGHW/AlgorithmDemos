/* File:            counting_sort.c
 * Coder:           FunctionGHW
 * Last Modified:   2014-08-09 13:29:17
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
 * 计数排序实现
 * 此算法的时间复杂度虽然是O(n)，但是有不小的空间开销
 * 空间复杂度为O(n) + O(range_size)
 * */
void counting_sort(int arr[], int length, int range_start, int range_end)
{
    int range_size = range_end - range_start;
    int i;
    int* counting_arr = (int*)malloc(sizeof(int) * range_size);
    int* sorted_arr = (int*)malloc(sizeof(int) * length);

    //Initialize
    for (i = 0; i < range_size; i++)
    {
        counting_arr[i] = 0;
    }

    //counting
    for (i = 0; i < length; i++)
    {
        //index = value - range_start
        counting_arr[arr[i] - range_start]++;
    }

    // 累加过程，
    // 最终的结果为:
    // (用b[]表示累加后的结果，a[]表示累加前的计数)：
    // b[0] = a[0]
    // b[1] = a[1] + a[0]
    // ...
    // b[i] = a[i] + a[i - 1] + a[i - 2] + ... + a[0]
    // (可以确定 b[i_max] == arr.length)
    for (i = 1; i < range_size; i++)
    {
        //最终, counting_arr的index对应元素的值，
        //而value对应这个元素在最终数组中的位置(从1开始)
        counting_arr[i] += counting_arr[i - 1];
        //printf(" >>b[%d] : %d\n", i, counting_arr[i]);
    }
    //最后的过程就变成了:根据元素查表，放置到正确的位置
    for (i = length - 1; i >= 0; i--)
    {
        //position = counting_arr[element]
        //index = position - 1
        sorted_arr[counting_arr[arr[i]] - 1] = arr[i];
        counting_arr[arr[i]]--;
    }

    //copy back to origin array
    for (i = 0; i < length; i++)
    {
        arr[i] = sorted_arr[i];
    }

    free(counting_arr);
    free(sorted_arr);
}

int main()
{
    const int LEN = 100000000;
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

    //print_arr(arr, LEN);
    start = clock();
    counting_sort(arr, LEN, input_range_start, input_range_end);
    stop = clock();

    printf("bucket sort time: %fs\n", (double)(stop - start) / CLOCKS_PER_SEC);
    printf("is sorted? %d\n", is_sorted(arr, LEN));
    //print_arr(arr, LEN);

    return 0;
}
