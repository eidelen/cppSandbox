#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <chrono>

// product is order invariant
constexpr char GB = 'G'*'B';
constexpr char GR = 'G'*'R';

char getMissing(char a, char b)
{
    if(a == b)
        return a;

    const char prod = a*b;
    if(prod == GB)
        return 'R';
    else if(prod == GR)
        return 'B';
    else
        return 'G';
}

char triangleNaive(std::string row_str)
{
    if(row_str.length() == 1)
        return row_str[0];

    for(size_t k = row_str.length(); k > 0; k--)
        for(size_t i = 0; i < k-1; i++)
            row_str[i] = getMissing(row_str[i], row_str[i+1]);

    return row_str[0];
}

// https://www.youtube.com/watch?v=9JN5f7_3YmQ
size_t findMaxJumpDistance(size_t n)
{
    int i = 1;
    int jmpDist = 0;
    while( std::pow(3, i) + 1 <= n )
    {
        jmpDist = std::pow(3, i) + 1;
        i++;
    }

    return jmpDist;
}

char triangle(std::string row_str)
{
    size_t rowLength = row_str.length();
    size_t jumpRows = findMaxJumpDistance(rowLength);

    if( jumpRows == 0 )
        return triangleNaive(row_str); // the last 1 - 3 lines are naively computed

    std::string res;
    for(size_t i = 0; i < (rowLength-jumpRows+1); i++)
        res += getMissing(row_str[i], row_str[i+(jumpRows-1)]);

    return triangle(res);
}


int main (int argc, char *argv[])
{
    std::string test("RBRGBRBGGRRRBGBBBGG");
    char shouldRes = triangleNaive(test);
    std::cout << test << " evaluates to " << shouldRes << std::endl;
    std::cout << "Fast solution: " << triangle(test) << std::endl;


    /*
     *
     * test_cases({make_pair("B", 'B'),
                    make_pair("GB", 'R'),
                    make_pair("RRR", 'R'),
                    make_pair("RGBG", 'B'),
                    make_pair("RBRGBRB", 'G'),
                    make_pair("RBRGBRBGGRRRBGBBBGG", 'G')});


    // long test
    std::string longStr(100000, 'G'); // Besttime 3s, 2.4s, 4Hash = 19s and 149985000, 8Hash = 8s 64270710, new approach 1.3s (jump lines...)
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    char res = triangle(longStr);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    if(res == 'G')
        std::cout << "Fine: " <<  std::endl;
    else
        std::cout << "Wrong:" << res << std::endl;

    std::cout << "Duration ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
*/


    /*
    constexpr char P = 0b00; // padding
    constexpr char R = 0b01; // red
    constexpr char G = 0b10; // green
    constexpr char B = 0b11; // blue
    */


    /*

    std::string q("RGRB");
    char compTest = compress4in1(&q[0]);
    std::string decompTest = decompress1in4(compTest);
    std::cout << "Decomp: " << decompTest << std::endl;

    q = "RRRRR"; // 2 x char (3 values padded)
    std::vector<char> compLine = compressLine(q);
    std::bitset<8> b0(compLine[0]);
    std::bitset<8> b1(compLine[1]);
    std::cout << q << ": compressed to n chars = " << compLine.size() << ", bytes=" << b0 << ", " << b1 << std::endl;

    std::vector<char> lt = createLookup();std::vector<char> lt = createLookup();
    std::cout << "LookupTable: " << lt[(unsigned char)compress4in1("GGGG")] << std::endl;
    std::cout << "LookupTable: " << lt[(unsigned char)compress4in1("BBBR")] << std::endl;
    std::cout << "LookupTable: " << lt[(unsigned char)compress4in1("BB--")] << std::endl;


    std::string traverseString = "RRGBRBBG";
    std::cout << "Traverse Input: " << traverseString << std::endl;
    std::vector<char> traversEncoded = compressLine(traverseString);
    for(size_t j = 0; j < traversEncoded.size()-1; j++)
    {
        char a = traversEncoded[j];
        char b = traversEncoded[j+1];

        // combine into short
        short comb = a << 8 | b;

        std::bitset<16> ck(comb);
        std::cout << "Traverse: " << ck << std::endl;

        for(size_t step = 0; step < 4; step++)
        {
            char theCode = comb >> (8 - step*2);
            std::bitset<8> tc(theCode);
            std::cout << "Step: (" << j << "," << step << "): " << tc << "=" << decompress1in4(theCode) << std::endl;

        }
    }
    */
    /*
    constexpr char P = 0b00; // padding
    constexpr char R = 0b01; // red
    constexpr char G = 0b10; // green
    constexpr char B = 0b11; // blue
    */

    /*
    char res = triangle("--RBRGR-"); // padding removed
    if(res == 'R')
        std::cout << "Fine" << std::endl;
    else
        std::cout << "Wrong!!" << std::endl;

    res = triangle("BBBR");
    std::cout << "BBBR->" << res << std::endl;

    // long test
    std::string longStr(30000, 'B'); // Besttime 3s,
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    res = triangle(longStr);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    if(res == 'B')
        std::cout << "Fine" << std::endl;
    else
        std::cout << "Wrong!!" << std::endl;

    std::cout << "Duration ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
    */

    return 0;
}


