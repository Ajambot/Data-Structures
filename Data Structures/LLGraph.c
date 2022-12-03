#include <stdio.h>
#include <stdlib.h>

// Edge structure
typedef struct Edge{
    char name;
    int weight;
    struct Edge* next;
}Edge;

// Vertex structure
typedef struct Vertex{
    char name;
    struct Vertex* next;
    Edge* edge;
}Vertex;

// Graph meta-structure
typedef struct Graph{
    Vertex* head;
    int count;
    Vertex* tail;
}Graph;

// createEdge allocates memory and initializes a new edge
Edge* createEdge(char name, int weight)
{
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    if(edge)
    {
        edge->name= name;
        edge->weight = weight;
        edge->next=NULL;
        return edge;
    }
}

// createVertex allocates memory and initalizes newVertex
Vertex* createVertex(char name)
{
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
    if(vertex)
    {
        vertex->name= name;
        vertex->next=NULL;
        vertex->edge=NULL;
        return vertex;
    }
}

// createGraph allocates memory and initializes a new graph
Graph* createGraph()
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if(graph)
    {
        graph->head=NULL;
        graph->count=0;
        graph->tail = NULL;
        return graph;
    }
}

// Searches for a vertex in an existing graph. Returns reference to vertex if found, else returns NULL
Vertex* search(Graph* graph, char c)
{
    Vertex* ptr = graph->head;
    while(ptr!=NULL && ptr->name != c) ptr=ptr->next;
    return ptr;
}

// Adds an edge between two vertices to an existing graph. If any of the vertices do not exists, it creates them
void newEdge(Graph* graph, char u, char v, int weight)
{
    // if graph is empty, create u and v vertices and add them to graph including edges to each other
    if(graph->head == NULL)
    {
        graph->head = createVertex(u);
        graph->head->next = createVertex(v);
        graph->tail = graph->head->next;
        graph->head->edge = createEdge(v, weight);
        graph->tail->edge = createEdge(u, weight);
        (graph->count)+=2;
    }
    else // graph is not empty
    {
        // If u is not is graph, create it and add it with its respective edge
        if(search(graph, u)==NULL) {
            graph->tail->next = createVertex(u);
            graph->tail = graph->tail->next;
            graph->tail->edge = createEdge(v, weight);
            (graph->count)++;
        }
        else // u is in graph
        {
            if(search(graph, u)->edge == NULL) // if u has no edges, create edge to v and add it
                search(graph, u)->edge = createEdge(v, weight);
            else // u has at least 1 edge. Traverse until the end of the list of edges and append v
            {
                Edge* edge = search(graph, u)->edge;
                while(edge->next !=NULL) edge=edge->next;
                edge->next = createEdge(v, weight);
            }
        }
        // If v is not is graph, create it and add it with its respective edge
        if(search(graph, v)==NULL) {
            graph->tail->next = createVertex(v);
            graph->tail = graph->tail->next;
            graph->tail->edge = createEdge(u, weight);
            (graph->count)++;
        }
        else // v is in graph
        {
            if(search(graph, v)->edge == NULL) // if v has no edges, create edge to u and add it
                search(graph, v)->edge = createEdge(u, weight);
            else // v has at least 1 edge. Traverse until the end of the list of edges and append u
            {
                Edge* edge = search(graph, v)->edge;
                while(edge->next !=NULL) edge=edge->next;
                edge->next = createEdge(u, weight);
            }
        }
    }
}

// Prints the graph's vertices and edges
void Print(Graph* graph)
{
    Vertex* ptr = graph->head;
    while(ptr!=NULL)
    {
        printf("%c edges: ", ptr->name);
        Edge* ed = ptr->edge;
        while(ed!=NULL)
        {
            printf("%c(%i) ", ed->name, ed->weight);
            ed=ed->next;
        }
        ptr=ptr->next;
        printf("\n");
    }
}

int main() {
    Graph* graph = createGraph();
    newEdge(graph, 'A', 'B', 5);
    newEdge(graph, 'B', 'C', 3);
    newEdge(graph, 'A', 'C', 7);
    Print(graph);
    return 0;
}
