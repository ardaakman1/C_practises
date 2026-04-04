#include <stdio.h>
// O(n * logn) omega(n * logn)
void merge_sort(int numbers[], int min, int max);
void merge(int numbers[], int min, int mid, int max);

int main(void)
{
    int size;
    printf("\nPlease enter the element number: ");
    scanf("%d", &size);
    int numbers[size];
    for (int i = 0; i < size; i++)
    {
        printf("numbers[%d]: ", i);
        scanf("%d", &numbers[i]);
    }

    merge_sort(numbers, 0, size - 1);
    printf("\nSorted list:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", numbers[i]);
    }
    printf("\n");

    return 0;
}

// Part 1 (Recursive Splitter)
void merge_sort(int numbers[], int min, int max)
{
    if (min < max) // if min >= max, there is only 1 element there stop
    {
        int mid = (min + max) / 2;

        // Sort left part
        merge_sort(numbers, min, mid);
        
        // Sort right part
        merge_sort(numbers, mid + 1, max);

        // merge sorted parts
        merge(numbers, min, mid, max);
    }
}

// Part 2: merge
void merge(int numbers[], int min, int mid, int max)
{
    int i, j, k;
    int n1 = mid - min + 1; // size of left part
    int n2 = max - mid;     // size of right part

    // Gecici diziler olustur (Bellek kullanimi burada artar!)
    int L[n1], R[n2];

    // Verileri gecici dizilere kopyala
    for (i = 0; i < n1; i++)
        L[i] = numbers[min + i];
    for (j = 0; j < n2; j++)
        R[j] = numbers[mid + 1 + j];

    // Fermuar mantigiyla kiyasla ve ana diziye yerlestir
    i = 0; // Sol dizinin baslangic indeksi
    j = 0; // Sag dizinin baslangic indeksi
    k = min; // Ana dizinin guncellenecek indeksi

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]) // Kim kucukse onu ana diziye koy
        {
            numbers[k] = L[i];
            i++;
        }
        else
        {
            numbers[k] = R[j];
            j++;
        }
        k++;
    }

    // Eger sol dizide eleman kaldiysa onlari ekle
    while (i < n1)
    {
        numbers[k] = L[i];
        i++;
        k++;
    }

    // if there is element left in right array
    while (j < n2)
    {
        numbers[k] = R[j];
        j++;
        k++;
    }
}

// if array is sorted bubble sort might be better
// but if its average or worst scenerio merge sort will be faster
// just it will use more memory