/* File:            shell_sort.c
 * Coder:           FunctionGHW
 * Last Modified:   2014-08-09 11:39:43
 * 
 */

//
//题目大概是这样的：
//已知两个给定的整数数组，数组长度都是n, 记为x[n], y[n]。 
//两个数组已被排序(升序)，求这2n个整数的中位数。
//
//Link: http://functionghw.is-programmer.com/posts/38839.html

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//========迭代实现相关代码 Begin

/* 比较两个整数[ x and y]大小的函数.
 *   Return values:
 *       1: x > y.
 *       0: x == y.
 *       -1: x < y.
 * */
int compare2(int x, int y)
{
    return (x > y) ? 1 : ( (x == y) ? 0 : -1);
}

//这是个简单的排序函数, 你懂得<^_^>.
void sortFour(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n; ++i)
    {   for (j = i + 1; j < n; ++j)
        {   if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

/* 这个才是主角, 给定两个长度为(maxIndex + 1)的数组x[], y[],
 * 两个数组已被排序(升序). 使用二分的思想求两个数组所有元素的中位数.
 *   因为总元素数为偶数，故中位数由中间的两个数合成。这两个数可能位
 *   于同一个数组里，故每个数组二分时，最后保留两个元素，一共
 *   四个，再排序，取中间两个。
 * */
double findMedian(const int x[], const int y[], int maxIndex)
{
    if (maxIndex < 0)
    {   //老问题，检查一下
        puts("Wrong length of array!");
        exit(-1);
    }
    int Lx, Ly, Rx, Ry, Mx, My;
    Lx = Ly = 0;
    Rx = Ry = maxIndex;

    //当x, y都剩余两个或者一个元素时，停止二分.
    while ( Lx < (Rx - 1) )
    {
        Mx = (Lx + Rx) >> 1;
        /* * * * * * * * * * * * * * * * * * * *
         * 这里有个问题是,当区间长度是偶数时,
         * 比如,8,则Mx = 4，此时这个二分的中
         * 点也可以是5，对y[]也是一样。但是因为
         * 我们是从两边"逼近中间",所以若x是从左
         * 逼近,那么y就是从右边逼近,所以应该My = 5,
         * 而不是4,否则得不到正确的结果.
         * (有点像对称的意思,大概就这样,
         * 现在我还不会证明,见谅<^_^>)
         * * * * * * * * * * * * * * * * * * * */
        if ( ((Ry - Ly + 1) & 1))
        {
            My = (Ly + Ry) >> 1;
        }
        else
        {
            My = (Ly + Ry + 1) >> 1;
        }
        switch( compare2(x[Mx], y[My]) )
        {
            case 0:
                return x[Mx];
            case 1:
                Rx = Mx;
                Ly = My;
                break;
            case -1:
                Lx = Mx;
                Ry = My;
                break;
        }
    }
    //最后的四个数，
    int a[4] = {Lx, Rx, Ly, Ry};
    sortFour(a, 4);//排个序
    //结果用double 存放，保留小数.
    return (double)(a[1] + a[2]) / 2.0;
}

//========迭代实现相关代码 End

//========递归实现相关代码(推荐) Begin

//兼容qsort函数的compare
inline int compare(const void* x, const void* y)
{
    int num_x = *((int*)x);
    int num_y = *((int*)y);
    return (num_x > num_y) ? 1 : ((num_x == num_y) ? 0 : -1);
}

//因为只有4个数, 并且最多调用一次, 所以就直接冒泡了, 简单.
void sort_four_nums(int arr[])
{
    int n = 4,
        i, j, temp;
    for (i = 0; i < n; ++i)
    {   for (j = i + 1; j < n; ++j)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

//这个变量用来计数 搜索的次数;
static int count = 0;

/* 给定两个长度为 n(n > 0) 的数组x[], y[],
 * 两个数组已被排序(升序). 求两个数组共计2n个元素的中位数.
 * 此算法每次递归完成都使问题的规模缩小大约一半，直到找出答案.
 * 因此算法时间复杂度为 O(log n).
 * */
double get_median(const int x[], const int y[], const int n)
{
    if (1 == n)
    {
        count++;
        return (x[0] + y[0]) / 2.0;
    }
    if(2 == n)
    {
        int nums[] = {x[0], x[1], y[0], y[1]};
        sort_four_nums(nums);
        count++;
        return (nums[1] + nums[2]) / 2.0;
    }
    int key_index_x = (n - 1) >> 1;
    int key_index_y = key_index_x;
    if (0 == (n & 1))
    {   
        //n是偶数
        key_index_y++;
    }
    switch ( compare((x + key_index_x), (y + key_index_y)) )
    {
        case 0:
            count++;
            return x[key_index_x];
            break;
        case 1:
            count++;
            return get_median(x, y + key_index_y, n - key_index_y);
            break;
        case -1:
            count++;
            return get_median(x + key_index_x, y, n - key_index_x);
            break;
    }
}

//========递归实现相关代码 End

//Application start.
int main(void)
{
    //数组长度设为一亿, 小内存机器请注意, 两个数组加起来大约要750MB的内存,
    const int LEN = 10000000 - 1;
    int* nums_1 = (int*)malloc(LEN * sizeof(nums_1[0]));
    int* nums_2 = (int*)malloc(LEN * sizeof(nums_2[0]));

    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < LEN; ++i)
    {
        nums_1[i] = rand();
    }
    srand((unsigned int)time(NULL));
    for (i = 0; i < LEN; ++i)
    {
        nums_2[i] = rand();
    }
    //排序, 一亿个数排序就需要大约18s, 请耐心等待.
    qsort((void*)nums_1, LEN, sizeof(nums_1[0]), compare);
    qsort((void*)nums_2, LEN, sizeof(nums_2[0]), compare);

    /*const int LEN = 6;
    int i;
    int nums_1[] = {1,3,5,7,9,11};
    int nums_2[] = {2,4,5,6,8,10};*/
    double result;
    double mid;
    const int ITER = 1000000;
    time_t start_time = clock();
    
    //递归
    result = get_median(nums_1, nums_2, LEN);
    
    //迭代
    mid = findMedian(nums_1, nums_2, LEN -1);
    
    time_t stop_time = clock();

    printf("time used:%f\n", (double)(stop_time - start_time) / CLOCKS_PER_SEC);
    printf("serching count:%d, the middan is:%.2f\n", (count / ITER) , result);
    printf("                      the mid is:%.2f\n", mid);
    //getchar();
    return 0;
}
