#include "util.hpp"

/*
    This function find median in two passes with high probability.
    It uses the following algorithm:
    1. Read the file and get a sample of size n^(2/3) logn
    2. Find the left and right pivot of the sample
    3. Read the file again and get the numbers between the left and right pivot, and the rank of the left pivot
    4. Find the median using rank and numbers between the left and right pivot by STL's nth_element function
    5. Return the median
*/

int64 algo1(string filename, int64 n){
    reader fr(filename);
    int64 sample_size = pow(n, 2.0/3.0) * log(n); // n^(2/3) logn
    int64 * sample = get_sample(sample_size, n, fr);
    int64 offset = pow(n, 1.0/3.0) * log(n); // n^(1/3) logn
    int64 left_pivot = sample_size/2 - offset;
    int64 right_pivot = sample_size/2 + offset;
    nth_element(sample, sample + left_pivot, sample + sample_size); // get left pivot
    int64 left_median = sample[left_pivot]; // left pivot
    nth_element(sample, sample + right_pivot, sample + sample_size); // get right pivot
    int64 right_median = sample[right_pivot];   // right pivot
    fr.reset(); // reset the file for second pass

    int64 count = 0;
    int64 rank_lower = 0;
    for (int64 i = 0; i < n; i++){
        int64 num = fr.next();
        if (num >= left_median && num <= right_median){ // get numbers between left and right pivot
            sample[count++] = num;
            if (count == sample_size){
                cerr << "Sample size reached\n"; // sample size reached
                break;
            }
        }
        if (num < left_median){
            rank_lower++; // update rank of left pivot
        }
    }
    if (n/2 - rank_lower < 0 || n/2 - rank_lower >= count){ 
        // rank out of bounds, algorithm failed
        free(sample);
        fr.close();
        cerr << "Error: Rank out of bounds\n";
        return -1;
    }
    // find median using rank and numbers between left and right pivot
    nth_element(sample, sample + (n/2 - rank_lower), sample + count);
    int64 median = sample[n/2 - rank_lower];
    free(sample);
    fr.close();
    return median;
}

// main function, takes n as input (in command line)
int main(int argc, char *argv[]){
    int64 n = atoll(argv[1]);
    
    clock_t t_start, t_end;
    srand(time(0));
    t_start = clock();
    int64 result = algo1("data.bin", n);
    t_end = clock();
    double time_taken = ((double)(t_end - t_start)) * 1000 / CLOCKS_PER_SEC;
    printf("%lld, %.3lf", result, time_taken);
    return 0;
}
