#include "util.hpp"
/*
    Median finding algorithm from STL, takes O(n) space (can't use for large datasets)
*/

int algo4(string filename, int64 n){
    reader fr(filename);
    int64* arr = (int64 *)malloc(n * sizeof(int64));
    // Read the file
    for (int64 i = 0; i < n; i++)
    {
        arr[i] = fr.next();
    }
    nth_element(arr, arr + n/2, arr+n); // find median (STL)
    int64 median = arr[n/2];
    fr.close();
    free(arr);
    return median;
}

// main function, takes n as input (in command line)
int main(int argc, char *argv[]){
    int64 n = atoll(argv[1]);
    clock_t t_start, t_end;
    srand(time(0));
    t_start = clock();
    int64 result = algo4("data.bin", n);
    t_end = clock();
    double time_taken = ((double)(t_end - t_start)) * 1000 / CLOCKS_PER_SEC;
    printf("%lld, %.3lf", result, time_taken);
    return 0;
}
