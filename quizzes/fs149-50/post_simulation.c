#include <stdio.h>
#include <stdlib.h> /*malloc*/

#define M 5

void ChangeToNextInx( size_t *layer, size_t *row, size_t size){
    size_t temp_inx = *row;
    *row = size - 1 - *layer;
    *layer = temp_inx;
}

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void RotateMatrix90DegClockwise(int **matrix, size_t size)
{
    size_t mov_num = 0;
    size_t layer_inx = 0;
    size_t row_inx = 0;

    int temp  = 0;

    for(;layer_inx < (size/2); layer_inx++)
    {
        for(row_inx = layer_inx; row_inx < (size -1 -layer_inx); row_inx++)
        {
            for(temp = matrix[layer_inx][row_inx], mov_num = 0;mov_num < 4; mov_num++)
            {
                ChangeToNextInx(&layer_inx, &row_inx, size);
                Swap(&temp, &(matrix[layer_inx][row_inx]));
            }
        }
    }
    
}

void PrintMatrix(int **matrix,size_t size)
{
    size_t i = 0, j = 0;
   
    for(;i < size; i++)
    {
        for(j = 0; j < size ; j++)
        {
            printf("%d,\t",matrix[i][j]);
        }
        printf("\n");

    }
}

unsigned int NextPowerOfTwo(unsigned int num)
{
   return (num & (num -1)) == 0 ? num <<1 : (num << 1) & ((num << 1) -1);
}


unsigned int MirrorInt(unsigned int num){
    num = ((num & 0xf0) >> 4) | ((num & 0xf0) << 4);
    num = ((num & 0xcc) >> 2) | ((num & 0x33) << 2);
    num = ((num & 0xaa) >> 1) | ((num & 0x55) << 1);
    return num;
}


int main()
{
     int n = 3;
    int** arr = (int**)malloc(n * sizeof(int*));
    int i = 0, j = 0;
    for (; i < n; i++) {
        arr[i] = (int*)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            arr[i][j] = i * n + j + 1; 
        }
    }
    printf("before\n");
    PrintMatrix(arr, n);
    RotateMatrix90DegClockwise(arr, n);
    printf("\nafter\n");
    PrintMatrix(arr, n);

    for (i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);


    return 0;
}
