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
    uint nbrOfElements = 3000000;
    uint nbrOfSearches = 100;
    clock_t start, finish;

    cout << "Testing own search implementation" << endl << endl;

    // create test data structure
    vector<int> dataVector = ListOperations::CreateVectorOfRandomNumbers<int>( 0, 6000000, nbrOfElements );
    start = clock();
    TreeNode<int,int>* dataTree = createUnbalancedBinaryTree<int,int>(dataVector, dataVector);
    finish = clock();
    cout << "Building unbalanced binary tree of length " << nbrOfElements
         << " and tree depth of " << to_string( computeTreeDepth<int,int>(dataTree) )
         << " in " << ((double)(finish - start))/CLOCKS_PER_SEC << " seconds" << endl << endl;


    cout << "Search " << nbrOfSearches << " elements among " << nbrOfElements << " elements:" << endl;

    // elements to search for
    vector<int> elementsToSearchFor = ListOperations::CreateVectorOfRandomNumbers<int>( 0, 6000000, nbrOfSearches );

    start = clock();
    for( unsigned int i = 0; i < elementsToSearchFor.size(); i++ )
        search<int,int>( elementsToSearchFor.at(i), dataTree );
    finish = clock();
    cout << "Search in binary tree (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    start = clock();
    for( unsigned int i = 0; i < elementsToSearchFor.size(); i++ )
        ListOperations::Search<vector<int>::const_iterator,const int&>( dataVector.begin(), dataVector.end(), elementsToSearchFor.at(i) );
    finish = clock();
    cout << "Search in vector (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    start = clock();
    for( unsigned int i = 0; i < elementsToSearchFor.size(); i++ )
        ListOperations::SearchSSE<int>( dataVector, elementsToSearchFor.at(i) );
    finish = clock();
    cout << "Search in vector with SSE (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    start = clock();
    for( unsigned int i = 0; i < elementsToSearchFor.size(); i++ )
        find(dataVector.begin(), dataVector.end(), elementsToSearchFor.at(i) );
    finish = clock();
    cout << "Search in vector using STL (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    delete dataTree;


    return 0;
}


