#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define QUESTIONS_PER_QUIZ 5
#define QUESTIONS_PER_CATEGORY 8
#define MAX_RESULTS 500
#define NAME_LENGTH 50
#define RESULT_FILE "scores.txt"

typedef struct {
    char question[180];
    char options[4][100];
    int correct; /* 0=A, 1=B, 2=C, 3=D */
} Question;

typedef struct {
    char name[NAME_LENGTH];
    int category;
    int score;
    int total;
} Result;

const char *categories[] = {"C Programming", "Computer Basics", "General Knowledge"};

const Question bank[3][QUESTIONS_PER_CATEGORY] = {
    {
        {"Which function prints formatted output in C?", {"scanf", "printf", "fgets", "strlen"}, 1},
        {"Which header declares printf?", {"stdlib.h", "string.h", "stdio.h", "ctype.h"}, 2},
        {"What is the first index of a C array?", {"0", "1", "-1", "2"}, 0},
        {"Which operator tests equality?", {"=", "!=", "==", ">="}, 2},
        {"Which loop runs its body at least once?", {"for", "while", "nested for", "do-while"}, 3},
        {"Which symbol terminates a typical C statement?", {"Colon", "Semicolon", "Comma", "Period"}, 1},
        {"Which keyword returns a value from a function?", {"break", "continue", "return", "goto"}, 2},
        {"Which format specifier prints an int?", {"%f", "%c", "%s", "%d"}, 3}
    },
    {
        {"What does CPU stand for?", {"Central Processing Unit", "Computer Power Unit", "Central Program Utility", "Control Processing User"}, 0},
        {"Which device is typically used to enter text?", {"Monitor", "Keyboard", "Printer", "Speaker"}, 1},
        {"Which is volatile memory?", {"SSD", "ROM", "RAM", "DVD"}, 2},
        {"What does URL stand for?", {"Universal Read Link", "Uniform Resource Locator", "User Resource List", "Unified Router Location"}, 1},
        {"Which is an operating system?", {"Python", "Chrome", "Linux", "HTML"}, 2},
        {"How many bits are in one byte?", {"4", "16", "32", "8"}, 3},
        {"Which device displays visual output?", {"Monitor", "Mouse", "Microphone", "Scanner"}, 0},
        {"Which is a web browser?", {"Windows", "Firefox", "Excel", "Ubuntu"}, 1}
    },
    {
        {"What is the capital of Japan?", {"Seoul", "Beijing", "Tokyo", "Bangkok"}, 2},
        {"How many continents are commonly recognized?", {"5", "6", "7", "8"}, 2},
        {"Which planet is known as the Red Planet?", {"Venus", "Mars", "Jupiter", "Mercury"}, 1},
        {"Which is the largest ocean?", {"Atlantic", "Indian", "Arctic", "Pacific"}, 3},
        {"What is H2O commonly called?", {"Water", "Oxygen", "Salt", "Hydrogen"}, 0},
        {"Which country is home to the Taj Mahal?", {"Nepal", "India", "Egypt", "Thailand"}, 1},
        {"How many sides does a hexagon have?", {"5", "7", "6", "8"}, 2},
        {"Which gas do plants absorb during photosynthesis?", {"Oxygen", "Nitrogen", "Helium", "Carbon dioxide"}, 3}
    }
};

void readLine(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        puts("Input ended. Goodbye!");
        exit(0);
    }
    size_t len = strlen(buffer);
    if (len && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
}

int getChoice(const char *prompt, int min, int max) {
    char line[100], extra;
    int number;
    for (;;) {
        printf("%s", prompt);
        readLine(line, sizeof(line));
        if (sscanf(line, " %d %c", &number, &extra) == 1 && number >= min && number <= max)
            return number;
        printf("Invalid input. Enter a number from %d to %d.\n", min, max);
    }
}

void readName(char *name) {
    for (;;) {
        printf("Enter student name: ");
        readLine(name, NAME_LENGTH);
        if (name[0] != '\0' && strspn(name, " ") != strlen(name) && strchr(name, '|') == NULL)
            return;
        puts("Enter a non-empty name without the | character.");
    }
}

void shuffleQuestions(int indices[], int count) {
    for (int i = 0; i < count; i++) indices[i] = i;
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
}

const char *gradeFor(int score, int total) {
    int percent = score * 100 / total;
    if (percent >= 80) return "Excellent";
    if (percent >= 60) return "Good";
    if (percent >= 40) return "Average";
    return "Needs Improvement";
}

void saveResult(const Result *result) {
    FILE *file = fopen(RESULT_FILE, "a");
    if (!file) {
        puts("Warning: Could not save the result.");
        return;
    }
    fprintf(file, "%s|%d|%d|%d\n", result->name, result->category, result->score, result->total);
    fclose(file);
    puts("Result saved to scores.txt.");
}

int loadResults(Result results[], int capacity) {
    FILE *file = fopen(RESULT_FILE, "r");
    if (!file) return 0;
    int count = 0;
    char line[256];
    while (count < capacity && fgets(line, sizeof(line), file)) {
        Result r;
        if (sscanf(line, "%49[^|]|%d|%d|%d", r.name, &r.category, &r.score, &r.total) == 4 &&
            r.category >= 0 && r.category < 3 && r.total > 0 && r.score >= 0 && r.score <= r.total)
            results[count++] = r;
    }
    fclose(file);
    return count;
}

void startQuiz(void) {
    Result result;
    readName(result.name);
    puts("\nSelect category:");
    for (int i = 0; i < 3; i++) printf("%d. %s\n", i + 1, categories[i]);
    result.category = getChoice("Category (1-3): ", 1, 3) - 1;
    result.score = 0;
    result.total = QUESTIONS_PER_QUIZ;
    int indices[QUESTIONS_PER_CATEGORY];
    shuffleQuestions(indices, QUESTIONS_PER_CATEGORY);
    for (int i = 0; i < QUESTIONS_PER_QUIZ; i++) {
        const Question *q = &bank[result.category][indices[i]];
        printf("\nQuestion %d/%d: %s\n", i + 1, QUESTIONS_PER_QUIZ, q->question);
        for (int j = 0; j < 4; j++) printf("%c. %s\n", 'A' + j, q->options[j]);
        int answer = getChoice("Answer (1=A, 2=B, 3=C, 4=D): ", 1, 4) - 1;
        if (answer == q->correct) {
            puts("Correct!");
            result.score++;
        } else printf("Incorrect. Correct answer: %c. %s\n", 'A' + q->correct, q->options[q->correct]);
    }
    printf("\n=== QUIZ RESULT ===\nStudent: %s\nCategory: %s\nScore: %d/%d\nPercentage: %.1f%%\nPerformance: %s\n",
           result.name, categories[result.category], result.score, result.total,
           100.0 * result.score / result.total, gradeFor(result.score, result.total));
    saveResult(&result);
}

void viewHistory(void) {
    Result results[MAX_RESULTS];
    int count = loadResults(results, MAX_RESULTS);
    if (!count) { puts("No saved results yet."); return; }
    puts("\n=== SCORE HISTORY (oldest first) ===");
    for (int i = 0; i < count; i++)
        printf("%d. %-20s | %-16s | %d/%d\n", i + 1, results[i].name,
               categories[results[i].category], results[i].score, results[i].total);
    if (count == MAX_RESULTS) puts("Only the first 500 saved results are displayed.");
}

int compareResults(const void *a, const void *b) {
    const Result *x = (const Result *)a, *y = (const Result *)b;
    long left = (long)x->score * y->total;
    long right = (long)y->score * x->total;
    if (left != right) return left < right ? 1 : -1;
    return strcmp(x->name, y->name);
}

void showLeaderboard(void) {
    Result results[MAX_RESULTS];
    int count = loadResults(results, MAX_RESULTS);
    if (!count) { puts("No saved results yet."); return; }
    qsort(results, (size_t)count, sizeof(Result), compareResults);
    puts("\n=== LEADERBOARD (top 10 attempts) ===");
    for (int i = 0; i < count && i < 10; i++)
        printf("%2d. %-20s | %-16s | %d/%d\n", i + 1, results[i].name,
               categories[results[i].category], results[i].score, results[i].total);
}

void instructions(void) {
    puts("\n=== INSTRUCTIONS ===");
    puts("1. Enter your name and choose one of three categories.");
    puts("2. Answer five randomly ordered multiple-choice questions.");
    puts("3. Enter 1=A, 2=B, 3=C or 4=D for each question.");
    puts("4. Each correct answer earns 1 mark; no negative marking.");
    puts("5. Results are saved locally in scores.txt.");
    puts("6. Leaderboard ranks attempts by percentage, then name.");
}

int main(void) {
    srand((unsigned int)time(NULL));
    for (;;) {
        puts("\n================================");
        puts("       QUIZ MANAGEMENT SYSTEM");
        puts("================================");
        puts("1. Start Quiz\n2. View Instructions\n3. View Score History\n4. View Leaderboard\n5. Exit");
        int choice = getChoice("Enter your choice (1-5): ", 1, 5);
        switch (choice) {
            case 1: startQuiz(); break;
            case 2: instructions(); break;
            case 3: viewHistory(); break;
            case 4: showLeaderboard(); break;
            case 5: puts("Thank you for using Quiz Management System!"); return 0;
        }
    }
}