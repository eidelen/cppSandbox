#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

static size_t leaves = 0;

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

    // todo: make a best guess (largest element) to stop recursion

    std::cout << pos << ": " << sum << ", " << ", lb=" << lowerBound << ", ub=" << upperBound << std::endl;

    long solution = -1;
    for(size_t i = 0; i < digits.size(); i++)
    {
        long thenbr = digits[i];
        long nextSum = sum + (digits[i] * std::pow(10, pos));
        std::vector<long> nextDigits(digits);
        nextDigits.erase(nextDigits.begin() + i);
        long pSol = rabbitHole(nbr, nextSum, pos-1, nextDigits, bestSolution);

        if( (pSol > nbr) && (pSol < solution || solution < 0))
        {
            std::string nst = std::to_string(solution);
            std::cout << "yeahh: " << nst << std::endl;
            if (nst.find("8")!=std::string::npos)
                std::cout << "problem" << std::endl;

            solution = pSol;
            std::cout << pos << ": " <<"new solution: " << solution << std::endl;

            if(solution < bestSolution || bestSolution < 0)
            {
                bestSolution = solution;
                std::cout << pos << ": " << "Best solution: " << bestSolution << std::endl;
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
    long bestSolution = -1;
    return rabbitHole(n, 0, digits.size()-1, digits, bestSolution);
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
