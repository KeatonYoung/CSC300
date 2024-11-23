#include "graph.h"

Graph::Graph(int maxV)
{
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;
    adjMatrix = new int*[maxVertices];
    for (int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i] = new int[maxVertices];
        for (int j = 0; j < maxVertices; j++)
        {
            adjMatrix[i][j] = 0; 
        }
    }
    visited = new bool[maxVertices]{false}; 
}

Graph::~Graph()
{
    delete[] visited;

    for (int i = 0; i < maxVertices; i++) {
        delete[] adjMatrix[i];  // Free each row
    }
    delete[] adjMatrix;  // Free the array of row pointers

    vertex* tempVertex;
    while (vertices)
    {
        edge* tempEdge;
        while (vertices->aHead)
        {
            tempEdge = vertices->aHead;
            vertices->aHead = vertices->aHead->eNext;
            delete tempEdge;  // Delete each edge
        }

        // Now delete the vertex itself
        tempVertex = vertices;
        vertices = vertices->vNext;
        delete tempVertex; 
    }
}

void Graph::addVertex(char data)
{
    if (numVertices >= maxVertices)
    {
        cout << "Maximum number of vertices reached!" << endl;
        return;
    }

    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->vNext = vertices;
    newVertex->aHead = nullptr;
    newVertex->visited = 0; 
    vertices = newVertex;
    numVertices++;
}

void Graph::addEdge(char src, char dest, int weight)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    // Find the source and destination vertices
    while (srcVertex && srcVertex->data != src)
        srcVertex = srcVertex->vNext;
    while (destVertex && destVertex->data != dest)
        destVertex = destVertex->vNext;

    if (!srcVertex || !destVertex)
    {
        cout << "Vertices not found!" << endl;
        return;
    }

    // Add edge to adjacency list
    edge* newEdge = new edge;
    newEdge->dest = destVertex;
    newEdge->weight = weight;
    newEdge->eNext = srcVertex->aHead;
    srcVertex->aHead = newEdge;

    // Since undirected, add the reverse edge as well
    newEdge = new edge;
    newEdge->dest = srcVertex;
    newEdge->weight = weight;
    newEdge->eNext = destVertex->aHead;
    destVertex->aHead = newEdge;

    // Add edge to adjacency matrix 
    int srcIndex = srcVertex->data - 'A';
    int destIndex = destVertex->data - 'A';
    adjMatrix[srcIndex][destIndex] = weight;
    adjMatrix[destIndex][srcIndex] = weight;
}

void Graph::removeVertex(char data)
{
    // Find the vertex to remove
    vertex* temp = vertices;
    vertex* prev = nullptr;
    while (temp && temp->data != data)
    {
        prev = temp;
        temp = temp->vNext;
    }

    if (!temp)
    {
        cout << "Vertex not found!" << endl;
        return;
    }

    // Remove the vertex from adjacency list of all other vertices
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        edge* e = v->aHead;
        edge* prevEdge = nullptr;
        while (e)
        {
            if (e->dest->data == data)
            {
                if (prevEdge)
                    prevEdge->eNext = e->eNext;
                else
                    v->aHead = e->eNext;
                delete e;
                break;
            }
            prevEdge = e;
            e = e->eNext;
        }
    }

    // Remove vertex from the list
    if (prev)
        prev->vNext = temp->vNext;
    else
        vertices = temp->vNext;

    delete temp;


    // Remove from the adjacency matrix
    int index = temp->data - 'A';
    for (int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i][index] = 0;
        adjMatrix[index][i] = 0;
    }

    numVertices--;

}

void Graph::removeEdge(char src, char dest)
{
   // Complete this
   vertex* srcVertex = vertices;
   while (srcVertex && srcVertex->data != src)
   {
        srcVertex = srcVertex->vNext;
   }
   if(!srcVertex){
    cout << "Source vertex not found!"<< endl;
    return;
   }
   edge* prevEdge = nullptr;
    edge* currEdge = srcVertex->aHead;
    while (currEdge) {
        if (currEdge->dest->data == dest) {
            if (prevEdge)
                prevEdge->eNext = currEdge->eNext;
            else
                srcVertex->aHead = currEdge->eNext;
            delete currEdge;
            break;
        }
        prevEdge = currEdge;
        currEdge = currEdge->eNext;
    }
    vertex* destVertex = vertices;
    while(destVertex && destVertex->data != dest){
        destVertex = destVertex->eNext;
    }
    if(!destVertex){
        cout <<"Destination vertex not found" << endl;
        return;
    }
      prevEdge = nullptr;
    currEdge = destVertex->aHead;
    while (currEdge) {
        if (currEdge->dest->data == src) {
            if (prevEdge)
                prevEdge->eNext = currEdge->eNext;
            else
                destVertex->aHead = currEdge->eNext;
            delete currEdge;
            break;
        }
        prevEdge = currEdge;
        currEdge = currEdge->eNext;
    }

    int srcIndex = src - 'A';
    int destIndex = dest - 'A';
    adjMatrix[srcIndex][destIndex] = 0;
    adjMatrix[destIndex][srcIndex] = 0;
}

void Graph::displayAdjList()
{
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        cout << v->data << " -> ";
        for (edge* e = v->aHead; e != nullptr; e = e->eNext)
        {
            cout << e->dest->data << " ( " << e->weight << ") -> ";
        }
        cout << "null" << endl;
    }
}

void Graph::displayAdjMatrix()
{
    for (int i = 0; i < maxVertices; i++)
    {
        for (int j = 0; j < maxVertices; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}


void Graph::bfsL(char start)
{
    // Reset visited status
    for (int i = 0; i < maxVertices; i++) visited[i] = false;

    // Find the start vertex
    vertex* startVertex = vertices;
    while (startVertex && startVertex->data != start)
        startVertex = startVertex->vNext;
    
    if (!startVertex)
    {
        cout << "Start vertex not found!" << endl;
        return;
    }

    // Initialize queue for BFS traversal
    node* queue = nullptr;
    enqueue(queue, start);  // Enqueue the starting vertex
    visited[startVertex->data - 'A'] = true;

    cout << "BFS using Adjacency List: ";
    while (queue)
    {
        // Dequeue the front vertex
        char currentData = queue->data;
        dequeue(queue);
        cout << currentData << " ";

        // Find the vertex corresponding to the dequeued data
        vertex* currentVertex = vertices;
        while (currentVertex && currentVertex->data != currentData)
            currentVertex = currentVertex->vNext;

        // Traverse adjacent vertices
        for (edge* e = currentVertex->aHead; e != nullptr; e = e->eNext)
        {
            if (!visited[e->dest->data - 'A'])
            {
                enqueue(queue, e->dest->data);
                visited[e->dest->data - 'A'] = true;
            }
        }
    }
    cout << endl;
}

void Graph::bfsM(char start)
{
    // Reset visited status for all vertices
    for (int i = 0; i < maxVertices; i++) {
        visited[i] = false;
    }

    // Find the start vertex index
    int startIndex = start - 'A'; 

    if (startIndex < 0 || startIndex >= maxVertices) {
        cout << "Start vertex not found!" << endl;
        return;
    }

    // Initialize queue for BFS traversal
    node* queue = nullptr;
    enqueue(queue, start); 
    visited[startIndex] = true;

    cout << "BFS using Adjacency Matrix: ";
    while (queue) {
        // Dequeue the front vertex
        char currentData = queue->data;
        dequeue(queue);
        cout << currentData << " ";

        int currentIndex = currentData - 'A'; 

        // Explore all adjacent vertices using the adjacency matrix
        for (int i = 0; i < maxVertices; i++) {
            // If there is an edge (adjMatrix[currentIndex][i] == 1)
            // and the vertex is not visited
            if (adjMatrix[currentIndex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i + 'A');  // Enqueue the unvisited adjacent vertex (convert index to char)
            }
        }
    }
    cout << endl;
}

void Graph::dfsL(char start)
{
    // Complete this
    for (int i = 0; i < maxVertices; i++) visited[i] = false;

    
    vertex* startVertex = vertices;
    while (startVertex && startVertex->data != start)
        startVertex = startVertex->vNext;

    if (!startVertex) {
        cout << "Start vertex not found!" << endl;
        return;
    }

    cout << "DFS using Adjacency List: ";

    
    stack<vertex*> s;
    s.push(startVertex);
    visited[startVertex->data - 'A'] = true;

    while (!s.empty()) {
        vertex* currVertex = s.top();
        s.pop();
        cout << currVertex->data << " ";

        
        for (edge* e = currVertex->aHead; e; e = e->eNext) {
            if (!visited[e->dest->data - 'A']) {
                s.push(e->dest);
                visited[e->dest->data - 'A'] = true;
            }
        }
    }
    cout << endl;

}

void Graph::dfsM(char start)
{
    // Complete this
    for (int i = 0; i < maxVertices; i++) visited[i] = false;

    int startIndex = start - 'A';
    if (startIndex < 0 || startIndex >= maxVertices) {
        cout << "Start vertex not found!" << endl;
        return;
    }

    cout << "DFS using Adjacency Matrix: ";

    
    stack<int> s;
    s.push(startIndex);
    visited[startIndex] = true;

    while (!s.empty()) {
        int currIndex = s.top();
        s.pop();
        cout << (char)(currIndex + 'A') << " ";

        
        for (int i = 0; i < maxVertices; i++) {
            if (adjMatrix[currIndex][i] != 0 && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}
bool Graph::detectCycle() {
    for (int i = 0; i < maxVertices; i++) visited[i] = false;

    for (vertex* v = vertices; v; v = v->vNext) {
        if (!visited[v->data - 'A']) {
            if (detectCycleHelper(v, nullptr))
                return true;
        }
    }
    return false;
}

