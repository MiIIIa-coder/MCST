#include <iostream>
#include <vector>
#include <random>

std::vector<int> randomSample(std::vector<int>& A, int n) {
    std::vector<int> sample;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < n; ++i) {
        std::uniform_int_distribution<int> dist(i, A.size()-1);
        int idx = dist(gen);
        sample.push_back(A[idx]);
        std::swap(A[i], A[idx]);
    }
    
    return sample;
}

int main() 
{
    std::vector<int> A {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 3;
    
    std::vector<int> sample {randomSample(A, n)};
    
    for (int num : sample) {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    return 0;
}