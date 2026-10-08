#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PACKAGES 100
#define INPUT_SIZE 128

typedef struct {
    int id;
    double value;
    double weight;
    double ratio;
    double selected_weight;
} Package;

static Package packages[MAX_PACKAGES];
static int package_count = 0;
static double capacity = 0.0;
static double total_weight_used = 0.0;
static double maximum_value = 0.0;
static int ratios_ready = 0;
static int selection_ready = 0;

static int read_line(const char *prompt, char *buffer, size_t size)
{
    int character;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    if (buffer[0] != '\0' && buffer[strlen(buffer) - 1] != '\n') {
        while ((character = getchar()) != '\n' && character != EOF) {
        }
    }
    return 1;
}

static int read_integer(const char *prompt, int minimum, int maximum, int *result)
{
    char input[INPUT_SIZE];
    char *end;
    long value;

    for (;;) {
        if (!read_line(prompt, input, sizeof(input))) {
            return 0;
        }

        errno = 0;
        value = strtol(input, &end, 10);
        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (end != input && *end == '\0' && errno != ERANGE &&
            value >= minimum && value <= maximum) {
            *result = (int)value;
            return 1;
        }
        printf("Enter a whole number from %d to %d.\n", minimum, maximum);
    }
}

static int read_nonnegative_double(const char *prompt, double *result)
{
    char input[INPUT_SIZE];
    char *end;
    double value;

    for (;;) {
        if (!read_line(prompt, input, sizeof(input))) {
            return 0;
        }

        errno = 0;
        value = strtod(input, &end);
        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (end != input && *end == '\0' && errno != ERANGE &&
            isfinite(value) && value >= 0.0) {
            *result = value;
            return 1;
        }
        printf("Enter a finite number greater than or equal to zero.\n");
    }
}

static int read_positive_double(const char *prompt, double *result)
{
    double value;

    for (;;) {
        if (!read_nonnegative_double(prompt, &value)) {
            return 0;
        }
        if (value > 0.0) {
            *result = value;
            return 1;
        }
        printf("The value must be greater than zero.\n");
    }
}

static int compare_ratio_descending(const void *left, const void *right)
{
    const Package *first = (const Package *)left;
    const Package *second = (const Package *)right;

    if (first->ratio > second->ratio) {
        return -1;
    }
    if (first->ratio < second->ratio) {
        return 1;
    }
    return first->id - second->id;
}

static void calculate_ratios(void)
{
    int index;

    for (index = 0; index < package_count; index++) {
        packages[index].ratio = packages[index].value / packages[index].weight;
    }
    ratios_ready = 1;
}

static void sort_packages(void)
{
    if (!ratios_ready) {
        calculate_ratios();
    }
    qsort(packages, (size_t)package_count, sizeof(packages[0]),
          compare_ratio_descending);
    selection_ready = 0;
}

static int enter_package_details(void)
{
    int count;
    int index;
    char prompt[INPUT_SIZE];

    if (!read_integer("Number of packages (1-100): ", 1, MAX_PACKAGES, &count)) {
        return 0;
    }

    package_count = count;
    for (index = 0; index < package_count; index++) {
        packages[index].id = index + 1;
        packages[index].selected_weight = 0.0;

        snprintf(prompt, sizeof(prompt), "Value/profit of package %d: ", index + 1);
        if (!read_nonnegative_double(prompt, &packages[index].value)) {
            package_count = 0;
            return 0;
        }

        snprintf(prompt, sizeof(prompt), "Weight of package %d: ", index + 1);
        if (!read_positive_double(prompt, &packages[index].weight)) {
            package_count = 0;
            return 0;
        }
    }

    if (!read_positive_double("Vehicle capacity: ", &capacity)) {
        package_count = 0;
        return 0;
    }

    ratios_ready = 0;
    selection_ready = 0;
    total_weight_used = 0.0;
    maximum_value = 0.0;
    printf("Package details entered successfully.\n");
    return 1;
}

static int ensure_packages(void)
{
    if (package_count == 0) {
        printf("Enter package details first (menu option 1).\n");
        return 0;
    }
    return 1;
}

static void display_package_details(void)
{
    int index;

    if (!ensure_packages()) {
        return;
    }

    printf("\n%-10s %-14s %-14s", "Package", "Value", "Weight");
    if (ratios_ready) {
        printf(" %-14s", "Value/Weight");
    }
    printf("\n");

    for (index = 0; index < package_count; index++) {
        printf("%-10d %-14.2f %-14.2f", packages[index].id,
               packages[index].value, packages[index].weight);
        if (ratios_ready) {
            printf(" %-14.4f", packages[index].ratio);
        }
        printf("\n");
    }
    printf("Vehicle capacity: %.2f\n", capacity);
}

static void display_ratios(void)
{
    int index;

    if (!ensure_packages()) {
        return;
    }
    calculate_ratios();
    printf("\nValue/weight ratios:\n");
    for (index = 0; index < package_count; index++) {
        printf("Package %d: %.4f\n", packages[index].id, packages[index].ratio);
    }
}

static void display_sorted_packages(void)
{
    int index;

    if (!ensure_packages()) {
        return;
    }
    sort_packages();
    printf("\nPackages in decreasing value/weight ratio:\n");
    printf("%-10s %-14s %-14s %-14s\n", "Package", "Value", "Weight", "Ratio");
    for (index = 0; index < package_count; index++) {
        printf("%-10d %-14.2f %-14.2f %-14.4f\n", packages[index].id,
               packages[index].value, packages[index].weight,
               packages[index].ratio);
    }
}

static void find_maximum_value(void)
{
    int index;
    double remaining_capacity;

    if (!ensure_packages()) {
        return;
    }

    sort_packages();
    remaining_capacity = capacity;
    total_weight_used = 0.0;
    maximum_value = 0.0;
    for (index = 0; index < package_count; index++) {
        packages[index].selected_weight = 0.0;
        if (remaining_capacity <= 0.0) {
            break;
        }

        if (packages[index].weight <= remaining_capacity) {
            packages[index].selected_weight = packages[index].weight;
        } else {
            packages[index].selected_weight = remaining_capacity;
        }

        total_weight_used += packages[index].selected_weight;
        maximum_value += packages[index].selected_weight * packages[index].ratio;
        remaining_capacity -= packages[index].selected_weight;
    }

    selection_ready = 1;
    printf("\nMaximum value obtained: %.2f\n", maximum_value);
    printf("Total weight used: %.2f / %.2f\n", total_weight_used, capacity);
    printf("Time complexity: O(n log n) average for sorting with qsort, plus O(n) for selection.\n");
}

static void display_selected_packages(void)
{
    int index;

    if (!ensure_packages()) {
        return;
    }
    if (!selection_ready) {
        printf("Calculate the maximum value first (menu option 5).\n");
        return;
    }

    printf("\nSelected packages:\n");
    printf("%-10s %-14s %-16s %-14s %-14s\n", "Package", "Fraction",
           "Weight taken", "Value gained", "Selection");
    for (index = 0; index < package_count; index++) {
        if (packages[index].selected_weight > 0.0) {
            double fraction = packages[index].selected_weight / packages[index].weight;
            printf("%-10d %-14.4f %-16.2f %-14.2f %-14s\n",
                   packages[index].id, fraction, packages[index].selected_weight,
                   packages[index].selected_weight * packages[index].ratio,
                   fraction == 1.0 ? "Full" : "Fractional");
        }
    }
    printf("Total weight used: %.2f\n", total_weight_used);
    printf("Maximum value obtained: %.2f\n", maximum_value);
}

static void display_menu(void)
{
    printf("\n--- Smart Delivery Planning: Fractional Knapsack ---\n");
    printf("1. Enter Package Details\n");
    printf("2. Display Package Details\n");
    printf("3. Calculate Value/Weight Ratio\n");
    printf("4. Sort Packages by Ratio\n");
    printf("5. Find Maximum Value\n");
    printf("6. Display Selected Packages\n");
    printf("7. Exit\n");
}

int main(void)
{
    int choice;

    for (;;) {
        display_menu();
        if (!read_integer("Choose an option (1-7): ", 1, 7, &choice)) {
            printf("\nInput ended. Exiting.\n");
            return 0;
        }

        switch (choice) {
        case 1:
            if (!enter_package_details()) {
                printf("\nInput ended. Exiting.\n");
                return 0;
            }
            break;
        case 2:
            display_package_details();
            break;
        case 3:
            display_ratios();
            break;
        case 4:
            display_sorted_packages();
            break;
        case 5:
            find_maximum_value();
            break;
        case 6:
            display_selected_packages();
            break;
        case 7:
            printf("Exiting program.\n");
            return 0;
        }
    }
}
