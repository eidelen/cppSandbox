#include <iostream>

#include <string_view>
#include <string>

void recvAStringView(std::string_view sv)
{
    std::cout << "recv: " << sv << std::endl;
}

void tryStringView()
{
    std::cout << "Try string view:" << std::endl;

    std::string_view sv("String view content");
    const char* charArr = "Char array content";
    std::string normalString("String content");

    recvAStringView(sv);
    recvAStringView(charArr);
    recvAStringView(normalString);

    std::cout << std::endl;
}



#include <variant>
#include <exception>

void tryVariant()
{
    std::cout << "Try variant:" << std::endl;

    std::variant<float, std::string, int> v0;

    v0 = "abc";
    std::cout << "v0, read string = " << std::get<std::string>(v0) << std::endl;
    try
    {
        std::get<float>(v0);
    }
    catch( std::exception& e)
    {
        std::cout << "v0, get float not possible: " << e.what() << std::endl;
    }

    v0 = 3.0f;
    std::cout << "v0, get float after set float: " << std::get<float>(v0) << std::endl;

    std::cout << std::endl;
}



int main()
{
    tryStringView();
    tryVariant();


    return 0;
}