#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>

#include "listOperations.h"
#include "inheritance.h"
#include "myBinaryTree.h"

using namespace std;


int main (int argc, char *argv[])
{
    cout << "List Examples by A.Schneider" << endl << endl;


    //****** sort lists *************//

    uint nbrElements = 1000000;
    clock_t start, finish;

    /*vector<int> vec = ListOperations::CreateVectorOfRandomNumbers<int>( 0, 2000000, nbrElements );
    //cout << ListOperations::VecToStr< vector<int>::const_iterator >(vec.begin(), vec.end()) << endl;


    // 0.01
    vector<int> myQuickSortInput = vec;
    start = clock();
    ListOperations::QuickSort< vector<int>::iterator >( myQuickSortInput.begin(), myQuickSortInput.end() );
    finish = clock();
    cout << "Time for QuickSort (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;
    //cout << "QuickSort: " << ListOperations::VecToStr< vector<int>::const_iterator >(myQuickSortInput.begin(), myQuickSortInput.end()) << endl;


    vector<int> generalSortInput = vec;
    start = clock();
    sort( generalSortInput.begin(), generalSortInput.end() );
    finish = clock();
    cout << "Time for general sort (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;
    //cout << "GeneralSort: " << ListOperations::VecToStr< vector<int>::const_iterator >(generalSortInput.begin(), generalSortInput.end()) << endl;

    cout << "Lists are equal: " << ListOperations::CompareLists< vector<int>::iterator >( myQuickSortInput.begin(),
                    myQuickSortInput.end() , generalSortInput.begin() ) << endl << endl;

*/
    //****** compare lists *************//

    /*
    vector<int> cmpVec = ListOperations::CreateVectorOfRandomNumbers<int>( 0, 20000000, 100000000 );


    start = clock();
    bool cmp = ListOperations::CompareLists< vector<int>::const_iterator >( cmpVec.begin(), cmpVec.end() , cmpVec.begin() );
    finish = clock();
    cout << "Time for my compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl;

    start = clock();
    cmp = ListOperations::CompareLists_MT< vector<int>::const_iterator >( cmpVec.begin(), cmpVec.end() , cmpVec.begin(), 4 );
    finish = clock();
    cout << "Time for my MT compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl;

    start = clock();
    cmp = ListOperations::CompareLists_MT( cmpVec, cmpVec, 4 );
    finish = clock();
    cout << "Time for my Vector compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl;

    start = clock();
    cmp = equal( cmpVec.begin(), cmpVec.end() , cmpVec.begin() );
    finish = clock();
    cout << "Time for general compare (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << "  Res: " << cmp << endl<< endl;
*/


    //****** binary trees *************//

/*
    vector<int> binTreeTest = {5,3,6,8,2,7,4,5};
    TreeNode<int,int>* binaryTree = createUnbalancedBinaryTree<int,int>(binTreeTest, binTreeTest);

    cout << treeInfoAsString<int,int>( binaryTree ) << endl;

    cout << "search 7 -> " << search<int,int>(7, binaryTree)->mKey << endl;



    delete binaryTree;
*/


    vector<int> longvectree = ListOperations::CreateVectorOfRandomNumbers<int>( 0, 6000000, 3000000 );
    start = clock();
    TreeNode<int,int>* myLongTree = createUnbalancedBinaryTree<int,int>(longvectree, longvectree);
    finish = clock();
    cout << "Time for building unbalanced BT (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;
    cout << "Tree Depth = " << std::to_string( computeTreeDepth<int,int>(myLongTree) ) << endl << endl;

    // search in tree
    vector<int> keysToTest = ListOperations::CreateVectorOfRandomNumbers<int>( 0, 6000000, 100 );

    start = clock();
    for( unsigned int i = 0; i < keysToTest.size(); i++ )
        search<int,int>( keysToTest.at(i), myLongTree );
    finish = clock();
    cout << "Time for search in BT (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    start = clock();
    for( unsigned int i = 0; i < keysToTest.size(); i++ )
        ListOperations::Search<vector<int>::const_iterator,const int&>( longvectree.begin(), longvectree.end(), keysToTest.at(i) );
    finish = clock();
    cout << "Time for search in Vector (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    start = clock();
    for( unsigned int i = 0; i < keysToTest.size(); i++ )
        ListOperations::SearchSSE<int>( longvectree, keysToTest.at(i) );
    finish = clock();
    cout << "Time for SSE search in Vector (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;


    start = clock();
    for( unsigned int i = 0; i < keysToTest.size(); i++ )
        find(longvectree.begin(), longvectree.end(), keysToTest.at(i) );
    finish = clock();
    cout << "Time for STL search in Vector (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << endl;

    delete myLongTree;




    cout << endl;

    //doInheritanceTest();

    return 0;
}


