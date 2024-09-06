// write a C program to simulate page replacement algorithms: FIFO and optimal. Frame allocation has to be done as per user input and use dynamic allocation for all data structures.

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

void fifo(int *pages, int n, int m)
{
    int page_faults = 0;
    int *frame = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        frame[i] = -1;
    }

    int frame_index = 0;
    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int flag = 0;
        for (int j = 0; j < m; j++)
        {
            if (frame[j] == page)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            frame[frame_index] = page;
            frame_index = (frame_index + 1) % m;
            page_faults++;
        }
        print_frame(frame, m);
    }
    printf("Total Page Faults: %d\n", page_faults);
}

void optimal(int *pages, int n, int m)
{
    int page_faults = 0;
    int *frame = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        frame[i] = -1;
    }

    int frame_index = 0;
    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int flag = 0;
        for (int j = 0; j < m; j++)
        {
            if (frame[j] == page)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            if (frame[frame_index] != -1)
            {
                int *next = (int *)malloc(m * sizeof(int));
                for (int j = 0; j < m; j++)
                {
                    next[j] = -1;
                }

                for (int j = i + 1; j < n; j++)
                {
                    for (int k = 0; k < m; k++)
                    {
                        if (pages[j] == frame[k])
                        {
                            next[k] = j;
                            break;
                        }
                    }
                }

                int max = -1;
                int max_index = -1;
                for (int j = 0; j < m; j++)
                {
                    if (next[j] == -1)
                    {
                        max_index = j;
                        break;
                    }

                    if (next[j] > max)
                    {
                        max = next[j];
                        max_index = j;
                    }
                }

                frame[max_index] = page;
                page_faults++;
            }
            else
            {
                frame[frame_index] = page;
                frame_index = (frame_index + 1) % m;
                page_faults++;
            }
        }

        print_frame(frame, m);
    }
    printf("Total Page Faults: %d\n", page_faults);
}

int main()
{
    char choice;
    do
    {
        int n;
        printf("Enter the number of pages: ");
        scanf("%d", &n);
        int *pages = (int *)malloc(n * sizeof(int));
        printf("Enter the page numbers: ");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &pages[i]);
        }

        int m;
        printf("Enter the number of frames: ");
        scanf("%d", &m);

        printf("Choose the page replacement algorithm:\n1. FIFO\n2. Optimal\n");
        int algorithm;
        scanf("%d", &algorithm);

        switch (algorithm)
        {
        case 1:
            fifo(pages, n, m);
            break;
        case 2:
            optimal(pages, n, m);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');

    return 0;
}