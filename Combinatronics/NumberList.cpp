#include <iostream>

long long int
num_of_subarrays(int length) {
    long long int l = length;
    return (l*(l+1)) / 2;
}

int
main() {
    int num_of_test_cases;
    std::cin >> num_of_test_cases;
    for(int i = 0; i < num_of_test_cases; i++) {
        int n, k;
        std::cin >> n >> k;
        long long int global_counter = 0;
        int leq_counter = 0;
        for(int j = 0; j < n; j++) {
            int element;
            std::cin >> element;
            if(element <= k) {
                leq_counter++;
            } else {
                global_counter += num_of_subarrays(leq_counter);
                leq_counter = 0;
            }
        }
        if(leq_counter > 0) {
            global_counter += num_of_subarrays(leq_counter);
        }
        long long int total = num_of_subarrays(n);
        std::cout << total - global_counter << std::endl;
    }
    return 0;
}
