#include "util.hpp"

// generate data for the dataset
int main(int argc, char *argv[])
{
    int64 n = atoll(argv[1]);
    int mode = atoi(argv[2]);
    generate_data(n, mode, "data.bin"); // for dataset, if want sorted dataset set flag to be 1 or -1, otherwise 0 for random dataset
    return 0;
}