#include <stdio.h>
#include<stdlib.h>

// Structure for Node for Tree
typedef struct TreeNode{
    int *data; // data is an integer pointer, because it needs to be copied when we are queueing in our BFS
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

// Structure for Tree
typedef struct Tree{
    TreeNode* root;
    int count;
}Tree;

// Structure for Node for Queue
typedef struct QNode{
    TreeNode* node;
    struct QNode* next;
}QNode;

// Structure for Queue
typedef struct Queue{
    int count;
    QNode* head;
    QNode* rear;
}Queue;

// Function to Add a root to a tree
int addRoot(Tree* tree, int root)
{
    //allocate memory for root node and root data
    TreeNode* newRoot = (TreeNode*)malloc(sizeof(TreeNode));
    int* rootData = (int*)malloc(sizeof(int));
    if(newRoot && rootData)
    {
        *rootData=root; // Copy root data into root pointer
        newRoot->data = rootData;
        (tree->count)=1;
        //Default values
        newRoot->left = NULL;
        newRoot->right = NULL;
        tree->root=newRoot;
        return 1;
    }
    return 0;
}

// Function to create tree structure
Tree* createTree()
{
    Tree* newTree = (Tree*)malloc(sizeof(Tree)); // allocate memory
    if(newTree){
        // Default values
        newTree->root = NULL;
        newTree->count = 0;
        return newTree;
    }
}

//Function to add a children on either side of a node. If side is l, adds children in left side, if it's r it adds it in right side
int addChildren(Tree* tree, TreeNode* node, int val, char side)
{
    // allocate memory
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    int* newData = (int*)malloc(sizeof(int));
    if(newNode)
    {
        // initialize values
        *newData = val;
        newNode->data = newData;
        newNode->left = NULL;
        newNode->right = NULL;
        //conditionals decide where to append the newNode;
        if(side=='l' || side=='L')
            node->left = newNode;
        if(side=='r' || side=='R')
            node->right=newNode;
        (tree->count)++;
        return 1;
    }
    return 0;
}

// Function to create a Queue
Queue* createQueue()
{
    Queue* newQueue = (Queue*)malloc(sizeof(Queue)); // allocate memory
    if(newQueue)
    {
        // Default values
        newQueue->count=0;
        newQueue->head=NULL;
        newQueue->rear=NULL;
        return newQueue;
    }
}

// Function to enqueue in our queue struct
int enqueue(Queue* queue, TreeNode* node)
{
    QNode* newNode = (QNode*)malloc(sizeof(QNode)); // allocate memory
    if(newNode)
    {
        // initialize
        newNode->node=node;
        newNode->next=NULL;
        //if queue is empty, head and rear are newNode
        if(!(queue->count))
        {
            queue->head = newNode;
            queue->rear = newNode;
            (queue->count)++;
            return 1;
        }
        // else, append newNode at the end of queue
        queue->rear->next=newNode;
        queue->rear=newNode;
        (queue->count)++;
        return 1;
    }
    return 0;
}

// Function to Dequeue from queue struct
void dequeue(Queue* queue)
{
    // If queue is empty, we can't dequeue. Error
    if(queue->count==0)
    {
        printf("Queue is empty\n");
        return;
    }
    QNode* dlt = queue->head;
    queue->head = queue->head->next;
    free(dlt);
    (queue->count)--;
}

// Function to do a Breadth First Search on a tree
void BFS(Tree* tree)
{
    Queue* queue = createQueue(); // Create a queue with our predefined function
    TreeNode* current; // Pointer to current node
    enqueue(queue, tree->root); // We begin our traversal by the root
    while(queue->count!=0) // If queue is empty, we have traversed through all the nodes
    {
        current = queue->head->node; // current is the front of the queue
        printf("%i ", *(current->data)); // Print current data
        // If left and right nodes aren't NULL, we enqueue them
        if(current->left!=NULL)
            enqueue(queue, current->left);
        if(current->right!=NULL)
            enqueue(queue, current->right);
        dequeue(queue);
    }
}

/* We create the following tree and traverse it with a BFS
 *
 *                |-----1-----|
 *             |--2--|     |--3--|
 *             4     5     6     7
 *
 * it should print the numbers from 1-7 in ascendant order
*/
int main() {
    Tree* tree = createTree();
    addRoot(tree, 1);
    addChildren(tree, tree->root, 2, 'L');
    addChildren(tree, tree->root, 3, 'R');
    addChildren(tree, tree->root->left, 4, 'L');
    addChildren(tree, tree->root->left, 5, 'R');
    addChildren(tree, tree->root->right, 6, 'L');
    addChildren(tree, tree->root->right, 7, 'R');
    BFS(tree);
    return 0;
}
