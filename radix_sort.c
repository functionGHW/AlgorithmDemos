/* File:            radix_sort.c
 * Author:          functionghw
 * Created Time:    2014-08-16 10:30:10
 * Last Modified:   2014-08-19 23:09:54
 * Description:
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "CLinkedList.h"

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

//输入必须是非负整数???
void radix_sort(int arr[], int length)
{
    const int BOX_SIZE = 16;
    //以16进制表示时，整数的位数
    const int hex_form_len = sizeof(arr[0]) * 2;
    int i, j, node_pool_size = length / 8;
    LinkedList* box[BOX_SIZE];

    for (i = 0; i < BOX_SIZE; i++)
    {
        box[i] = new_lnklst(sizeof(arr[0]), node_pool_size);
    }

    for (i = 0; i < hex_form_len; i++)
    {
        for (j = 0; j < length; j++)
        {
            //取16进制形式的整数的从右边起第i位数
            //例如：0x0FABCD56的第0位是0x6
            //index = (num / 16^(i)) % 16
            int index = (arr[j] >> (i << 2)) & 0x0000000F;
            lnklst_add_last(box[index], (BYTE*)(arr + j));
        }
        int box_i = 0;
        j = 0;
        while (j < length)
        {
            if (lnklst_is_empty(box[box_i]))
            {
                box_i++;
            }
            else
            {
                int* tmp = (int*)lnklst_first_elemt(box[box_i]);
                arr[j++] = *tmp;
                lnklst_remove_first(box[box_i]);
            }
        }
    }
}

int main()
{
    const int LEN = 1000000;
    int* arr = (int*)malloc(sizeof(int) * LEN);
    int i;
    srand(time(NULL));
    for (i = 0; i < LEN; i++)
    {
        arr[i] = rand() % 133;
    }
    printf("sizeof:%d\n", sizeof(LnkLstNode));

    time_t start, stop;

    start = clock();
    radix_sort(arr, LEN);
    stop = clock();

    printf("radix sort time: %fs\n", (double)(stop - start) / CLOCKS_PER_SEC);
    printf("sorted?%d\n", is_sorted(arr, LEN));

    return 0;
}
