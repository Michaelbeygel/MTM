#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_power_of_two(int num) {
    return (num > 0) && ((num & (num - 1)) == 0);
}

int getPowerOfTwo(int n) {
    int count = 0;

    // Count the number of set bits until there is no bit set
    while (n > 1) {
        n = n >> 1;
        count++;
    }

    return count;
}


int main() {
    int size;

    // Get the number of integers from the user
    printf("Enter size of input:\n");

    if(scanf("%d", &size) != 1)
    {
        printf("Invalid number\n");
        return 0;
    }


    if(size < 1)
    {
        printf("Invalid size\n");
        return 0;
    }

    int *numbers = (int *)malloc(size * sizeof(int));
    if(numbers == NULL)
    {
        printf("Invalid size\n");
        return 0;
    }

    // Input the integers from the user
    printf("Enter numbers:\n");
    for (int i = 0; i < size; i++) {
        if(scanf("%d", &numbers[i]) != 1)
        {
            printf("Invalid number\n");
            return 0;
        }
    }


    int power = 0;
    int powers_sum = 0;
    for(int j = 0; j < size; j++){
        if (is_power_of_two(numbers[j]))
        {
            power = getPowerOfTwo(numbers[j]);
            powers_sum += power;
            printf("The number %d is a power of 2: %d = 2^%d\n",numbers[j], numbers[j], power);
        }
    }

    printf("Total exponent sum is %d\n", powers_sum);   
    // Free the dynamically allocated memory
    free(numbers);


    return 0;
}
