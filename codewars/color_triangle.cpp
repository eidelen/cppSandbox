#include <string>
#include <iostream>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <algorithm>

#include <chrono>

// product is order invariant
constexpr char GB = 'G'*'B';
constexpr char GR = 'G'*'R';
constexpr char RB = 'R'*'B';

constexpr char P = 0b00; // padding
constexpr char R = 0b01; // red
constexpr char G = 0b10; // green
constexpr char B = 0b11; // blue

std::string decompress1in4(char data)
{
    std::string decompressed(4, ' ');
    for(int i = 0; i < 4; i++)
    {
        char val = (data >> (6 - i*2)) & 0b11;
        char col = val == R ? 'R' : ( val == G ? 'G' : ( val == B ? 'B' : '-') );
        decompressed[i] = col;
    }

    return decompressed;
}

unsigned char compress4in1(const char* data)
{
    char compressed = 0x00;
    for(int i = 0; i < 4; i++)
    {
        char a = data[i];
        char code = a=='R' ? R : ( a=='G' ? G : ( a=='B' ? B : P));
        compressed = compressed | (code << (6 - i*2));

        //std::bitset<8> y(compressed);
        //std::cout << y << std::endl;
    }

    return compressed;
}

std::vector<char> compressLine(std::string line)
{
    // line length multiple of 4 -> padding
    size_t paddingLength = line.length() % 4 == 0 ? 0 : 4 - (line.length() % 4);
    line.append(paddingLength, '-');

    std::vector<char> compLine(line.length() / 4); // compress 4 elements into 1 char
    char* lineChr = &line[0];
    for(size_t i = 0; i < compLine.size(); i++)
    {
        compLine[i] = compress4in1(lineChr);
        lineChr = lineChr + 4;
    }

    return compLine;
}


char getMissing(char a, char b)
{
    if(a == '-' || b == '-') // do not propagate padding
        return '-';

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
    // remove padding
    //row_str.erase(std::remove(row_str.begin(), row_str.end(), '-'), row_str.end());
    //if(row_str.length() == 0)
    //    return '-';

    if(row_str.length() == 1)
        return row_str[0];

    for(size_t k = row_str.length(); k > 0; k--)
    {
        for(size_t i = 0; i < k-1; i++)
        {
            row_str[i] = getMissing(row_str[i], row_str[i+1]);
        }
    }
    return row_str[0];
}

std::vector<char> createLookup()
{
    std::vector<char> table(255);
    for(size_t code = 0; code < 255; code++)
    {
        std::string config = decompress1in4((char)code);
        char config_res = triangleNaive(config);
        table[code] = config_res;
    }

    return table;
}

char triangle(std::string row_str)
{
    std::vector<char> lt = createLookup();
    std::vector<char> cLine = compressLine(row_str);

    // process three lines at once
    for(size_t k = 0; k < row_str.length()/3; k++)
    {
        std::vector<char> storeRes;

        for(size_t j = 0; j < cLine.size(); j++)
        {
            char a = cLine[j];
            char b = (j < cLine.size() ) ? cLine[j+1] : 0x00; // padding the last element of the line

            // combine into short
            short comb = a << 8 | b;

            std::bitset<16> ck(comb);
            std::cout << "Traverse: " << ck << std::endl;


            std::string res(4, '-');
            for(size_t step = 0; step < 4; step++)
            {
                char theCode = comb >> (8 - step*2);
                char evalCode = lt[(unsigned char)theCode];
                res[step] = evalCode;

                std::bitset<8> tc(theCode);
                std::cout << "Step: (" << j << "," << step << "): " << tc << "=" << decompress1in4(theCode) << ", eval=" << evalCode << std::endl;

            }

            char resCompress = compress4in1(&res[0]);
            if(resCompress != 0x00) // do not store padding
            {
                storeRes.push_back(resCompress);
                std::bitset<8> stepResPrint(resCompress);
                std::cout << "Steps Res: (" << j << "): " << stepResPrint << ", size res vect: " << storeRes.size() << std::endl;
            }
        }

        cLine = storeRes;
    }

    // naive approach for the 1 - 3 remaining lines
    std::string finalLine = decompress1in4(cLine[0]);
    finalLine.erase(std::remove(finalLine.begin(), finalLine.end(), '-'), finalLine.end()); // remove any padding character
    return triangleNaive(finalLine);
}


int main (int argc, char *argv[])
{
    std::string test("GBGBG"); // failing -> wrong encoded?

    char shouldRes = triangleNaive(test);
    std::cout << test << " evaluates to " << shouldRes << std::endl;
    std::cout << "Fast solution: " << triangle(test) << std::endl;

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


