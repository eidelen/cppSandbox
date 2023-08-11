#include <string>
#include <iostream>
#include <unordered_map>
#include <bitset>
#include <vector>

#include <chrono>

// product is order invariant
constexpr char GB = 'G'*'B';
constexpr char GR = 'G'*'R';

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

char compress4in1(const char* data)
{
    char compressed = 0x00;
    for(int i = 0; i < 4; i++)
    {
        char a = data[i];
        char code = a=='R' ? R : ( a=='G' ? G : ( a=='B' ? B : P));
        compressed = compressed | (code << (6 - i*2));

        std::bitset<8> y(compressed);
        std::cout << y << std::endl;
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

void getMissingInplace(char* aAdr)
{
    char a = *aAdr;
    char b = *(aAdr+1);

    if(a == b)
        return;

    const char prod = a*b;
    if(prod == GB)
        *aAdr = 'R';
    else if(prod == GR)
        *aAdr = 'B';
    else
        *aAdr = 'G';
}

char triangle(std::string row_str)
{
    for(size_t k = row_str.length(); k > 0; k--)
    {
        for(size_t i = 0; i < k-1; i++)
        {
            getMissingInplace(&row_str[i]); //getMissing(row_str[i], row_str[i+1]);
        }
    }
    return row_str[0];
}


int main (int argc, char *argv[])
{
    std::string q("RGRB");
    char compTest = compress4in1(&q[0]);
    std::string decompTest = decompress1in4(compTest);
    std::cout << "Decomp: " << decompTest << std::endl;

    q = "RRRRR"; // 2 x char (3 values padded)
    std::vector<char> compLine = compressLine(q);
    std::bitset<8> b0(compLine[0]);
    std::bitset<8> b1(compLine[1]);
    std::cout << q << ": compressed to n chars = " << compLine.size() << ", bytes=" << b0 << ", " << b1 << std::endl;


    char res = triangle("RBRGBRB");
    if(res == 'G')
        std::cout << "Fine" << std::endl;
    else
        std::cout << "Wrong!!" << std::endl;

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


    return 0;
}


