#include <stdio.h>

#define MAX 100

/* Utility: Bubble Sort if input is unsorted */
void bubbleSort(int a[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

/* Check whether array is sorted */
int isSorted(int a[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1])
            return 0;
    }
    return 1;
}

/* Linear Search */
int linearSearch(int a[], int n, int key, int *comparisons) {
    int i;
    *comparisons = 0;

    for (i = 0; i < n; i++) {
        (*comparisons)++;
        if (a[i] == key)
            return i;
    }
    return -1;
}

/* Iterative Binary Search (Returns First Occurrence) */
int binarySearchIterative(int a[], int n, int key, int *comparisons) {
    int low = 0, high = n - 1, mid;
    int result = -1;
    *comparisons = 0;

    while (low <= high) {
        mid = low + (high - low) / 2;
        printf("low = %d, high = %d, mid = %d\n", low, high, mid);

        (*comparisons)++;
        if (a[mid] == key) {
            result = mid;     /* Record match, continue searching left for first occurrence */
            high = mid - 1;
        } else if (a[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

/* Recursive Binary Search (Returns First Occurrence) */
int binarySearchRecursive(int a[], int low, int high, int key, int *comparisons) {
    int mid;

    if (low > high)
        return -1;

    mid = low + (high - low) / 2;
    printf("low = %d, high = %d, mid = %d\n", low, high, mid);
    (*comparisons)++;

    if (a[mid] == key) {
        if (mid == 0) return mid;
        
        (*comparisons)++; /* Count comparison for checking duplicate on the left */
        if (a[mid - 1] != key) {
            return mid;
        }
        return binarySearchRecursive(a, low, mid - 1, key, comparisons);
    } else if (key < a[mid]) {
        return binarySearchRecursive(a, low, mid - 1, key, comparisons);
    } else {
        return binarySearchRecursive(a, mid + 1, high, key, comparisons);
    }
}

/* Display array */
void display(int a[], int n) {
    int i;
    printf("\nRecords: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[MAX];
    int n, i, choice, key, result, comparisons;

    printf("Enter number of records: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid record count.\n");
        return 1;
    }

    printf("Enter records:\n");
    for (i = 0; i < n; i++) {
        printf("Record %d: ", i);
        fflush(stdout);
        scanf("%d", &a[i]);
    }

    /* Check and enforce sorted condition */
    if (!isSorted(a, n)) {
        printf("\n[Validation] Records were NOT sorted. Automatically sorting using Bubble Sort...\n");
        bubbleSort(a, n);
    } else {
        printf("\n[Validation] Records are verified as sorted.\n");
    }

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Display Records\n");
        printf("2. Iterative Binary Search\n");
        printf("3. Recursive Binary Search\n");
        printf("4. Linear Search\n");
        printf("5. Exit\n");
        printf("===========================\n");
        printf("Enter your choice: ");
        fflush(stdout);
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                display(a, n);
                break;

            case 2:
                printf("Enter value to search: ");
                fflush(stdout);
                scanf("%d", &key);
                printf("\n--- Iterative Binary Search ---\n");
                result = binarySearchIterative(a, n, key, &comparisons);
                if (result != -1)
                    printf("Result: Found at index %d (Value = %d)\n", result, a[result]);
                else
                    printf("Result: Record NOT found.\n");
                printf("Comparisons = %d\n", comparisons);
                break;

            case 3:
                printf("Enter value to search: ");
                fflush(stdout);
                scanf("%d", &key);
                comparisons = 0;
                printf("\n--- Recursive Binary Search ---\n");
                result = binarySearchRecursive(a, 0, n - 1, key, &comparisons);
                if (result != -1)
                    printf("Result: Found at index %d (Value = %d)\n", result, a[result]);
                else
                    printf("Result: Record NOT found.\n");
                printf("Comparisons = %d\n", comparisons);
                break;

            case 4:
                printf("Enter value to search: ");
                fflush(stdout);
                scanf("%d", &key);
                printf("\n--- Linear Search ---\n");
                result = linearSearch(a, n, key, &comparisons);
                if (result != -1)
                    printf("Result: Found at index %d (Value = %d)\n", result, a[result]);
                else
                    printf("Result: Record NOT found.\n");
                printf("Comparisons = %d\n", comparisons);
                break;

            case 5:
                printf("\nProgram ended successfully.\n");
                break;

            default:
                printf("\nInvalid choice! Please select 1-5.\n");
        }
    } while (choice != 5);

    return 0;
}
