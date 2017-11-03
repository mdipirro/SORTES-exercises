#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STD_NUMBER_LENGTH 10
#define STD_NAME_LENGTH 20
#define MAX_STUDENTS 100

struct student {
    char std_number[STD_NUMBER_LENGTH];
    char std_name[STD_NAME_LENGTH];
    char gender;
    float quiz1;
    float quiz2;
    float assignment;
    float midterm;
    float final;
    float total;
};

// Helper functions
void print_student(const struct student* const);
void print_students_by_total_score(const struct student* const, int, int);
int gt(const void*, const void*);

// Exercise's functions
void display_menu();
int add_student(struct student*, int, struct student);
int delete_student(struct student* const, int, const char* const);
void print_students(const struct student* const, int);
double get_scores_average(const struct student* const, int, const char* const);
void print_students_with_max_total_score(const struct student* const, int);
void print_students_with_min_total_score(const struct student* const, int);
struct student* find_student_by_id(const struct student* const, int, const char* const);
struct student* sort_students_by_total_score(const struct student* const, int);

/**
 * Print a given student.
 * @param student The student
 */ 
void print_student(const struct student* const student) {
    if (student) {
        printf("Student's number: %s\n", student -> std_number);
        printf("\tStudent's name: %s\n", student -> std_name);
        printf("\tGender: %c\n", student -> gender);
        printf("\tScores: \n");
        printf("\t\tQuiz 1: %e\n", student -> quiz1);
        printf("\t\tQuiz 2: %e\n", student -> quiz2);
        printf("\t\tAssignment: %e\n", student -> assignment);
        printf("\t\tMidterm: %e\n", student -> midterm);
        printf("\t\tFinal: %e\n", student -> final);
        printf("\t\tTotal: %e\n", student -> total);
    } else {
        printf("Invalid student");
    }
}

/**
 * Print the students with a given total score.
 * @param students A pointer to an array of students
 * @param length students' length
 * @param score The score
 */ 
void print_students_by_total_score(const struct student* const students, int length, int score) {
    for(int i = 0; i < length; i++) {
        if (students[i].total == score) {
            print_student(students + i * sizeof(struct student));
        }
    }
}

/**
 * Compare two floats and return 1 iff a > b
 * @param a A void pointer to a float
 * @param b A void pointer to a float
 * @return 1 iff the float pointed to by `a` is greater than the float pointed to by `b`
 */ 
int gt(const void* a, const void* b) {
    return (*(float*) a) > (*(float*) b);
}

/**
 * Display the main menu.
 */ 
void display_menu() {
    printf("--------------------------------------------------------------------------------");
    printf("--------------------------------------MENU--------------------------------------");
    printf("--------------------------------------------------------------------------------");
    printf("1) Add student record");
    printf("2) Delete student record");
    printf("3) Update student record");
    printf("4) View all student records");
    printf("5) Calculate an average of a selected student’s scores");
    printf("6) Show student who gets the max total score");
    printf("7) Show student who gets the min total score");
    printf("8) Find student by ID");
    printf("9) Sort records by total scores");
    printf("Enter your choice: ");
}

/**
 * PLEASE take note this program makes use of the vulnerable strcpy function and does
 * not check for strings length. The purpose of this exerccise is not to show how to
 * write secure code in C, but to test some struct aspects. A proper C code should 
 * perform each necessary sanity check, included, but not limited to, a check before
 * copying strings.
 */ 
int add_student(struct student* students, int length, struct student std) {
    if (length + 1 < MAX_STUDENTS) {
        if (!find_student_by_id(students, length, std.std_number)) {
            length++;
            strcpy(std.std_number, students[length].std_number);
            strcpy(std.std_name, students[length].std_name);
            students[length].gender = std.gender;
            students[length].quiz1 = std.quiz1;
            students[length].quiz2 = std.quiz2;
            students[length].assignment = std.assignment;
            students[length].midterm = std.midterm;
            students[length].final = std.final;
            students[length].total = std.quiz1 + std.quiz2 + std.assignment + std.midterm + std.final;
        } else {
            printf("A student with the same ID is already present");
        }
    } else {
        printf("No more spot for other students");
    }
    return length;
}

/**
 * Delete a student with a given  `student_id`. If such student is not present, leave the array
 * untouched. It returns the new array's length (decreased by 1 or the same as before the invocation).
 * @param students A pointer to an array of students
 * @param length students' length
 * @param student_id The ID of the student to be deleted
 * @return The length of the new array. If it the same as before the invocation, no deletion has happened
 */ 
int delete_student(struct student* const students, int length, const char* const student_id) {
    int i = 0, found = 0;
    while (i < length && !found) {
        found = strcmp(students[i++].std_number, student_id);
    }
    if (found) {
        free(students + (i - 1) * sizeof(struct student));
        for (; i < length; i++) {
            students[i - 1] = students[i];
        }
        return length - 1;
    }
    return length;
}

/**
 * Print an array of students
 * @param students A pointer to an array of students
 * @param length students' length
 */ 
void print_students(const struct student* const students, int length) {
    for (int i = 0; i < length; i++) {
        print_student(students + i * sizeof(struct student));
    }
}

/**
 * Calculate the average of a selected student's scores.
 * @param students A pointer to an array of students
 * @param length students' length
 * @param student_id Selected student's ID
 * @return The average of the scores of that student, if any; 0 otherwise
 */ 
double get_scores_average(const struct student* const students, int length, const char* const student_id) {
    struct student* student = find_student_by_id(students, length, student_id);
    if (student) {
        return student -> total / 5;
    }
    return 0; // Student not found
}

void print_students_with_max_total_score(const struct student* const students, int length) {
    int max = 0;
    for (int i = 0; i < length; i++) {
        if (students[i].total > max) {
            max = students[i].total;
        }
    }
    print_students_by_total_score(students, length, max);
}

void print_students_with_min_total_score(const struct student* const students, int length) {
    int min = 100;
    for (int i = 0; i < length; i++) {
        if (students[i].total < min) {
            min = students[i].total;
        }
    }
    print_students_by_total_score(students, length, min);
}

/**
 * Find a student given its student_id.
 * @param students Array of students
 * @param length Length of `students`
 * @param student_id ID to be found
 * @return A pointer to the student, if any, NULL otherwise
 */ 
struct student* find_student_by_id(const struct student* const students, int length, const char* const student_id) {
    int i = 0, found = 0;
    while (i < length && !found) {
        found = strcmp(students[i++].std_number, student_id);
    }
    return (found) ? (students + (i - 1) * sizeof(struct student)) : NULL;
}

/**
 * Find a student given its student_id.
 * @param students Array of students
 * @param length Length of `students`
 * @return The same array, but sorted by total score.
 */ 
struct student* sort_students_by_total_score(const struct student* const students, int length) {
    qsort((void*)students, length, sizeof(struct student), gt);
}

int main() {
    
}