# Employee Salary Analysis System

A menu-driven **C program** for managing employee records and analyzing employee salaries using **Selection Sort** and **Insertion Sort**.

The project demonstrates basic data structures, sorting algorithms, searching, and time-complexity analysis.

## Features

* Add employee records
* Display all employee records
* Search an employee by ID
* Display employees department-wise
* Generate a salary report
* Sort employees using **Selection Sort**
* Sort employees using **Insertion Sort**
* Compare both sorting algorithms based on:

  * Number of comparisons
  * Number of data movements
* Analyze best, average, and worst-case complexities
* Analyze performance with increasing input size

## Employee Information

Each employee record contains:

* Employee ID
* Employee Name
* Salary
* Department
* Age

The program stores up to **100 employee records** using a C structure.

## Sorting Algorithms

### Selection Sort

Employees are sorted by salary in **descending order**.

**Time Complexity:**

| Case         | Complexity |
| ------------ | ---------- |
| Best Case    | O(n²)      |
| Average Case | O(n²)      |
| Worst Case   | O(n²)      |

### Insertion Sort

Employees are also sorted by salary in **descending order**.

**Time Complexity:**

| Case         | Complexity |
| ------------ | ---------- |
| Best Case    | O(n)       |
| Average Case | O(n²)      |
| Worst Case   | O(n²)      |

Both algorithms use **O(1) auxiliary space** in their sorting functions.

## Algorithm Comparison

The program calculates and displays:

* Number of comparisons
* Number of data movements

It then determines which algorithm performs fewer comparisons and movements for the given input.

## Increasing Input Size Analysis

The program tests both sorting algorithms with increasing numbers of employee records and displays their comparisons and movements.

This helps demonstrate how the performance of the algorithms changes as the input size increases.

## Menu

```text
1. Add Employee
2. Display Employees
3. Search Employee by ID
4. Department-wise Display
5. Salary Report
6. Sort using Selection Sort
7. Sort using Insertion Sort
8. Compare Selection Sort and Insertion Sort
9. Best/Average/Worst Case Analysis
10. Increasing Input Size Analysis
11. Exit
```

## Technologies Used

* **Language:** C
* **Concepts:** Structures, Arrays, Functions, Searching, Sorting
* **Algorithms:** Selection Sort, Insertion Sort

## How to Run

### 1. Clone the repository

```bash
git clone <your-repository-link>
```

### 2. Open the project folder

```bash
cd <project-folder>
```

### 3. Compile the program

Using GCC:

```bash
gcc employee_salary_analysis.c -o employee_salary_analysis
```

### 4. Run the program

**Windows:**

```bash
employee_salary_analysis.exe
```

**Linux/macOS:**

```bash
./employee_salary_analysis
```

## Learning Outcomes

Through this project, the following concepts are demonstrated:

* Using structures to store employee information
* Implementing searching and sorting algorithms
* Understanding Selection Sort and Insertion Sort
* Measuring comparisons and data movements
* Understanding best, average, and worst-case complexity
* Studying algorithm performance with increasing input size

## Conclusion

The **Employee Salary Analysis System** combines employee record management with sorting algorithm analysis. It provides a practical way to understand how **Selection Sort and Insertion Sort** behave with different input sizes and how their performance can be compared using comparisons and data movements.
