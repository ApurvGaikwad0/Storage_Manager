#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "storage_mgr.h"
#include "dberror.h"
#include "test_helper.h"

/* Global test identifier for output messages */
char *testName;

/* Unified test file name definition */
#define TEST_PAGE_FILE "test_pagefile_v2.bin"

/* Function prototypes for test cases */
static void EnsureCapacity(void);
static void ReadWriteToLastBlock(void);


/* Main test orchestrator */
int main(void)
{
  testName = ""; // Reset test name for each case
  // Execute test cases sequentially
  EnsureCapacity();
  ReadWriteToLastBlock();
  return 0;
}

/* ====================================================================== */
/* TEST CASE 1: Capacity Validation and Extension Test */
/* ====================================================================== */
void EnsureCapacity(void)
{
  SM_FileHandle fileHandle;
  SM_PageHandle pageData;
  int index = 0; // Index variable for buffer operations

  testName = "Capacity Enforcement and Page Allocation Verification";
  
  // Allocate memory for page buffer
  pageData = (SM_PageHandle)malloc(PAGE_SIZE);

  /* -------------------- Phase 1: File Creation -------------------- */
  // Created new page file with initial capacity
  TEST_CHECK(createPageFile(TEST_PAGE_FILE));
  // Established file connection
  TEST_CHECK(openPageFile(TEST_PAGE_FILE, &fileHandle));
  printf("1. File creation and opening completed successfully\n");

  /* -------------------- Phase 2: Capacity Expansion -------------------- */
  // Requested minimum capacity of 10 pages
  TEST_CHECK(ensureCapacity(7, &fileHandle));
  // Verified total pages matches requested capacity
  ASSERT_TRUE((fileHandle.totalNumPages == 7), 
             "2. File expansion to 10-page capacity confirmed");

  /* -------------------- Phase 3: Data Verification -------------------- */
  // Generated test pattern for page population
  while(index < PAGE_SIZE) {
    // Created alternating pattern using capital letters
    pageData[index] = (index % 10) + 'Y'; // ASCII range: Z (90) to ] (93)
    index++;
  }
  
  // Wrote test pattern to last allocated page (index 6)
  int last_pg_num = fileHandle.totalNumPages - 1;
  TEST_CHECK(writeBlock(last_pg_num, &fileHandle, pageData));
  printf("3. Test pattern written to final page\n");

  /* -------------------- Phase 4: Data Validation -------------------- */
  // Reset index for validation loop
  index = 0;
  // Retrieved last page contents
  TEST_CHECK(readLastBlock(&fileHandle, pageData));
  
  // Verified data integrity in all page positions
  while(index < PAGE_SIZE) {
    ASSERT_TRUE((pageData[index] == (index % 10) + 'Y'), 
               "4. Data integrity check at last page");
    index++;
  }
  printf("4. Full page content validation completed successfully\n");

  /* -------------------- Phase 5: Resource Cleanup -------------------- */
  // Removed test file from storage
  TEST_CHECK(destroyPageFile(TEST_PAGE_FILE));
  // Released memory resources
  free(pageData);

  TEST_DONE();
}

/* ====================================================================== */
/* TEST CASE 2: Append Operations and Boundary Write Test */
/* ====================================================================== */
void ReadWriteToLastBlock(void)
{
  SM_FileHandle fileHandle;
  SM_PageHandle pageData;
  int index = 0; // Multi-purpose index variable
  int appendCount = 0; // Counter for append operations

  testName = "Append Functionality and Terminal Block Access Test";
  
  // Allocated page buffer memory
  pageData = (SM_PageHandle)malloc(PAGE_SIZE);

  /* -------------------- Phase 1: File Initialization -------------------- */
  // Created base page file structure
  TEST_CHECK(createPageFile(TEST_PAGE_FILE));
  // Opened file for extended operations
  TEST_CHECK(openPageFile(TEST_PAGE_FILE, &fileHandle));
  printf("1. Base file structure initialized successfully\n");

  /* -------------------- Phase 2: File Expansion -------------------- */
  // Performed 5 sequential append operations
  while(appendCount < 10) {
    TEST_CHECK(appendEmptyBlock(&fileHandle));
    appendCount++;
  }
  printf("2. Successfully appended %d empty pages\n", appendCount);

  /* -------------------- Phase 3: Terminal Write Test -------------------- */
  // Prepared distinctive data pattern
  while(index < PAGE_SIZE) {
    // Created alternating pattern using different capital letters
    pageData[index] = (index % 10) + 'S'; // ASCII range: X (88) to Y (89)
    index++;
  }
  
  int last_pg_num = fileHandle.totalNumPages - 1;
  // Wrote to last page (index 5 since 0-based: initial 1 + 5 appended)
  TEST_CHECK(writeBlock(last_pg_num, &fileHandle, pageData));
  printf("3. Unique pattern written to last page\n");

  /* -------------------- Phase 4: Readback Verification -------------------- */
  // Reset index for validation loop
  index = 0;
  // Accessed last page contents
  TEST_CHECK(readLastBlock(&fileHandle, pageData));
  
  // Confirmed pattern persistence in all byte positions
  while(index < PAGE_SIZE) {
    ASSERT_TRUE((pageData[index] == (index % 10) + 'S'), 
               "4. Data consistency check at last page");
    index++;
  }
  printf("4. Terminal page validation completed successfully\n");

  /* -------------------- Phase 5: Resource Management -------------------- */
  // Removed test artifact from filesystem
  TEST_CHECK(destroyPageFile(TEST_PAGE_FILE));
  // Released allocated memory
  free(pageData);

  TEST_DONE();
}