#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below
    if(root == nullptr)
    {
        return true;
    }

    if(depth(root -> left) == depth(root -> right) || ((depth(root -> left) <= 1) && (depth(root -> right) <= 1)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int depth(Node*root){
    if(root == nullptr)
    {
        return 0;
    }

    return max(depth(root -> left) + 1, depth(root -> right) + 1);
}