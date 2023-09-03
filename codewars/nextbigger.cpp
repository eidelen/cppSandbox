#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

static size_t leaves = 0;
static size_t reccnt = 0;

long rabbitHole(const long nbr, const long sum, const long pos, std::vector<long> digits, long& bestSolution)
{
    if(pos < 0)
    {
        leaves++;
        return sum;
    }


    // pruning recursion
    auto[minE, maxE] = std::minmax_element(digits.begin(), digits.end());
    long lowerBound = sum + *minE * std::pow(10, pos);
    long upperBound = sum + (*maxE) * std::pow(10, pos) + (std::pow(10, pos)-1);
    if( upperBound <= nbr && upperBound > 0) //overflow!
        return -1;
    if( lowerBound > bestSolution && bestSolution != -1)
        return -1;


    //std::cout << pos << ": " << sum << ", " << ", lb=" << lowerBound << ", ub=" << upperBound << std::endl;

    long solution = -1;
    for(size_t i = 0; i < digits.size(); i++)
    {
        long thenbr = digits[i];
        long mulPos = std::pow(10l, pos);
        long mulAdd = thenbr * mulPos;
        long nextSum = sum + mulAdd;
        std::vector<long> nextDigits(digits);
        nextDigits.erase(nextDigits.begin() + i);
        long pSol = rabbitHole(nbr, nextSum, pos-1, nextDigits, bestSolution);

        if( (pSol > nbr) && (pSol < solution || solution < 0))
        {
            reccnt++;

            solution = pSol;
            //std::cout << pos << ": " <<"new solution: " << solution << ", reccnt: " << reccnt << std::endl;

            if(solution < bestSolution || bestSolution < 0)
            {
                bestSolution = solution;
                //std::cout << pos << ": " << "Best solution: " << bestSolution << std::endl;
            }
        }
    }

    return solution;
}

long nextBigger(long n)
{
    std::string nStr = std::to_string(n);
    std::vector<long> digits(nStr.length(), 0);
    std::transform(nStr.begin(), nStr.end(), digits.begin(), [](char c) -> long { return c - 48; });

    // swap next smaller element coming from the back
    int swapPos = -1;
    for(int m = digits.size()-1; m >= 0 && swapPos < 0; m--)
    {
        long sw1 = digits[m];
        for(int n = m; n >= 0 && swapPos < 0; n--)
        {

            long sw2 = digits[n];

            std::cout << "compare: " << sw2 << ", " << sw1 << std::endl;

            if(sw2 < sw1)
            {
                std::cout << "swap: " << sw2 << ", " << sw1 << std::endl;
                std::swap(digits[n], digits[m]);
                swapPos = n;
            }

        }
    }

    for(auto l: digits)
        std::cout << l << ", ";
    std::cout << std::endl;

    std::cout << "swappos:" << swapPos << std::endl;

    std::sort(digits.begin()+swapPos+1, digits.end());

    for(auto l: digits)
        std::cout << l << ", ";
    std::cout << std::endl;

    long res = 0;
    for(int p = 0; p < digits.size(); p++)
        res += digits[p] * (long)std::pow(10l, digits.size() - p - 1);

    return res;
}


int main (int argc, char *argv[])
{
    long nbrIn = 7799665555444321100;
    long resOut = 7900112344455556679;
    long res = nextBigger(nbrIn);

    if(res == resOut)
        std::cout << "Correct: " << nbrIn << " -> " << res << std::endl;
    else
        std::cout << "Wrong: " << nbrIn << " -> " << res << " should be " << resOut << std::endl;

    std::cout << "nleaves=" << leaves << std::endl;

    return 0;
}
