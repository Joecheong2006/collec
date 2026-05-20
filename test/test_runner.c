#include "test.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <setjmp.h>

static double calculate_elapsed_seconds(struct timespec start, struct timespec end) {
    double seconds = (double)(end.tv_sec - start.tv_sec);
    double nanoseconds = (double)(end.tv_nsec - start.tv_nsec);
    
    // Convert nanoseconds to fractional seconds and combine
    return seconds + (nanoseconds / 1000000000.0);
}

static jmp_buf test_crash_anchor;
static volatile sig_atomic_t test_failed_flag = 0;

static void handle_assertion_crash(int signal_type) {
    (void)signal_type;
    test_failed_flag = 1;
    longjmp(test_crash_anchor, 1); 
}

static TestFuncNode *g_node = NULL;
static int total_tests = 0;

void register_test_func(TestFuncNode *node) {
    node->next = g_node;
    g_node = node;
    total_tests += 1;
}

int main() {
    signal(SIGABRT, handle_assertion_crash);

    printf("Test project %s\n", TEST_PROJECT_DIR);

    // Text helper vars
    const char *current_testing_filepath = "";
    const char *dots = "...........................";
    int total_width = strlen(dots);

    // Records trackers
    int nth_test = 1;
    int passed_tests = 0;
    int failed_tests = 0;

    // Capture global suite start time natively in C11
    struct timespec global_start, global_end;
    timespec_get(&global_start, TIME_UTC);

    TestFuncNode *current = g_node;
    while (current) {
        if (strcmp(current_testing_filepath, current->filename)) {
            current_testing_filepath = current->filename;
            printf("     Running tests from: %s\n", current_testing_filepath);
        }

        printf(" %d/%d Test #%d: %s %.*s",
                nth_test,
                total_tests,
                nth_test,
                current->funcName,
                (int)(total_width - strlen(current->funcName)), dots);

        nth_test += 1;

        test_failed_flag = 0;

        struct timespec test_start, test_end;
        timespec_get(&test_start, TIME_UTC);

        if (setjmp(test_crash_anchor) == 0) {
            current->func();
        }

        timespec_get(&test_end, TIME_UTC);
        double duration = calculate_elapsed_seconds(test_start, test_end);

        if (test_failed_flag) {
            printf(" ***Failed ");
            failed_tests += 1;
        } else {
            printf("    Passed ");
            passed_tests += 1;
        }

        printf(" %.2f sec\n", duration);

        current = current->next;
    }

    int passed_percentage = (total_tests > 0) ? 100.0 * ((float)passed_tests / total_tests) : 0;
    timespec_get(&global_end, TIME_UTC);
    double total_time = calculate_elapsed_seconds(global_start, global_end);

    printf("\n%d%% tests passed, ", passed_percentage);
    printf("%d tests failed out of %d\n", failed_tests, total_tests);
    printf("\nTotal Test time (real) = %.2f sec\n", total_time);

    return 0;
}
