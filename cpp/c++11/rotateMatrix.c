// void rotateOne(int **matrix, int size)
// {
//     int layer = 0;
//     int i = 0, j = 0;
//     int cornerTemp;

//     for(;layer < size / 2; ++layer)
//     {
//         i = j = layer ;//layer corner
//         cornerTemp = matrix[i][j];
//         int lineTemp = 0;
//         while(j < (size - 1 - layer))//top line move right
//         {   
            
//             lineTemp = matrix[i][j + 1];
//             matrix[i][j+1] = matrix[i][j];

//             ++j;
//         }
//         while(i < (size - 1 -layer))//right line move down
//         {
//             lineTemp = matrix[i + 1][j];
//             matrix[i + 1][j] = matrix[i][j];
//             i++;            
//         }
//         while(j > layer)//bottom line move left
//         {
//             lineTemp = matrix[i][j-1];
//             matrix[i][j - 1] = matrix[i][j];
//             j--;
//         }
//         while(i < layer)//left line move up
//         {
//             lineTemp = matrix[i-1][j];
//             matrix[i -1][j] = matrix[i][j];
//             i--;
//         }
//     }
// }


#include <stdio.h>
#include <stdbool.h>
int bubbleSort(int* arr, int size)
{
    int swaped = 1;
    int i = 0;
    int swapTemp;
    while(swaped)
    {
        swaped = 0;
        for(i = 0; i < size - 1; i++)
        {
            if(arr[i+1] < arr[i])
            {
                swapTemp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = swapTemp;
                swaped = 1;            
            }
        }
    }
    
}
int selectionSort(int* arr, int size)
{
    int sortedInx = 0;
    int i = 0;
    int curMin = 0;
    int curMinInx = 0;
    int swapTemp = 0;

    for(;sortedInx < size -1; sortedInx++)
    {
        curMin = arr[sortedInx];
        curMinInx = sortedInx;
        for(i = sortedInx; i < size - 1; i ++)
        {
            if(arr[i] < curMin)
            {
                curMin = arr[i];
                curMinInx = i;
            }
        }
        swapTemp = arr[sortedInx];
        arr[sortedInx] = arr[curMinInx];
        arr[curMinInx] = swapTemp;
    }
}


// Helper function to print an array
void printArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Test function
void testBubbleSort() {
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int(*sortFunc)(int*,int)  = selectionSort;;
    printf("Original array:\n");
    printArray(arr1, size1);

    sortFunc(arr1, size1);

    printf("Sorted array:\n");
    printArray(arr1, size1);

    // Validate the result
    bool passed = true;
    for (int i = 1; i < size1; ++i) {
        if (arr1[i - 1] > arr1[i]) {
            passed = false;
            break;
        }
    }
    printf("Test %s\n", passed ? "PASSED" : "FAILED");

    // Test case: empty array
    int arr2[] = {};
    int size2 = 0;
    int result = sortFunc(arr2, size2);
    printf("Empty array test %s\n", result == -1 ? "PASSED" : "FAILED");

    // Test case: already sorted array
    int arr3[] = {1, 2, 3, 4, 5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    sortFunc(arr3, size3);
    printf("Already sorted array:\n");
    printArray(arr3, size3);

    // Test case: single element array
    int arr4[] = {42};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    sortFunc(arr4, size4);
    printf("Single element array:\n");
    printArray(arr4, size4);
}

int main() {
    testBubbleSort();
    return 0;
}