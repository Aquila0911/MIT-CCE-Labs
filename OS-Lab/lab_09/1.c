// Write a C program to implement dynamic storage allocation strategy for first fit and best fit using dynamic allocations for all the required data structures

#include <stdio.h>
#include <stdlib.h>

void first_fit(int *block_size, int m, int *process_size, int n)
{
    int allocation[n];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (block_size[j] >= process_size[i])
            {
                allocation[i] = j;
                block_size[j] -= process_size[i];
                break;
            }
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

void best_fit(int *block_size, int m, int *process_size, int n)
{
    int allocation[n];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int best_index = -1;
        for (int j = 0; j < m; j++)
        {
            if (block_size[j] >= process_size[i])
            {
                if (best_index == -1)
                {
                    best_index = j;
                }
                else if (block_size[j] < block_size[best_index])
                {
                    best_index = j;
                }
            }
        }

        if (best_index != -1)
        {
            allocation[i] = best_index;
            block_size[best_index] -= process_size[i];
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
    char choice;
    do
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

        printf("1. First Fit\n2. Best Fit\nEnter your choice: ");
        int ch;
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            first_fit(block_size, m, process_size, n);
            break;
        case 2:
            best_fit(block_size, m, process_size, n);
            break;
        default:
            printf("Invalid choice\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');
    return 0;
}