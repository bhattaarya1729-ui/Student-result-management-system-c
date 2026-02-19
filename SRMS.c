#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBJECT_MARKS 100

// Structure to store student details
typedef struct {
    char name[50];
    float english, maths, ip;
    float total, percentage;
    char grade;
    char remarks[50];
    int rank;
    int isPass;
} Student;

// Function to calculate grade and remarks
void calculateGrade(Student *s) {
    if (!s->isPass) {
        s->grade = 'F';
        strcpy(s->remarks, "Failed");
        return;
    }
    if (s->percentage >= 90) s->grade = 'A';
    else if (s->percentage >= 75) s->grade = 'B';
    else if (s->percentage >= 60) s->grade = 'C';
    else if (s->percentage >= 40) s->grade = 'D';
    else s->grade = 'F';

    switch (s->grade) {
        case 'A': strcpy(s->remarks, "Excellent Performance"); break;
        case 'B': strcpy(s->remarks, "Good Job"); break;
        case 'C': strcpy(s->remarks, "Needs Improvement"); break;
        case 'D': strcpy(s->remarks, "Just Passed"); break;
        case 'F': strcpy(s->remarks, "Better Luck Next Time"); break;
    }
}

// Function to sort students by percentage
void sortStudents(Student *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].percentage < arr[j + 1].percentage) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    // Assign ranks with tie handling
    int currentRank = 1;
    for (int i = 0; i < n; i++) {
        if (!arr[i].isPass) {
            arr[i].rank = -1; // No rank for fails
            continue;
        }
        if (i > 0 && arr[i].percentage == arr[i - 1].percentage) {
            arr[i].rank = arr[i - 1].rank; // Same rank for tie
        } else {
            arr[i].rank = currentRank;
        }
        currentRank++;
    }
}

// Function to validate marks
float getValidMarks(const char *subject) {
    float marks;
    do {
        printf("%s marks (0-%d): ", subject, MAX_SUBJECT_MARKS);
        scanf("%f", &marks);
        if (marks < 0 || marks > MAX_SUBJECT_MARKS) {
            printf("Invalid marks! Please enter again.\n");
        }
    } while (marks < 0 || marks > MAX_SUBJECT_MARKS);
    return marks;
}

int main() {
    int n, passCount = 0, failCount = 0;
    float totalPercentage = 0;

    printf("Enter number of students: ");
    scanf("%d", &n);
    getchar();

    Student *students = (Student *)malloc(n * sizeof(Student));

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Student %d\n", i + 1);
        printf("Name: ");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0;

        students[i].english = getValidMarks("English");
        students[i].maths = getValidMarks("Maths");
        students[i].ip = getValidMarks("IP");
        getchar();

        students[i].total = students[i].english + students[i].maths + students[i].ip;
        students[i].percentage = (students[i].total / 300) * 100;

        if (students[i].english >= 33 && students[i].maths >= 33 && students[i].ip >= 33 && students[i].percentage >= 40) {
            students[i].isPass = 1;
            passCount++;
        } else {
            students[i].isPass = 0;
            failCount++;
        }

        calculateGrade(&students[i]);
        totalPercentage += students[i].percentage;
    }

    sortStudents(students, n);

    // Find subject toppers
    int engTop = 0, mathTop = 0, ipTop = 0;
    for (int i = 1; i < n; i++) {
        if (students[i].english > students[engTop].english) engTop = i;
        if (students[i].maths > students[mathTop].maths) mathTop = i;
        if (students[i].ip > students[ipTop].ip) ipTop = i;
    }

    // Display results in table
    printf("\n----------------------------------------------------------------------------------------------\n");
    printf("Rank | Name                 | Eng   | Math  | IP    | Total | %%     | Grade | Remarks\n");
    printf("----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (students[i].rank == -1)
            printf(" --  | %-20s | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5c | %s\n",
                   students[i].name, students[i].english, students[i].maths,
                   students[i].ip, students[i].total, students[i].percentage,
                   students[i].grade, students[i].remarks);
        else
            printf("%-4d | %-20s | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5c | %s\n",
                   students[i].rank, students[i].name, students[i].english, students[i].maths,
                   students[i].ip, students[i].total, students[i].percentage,
                   students[i].grade, students[i].remarks);
    }
    printf("----------------------------------------------------------------------------------------------\n");

    printf("\nClass Statistics:\n");
    printf("Pass Count: %d\n", passCount);
    printf("Fail Count: %d\n", failCount);
    printf("Average Class Percentage: %.2f%%\n", totalPercentage / n);
    printf("Highest Scorer: %s (%.2f%%)\n", students[0].name, students[0].percentage);
    printf("Lowest Scorer: %s (%.2f%%)\n", students[n - 1].name, students[n - 1].percentage);
    printf("Top in English: %s (%.1f)\n", students[engTop].name, students[engTop].english);
    printf("Top in Maths: %s (%.1f)\n", students[mathTop].name, students[mathTop].maths);
    printf("Top in IP: %s (%.1f)\n", students[ipTop].name, students[ipTop].ip);

    // Save to file
    FILE *fp = fopen("results.txt", "w");
    if (fp) {
        fprintf(fp, "Rank | Name                 | Eng   | Math  | IP    | Total | %%     | Grade | Remarks\n");
        for (int i = 0; i < n; i++) {
            if (students[i].rank == -1)
                fprintf(fp, " --  | %-20s | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5c | %s\n",
                        students[i].name, students[i].english, students[i].maths,
                        students[i].ip, students[i].total, students[i].percentage,
                        students[i].grade, students[i].remarks);
            else
                fprintf(fp, "%-4d | %-20s | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5c | %s\n",
                        students[i].rank, students[i].name, students[i].english, students[i].maths,
                        students[i].ip, students[i].total, students[i].percentage,
                        students[i].grade, students[i].remarks);
        }
        fclose(fp);
        printf("\nResults saved to results.txt\n");
    } else {
        printf("\nError saving file.\n");
    }

    free(students);
    return 0;
}
