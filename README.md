# PS5: DNA Alignment

## Contact
Name: Vy Tran
Section: 201
Time to Complete: 5 hours
vtran1@student.uml.edu

## Statement of functionality of your program
Fully works with extra credit (Hirschberg).

## Experimental results

### CPU speed in MHz
Base frequency of 2.0 GHz and a maximum turbo frequency of 3.2 GHz

### Memory and time
- ecoli10000.txt
Execution time is 5.26501 seconds
Memory 472.7 MB

- ecoli20000.txt
Execution time is 20.9834 seconds
Memory 1.53 GB

- ecoli28284.txt
Execution time is 42.3181 seconds
Memory 3.03 GB

- ecoli50000.txt
Execution time is 137.361 seconds
Memory 9.93 GB

### Implementation
Hirschberg

### Array method
vector<vector<int>> matrix

### Operating system
macOS Ventura 13.1 (22C65)

### CPU type
Apple M1

## Key features or algorithms used
This program utilizes Hirschberg's algorithm for computing the edit distance between two strings with linear space complexity, employing dynamic programming for optimal substructure calculation and traceback for alignment reconstruction.

## Extra credit
Used Hirschberg algorithm and ran on a larger input (ecoli50000.txt)
