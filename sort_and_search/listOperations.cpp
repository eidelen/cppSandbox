#include "listOperations.h"
#include <functional>


void cmpFunction(const vector<int> &v1, const vector<int> &v2, const size_t &start, const size_t &end, bool *result)
{
    bool ret = true;

    for( size_t i = start; i < end; i++ )
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
    for( size_t tr = 0; tr < cmpThreads.size(); tr++ )
    {
        cmpThreads.at(tr).join();
        ret = ret && results[tr];
    }

    delete[] results;

    return ret;
}

bool ListOperations::CompareVectors_SSE( const vector<int>& a, const vector<int>& b)
{
    if( a.size() != b.size() )
        return false;

    unsigned int n = a.size();
    if( n % 4 != 0)
    {
        cout << "CompareVectors_SSE warning: input length not multiple of 4!" << endl;
    }

    __m128i* data_A_ptr = (__m128i*) a.data();
    __m128i* data_B_ptr = (__m128i*) b.data();

    for( unsigned int i = 0; i < n; i += 4 )
    {
        __m128i reg_A_SSE = _mm_load_si128(data_A_ptr);
        __m128i reg_B_SSE = _mm_load_si128(data_B_ptr);
        __m128i reg_cmp = _mm_cmpeq_epi32( reg_A_SSE, reg_B_SSE );

        // add comparison values
        reg_cmp = _mm_hadd_epi32(reg_cmp,reg_cmp);
        reg_cmp = _mm_hadd_epi32(reg_cmp,reg_cmp);

        int sum_cmp = _mm_extract_epi32(reg_cmp, 0);

        if( sum_cmp < 4 && sum_cmp > -4 )
        {
            return false;
        }

        data_A_ptr++;
        data_B_ptr++;
    }

    return true;
}
