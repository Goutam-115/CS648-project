#include "util.hpp"

/*
    This algorithm computes the median of n random integers in a single pass with high probability, the input should be a uniformly random permutation
    Algorithm:
    1. Read the first sqrt(n) integers from the stream and store them in a multiset.
    2. For the next n-sqrt(n) integers, if the integer is less than the smallest integer in the multiset, increment low.
    3. If the integer is greater than the largest integer in the multiset, increment high.
    4. If the integer is between the smallest and largest integer in the multiset, replace the smallest or largest integer in the multiset with the integer.
    5. The median is the (n/2 - low + 1)th element in the multiset.
*/
int64 algo3(string filename, int64 n){
    reader fr(filename);
    multiset<int64> curr_set; // maintain the set of elements in the middle
    int64 low=0, high=0;
    int64 curr;
    int64 buffer_size = sqrt(n) * log(n);
    for (int64 i = 0; i < buffer_size; i++) // read the first sqrt(n) elements
    {
        curr = fr.next();
        curr_set.insert(curr);
    }
    for (int64 i = buffer_size; i < n; i++)
    {
        curr = fr.next();
        int64 mn = *curr_set.begin();
        int64 mx = *curr_set.rbegin();
        if (curr <= mn)
        {
            low++;
        }
        else if (curr >= mx)
        {
            high++;
        }
        else
        {
            if (low < high)
            {
                curr_set.erase(curr_set.begin()); // remove the smallest element
                curr_set.insert(curr);
                low++;
            }
            else
            {
                curr_set.erase(--curr_set.end()); // remove the largest element
                curr_set.insert(curr);
                high++;
            }
        }
    }

    fr.close();
    int64 index_needed = (n/2) - low; 
    if(index_needed > buffer_size){
        // one-pass algorithm failed
        cerr << "One-pass Algorithm Failed" << endl;
        return -1;
    }
    else{
        auto it = curr_set.begin();
        for(int64 i = 0;i<index_needed;i++){
            ++it;
        }
        int64 guessed_median = *it; // the median is the (n/2 - low + 1)th element in the multiset
        return guessed_median;
    }
}


int main(int argc, char *argv[]){
    int64 n = atoll(argv[1]);
    clock_t t_start, t_end;
    srand(time(0));
    t_start = clock();
    int64 result = algo3("data.bin", n);
    t_end = clock();
    double time_taken = ((double)(t_end - t_start)) * 1000 / CLOCKS_PER_SEC;
    printf("%lld, %.3lf", result, time_taken);
    return 0;
}
