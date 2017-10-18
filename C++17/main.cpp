#include <iostream>
#include <string_view>
#include <string>

void recvAStringView( std::string_view sv)
{
    std::cout << "recv: " << sv << std::endl;
}

int main()
{
    // try string_view
    std::string_view sv("String view content");
    const char* charArr = "Char array content";
    std::string normalString("String content");

    recvAStringView(sv);
    recvAStringView(charArr);
    recvAStringView(normalString);

    return 0;
}