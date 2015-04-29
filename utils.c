/* File:            utils.c
 * Author:          functionghw<functionghw@hotmail.com>
 * Created Time:    2015-04-27 17:40:11
 * Last Modified:   2015-04-27 17:40:11
 * Version:         v1.0
 * Description: declare and implement some helper functions that are in common use.
 *              You should include this file in other source files.
 *
 * */
#ifndef __UTILS_C__
#define __UTILS_C__
#include <stdio.h>
#include <stdlib.h>

// swap two integers by points.
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// check if the given array is sorted with ascending order.
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

// print array in the screen.
void print_arr(int arr[], int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%d, ", arr[i]);
    }
    puts("");
}

// create an array filling random integers,
// each number is between [range_begin, range_end).
int* create_random_array(int length, int range_begin, int range_end)
{
    if (length < 1)
    {
        return NULL;
    }
    if (range_begin > range_end)
    {
        return NULL;
    }
    int mod = range_end - range_begin + 1;
    int i = 0;
    int* arr = malloc(sizeof(int) * length);
    if (arr == NULL)
    {
        return NULL;
    }
    for (i = 0; i < length; i++)
    {
        arr[i] = rand() % mod + range_begin;
    }
    return arr;
}

#endif
