#include <iostream>
#include <exception>
#include <vector>

// provoke segmentation fault
void segFault()
{
    *((int*) nullptr) = 0;
}

void invalidVectorAccessing()
{
    std::vector<int> vec;
    vec.at(2);
}


int main (int argc, char *argv[])
{
    // Interesting!
    // Segmentation fault is not handled with try/catch
    try
    {
        //disable: segFault();
    }
    catch(...)
    {
        std::cout << "Segmentation fault catch" << std::endl;
    }


    // invalid accessing std::vector
    try
    {
        invalidVectorAccessing();
    }
    catch( std::out_of_range& e)
    {
        std::cout << "Out of Range exception: " << e.what() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    return 0;
}