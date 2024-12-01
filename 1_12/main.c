#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>

void sort_array(int *array, int size);

int main() 
{
    FILE *file_with_input = fopen("example.txt", "r");

    if (file_with_input == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int lines = 0;
    char ch;
    int end_with_new_line = 0;

    while ((ch = fgetc(file_with_input)) != EOF)
    {
        if (ch == '\n')
        {
            end_with_new_line = 1;
            lines++;
        }
        else 
        {
            end_with_new_line = 0;
        }
    }

    if(!end_with_new_line)
    {
        lines++;
    }

    printf("%d ", lines);
    rewind(file_with_input);

    int *arr1 = malloc(lines * sizeof(int));
    int *arr2 = malloc(lines * sizeof(int));
    if (arr1 == NULL || arr2 == NULL) 
    {
        fclose(file_with_input);
        return 1;
    }

    for (int index = 0; index < lines; index++) 
    {
        if (fscanf(file_with_input, "%d %d", &arr1[index], &arr2[index]) != 2) 
        {
            break;
        }
    }
    fclose(file_with_input);

    sort_array(arr1, lines);
    sort_array(arr2, lines);

    int part1_result = 0;
    for (int index = 0; index < lines; index++)
    {
        if (arr1[index] >= arr2[index]) 
        {
            part1_result += arr1[index] - arr2[index];
        }
        else 
        {
            part1_result += arr2[index] - arr1[index];
        }
    }

    int part2_result = 0;
    for (int i = 0; i < lines; i++)
    {
        int number_to_check = arr1[i];
        int occurrence = 0;
        int number_exist = 0;
        for (int j = 0; j < lines; j++)
        {
            if(number_to_check == arr2[j])
            {
                number_exist = 1;
                occurrence++;
            }

            if(number_to_check != arr2[j] && number_exist == 1)
            {
                break;
            }
        }
        printf("\n");
        printf("%d ", number_to_check);
        printf(" %d ", occurrence);
        part2_result += number_to_check * occurrence;
    }

    free(arr1);
    free(arr2);
    printf("\n");
    printf("%d ", part1_result);
    printf("\n");
    printf("%d ", part2_result);
    return 0;
}

void sort_array(int *array, int size) 
{
    for (int i = 0; i < size - 1; i++) 
    {
        for (int j = 0; j < size - i - 1; j++) 
        {
            if (array[j] > array[j + 1]) 
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}