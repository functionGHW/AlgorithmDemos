/* File:            heap_sort.c
 * Coder:           FunctionGHW
 * Last Modified:   2014-08-09 11:07:58
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

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


// 用于计算下标为i的节点的两个子节点的下标值
#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * ((i) + 1))

/* 这里有个地方要注意，就是当i=0(根节点)时，结果是0!*/
#define PARENT(i) ((i) - 1) / 2

void print_arr(int arr[], int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%3d, ", arr[i]);
    }
    puts("");
}

void swap_val(int* x, int * y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/* 此函数把一颗二叉树中以node为根的子树变成最大堆。
 * 注意: 使用的前提条件是 node节点的左右子树(如果存在的话)都是最大堆。
 * 这个函数是整个算法的关键。
 */
void max_heapify(int heap[], int heap_size, int node)
{
    // 这里先不考虑整数溢出的问题
    // 先把注意力放在主要的功能上
    // 如果数据规模够大,int类型必然会溢出
    int l_child = LEFT(node);
    int r_child = RIGHT(node);

    int max_value = node;

    if (l_child < heap_size && heap[l_child] > heap[max_value])
    {
        max_value = l_child;
    }
    if (r_child < heap_size && heap[r_child] > heap[max_value])
    {
        max_value = r_child;
    }
    if (max_value != node)
    {
        swap_val(heap + node, heap + max_value);

        // 之后还要保证被交换的子节点构成的子树仍然是最大堆
        // 如果不是这个节点会继续"下沉"到合适的位置
        max_heapify(heap, heap_size, max_value);
    }
}

/* 将一个堆(数组)变成最大堆
 * 自底向上的利用max_heapify函数处理
 */
void build_max_heap(int heap[], int heap_size)
{
    if (heap_size < 2)
    {
        return;
    }
    int first_leaf = heap_size >> 1;//第一个叶子节点的下标

    int i;
    // 从最后一个非叶子节点开始自底向上构建，
    // 叶子节点都看作最大堆，因此可以使用max_heapify函数
    for (i = first_leaf - 1; i >= 0; i--)
    {
        max_heapify(heap, heap_size, i);
    }
}

/* heap sort主函数
 */
void heap_sort(int heap[], int heap_size)
{
    if (heap == NULL || heap_size < 2)
    {
        return;
    }

    //构建最大堆
    build_max_heap(heap, heap_size);

    int i;
    for (i = heap_size - 1; i > 0; i--)
    {
        /* 把当前堆的最大值(heap[0])交换到末尾
         * 相当于取出最大值，堆的规模变小。
         * 交换后的堆不是最大堆，但是根的两颗子树都是最大堆
         * 满足调用max_heapify的要求。
         */
        swap_val(heap, heap + i);

        heap_size--;
        //保持最大堆
        max_heapify(heap, heap_size, 0);
    }
}

int main()
{
    const int LEN = 10000001;
    int i;
    int* arr = (int*)malloc(sizeof(int) * LEN);

    int input_range_start = 0;
    int input_range_end = 1333;

    srand(time(NULL));
    for (i = 0; i < LEN; i++)
    {
        arr[i] = input_range_start + rand() % (input_range_end - input_range_start);
    }

    //printf("is sorted? %d\n", is_sorted(arr, LEN));

    //print_arr(arr, LEN);
    time_t start, stop;

    start = clock();
    heap_sort(arr, LEN);
    stop = clock();

    //print_arr(arr, LEN);
    printf("time: %fs\n", (double)(stop - start) / CLOCKS_PER_SEC);
    printf("is sorted? %d\n", is_sorted(arr, LEN));

    return 0;
}
