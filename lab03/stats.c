#include <stdio.h>
#include <stdlib.h>

void findStats(int *nums, int numsSize, int *minn, int *maxx, double *avg)
{
    *minn = nums[0];
    *maxx = nums[0];
    int i;
    double sum;
    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] > *maxx)
        {
            *maxx = nums[i];
        }
        if (nums[i] < *minn)
        {
            *minn = nums[i];
        }
        sum += nums[i];
    }
    *avg = sum / numsSize;
}

int main(void)
{
    int n, i, maxi, mini;
    double avg;
    int *nums;

    scanf("%d", &n);
    nums = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        scanf("%d", nums + i);
    findStats(nums, n, &mini, &maxi, &avg);
    printf("%.2f %d %d", avg, maxi, mini);
    return 0;
}