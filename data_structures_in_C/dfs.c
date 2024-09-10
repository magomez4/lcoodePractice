// RECURSIVE
bool dfs(node* currNode, node* target)
{
    if(currNode == target)
    {
        return true;
    }
    for(int i = 0; i< neighbors; i++)
    {
        // service neighbor node
        if(neighbor not seen)
        {
            // mark neighbor as seen
            return dfs(currNode->neighbor[i]);
        }
    }
    return false;
}

// ITERATIVE
bool dfs(nodeType * root, nodeType* target)
{
    stack* dfsStack;
    // mark root seen
    pushStack(dfsStack, root);
    while(dfsStack not empty)
    {
        nodeType currNode = top of stack;
        // remove currNode from stack
        if(currNode == target)
        {
            return true;
        }
        for(int i = 0; i< currNode->Neighbors; i++)
        {
            // service neighbor node
            if(neighbor not seen)
            {
                // mark neighbor as seen
                pushStack(dfsStack, neighbor);
            }
        }
    }
    return false;
}