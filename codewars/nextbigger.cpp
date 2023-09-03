#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
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
    long nbrIn = 59884848459853;
    long resOut = 59884848483559;
    long res = nextBigger(nbrIn);

    if(res == resOut)
        std::cout << "Correct: " << nbrIn << " -> " << res << std::endl;
    else
        std::cout << "Wrong: " << nbrIn << " -> " << res << " should be " << resOut << std::endl;

    std::cout << "nleaves=" << leaves << std::endl;

    return 0;
}
