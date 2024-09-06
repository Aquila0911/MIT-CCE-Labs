//  Write a C program to simulate LRU Page Replacement. Frame allocation has to be done as per user input and dynamic allocation for all data structures.

#include <stdio.h>
#include <stdlib.h>

void print_frame(int *frame, int m)
{
    printf("Frame: ");
    for (int i = 0; i < m; i++)
    {
        if (frame[i] == -1)
        {
            printf(" ");
        }
        else
        {
            printf("%d", frame[i]);
        }
        if (i != m - 1)
        {
            printf(" | ");
        }
    }
    printf("\n");
}


void lru(int *pages, int n, int m)
{
    int page_faults = 0;
    int *frame = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        frame[i] = -1;
    }

    int *last_used = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        last_used[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int flag = 0;
        for (int j = 0; j < m; j++)
        {
            if (frame[j] == page)
            {
                flag = 1;
                last_used[j] = i;
                break;
            }
        }

        if (flag == 0)
        {
            int min = 0;
            for (int j = 0; j < m; j++)
            {
                if (last_used[j] < last_used[min])
                {
                    min = j;
                }
            }
            frame[min] = page;
            last_used[min] = i;
            page_faults++;
        }
        print_frame(frame, m);
    }
    printf("Total Page Faults: %d\n", page_faults);
}

int main()
{
    int n, m;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int *pages = (int *)malloc(n * sizeof(int));
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &m);
    lru(pages, n, m);
    return 0;
}