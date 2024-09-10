int dsuFind(int* dsu, int val)
{
    if(dsu[val] > -1)
    {
        dsu[val] = dsuFind(dsu, dsu[val]);
        return dsu[val];
    }
    return val;
}

// NOTE: if we need to keep track of 
// number of roots, we pass it as a 
// parameter of dsuUnion and every
// time we make a union, reduce the
// number of roots by 1.
void dsuUnion(int* dsu, int v1, int v2)
{
    int v1Root = dsuFind(dsu, v1);
    int v2Root = dsuFind(dsu, v2);
    if(v1Root != v2Root)
    {
        // we can join these two sets
        // find their ranks
        int root1Rank = (-1)*dsu[v1Root];
        int root2Rank = (-1)*dsu[v2Root];
        int newRank = dsu[v1Root] + dsu[v2Root];
        if(root1Rank >= root2Rank)
        {
            dsu[v2Root] = v1Root;
            dsu[v1Root] = newRank;
        }
        else
        {
            dsu[v1Root] = v2Root;
            dsu[v2Root] = newRank;
        }
    }
    // we don't have to do any work if
    // the roots are the same because it
    // means they are already a single set.
    // THIS IS WHERE WE WOULD PUT A RETURN
    // IN AN ELSE STATEMENT WITH A -1 IF
    // WE NEEDED TO DETECT A CYCLE
}
