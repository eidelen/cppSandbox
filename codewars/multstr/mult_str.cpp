#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::string charV2str(std::vector<char> v)
{
    std::transform(v.begin(), v.end(), v.begin(), [](char c) -> char { return c+48; });
    return std::string(v.begin(), v.end());
}

std::string multiply(std::string a, std::string b)
{
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    std::vector<char> res(a.length()+b.length(), 0);
    for(size_t ia = 0; ia < a.length(); ia++)
    {
        char ca = a[ia] - 48;
        for(size_t ib = 0; ib < b.length(); ib++)
        {
            char cb = b[ib] - 48;
            char mul = ca * cb;

            for(size_t q = ia + ib; q < res.size(); q++)
            {
                char sum = res[q] + (mul % 10);
                res[q] = sum % 10;

                mul = mul/10 + sum/10;

                if(mul == 0)
                    break;
            }
        }
    }

    // remove unnecessary 0 from the back
    while(res.size() > 1 && res.back() == 0)
        res.pop_back();

    std::transform(res.begin(), res.end(), res.begin(), [](char c) -> char { return c+48; });
    std::string resStr(res.begin(), res.end());
    std::reverse(resStr.begin(), resStr.end());
    return resStr;
}

int main (int argc, char *argv[])
{
    auto res = multiply("25", "12");
    std::string correctAnsw = "300";
    if(res.compare(correctAnsw)==0)
        std::cout << "Correct: " << correctAnsw << std::endl;
    else
        std::cout << "Wrong: " << res << " should be " << correctAnsw << std::endl;

    return 0;
}
