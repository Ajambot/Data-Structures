#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for the list of edges. An edge in the list represents and undirected edge between u and v with weight w
typedef struct edgeList
{
    char u;
    char v;
    int w;
}edgeList;

// Bubble sorts the array of edges ascendingly by weight
void sort(edgeList edges[], int n)
{
    // Bubble sort
    for(int i=0; i<n; i++)
    {
        for(int o=0; o<n-i; o++)
        {
            if(edges[o].w > edges[o+1].w) // If current edge weight is bigger than next edge weight, swap them
            {
                // Swap code
                edgeList temp;
                temp.u = edges[o+1].u;
                temp.v = edges[o+1].v;
                temp.w = edges[o+1].w;
                edges[o+1].u = edges[o].u;
                edges[o+1].v = edges[o].v;
                edges[o+1].w = edges[o].w;
                edges[o].u = temp.u;
                edges[o].v = temp.v;
                edges[o].w = temp.w;
            }
        }
    }
}

// Given an array of edges and a size of the array, check if there is a cycle in the graph
int isCycle(edgeList edges[], int n)
{
    int visited[256]; // Array of visited vertices
    memset(visited, 0, 256*sizeof(int)); // Initialize visited array to 0
    int ascii = (int)edges[0].u; // get the ascii value of the first vertex
    visited[ascii] = 1; // Visit the first vertex
    for(int i=0; i<n; i++) // for each edge in the array
    {
        ascii = (int)edges[i].v; // get the ascii value of the v vertex
        if(visited[ascii]) // if we already visited it, there's a cycle. Return true
            return 1;
        visited[ascii]=1; // Visit v vertex
    }
    return 0;
}

// Given a graph, find and return the Minimum Spanning Tree using Kruskal's algorithm
edgeList* findMST(edgeList edges[], int n)
{
    edgeList *MST = calloc(n, sizeof(MST)); // allocate memory for MST
    int mstN = 0; // Represents the amount of elements in the MST
    sort(edges, n); // Sort the list of edges by weight
    for(int i=0; i<n; i++)
    {
        // Insert edge i to the MST
        MST[mstN].u = edges[i].u;
        MST[mstN].v = edges[i].v;
        MST[mstN].w = edges[i].w;
        // Check if there is a cycle with the new edge added. if there is don't add the edge to the MST, else add the edge
        if(!isCycle(MST, mstN+1)) mstN++;
    }
    return MST; // return our resulting MST
}

// Prints a graph by printing the list of edges
void Print(edgeList edges[], int n)
{
    // Traverse through every edge and print it
    for(int i=0; i<n; i++)
    {
        printf("\t%c<->%c weight: %i\n", edges[i].u, edges[i].v, edges[i].w);
    }
}


int main() {
    edgeList edges[1000]; // Graph. Can have at most 1000 edges
    int vertices = 5; // number of vertices in the list
    int edgeNumber=7; // number of edges in the list
    // Add 7 edges to the list
    edges[0].u = 'A';
    edges[0].v = 'B';
    edges[0].w = 5;
    edges[1].u = 'B';
    edges[1].v = 'C';
    edges[1].w = 6;
    edges[2].u = 'C';
    edges[2].v = 'E';
    edges[2].w = 8;
    edges[3].u = 'B';
    edges[3].v = 'E';
    edges[3].w = 4;
    edges[4].u = 'A';
    edges[4].v = 'E';
    edges[4].w = 7;
    edges[5].u = 'D';
    edges[5].v = 'E';
    edges[5].w = 2;
    edges[6].u = 'A';
    edges[6].v = 'D';
    edges[6].w = 1;
    printf("Initial Graph:\n");
    Print(edges, edgeNumber); // Print the initial graph
    edgeList *MST = findMST(edges, edgeNumber); // Find the MST of the graph
    printf("MST:\n");
    Print(MST, vertices-1); // Print the MST. The number of edges = vertices-1 since each node (except the root) has an in-degree of 1
    int sum=0;
    for(int i=0; i<vertices-1; i++)
        sum+=MST[i].w;
    printf("\nSum of weights of edges in MST = %i\n", sum);


    return 0;
}
