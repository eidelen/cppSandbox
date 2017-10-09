#ifndef _LISTOPERATION_
#define _LISTOPERATION_

#include <string>
#include <array>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <smmintrin.h>  // SSE4

#include "myMath.h"

using namespace std;



class ListOperations
{
public:
    template<typename T> static string ArrToStr( const T* arr, const uint32_t& length );
    template<typename Iter> static string VecToStr(Iter begin, Iter end );
    template<typename T> static T* CreateArrOfRandomNumbers( const int& min, const int& max, const uint32_t& length );
    template<typename T> static vector<T> CreateVectorOfRandomNumbers( const int& min, const int& max, const size_t& length );

    // Sort Algorithms
    template<typename Iter> static void BubbleSort( Iter begin, Iter end );
    template<typename Iter> static void QuickSort( Iter begin, Iter end );

    // Compare Algorithms
    template<typename Iter> static bool CompareLists( Iter b1, Iter e1, Iter b2 );
    template<typename Iter> static bool CompareLists_MT( Iter b1, Iter e1, Iter b2, const int& nbrOfThreads = 1 );
    static bool CompareLists_MT( const vector<int>& v1, const vector<int>& v2, const int& nbrOfThreads = 1 );
    static bool CompareVectors_SSE( const vector<int>& a, const vector<int>& b);

    // Search
    template<typename Iter, typename key> static Iter Search( Iter begin, Iter end, key aKey);
    template<typename t> static int SearchSSE( const vector<t> v, t aKey );
};


//------------------------ Implementations -----------------------//

template<typename T> string ListOperations::ArrToStr(const T* arr, const uint32_t &length )
{
    string ret = "[ ";
    for( uint32_t i = 0; i < length; i++ )
    {
        ret.append( std::to_string( arr[i] ) );

        if( (i+1) < length)
            ret.append( ", " );
    }

    ret.append(" ]");

    return ret;
}

template<typename Iter> string ListOperations::VecToStr( Iter begin, Iter end )
{
    if( end - begin < 0 )
    {
        return "invalid iterators";
    }

    string ret = "[ ";
    for( Iter it = begin; it != end; it++ )
    {
        ret.append( std::to_string( *it ) );

        if( (it+1) != end )
            ret.append( ", " );
    }

    ret.append(" ]");

    return ret;
}

template<typename T> T* ListOperations::CreateArrOfRandomNumbers( const int& min, const int& max, const uint32_t& length )
{
    T* arr = new T[length];
    for( uint32_t i = 0; i < length; i++ )
        arr[i] = MyMath::RandomNumber(min,max);

    return arr;
}

template<typename T> vector<T> ListOperations::CreateVectorOfRandomNumbers( const int& min, const int& max, const size_t & length )
{
    vector<T> vec;
    for( uint32_t i = 0; i < length; i++ )
        vec.push_back( MyMath::RandomNumber(min,max) );

    return vec;
}

template<typename Iter> void ListOperations::BubbleSort( Iter begin, Iter end )
{
    bool goOn = true;
    uint32_t i = 0;

    // stops when no swaps were done anymore
    while( goOn )
    {
        goOn = false;

        for( Iter it = begin; (it+1) != (end-i); it++ )
        {
            if( (*it) > (*(it+1)) )
            {
                iter_swap( it, it+1 );
                goOn = true;
            }
        }
        i++;
    }
}


template<typename Iter> void qs_partitioning( Iter begin, Iter end )
{
    if( (end - begin) < 2 )
        return;

    Iter pivotElement = begin, right = end-1, left = begin+1;
    auto pivot = *pivotElement;
    bool hasSwapped = true;

    while( hasSwapped )
    {
        hasSwapped = false;

        while( pivotElement < right )
        {
            if( pivot > *right )
            {
                iter_swap( right, pivotElement );
                pivotElement = right--; // -> pivotElement = right; right = right - 1;
                hasSwapped = true;
                break;
            }

            right--;
        }

        while( pivotElement > left )
        {
            if( pivot < *left )
            {
                iter_swap( left, pivotElement );
                pivotElement = left++;
                hasSwapped = true;
                break;
            }

            left++;
        }
    }

    // partioning left
    qs_partitioning<Iter>(begin,pivotElement);

    // partitioning right
    qs_partitioning<Iter>(pivotElement+1,end);
}

template<typename Iter> void ListOperations::QuickSort( Iter begin, Iter end )
{
    qs_partitioning<Iter>(begin,end);
}

template<typename Iter> bool ListOperations::CompareLists( Iter b1, Iter e1, Iter b2)
{
    for( ; b1 != e1; ++b1, ++b2 )
        if( *b1 != *b2 )
            return false;

    return true;
}


template<typename Iter> void cmpList( Iter b1, Iter e1, Iter b2, bool* result )
{
    *result = ListOperations::CompareLists<Iter>(b1, e1, b2);
}

template<typename Iter> bool ListOperations::CompareLists_MT(Iter b1, Iter e1, Iter b2, const int &nbrOfThreads )
{
    // distribute problem to nbrOfThreads threads
    int nbrOfElements = e1 - b1;

    int range = nbrOfElements / nbrOfThreads;

    bool* results = new bool[nbrOfThreads];
    vector<thread> cmpThreads;

    for( int tr = 0; tr < nbrOfThreads; tr++ )
    {
        //*** make partition ***//

        Iter cBegin1 = b1 + tr*range;
        Iter cBegin2 = b2 + tr*range;

        Iter cEnd;
        if( (tr + 1) ==  nbrOfThreads )
            cEnd = e1;  // put all remainging elements to the last thread
        else
            cEnd = cBegin1+range;   // always put 'range' of elements

        // start new thread
        cmpThreads.push_back( thread( cmpList<Iter>, cBegin1 , cEnd,  cBegin2, results+tr ) );
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

template<typename Iter, typename key> Iter ListOperations::Search( Iter begin, Iter end, key aKey)
{
    // runtime 2.5 s
    /*for( Iter it = begin; it != end; it++ )
        if( *it == aKey )
            return it;*/

    // runtime 3.6 s
    /*while( begin != end )
        if( *begin == aKey )
            return begin;
        else
            begin++;*/

    // runtime 2.1 s
    unsigned int n = end - begin;
    for( unsigned int i = 0; i < n; i++ )
    {
        if( *(begin+i) == aKey )
            return (begin+i);
    }


    // runtime 3.4
    /*
    unsigned int n = end - begin;
    __m128i keySSE = _mm_set_epi32( aKey, aKey, aKey, aKey );
    for( unsigned int i = 0; i < n; i += 4 )
    {
        __m128i inNbrSSE = _mm_set_epi32( *(begin+i), *(begin+i+1), *(begin+i+2), *(begin+i+3) );
        __m128i cmpSSE = _mm_cmpeq_epi32( inNbrSSE, keySSE );

        // add comparison values
        cmpSSE = _mm_hadd_epi32(cmpSSE,cmpSSE);
        cmpSSE = _mm_hadd_epi32(cmpSSE, cmpSSE);
        int sum = _mm_extract_epi32(cmpSSE, 0);

        if( sum != 0 )
        {
            // the element was found among those 4
            for( int k = 0; k < 4; k++ )
            {
                if( *(begin+i+k) == aKey )
                    return (begin+i+k) ;
            }
        }
    }
    */

    return end;
}

template<typename t> int ListOperations::SearchSSE( const vector<t> v, t aKey )
{
    unsigned int n = v.size();
    if( n % 4 != 0)
    {
        cout << "SearchSSE warning: input length not multiple of 4!" << endl;
    }

    __m128i* dataPtr = (__m128i*) v.data();
    __m128i keySSE = _mm_set_epi32( aKey, aKey, aKey, aKey );

    for( unsigned int i = 0; i < n; i += 4 )
    {
        __m128i inNbrSSE = _mm_load_si128(dataPtr);
        __m128i cmpSSE = _mm_cmpeq_epi32( inNbrSSE, keySSE );

        // add comparison values
        cmpSSE = _mm_hadd_epi32(cmpSSE,cmpSSE);
        cmpSSE = _mm_hadd_epi32(cmpSSE, cmpSSE);
        int sum = _mm_extract_epi32(cmpSSE, 0);

        if( sum != 0 )
        {
            // the element was found among those 4
            for( int k = 0; k < 4; k++ )
            {
                if( v.at(i+k) == aKey )
                    return i+k ;
            }
        }

        dataPtr++;
    }

    return -1;
}


#endif
