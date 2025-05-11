# Storage Manager - CS525 Group 04

# Overview
The Storage Manager is a module designed for efficient page file management. It provides functionality for creating, opening, closing, and deleting page files, as well as reading from and writing to these files. The manager works with fixed-size pages and maintains essential file information.

## How to Compile and Run the Code
This repository contains the implementation of a simple storage manager for handling page files. To compile and run the code using the provided Makefile, follow these steps:

### Compilation
1. Open a terminal in the project directory.
2. Run the following command to compile the test cases:
   ```
   make
   ```
   This will generate the executables `test_assign1` and `test_assign2`.

### Running Test Cases
After compilation, run the tests as follows:

- To run `test_assign1`:
  ```
  ./test_assign1
  ```
- To run `test_assign2` (which includes additional test cases):
  ```
  ./test_assign2
  ```

To clean compiled binaries, use:
```
make clean
```

---

## Overview of `storage_mgr.c`
The `storage_mgr.c` file contains functions that implement the core functionalities of the storage manager. Below are the key functions:

### 1. `initStorageManager()`
   - Purpose: Initializes the storage manager.
   - Key Feature: Prints a success message indicating initialization.

### 2. `createPageFile(char *fileName)`
   - Purpose: Creates a new page file with a single empty page.
   - Key Feature: Initializes the page with '\0' characters and sets the file size to PAGE_SIZE.

### 3. `openPageFile(char *fileName, SM_FileHandle *fHandle)`
   - Purpose: Opens an existing page file and sets the file handle.
   - Key Feature: Retrieves total number of pages and current position.

### 4. `closePageFile(SM_FileHandle *fHandle)`
   - Purpose: Closes an open file.
   - Key Feature: Uses `fclose()` to close the file.

### 5. `destroyPageFile(char *fileName)`
   - Purpose: Deletes a page file from the file system.
   - Key Feature: Uses `remove()` to delete the file.

### 6. `readBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)`
   - Purpose: Reads a specific page from the file into memory.
   - Key Feature: Ensures the page exists before reading.

### 7. `writeBlock(int pageNum, SM_FileHandle *fHandle, SM_PageHandle memPage)`
   - Purpose: Writes data to a specific page.
   - Key Feature: Moves file pointer and writes data.

### 8. `appendEmptyBlock(SM_FileHandle *fHandle)`
   - Purpose: Adds a new empty page to the file.
   - Key Feature: Ensures the new page is properly initialized.

### 9. `ensureCapacity(int numberOfPages, SM_FileHandle *fHandle)`
   - Purpose: Ensures that the file has at least the specified number of pages.
   - Key Feature: Appends empty blocks if needed.

---
## Data Structures
### SM_FileHandle
   Represents an open file with the following attributes:
⁠   char *fileName ⁠: The name of the file.
⁠   int totalNumPages ⁠: Total number of pages in the file.
⁠   int curPagePos ⁠: Current position in the file.
⁠   void *mgmtInfo ⁠: Additional management information (e.g., file descriptor).

### SM_PageHandle
    A pointer to a memory block used to store the contents of a page.

## Overview of `test_assign1_2.c`
The file `test_assign1_2.c` is an additional test case file created to verify the robustness of the storage manager. It contains:

- **EnsureCapacity Test**: Checks if `ensureCapacity()` properly extends the file.
- **ReadWriteToLastBlock Test**: Verifies reading and writing operations on the last block.
- **Custom Scenarios**: Additional scenarios for validating file management functionalities.

To execute this test file, compile and run:
```
make
./test_assign2
```

---

## Contributors
| Name                 | CWID       | Contribution (%) | Contribution Description |
|----------------------|-----------|-----------------|--------------------------|
| Apurv Gaikwad       | A20569178  | 33.33%         | Contributed to the development of `storage_mgr.c`, `Makefile`, `test_assign1_2.c`, and this `README.txt`. Worked on file handling, testing, and documentation. |
| Nishant Uday Dalvi  | A20556507  | 33.33%         | Collaborated on the implementation of `storage_mgr.c`, structured `Makefile`, designed `test_assign1_2.c`, and contributed to documentation. |
| Satyam Borade       | A20586631  | 33.33%         | Assisted in coding `storage_mgr.c`, refining `Makefile`, validating `test_assign1_2.c`, and co-writing the `README.txt`. |

---


