// Priority Queue implementation in C inspired by: https://www.programiz.com/dsa/priority-queue
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct
{
    int x;
    int y;
    int distance;
} cell;

int dp[50][50][2000];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int size = 0;
int ind = 0;
void swap(cell *a, cell *b)
{
    cell temp = *b;
    *b = *a;
    *a = temp;
}

int isEqual(cell a, cell b)
{
    return a.x == b.x && a.y == b.y;
}

int isGreater(cell a, cell b)
{
    return a.x > b.x + a.y > b.y;
}

int isLess(cell a, cell b)
{
    return a.x < b.x + a.y < b.y;
}

// Function to heapify the tree
void heapify(cell array[], int size, int i)
{
    if (size == 1)
    {
        printf("Single element in the heap");
    }
    else
    {
        // Find the largest among root, left child and right child
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < size && isGreater(array[l], array[largest]))
            largest = l;
        if (r < size && isGreater(array[r], array[largest]))
            largest = r;

        // Swap and continue heapifying if root is not largest
        if (largest != i)
        {
            swap(&array[i], &array[largest]);
            heapify(array, size, largest);
        }
    }
}

// Function to insert an element into the tree
void insert(cell array[], cell newNum)
{
    if (size == 0)
    {
        array[0] = newNum;
        size += 1;
    }
    else
    {
        array[size] = newNum;
        size += 1;
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(array, size, i);
        }
    }
}

// Function to delete an element from the tree
void deleteRoot(cell array[], cell num)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (isEqual(num, array[i]))
            break;
    }

    swap(&array[i], &array[size - 1]);
    size -= 1;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(array, size, i);
    }
}

// Print the array
void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

int compareCells(cell *a, cell *b)
{
    if (a->distance < b->distance)
    {
        return -1;
    }
    else if (a->distance > b->distance)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int shortestPath(int *matrix, int rows, int column, int startX, int startY, int endX, int endY, cell *path)
{
    // fill dp with int_max
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            for (int k = 0; k < 2000; k++)
            {
                dp[i][j][k] = INT_MAX;
            }
        }
    }

    // Create a priority queue to store vertices
    cell heap[rows * column];
    cell c;
    c.x = startX;
    c.y = startY;

    insert(heap, c);

    while (size > 0)
    {
        int x = heap[0].x;
        int y = heap[0].y;
        int distance = heap[0].distance;

        // prints the data

        deleteRoot(heap, heap[0]);

        if (x == endX && y == endY)
        {
            return distance;
        }

        distance++;

        for (int i = 0; i < 4; i++)
        {

            int newX = x + dir[i][0];
            int newY = y + dir[i][1];

            if (newX == endX && newY == endY)
            {
                return distance;
            }

            if (newX >= 0 && newY >= 0 && newX < rows && newY < column && matrix[newX + newY * rows] == 0)
            {

                if (distance < dp[newX][newY][0])
                {
                    dp[newX][newY][0] = distance;
                    c.x = newX;
                    c.y = newY;
                    c.distance = distance;
                    path[distance] = c;
                    insert(heap, c);
                }
            }
        }
    }
    return -1;
}

int main()
{
    int rows = 4;
    int column = 4;
    /* matrix with 0 and 1 */
    int matrix[4][4] = {{0, 0, 0, 0},
                        {1, 1, 0, 1},
                        {1, 0, 0, 1},
                        {0, 1, 0, 0}};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    cell heap[rows * column];
    cell path[rows * column];

    int startX = 0;
    int startY = 0;

    int endX = 3;
    int endY = 3;

    int length = shortestPath((int **)matrix, rows, column, startX, startY, endX, endY, path);

    printf("\nLength of the shortest path is %d\n", length);

    printf("\nPath is:\n");

    // print the path
    for (int i = 1; i < length; i++)
    {
        printf("%d %d\n", path[i].x, path[i].y);
    }

    return 0;
}
