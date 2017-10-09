#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>

#include "listOperations.h"
#include "myBinaryTree.h"

using namespace std;


int main (int argc, char *argv[])
{
    //****** sort lists *************//

    size_t nbrOfElementsToSort = 1000000;
    clock_t start, finish;


    //****** sort *************//

    cout << "Sort a vector of length " << nbrOfElementsToSort << endl;

    // sort data input
    vector<int> dataInputVector = ListOperations::CreateVectorOfRandomNumbers<int>( 0, 2000000, nbrOfElementsToSort );


    // 0.01
    vector<int> quickSortInput = dataInputVector;
    start = clock();
    ListOperations::QuickSort< vector<int>::iterator >( quickSortInput.begin(), quickSortInput.end() );
    finish = clock();
    cout << "QuickSort (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    vector<int> generalSortInput = dataInputVector;
    start = clock();
    sort( generalSortInput.begin(), generalSortInput.end() );
    finish = clock();
    cout << "STL sort (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    cout << "Lists are equal: " << ListOperations::CompareLists< vector<int>::iterator >( quickSortInput.begin(),
                    quickSortInput.end() , generalSortInput.begin() ) << endl << endl;


    //****** compare lists *************//

    size_t nbrOfElementsToCompare = 100000000;

    cout << "Compare vectors of length " << nbrOfElementsToCompare << endl;

    vector<int> cmpVec = ListOperations::CreateVectorOfRandomNumbers<int>( 0, 20000000, nbrOfElementsToCompare );


    start = clock();
    bool cmp = ListOperations::CompareLists< vector<int>::const_iterator >( cmpVec.begin(), cmpVec.end() , cmpVec.begin() );
    finish = clock();
    cout << "Own simple compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl;

    start = clock();
    cmp = ListOperations::CompareLists_MT< vector<int>::const_iterator >( cmpVec.begin(), cmpVec.end() , cmpVec.begin(), 4 );
    finish = clock();
    cout << "Own multi-thread compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl;

    start = clock();
    cmp = ListOperations::CompareLists_MT( cmpVec, cmpVec, 4 );
    finish = clock();
    cout << "Own multi-thread vector compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl;

    start = clock();
    cmp = ListOperations::CompareVectors_SSE( cmpVec, cmpVec);
    finish = clock();
    cout << "Own SSE vector compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl;

    start = clock();
    cmp = equal( cmpVec.begin(), cmpVec.end() , cmpVec.begin() );
    finish = clock();
    cout << "STL compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl<< endl;



    return 0;
}


