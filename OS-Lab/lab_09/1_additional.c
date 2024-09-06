// Write a C program to implement dynamic storage allocation strategy for worst fit using dynamic allocations for all the required data structures.

#include <stdio.h>
#include <stdlib.h>

void worst_fit(int *block_size, int m, int *process_size, int n)
{
    int allocation[n];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int worst_index = -1;
        for (int j = 0; j < m; j++)
        {
            if (block_size[j] >= process_size[i])
            {
                if (worst_index == -1)
                {
                    worst_index = j;
                }
                else if (block_size[worst_index] < block_size[j])
                {
                    worst_index = j;
                }
            }
        }

        if (worst_index != -1)
        {
            allocation[i] = worst_index;
            block_size[worst_index] -= process_size[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, process_size[i]);
        if (allocation[i] != -1)
        {
            printf("%d\n", allocation[i] + 1);
        }
        else
        {
            printf("Not Allocated\n");
        }
    }
}

int main()
{
    int m, n;
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    int *block_size = (int *)malloc(m * sizeof(int));
    printf("Enter the block sizes: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &block_size[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int *process_size = (int *)malloc(n * sizeof(int));
    printf("Enter the process sizes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &process_size[i]);
    }

    worst_fit(block_size, m, process_size, n);

    free(block_size);
    free(process_size);
    return 0;
}