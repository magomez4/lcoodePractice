// USING QSORT WITH A CUSTOM COMPARISON FOR
// A 2D ARRAY

int compareLogs(const void* a, const void* b)
{
    // compares logs based on the first 
    // element
    // cast the elements into a row-type (int*)
    int* logA = *(int**)a;
    int* logB = *(int**)b;
    // comparelogs needs to return 1 if a goes after b
    // 0 if they are equal
    // -1 if a goes before b
    // For sorting in increasing order, you can reduce
    // it to a ">" operator which will return true (1) if
    // "a" is greater than "b", meaning a goes after b
    return (logA[0] > logB[0]);

}

// update this file to have other options of comparator
// like for sorting a 1D array

void sortLogs(int** logs, int logsSize, int* logsColSize) {
    // QSORT SIGNATURE:
    // pointer to array logs, size of array, size of each row (each
    // row is a pointer to int because they are arrays), name of
    // comparator function.
    qsort(logs, logsSize, sizeof(int*), compareLogs);
}