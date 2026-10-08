#include <stdio.h>
#include <string.h>

#define MAX 100

struct Employee
{
    int id;
    char name[50];
    float salary;
    char department[30];
    int age;
};

struct Employee emp[MAX];
int n = 0;


/* Add Employee */
void addEmployee()
{
    if (n >= MAX)
    {
        printf("\nEmployee limit reached!\n");
        return;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &emp[n].id);

    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp[n].name);

    printf("Enter Salary: ");
    scanf("%f", &emp[n].salary);

    printf("Enter Department: ");
    scanf(" %[^\n]", emp[n].department);

    printf("Enter Age: ");
    scanf("%d", &emp[n].age);

    n++;

    printf("\nEmployee added successfully!\n");
}


/* Display Employees */
void displayEmployees()
{
    int i;

    if (n == 0)
    {
        printf("\nNo employee records available!\n");
        return;
    }

    printf("\n================ EMPLOYEE RECORDS ================\n");

    printf("%-8s %-18s %-12s %-18s %-5s\n",
           "ID", "Name", "Salary", "Department", "Age");

    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%-8d %-18s %-12.2f %-18s %-5d\n",
               emp[i].id,
               emp[i].name,
               emp[i].salary,
               emp[i].department,
               emp[i].age);
    }

    printf("---------------------------------------------------------------\n");
}


/* Search Employee */
void searchEmployee()
{
    int id;
    int i;

    if (n == 0)
    {
        printf("\nNo employee records available!\n");
        return;
    }

    printf("\nEnter Employee ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < n; i++)
    {
        if (emp[i].id == id)
        {
            printf("\n========== EMPLOYEE FOUND ==========\n");
            printf("ID         : %d\n", emp[i].id);
            printf("Name       : %s\n", emp[i].name);
            printf("Salary     : %.2f\n", emp[i].salary);
            printf("Department : %s\n", emp[i].department);
            printf("Age        : %d\n", emp[i].age);
            printf("====================================\n");

            return;
        }
    }

    printf("\nEmployee not found!\n");
}


/* Department-wise Display */
void departmentDisplay()
{
    char department[30];
    int i;
    int found = 0;

    if (n == 0)
    {
        printf("\nNo employee records available!\n");
        return;
    }

    printf("\nEnter Department: ");
    scanf(" %[^\n]", department);

    printf("\n========== %s DEPARTMENT ==========\n", department);

    printf("%-8s %-18s %-12s %-5s\n",
           "ID", "Name", "Salary", "Age");

    printf("-----------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (strcmp(emp[i].department, department) == 0)
        {
            printf("%-8d %-18s %-12.2f %-5d\n",
                   emp[i].id,
                   emp[i].name,
                   emp[i].salary,
                   emp[i].age);

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No employees found in this department.\n");
    }

    printf("-----------------------------------------------\n");
}


/* Salary Report */
void salaryReport()
{
    struct Employee temp[MAX];
    struct Employee swap;
    int i;
    int j;

    if (n == 0)
    {
        printf("\nNo employee records available!\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        temp[i] = emp[i];
    }

    /* Sort by salary - highest to lowest */
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (temp[i].salary < temp[j].salary)
            {
                swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
        }
    }

    printf("\n================ SALARY REPORT ================\n");

    printf("%-8s %-8s %-18s %-12s\n",
           "Rank", "ID", "Name", "Salary");

    printf("------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%-8d %-8d %-18s %-12.2f\n",
               i + 1,
               temp[i].id,
               temp[i].name,
               temp[i].salary);
    }

    printf("------------------------------------------------\n");
}


/* Selection Sort */
void selectionSort(struct Employee arr[], int size,
                   long *comparisons, long *movements)
{
    int i;
    int j;
    int maxIndex;
    struct Employee temp;

    *comparisons = 0;
    *movements = 0;

    for (i = 0; i < size - 1; i++)
    {
        maxIndex = i;

        for (j = i + 1; j < size; j++)
        {
            (*comparisons)++;

            if (arr[j].salary > arr[maxIndex].salary)
            {
                maxIndex = j;
            }
        }

        if (maxIndex != i)
        {
            temp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = temp;

            *movements = *movements + 3;
        }
    }
}


/* Insertion Sort */
void insertionSort(struct Employee arr[], int size,
                   long *comparisons, long *movements)
{
    int i;
    int j;
    struct Employee key;

    *comparisons = 0;
    *movements = 0;

    for (i = 1; i < size; i++)
    {
        key = arr[i];
        (*movements)++;

        j = i - 1;

        while (j >= 0)
        {
            (*comparisons)++;

            if (arr[j].salary < key.salary)
            {
                arr[j + 1] = arr[j];
                (*movements)++;
                j--;
            }
            else
            {
                break;
            }
        }

        arr[j + 1] = key;
        (*movements)++;
    }
}


/* Sort using Selection Sort */
void performSelectionSort()
{
    long comparisons;
    long movements;

    if (n == 0)
    {
        printf("\nNo employee records available!\n");
        return;
    }

    selectionSort(emp, n, &comparisons, &movements);

    printf("\n========== SELECTION SORT ==========\n");
    printf("Number of Records : %d\n", n);
    printf("Comparisons       : %ld\n", comparisons);
    printf("Data Movements    : %ld\n", movements);
    printf("Sorting Order     : Highest Salary to Lowest\n");
    printf("====================================\n");

    displayEmployees();
}


/* Sort using Insertion Sort */
void performInsertionSort()
{
    long comparisons;
    long movements;

    if (n == 0)
    {
        printf("\nNo employee records available!\n");
        return;
    }

    insertionSort(emp, n, &comparisons, &movements);

    printf("\n========== INSERTION SORT ==========\n");
    printf("Number of Records : %d\n", n);
    printf("Comparisons       : %ld\n", comparisons);
    printf("Data Movements    : %ld\n", movements);
    printf("Sorting Order     : Highest Salary to Lowest\n");
    printf("====================================\n");

    displayEmployees();
}


/* Compare Selection Sort and Insertion Sort */
void compareSorts()
{
    struct Employee selectionArray[MAX];
    struct Employee insertionArray[MAX];

    long selectionComparisons;
    long selectionMovements;

    long insertionComparisons;
    long insertionMovements;

    int i;

    if (n == 0)
    {
        printf("\nNo employee records available!\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        selectionArray[i] = emp[i];
        insertionArray[i] = emp[i];
    }

    selectionSort(selectionArray, n,
                  &selectionComparisons,
                  &selectionMovements);

    insertionSort(insertionArray, n,
                  &insertionComparisons,
                  &insertionMovements);

    printf("\n========== SORT COMPARISON ==========\n");

    printf("%-25s %-15s %-15s\n",
           "Algorithm", "Comparisons", "Movements");

    printf("----------------------------------------------------------\n");

    printf("%-25s %-15ld %-15ld\n",
           "Selection Sort",
           selectionComparisons,
           selectionMovements);

    printf("%-25s %-15ld %-15ld\n",
           "Insertion Sort",
           insertionComparisons,
           insertionMovements);

    printf("----------------------------------------------------------\n");

    if (selectionComparisons < insertionComparisons)
    {
        printf("Selection Sort used fewer comparisons.\n");
    }
    else if (selectionComparisons > insertionComparisons)
    {
        printf("Insertion Sort used fewer comparisons.\n");
    }
    else
    {
        printf("Both used the same number of comparisons.\n");
    }

    if (selectionMovements < insertionMovements)
    {
        printf("Selection Sort used fewer movements.\n");
    }
    else if (selectionMovements > insertionMovements)
    {
        printf("Insertion Sort used fewer movements.\n");
    }
    else
    {
        printf("Both used the same number of movements.\n");
    }
}


/* Best, Average and Worst Case Analysis */
void caseAnalysis()
{
    int size;

    if (n == 0)
    {
        printf("\nNo employee records available!\n");
        return;
    }

    size = n;

    printf("\n========== BEST / AVERAGE / WORST CASE ==========\n");

    printf("\nSELECTION SORT\n");
    printf("----------------------------------------\n");

    printf("Best Case     : O(n^2)\n");
    printf("Average Case  : O(n^2)\n");
    printf("Worst Case    : O(n^2)\n");

    printf("Comparisons   : %d in all cases\n",
           size * (size - 1) / 2);

    printf("\nINSERTION SORT\n");
    printf("----------------------------------------\n");

    printf("Best Case     : O(n)\n");
    printf("Average Case  : O(n^2)\n");
    printf("Worst Case    : O(n^2)\n");

    printf("\nSPACE COMPLEXITY\n");
    printf("----------------------------------------\n");
    printf("Selection Sort : O(1)\n");
    printf("Insertion Sort : O(1)\n");

    printf("\nObservation:\n");
    printf("Selection Sort performs O(n^2) comparisons\n");
    printf("in all cases.\n");

    printf("Insertion Sort performs best when the data\n");
    printf("is already sorted.\n");
}


/* Increasing Input Size Analysis */
void increasingInputSize()
{
    struct Employee selectionArray[MAX];
    struct Employee insertionArray[MAX];

    long selectionComparisons;
    long selectionMovements;

    long insertionComparisons;
    long insertionMovements;

    int size;
    int i;

    if (n < 2)
    {
        printf("\nPlease add at least 2 employees first.\n");
        return;
    }

    printf("\n========== INCREASING INPUT SIZE ANALYSIS ==========\n");

    printf("\n%-10s %-18s %-18s %-18s %-18s\n",
           "Records",
           "Selection Comp.",
           "Selection Move.",
           "Insertion Comp.",
           "Insertion Move.");

    printf("-------------------------------------------------------------------------------\n");

    for (size = 2; size <= n; size = size + 2)
    {
        for (i = 0; i < size; i++)
        {
            selectionArray[i] = emp[i];
            insertionArray[i] = emp[i];
        }

        selectionSort(selectionArray,
                      size,
                      &selectionComparisons,
                      &selectionMovements);

        insertionSort(insertionArray,
                      size,
                      &insertionComparisons,
                      &insertionMovements);

        printf("%-10d %-18ld %-18ld %-18ld %-18ld\n",
               size,
               selectionComparisons,
               selectionMovements,
               insertionComparisons,
               insertionMovements);
    }

    if (n % 2 != 0)
    {
        for (i = 0; i < n; i++)
        {
            selectionArray[i] = emp[i];
            insertionArray[i] = emp[i];
        }

        selectionSort(selectionArray,
                      n,
                      &selectionComparisons,
                      &selectionMovements);

        insertionSort(insertionArray,
                      n,
                      &insertionComparisons,
                      &insertionMovements);

        printf("%-10d %-18ld %-18ld %-18ld %-18ld\n",
               n,
               selectionComparisons,
               selectionMovements,
               insertionComparisons,
               insertionMovements);
    }

    printf("-------------------------------------------------------------------------------\n");

    printf("\nObservation:\n");
    printf("As input size increases, comparisons increase.\n");
    printf("Selection Sort and Insertion Sort have O(n^2)\n");
    printf("average and worst-case time complexity.\n");
}


/* MAIN FUNCTION */
int main()
{
    int choice;

    do
    {
        printf("\n\n============================================================\n");
        printf("             EMPLOYEE SALARY ANALYSIS SYSTEM\n");
        printf("============================================================\n");

        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Department-wise Display\n");
        printf("5. Salary Report\n");
        printf("6. Sort using Selection Sort\n");
        printf("7. Sort using Insertion Sort\n");
        printf("8. Compare Selection Sort and Insertion Sort\n");
        printf("9. Best/Average/Worst Case Analysis\n");
        printf("10. Increasing Input Size Analysis\n");
        printf("11. Exit\n");

        printf("============================================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                departmentDisplay();
                break;

            case 5:
                salaryReport();
                break;

            case 6:
                performSelectionSort();
                break;

            case 7:
                performInsertionSort();
                break;

            case 8:
                compareSorts();
                break;

            case 9:
                caseAnalysis();
                break;

            case 10:
                increasingInputSize();
                break;

            case 11:
                printf("\nThank you for using Employee Salary Analysis System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 11);

    return 0;
}
