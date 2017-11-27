// IMPORTANT: this file is only to be included into drivers.cpp and nowhere else
void Runner_ai::parallelSort(int *comparer, int *latched, int size) {
    int i, j;

    for (i = 0; i < size - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < size - i - 1; j++) {
            if (comparer[j] < comparer[j + 1]) {
                swap(&comparer[j], &comparer[j + 1]);
                swap(&latched[j], &latched[j + 1]);
            }
        }
    }
}
