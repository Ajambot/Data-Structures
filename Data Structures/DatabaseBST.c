#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

// Program to save usernames and phones in a BST. Available operations are: insertion,
// deletion, search and print

//BST Node Structure
typedef struct Node{
    char *name;
    int number;
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

// Function to compare two names lexicographically
int compareName(char name[], Node* root)
{
    // Check character per character to see if they are different values. Return -1 if name is < key, 1 if name>key and 0 if name=key
    for(int i=0; name[i]!='\0' || root->name[i]!='\0'; i++) {
        if(tolower(name[i]) < tolower(root->name[i]))
            return -1;
        if (tolower(name[i]) > tolower(root->name[i]))
            return 1;
    }
    return 0;
}

// Function to insert a node in a BST
Node* insert(Node* root, char name[], int number)
{
    if(root==NULL) // If subtree is empty, insert node here
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->name = name;
        newNode->number = number;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    // If data <= data in current root, recursively insert data in the left subtree
    if(compareName(name, root)==-1 || !compareName(name, root))
        root->left = insert(root->left, name, number);
    // If data > data in current root, recursively insert data in the right subtree
    else
        root->right = insert(root->right, name, number);
    return root;
}

// Function to delete a node in a BST
Node* delete(Node* root, char name[])
{
    if(root==NULL) // If current root is NULL, that means node is not in tree, return NULL
        return NULL;
    if(compareName(name, root)==-1) // If data < data in current root, recursively delete data in left subtree
        root->left = delete(root->left, name);
    else if(compareName(name, root)==1) // If data > data in current root, recursively delete data in right subtree
        root->right = delete(root->right, name);
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

        // copy data from inorder successor to root
        strcpy(root->name, dlt->name);
        root->number = dlt->number;
        root->left = delete(root->left, root->name); // Recursively delete the duplicate data
    }
    return root;
}

// Function to search if a specific name is in the list
int search(Node* root, char* name)
{
    if(root==NULL) // If we reach a leaf, name is not in list. return false
        return 0;

    if(compareName(name, root)==-1) // If name < key, check left subtree
        return search(root->left, name);
    if(compareName(name, root)==1) // If name > key, check right subtree
        return search(root->right, name);
    return 1; // else, name=key, so return true
}

// Function to print tree by inorder traversal to file
void print(Node* root, FILE* ptr) {
    if(root != NULL) {
        print(root->left, ptr);
        printf("%s, %i\n", root->name, root->number);
        fprintf(ptr, "%s, %i\n", root->name, root->number);
        print(root->right, ptr);
    }
}

int main() {
    FILE* ptr;
    //Opening file in reading mode
    ptr = fopen("Test.txt", "r");

    if (ptr==NULL) { // Check if file exists
        printf("file can't be opened \n");
        return 1;
    }

    BST* tree = createBST(); // create tree with predefined function
    for(int i=0; i<10; i++)
    {
        char* name = (char*)malloc(sizeof(char)); // dynamically allocate space for string
        int num;
        // Get name from file until we reach a space or a comma
        char c = fgetc(ptr);
        int end;
        for(int i=0; c!=' ' && c!=','; i++)
        {
            name[i]=c;
            c=fgetc(ptr);
            end=i;
        }
        name[++end]='\0'; // append null character at the end of string since malloc does not initialize string
        fscanf(ptr, "%i", &num); // read telephone number
        fscanf(ptr, "%c", &c); // read line break \n
        tree->root = insert(tree->root, name, num); // Insert new data
    }

    // Menu code
    while(1) {
        printf("Options:\n1. Search for a name\n2. Insert a new user\n"
               "3. Delete an existing user\n4. Print current list to file and end program\n");
        int option;
        scanf("%i", &option);
        switch (option) { // Menu case handler
            case 1: // Perform search
                char name[100];
                printf("Enter user name to search for: ");
                scanf("%s", name);
                printf("Element %s", (search(tree->root, name))? "found in list\n": "not found in list\n");
                break;
            case 2: // insert value
                int num;
                char *name2;
                name2 = (char *) malloc(sizeof(char)); // allocate memory for string to insert
                printf("Enter user name and phone number (separated by space): ");
                scanf("%s", name2);
                scanf("%i", &num);
                tree->root = insert(tree->root, name2, num); // insert new data
                printf("\n");
                break;
            case 3: // delete value
                char name3[100];
                printf("Enter user name to delete: ");
                scanf("%s", name3);
                tree->root = delete(tree->root, name3);
                printf("\n");
                break;
            case 4: // Print to file and end program
                ptr = fopen("Test.txt", "w"); // Open file in write mode
                print(tree->root, ptr); // Print to file in inorder traversal
                fclose(ptr); // Close file
                return 0; // end program
        }
    }
    fclose(ptr); // Close file
    return 0;
}
