#include <stdio.h>
#include <stdlib.h>

#define DESCRIPTORS 100

struct descriptor {
    int (*function)(void* input, void* output);
    size_t input_size;
    size_t output_size;
};

struct descriptor* table[DESCRIPTORS];

enum sample {FUN1, FUN2};

/** 
 * Error codes:
 * 1 -> NULL input
 * 2 -> NULL output
 * 3 -> NULL enum pointer
 * 4 -> INVALID descriptors table
 * 
 * Functions in descriptors must check and report at least the following bad situations:
 * 1 -> NULL input
 */
int dispatch(enum sample* sample, void* input, void* output) {
    if (!sample) {return 3;}
    if (!input) {return 1;}

    // supposing descriptors contains for sure an element for each enum value
    if (!table) {return 4;}
    struct descriptor* descriptor = table[*sample];
    
    descriptor -> input_size = sizeof(*input);
    int status = (*(descriptor -> function))(input, output);
    if (status != 0) {return status;}
    if (!output) {return 2;}
    descriptor -> output_size = sizeof(*output);
    return 0;   
}

int fun1(void* input, void* output) {
    if (!input) return 1;
    int* in = (int*)input;
    int* out = (int*)output;
    *out = *in > 10;
    return 0;
}

int fun2(void* input, void* output) {
    if (!input) return 1;
    char* in = (char*)input;
    int* out = (int*)output;
    *out = *in >= 97 && *in <= 122;
    return 0;
}

int main() {
    table[FUN1] = (struct descriptor*) malloc(sizeof(struct descriptor));
    table[FUN1] -> function = fun1;
    table[FUN2] = (struct descriptor*) malloc(sizeof(struct descriptor));
    table[FUN2] -> function = fun2;
    int x = 50; char y = 'B';
    int output; enum sample f = FUN1;
    printf("%d ", dispatch(&f, &x, &output));
    printf("%d %ld %ld\n", output, table[FUN1] -> input_size, table[FUN1] -> output_size);
    
    return 0;
}