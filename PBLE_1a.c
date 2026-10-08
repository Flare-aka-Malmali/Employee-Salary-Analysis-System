#include <stdio.h>

#define MAX 100

// Structure to store package details
struct Package
{
    int id;
    float value;
    float weight;
    float ratio;
    float selected;
};

// Function to calculate value/weight ratio
void calculateRatio(struct Package p[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        p[i].ratio = p[i].value / p[i].weight;
    }

    printf("\nValue/Weight ratios calculated successfully.\n");
}

// Function to sort packages by ratio in decreasing order
void sortPackages(struct Package p[], int n)
{
    int i, j;
    struct Package temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].ratio < p[j + 1].ratio)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    printf("\nPackages sorted by Value/Weight ratio.\n");
}

// Function to display package details
void displayPackages(struct Package p[], int n)
{
    int i;

    printf("\n--------------------------------------------------\n");
    printf("ID\tValue\tWeight\tRatio\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].id,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
}

// Function to find maximum value
void findMaximumValue(struct Package p[], int n, float capacity)
{
    int i;
    float remainingCapacity = capacity;
    float totalValue = 0;
    float totalWeight = 0;

    // Reset selected quantity
    for (i = 0; i < n; i++)
    {
        p[i].selected = 0;
    }

    for (i = 0; i < n; i++)
    {
        if (remainingCapacity == 0)
        {
            break;
        }

        // Take the complete package
        if (p[i].weight <= remainingCapacity)
        {
            p[i].selected = 1;

            remainingCapacity = remainingCapacity - p[i].weight;
            totalWeight = totalWeight + p[i].weight;
            totalValue = totalValue + p[i].value;
        }

        // Take only a fraction of the package
        else
        {
            p[i].selected = remainingCapacity / p[i].weight;

            totalWeight = totalWeight + remainingCapacity;
            totalValue = totalValue + (p[i].ratio * remainingCapacity);

            remainingCapacity = 0;
        }
    }

    printf("\nMaximum Value = %.2f\n", totalValue);
    printf("Total Weight Used = %.2f\n", totalWeight);
}

// Function to display selected packages
void displaySelected(struct Package p[], int n)
{
    int i;

    printf("\n--------------------------------------------------\n");
    printf("Package\tFraction Selected\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (p[i].selected > 0)
        {
            printf("%d\t%.2f\n", p[i].id, p[i].selected);
        }
    }
}

int main()
{
    struct Package p[MAX];

    int n;
    int choice;
    int i;

    float capacity;

    printf("===== FRACTIONAL KNAPSACK =====\n");

    printf("\nEnter number of packages: ");
    scanf("%d", &n);

    // Enter package details
    for (i = 0; i < n; i++)
    {
        p[i].id = i + 1;

        printf("\nEnter value of package %d: ", i + 1);
        scanf("%f", &p[i].value);

        printf("Enter weight of package %d: ", i + 1);
        scanf("%f", &p[i].weight);

        p[i].ratio = 0;
        p[i].selected = 0;
    }

    printf("\nEnter vehicle capacity: ");
    scanf("%f", &capacity);

    // Menu
    do
    {
        printf("\n\n========== MENU ==========\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nPackage details were already entered.\n");
                break;

            case 2:
                displayPackages(p, n);
                break;

            case 3:
                calculateRatio(p, n);
                break;

            case 4:
                sortPackages(p, n);
                break;

            case 5:
                findMaximumValue(p, n, capacity);
                break;

            case 6:
                displaySelected(p, n);
                break;

            case 7:
                printf("\nProgram ended.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}