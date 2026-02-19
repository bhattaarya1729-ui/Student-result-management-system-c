# Student-result-management-system-c
Menu-driven Student Result Management System in C. Calculates total, percentage, grade, rank (with tie handling), pass/fail status, subject toppers, class statistics, and exports results to a file using dynamic memory and structured programming. 
# Student Result Management System (C)

A console-based Student Result Management System written in C.  
This program manages student academic records, calculates grades and rankings, generates class statistics, and saves results to a file.

---

## Features

- Dynamic student record handling using malloc
- Input validation for marks (0–100)
- Automatic calculation of:
  - Total marks
  - Percentage
  - Pass/Fail status
  - Grade and remarks
- Ranking system with tie handling
- Subject toppers (English, Maths, IP)
- Class statistics (average, highest, lowest, pass/fail count)
- Saves results to `results.txt`

---

## Grading Criteria

| Percentage | Grade |
|------------|-------|
| 90+        | A     |
| 75–89      | B     |
| 60–74      | C     |
| 40–59      | D     |
| Below 40   | F     |

A student must score:
- At least 33 marks in each subject
- At least 40% overall
to be considered Pass.

---

## Technologies Used

- C Programming Language
- Structures
- Pointers
- Dynamic Memory Allocation
- File Handling
- Sorting (Bubble Sort)
- String Handling

---

## How to Compile and Run

### Compile:
```
gcc filename.c -o result
```

### Run:
```
./result
```

---

## Output Includes

- Ranked result table
- Grade and remarks
- Class statistics
- Subject toppers
- Exported file: `results.txt`

---

## Future Improvements

- Add more subjects dynamically
- Replace bubble sort with more efficient sorting
- Store data permanently using file-based database
- Add search and update student functionality
- Convert into a modular multi-file project

---

## Author

Aarya Bhatt
