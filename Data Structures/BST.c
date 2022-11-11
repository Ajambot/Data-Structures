#include <stdio.h>
#include <stdlib.h>

/* The program implements a binary search tree with insert, delete and print functions.
 * In main, it creates a BST, inserts 5 nodes and prints the tree. Then it deletes 2 and
 * prints the tree again. It works for deleting both leaf and non-leaf nodes
*/

//BST Node Structure
typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

// BST Metadata Structure
typedef struct BST{
    Node* root;
}BST;

// Function to create a BST
BST* createBST()
{
    BST* newBST = (BST*)malloc(sizeof(BST));
    // Initialize default values
    if(newBST)
    {
        newBST->root =NULL;
        return newBST;
    }
}

// Function to insert a node in a BST
Node* insert(Node* root, int data)
{
    if(root==NULL) // If subtree is empty, insert node here
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    // If data <= data in current root, recursively insert data in the left subtree
    if(data<=root->data)
        root->left = insert(root->left, data);
    // If data > data in current root, recursively insert data in the right subtree
    else
        root->right = insert(root->right, data);
    return root;
}

// Function to delete a node in a BST
Node* delete(Node* root, int data)
{
    if(root==NULL) // If current root is NULL, that means node is not in tree, return NULL
        return NULL;
    if(data < root->data) // If data < data in current root, recursively delete data in left subtree
        root->left = delete(root->left, data);
    else if(data > root->data) // If data > data in current root, recursively delete data in right subtree
        root->right = delete(root->right, data);
    else // Current node is the node we want to delete
    {
        if(root->left==NULL) { // If no left subtree, make right subtree the root
            Node* dlt = root->right;
            free(root);
            return dlt;
        }
        if(root->right==NULL) // If no right subtree, make left subtree the root
        {
            Node* dlt = root->left;
            free(root);
            return dlt;
        }
        // Search for inorder successor in left subtree (max node in left subtree)
        Node* dlt = root->left;
        while(dlt->right!=NULL) // Search for inorder successor
            dlt=dlt->right;
        root->data = dlt->data; // copy data from inorder successor to root
        root->left = delete(root->left, dlt->data); // Recursively delete the duplicate data
    }
    return root;
}

// Function to print tree by inorder traversal
void print(Node* root) {
    if(root != NULL) {
        print(root->left);
        printf("%i ", root->data);
        print(root->right);
    }
}



int main() {
    BST* bst = createBST(); // Create BST
    // Insert 5 nodes
    bst->root = insert(bst->root, 23);
    bst->root = insert(bst->root, 18);
    bst->root = insert(bst->root, 19);
    bst->root = insert(bst->root, 44);
    bst->root = insert(bst->root, 12);
    // Print tree
    printf("Content of the bst (in-order traversal): ");
    print(bst->root);
    printf("\n");
    // Delete 2 Nodes
    bst->root = delete(bst->root, 44);
    bst->root = delete(bst->root, 23);
    // Print tree
    printf("Content of the bst after deleting 2 elements (inorder): ");
    print(bst->root);
    return 0;
}
