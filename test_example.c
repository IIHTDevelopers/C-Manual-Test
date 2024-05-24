#include <stdio.h>

/* Include MinUnit */
#include "minunit.h"

int tests_run = 0;

/* Sample functions to be tested */
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

/* Test case for add() function */
static char * test_add() {
    mu_assert("error, add(2, 2) != 4", add(2, 2) == 4);
    mu_assert("error, add(0, 0) != 0", add(0, 0) == 0);
    mu_assert("error, add(-1, 1) != 0", add(-1, 1) == 0);
    return 0;
}

/* Test case for subtract() function */
static char * test_subtract() {
    mu_assert("error, subtract(2, 2) != 0", subtract(2, 2) == 0);
    mu_assert("error, subtract(2, 0) != 2", subtract(2, 0) == 2);
    mu_assert("error, subtract(0, 2) != -2", subtract(0, 2) == -2);
    return 0;
}

/* Test case for multiply() function */
static char * test_multiply() {
    mu_assert("error, multiply(2, 2) != 4", multiply(2, 2) == 4);
    mu_assert("error, multiply(2, 0) != 0", multiply(2, 0) == 0);
    mu_assert("error, multiply(-1, 2) != -2", multiply(-1, 2) == -2);
    return 0;
}

/* Main function to run the tests */
static char * all_tests() {
    mu_run_test(test_add);
    mu_run_test(test_subtract);
    mu_run_test(test_multiply);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
