/* student_mgmt.c
   Simple Student Mark Management (menu-driven)
   Compile: gcc -o student_mgmt student_mgmt.c
   Run: ./student_mgmt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define DATA_FILE "students.dat"

typedef struct {
    int roll;
    char name[MAX_NAME];
    int marks[5];   // assume 5 subjects
    int total;
    float percent;
    char grade[3];
} Student;

/* Function prototypes */
void load_records(Student **arr, int *count);
void save_records(Student *arr, int count);
void add_student(Student **arr, int *count);
void display_all(Student *arr, int count);
int find_index_by_roll(Student *arr, int count, int roll);
void search_student(Student *arr, int count);
void update_student(Student *arr, int count);
void delete_student(Student **arr, int *count);
void calculate_results(Student *s);
void pause_console();

int main() {
    Student *students = NULL;
    int count = 0;
    int choice;

    load_records(&students, &count);

    do {
        printf("\n=== Student Mark Management ===\n");
        printf("1. Add student\n");
        printf("2. Display all students\n");
        printf("3. Search student by roll\n");
        printf("4. Update student\n");
        printf("5. Delete student\n");
        printf("6. Save & Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            // clear invalid input
            while (getchar() != '\n');
            choice = 0;
        }
        switch (choice) {
            case 1: add_student(&students, &count); break;
            case 2: display_all(students, count); break;
            case 3: search_student(students, count); break;
            case 4: update_student(students, count); break;
            case 5: delete_student(&students, &count); break;
            case 6: save_records(students, count); printf("Saved. Exiting.\n"); break;
            default: if (choice != 6) printf("Invalid option, try again.\n");
        }
    } while (choice != 6);

    free(students);
    return 0;
}

/* Load records from DATA_FILE (binary) */
void load_records(Student **arr, int *count) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        *arr = NULL;
        *count = 0;
        return;
    }

    // find file size / number of records
    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    rewind(fp);

    if (sz > 0) {
        *count = (int)(sz / sizeof(Student));
        *arr = malloc((*count) * sizeof(Student));
        if (!*arr) {
            perror("Memory allocation failed");
            *count = 0;
            fclose(fp);
            return;
        }
        size_t read = fread(*arr, sizeof(Student), *count, fp);
        if ((int)read != *count) {
            fprintf(stderr, "Warning: Could not read all records.\n");
            *count = (int)read;
        }
    } else {
        *arr = NULL;
        *count = 0;
    }
    fclose(fp);
}

/* Save records to DATA_FILE (binary) */
void save_records(Student *arr, int count) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }
    fwrite(arr, sizeof(Student), count, fp);
    fclose(fp);
}

/* Add a new student */
void add_student(Student **arr, int *count) {
    Student s;
    printf("\nEnter roll number: ");
    if (scanf("%d", &s.roll) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); return; }
    while (getchar() != '\n'); // clear newline
    printf("Enter name: ");
    fgets(s.name, MAX_NAME, stdin);
    // strip newline
    size_t len = strlen(s.name);
    if (len && s.name[len-1] == '\n') s.name[len-1] = '\0';

    for (int i = 0; i < 5; ++i) {
        printf("Enter marks for subject %d (0-100): ", i+1);
        if (scanf("%d", &s.marks[i]) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); return; }
        if (s.marks[i] < 0) s.marks[i] = 0;
        if (s.marks[i] > 100) s.marks[i] = 100;
    }

    calculate_results(&s);

    // check unique roll
    if (find_index_by_roll(*arr, *count, s.roll) != -1) {
        printf("A student with roll %d already exists. Use update instead.\n", s.roll);
        return;
    }

    Student *tmp = realloc(*arr, (*count + 1) * sizeof(Student));
    if (!tmp) {
        perror("Memory allocation failed");
        return;
    }
    *arr = tmp;
    (*arr)[*count] = s;
    (*count)++;
    printf("Student added.\n");
}

/* Display all students */
void display_all(Student *arr, int count) {
    if (count == 0) {
        printf("\nNo records to display.\n");
        return;
    }
    printf("\n%-6s %-20s %-6s %-6s %-6s %-6s %-6s %-6s %-8s %s\n",
           "Roll", "Name", "S1", "S2", "S3", "S4", "S5", "Total", "Percent", "Grade");
    for (int i = 0; i < count; ++i) {
        Student *s = &arr[i];
        printf("%-6d %-20s %-6d %-6d %-6d %-6d %-6d %-6d %-8.2f %s\n",
               s->roll, s->name, s->marks[0], s->marks[1], s->marks[2],
               s->marks[3], s->marks[4], s->total, s->percent, s->grade);
    }
}

/* Find index by roll number; returns -1 if not found */
int find_index_by_roll(Student *arr, int count, int roll) {
    for (int i = 0; i < count; ++i) {
        if (arr[i].roll == roll) return i;
    }
    return -1;
}

/* Search student */
void search_student(Student *arr, int count) {
    if (count == 0) { printf("\nNo records.\n"); return; }
    int roll;
    printf("\nEnter roll to search: ");
    if (scanf("%d", &roll) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); return; }
    int idx = find_index_by_roll(arr, count, roll);
    if (idx == -1) {
        printf("Student with roll %d not found.\n", roll);
        return;
    }
    Student *s = &arr[idx];
    printf("\nFound:\nRoll: %d\nName: %s\n", s->roll, s->name);
    for (int i = 0; i < 5; ++i) printf("Subject %d: %d\n", i+1, s->marks[i]);
    printf("Total: %d\nPercentage: %.2f\nGrade: %s\n", s->total, s->percent, s->grade);
}

/* Update student */
void update_student(Student *arr, int count) {
    if (count == 0) { printf("\nNo records.\n"); return; }
    int roll;
    printf("\nEnter roll to update: ");
    if (scanf("%d", &roll) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); return; }
    int idx = find_index_by_roll(arr, count, roll);
    if (idx == -1) { printf("Not found.\n"); return; }

    Student *s = &arr[idx];
    while (getchar() != '\n');
    printf("Current name: %s\nEnter new name (or press enter to keep): ", s->name);
    char tmp[MAX_NAME];
    fgets(tmp, MAX_NAME, stdin);
    if (tmp[0] != '\n') {
        size_t len = strlen(tmp);
        if (len && tmp[len-1] == '\n') tmp[len-1] = '\0';
        strncpy(s->name, tmp, MAX_NAME);
    }

    for (int i = 0; i < 5; ++i) {
        printf("Current marks for subject %d: %d\nEnter new marks (-1 to keep): ", i+1, s->marks[i]);
        int m;
        if (scanf("%d", &m) != 1) { while (getchar() != '\n'); printf("Invalid input, skipping.\n"); continue; }
        if (m >= 0 && m <= 100) s->marks[i] = m;
    }
    calculate_results(s);
    printf("Updated.\n");
}

/* Delete student */
void delete_student(Student **arr, int *count) {
    if (*count == 0) { printf("\nNo records.\n"); return; }
    int roll;
    printf("\nEnter roll to delete: ");
    if (scanf("%d", &roll) != 1) { while (getchar() != '\n'); printf("Invalid input.\n"); return; }
    int idx = find_index_by_roll(*arr, *count, roll);
    if (idx == -1) { printf("Not found.\n"); return; }

    // shift remaining left
    for (int i = idx; i < *count - 1; ++i) {
        (*arr)[i] = (*arr)[i+1];
    }
    Student *tmp = realloc(*arr, (*count - 1) * sizeof(Student));
    if (tmp || (*count - 1) == 0) {
        *arr = tmp;
    }
    (*count)--;
    printf("Deleted student with roll %d.\n", roll);
}

/* Calculate total, percent and grade for a student */
void calculate_results(Student *s) {
    s->total = 0;
    for (int i = 0; i < 5; ++i) s->total += s->marks[i];
    s->percent = (float)s->total / 5.0f;
    if (s->percent >= 90) strcpy(s->grade, "A+");
    else if (s->percent >= 80) strcpy(s->grade, "A");
    else if (s->percent >= 70) strcpy(s->grade, "B+");
    else if (s->percent >= 60) strcpy(s->grade, "B");
    else if (s->percent >= 50) strcpy(s->grade, "C");
    else strcpy(s->grade, "F");
}

/* Optional pause helper (not used) */
void pause_console() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}
