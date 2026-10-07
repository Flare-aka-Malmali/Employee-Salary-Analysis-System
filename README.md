# EmpRank: Employee Salary Analysis System

<p align="center">
  <img src="https://img.shields.io/badge/C-Programming-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Programming" />
  <img src="https://img.shields.io/badge/Project-EmpRank-0A84FF?style=for-the-badge" alt="EmpRank" />
  <img src="https://img.shields.io/badge/Status-Ready-28A745?style=for-the-badge" alt="Ready" />
</p>

EmpRank is a simple C-based employee management and salary analysis program. It helps store employee details, search records, filter by department, rank employees by salary, and compare sorting algorithms such as Selection Sort and Insertion Sort.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [How to Run](#how-to-run)
- [Program Menu](#program-menu)
- [Example Workflow](#example-workflow)
- [Sorting Analysis](#sorting-analysis)
- [Notes](#notes)

## Overview

This project simulates an employee record system with analytical features. It is useful for learning:

- C arrays and structures
- File-less in-memory data storage
- Searching and filtering records
- Sorting salary data
- Time complexity comparison for algorithm analysis

<details>
<summary><strong>Click to see the system in action</strong></summary>

The program provides a menu-driven console UI where users can perform operations like:

- Add employees
- Display all records
- Search by employee ID
- View employees in a department
- Generate salary ranking
- Compare sorting techniques
- Analyze algorithm performance

</details>

## Features

- Add employee records with ID, name, salary, department, and age
- View all employees in a formatted table
- Search an employee by ID
- Display employees department-wise
- Generate salary report ranked from highest to lowest
- Sort records using Selection Sort and Insertion Sort
- Compare sorting metrics like comparisons and data movements
- Analyze best, average, and worst-case complexity
- Evaluate increasing input sizes

## Project Structure

```text
MiniProjectAOA/
├── EmpRank.c
├── EmpRank.exe
├── README.md
└── .git/
```

## How to Run

### Windows

1. Open Command Prompt or PowerShell in the project folder.
2. Compile the C program:

```bash
gcc EmpRank.c -o EmpRank
```

3. Run the program:

```bash
EmpRank.exe
```

### Alternative

If you are already using the compiled executable, simply run:

```bash
./EmpRank.exe
```

## Program Menu

```text
============================================================
             EMPLOYEE SALARY ANALYSIS SYSTEM
============================================================
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
============================================================
```

## Example Workflow

<details>
<summary><strong>Example: Add and rank employees</strong></summary>

1. Choose option `1` to add an employee.
2. Enter the employee ID, name, salary, department, and age.
3. Repeat to add multiple employees.
4. Choose option `5` to view the salary report.
5. Choose option `6` or `7` to sort data using a chosen algorithm.
6. Use option `8` to compare both algorithms.

</details>

## Sorting Analysis

The project compares two sorting methods:

- Selection Sort
- Insertion Sort

### Metrics tracked

- Number of comparisons
- Number of data movements
- Sorting order by descending salary

### Complexity summary

| Algorithm | Best Case | Average Case | Worst Case | Space |
|----------|-----------|--------------|------------|-------|
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) |

## Notes

- The current project stores data in memory while the program is running.
- It does not persist records to a file.
- This is a beginner-friendly project for learning C programming and algorithm analysis.

## Quick Start Demo

```bash
gcc EmpRank.c -o EmpRank
./EmpRank
```

Then choose a menu option and explore the employee database.

---

<p align="center">
  <b>Built with C • Designed for employee data analysis</b>
</p>
