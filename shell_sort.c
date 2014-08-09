/* File:            shell_sort.c
 * Coder:           FunctionGHW
 * Last Modified:   2014-08-09 11:07:58
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

/*希尔排序*/
void shell_sort(int arr[], int length)
{
    int h = 1, i, j;
    // 计算增量的最大值，不超过数组长度的1/3.
    while (h < length / 3)
    {
        // 这个就是"生成"增量序列的表达式
        h = 3 * h + 1; // 1, 4, 13, 40, 121, 364, 1093...
    }

    while (h >= 1)
    {
        // h-sort the array.
        for (i = h; i < length; i++)
        {
            // 对"子序列"进行插入插排
            for (j = i; j >= h; j -= h)
            {
                if (arr[j] < arr[j - h])
                {
                    int tmp = arr[j];
                    arr[j] = arr[j - h];
                    arr[j - h] = tmp;
                }
            }
        }
        h = h / 3;
    }
}

int main()
{
    const int LEN = 10;
    int i;
    int* arr = (int*)malloc(sizeof(int) * LEN);

    srand(time(NULL));
    for (i = 0; i < LEN; i++)
    {
        arr[i] = rand() % 133;
    }
    printf("is sorted? %d\n", is_sorted(arr, LEN));

    printf("xxxxx ");
    print_arr(arr, LEN);
    time_t start, stop;

    start = clock();
    shell_sort(arr, LEN);
    stop = clock();

    //print_arr(arr, LEN);
    printf("time: %fs\n", (double)(stop - start) / CLOCKS_PER_SEC);
    printf("is sorted? %d\n", is_sorted(arr, LEN));

    return 0;
}
