#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>


long nextBigger(long n)
{
    // transform to vector
    std::string nStr = std::to_string(n);
    std::vector<long> digits(nStr.length(), 0);
    std::transform(nStr.begin(), nStr.end(), digits.begin(), [](char c) -> long { return c - 48; });

    // swap next smaller element coming from the back -> best option has max n
    std::pair<int, int> swapPos = {-1, -1};
    for(int m = digits.size()-1; m >= 0; m--)
        for(int n = m; n >= 0; n--)
            if(digits[n] < digits[m])
                if( n > swapPos.second )
                    swapPos = {m, n};

    if(swapPos.second == -1)
        return -1; // no swap found

    std::swap(digits[swapPos.first], digits[swapPos.second]);

    // sort remaining elements after swap position
    std::sort(digits.begin()+swapPos.second+1, digits.end());

    // accumulate
    return std::accumulate(digits.begin(), digits.end(), 0l, [idx = 0, nbrElems = digits.size()](long sum, long val) mutable ->long {
        return sum + val * (long)std::pow(10l, nbrElems - (idx++) - 1); });
}


int main (int argc, char *argv[])
{
    long nbrIn = 599776611;
    long resOut = 2071;
    long res = nextBigger(nbrIn);

    if(res == resOut)
        std::cout << "Correct: " << nbrIn << " -> " << res << std::endl;
    else
        std::cout << "Wrong: " << nbrIn << " -> " << res << "should be " << resOut << std::endl;

    return 0;
}
