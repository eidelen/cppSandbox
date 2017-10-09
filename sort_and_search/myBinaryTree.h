#ifndef _mybinarytree_H_
#define _mybinarytree_H_

#include <vector>
#include <string>
#include <iomanip>

using namespace std;

template<typename key, typename obj>
class TreeNode
{
    public:
        TreeNode( key aKey, obj aObj ) : mKey(aKey), mObj(aObj), mLeft(NULL), mRight(NULL) { }
        ~TreeNode()
        {
            if( mLeft )
                delete mLeft;
            if( mRight )
                delete mRight;
        }

        const key mKey;
        const obj mObj;
        TreeNode* mLeft;
        TreeNode* mRight;
};

template<typename key, typename obj> unsigned int computeTreeDepth( const TreeNode<key,obj>* aTree )
{
    if( aTree == NULL )
        return 0;
    else
        return 1 + max( computeTreeDepth(aTree->mLeft), computeTreeDepth(aTree->mRight) );
}

template<typename key, typename obj> string treeAsString( const TreeNode<key,obj>* aTree )
{
    string ret = "";

    if( aTree == NULL )
    {
        ret = "N";
    }
    else
    {
        ret = ret.append( std::to_string( aTree->mKey ));

        if( aTree->mLeft != NULL || aTree->mRight!= NULL)
        {
            ret = ret.append( "(" );
            ret = ret.append( treeAsString<key,obj>(aTree->mLeft) );
            ret = ret.append( "," );
            ret = ret.append( treeAsString<key,obj>(aTree->mRight) );
            ret = ret.append( ")" );
        }
    }

    return ret;
}

template<typename key, typename obj> string treeInfoAsString( const TreeNode<key,obj>* aTree )
{
    string info = "Tree Depth : ";
    info = info.append( std::to_string(computeTreeDepth<key,obj>(aTree)) );
    info = info.append("\n");
    info = info.append( treeAsString<key,obj>(aTree) );
    info = info.append("\n");

    return info;
}

template<typename key, typename obj> const TreeNode<key,obj>* search( const key& aKey, const TreeNode<key,obj>* aNode )
{
    if( aNode == NULL )
    {
        return NULL;
    }
    else if( aNode->mKey == aKey )
    {
        return aNode;
    }
    else
    {
        if( aKey < aNode->mKey )
            return search<key,obj>( aKey, aNode->mLeft );
        else
            return search<key,obj>( aKey, aNode->mRight );
    }
}

template<typename key, typename obj> TreeNode<key,obj>* insertNode( const key& aKey, const obj aObj, TreeNode<key,obj>* aNode )
{
    if( aNode == NULL )
    {
        // it is a leafe = place it here
        aNode = new TreeNode<key,obj>(aKey, aObj);
    }
    else
    {
        if( aNode->mKey > aKey )
            aNode->mLeft = insertNode<key,obj>( aKey, aObj, aNode->mLeft ) ;
        else
            aNode->mRight = insertNode<key,obj>( aKey, aObj, aNode->mRight ) ;
    }

    return aNode;
}

template<typename key, typename obj> TreeNode<key,obj>* createUnbalancedBinaryTree( vector<key> keys, vector<obj> objs )
{
    TreeNode<key,obj>* tree = NULL;
    for( size_t i = 0; i < keys.size(); i++ )
    {
        tree = insertNode<key,obj>(keys.at(i), objs.at(i), tree);
    }
    return tree;
}


#endif // _mybinarytree_H_
