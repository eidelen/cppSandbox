#include "listOperations.h"
#include <functional>


void cmpFunction( const vector<int>& v1, const vector<int>& v2, const uint& start, const uint& end, bool* result )
{
    bool ret = true;

    for( int i = start; i < end; i++ )
    {
        if( v1[i] != v2[i] )
        {
            ret = false;
            break;
        }
    }

    *result = ret;
}

bool ListOperations::CompareLists_MT( const vector<int>& v1, const vector<int>& v2, const int& nbrOfThreads )
{
    if( v1.size() != v2.size() )
        return false;

    // distribute problem to nbrOfThreads threads
    uint nbrOfElements = v1.size();
    uint range = nbrOfElements / nbrOfThreads;
    bool* results = new bool[nbrOfThreads];

    vector<thread> cmpThreads;

    for( int tr = 0; tr < nbrOfThreads; tr++ )
    {
        //*** make partition ***//
        uint thisStart = tr*range;

        uint thisEnd;
        if( (tr+1) == nbrOfThreads )
            thisEnd = nbrOfElements;
        else
            thisEnd = thisStart + range;


        // start new thread
        cmpThreads.push_back( thread( cmpFunction, std::ref( v1 ) , std::ref( v2 ),  thisStart, thisEnd, results+tr ) );
    }


    // compile results
    bool ret = true;
    for( int tr = 0; tr < cmpThreads.size(); tr++ )
    {
        cmpThreads.at(tr).join();
        ret = ret && results[tr];
    }

    delete[] results;

    return ret;
}
