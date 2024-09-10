// <<<BFS>>> shortest path from root to target while keep track of visited:

int BFS(Node root, Node target) {
  queue* bfsQ;  // nodes to process 
  set* visited; // visited nodes 
  int step = 0; // steps needed from root to current node
  // INITIALIZATION
  add root to queue;
  add root to visited;
  // BFS
  while (bfsQ is not empty) 
  {
    // iterate nodes already in the queue
    int size = bfsQ.size();
    for (int i = 0; i < size; ++i) 
    {
      Node* cur = the first node in bfsQ;
      return step if cur is target;
      for (Node* next : neighbors of cur) 
      {
          if (next is not in visited) 
          {
              add next to bfsQ;
              add next to visited;
          }
      }
      remove the first node from bfsQ;
    }
    step = step + 1;
  }
  return -1; // no path from root to target
}
