#include <stdio.h>
#include <stdlib.h>

enum role {
    PROF,
    ASSIST,
    STD
};

union pers_data {
    int age;
    char gender;
};

int prof(union pers_data* data) {
    return data -> gender == 'M';
}

int assist(union pers_data* data) {
    return data -> age > 25;
}

int std(union pers_data* data) {
    return data -> age < 25;
}

int (*handle[3])(union pers_data*);

void january2010a(enum role* role, union pers_data* data, int* status) {
    *status = (*(handle[*role]))(data);
}

int main() {
    handle[0] = &prof;
    handle[1] = &assist;
    handle[2] = &std;

    enum role role = PROF;
    union pers_data data; data.gender = 'F';
    int status = 1000;

    january2010a(&role, &data, &status);
    printf("Should be 0: %d\n", status);
    data.gender = 'M';
    january2010a(&role, &data, &status);
    printf("Should be 1: %d\n", status);

    data.age = 30; role = ASSIST;
    january2010a(&role, &data, &status);
    printf("Should be 1: %d\n", status);


    role = STD;
    january2010a(&role, &data, &status);
    printf("Should be 0: %d\n", status);
    return 0;
}