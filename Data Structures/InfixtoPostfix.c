#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * Description: Program uses a character stack to transform a string containing an infix expression to a postfix expression.
 * It also evaluates an infix expression by transforming it into postfix and then using a double stack to get the result.
 * (Both processes explained further below).
*/

// Node for the character stack
typedef struct Node_char{
    char op; // op stands for operator
    struct Node_char* next;
}Node_char;

// Node for the double stack
typedef struct Node_double{
    double data;
    struct Node_double* next;
}Node_double;

// Character Stack. We use it for infix to postfix function
typedef struct Stack_char{
    int count;
    Node_char* top;
}Stack_char;

// double Stack. We use it for evaluate expression function
typedef struct Stack_double{
    int count;
    Node_double* top;
}Stack_double;

// create a character stack
Stack_char* createStack_char()
{
    Stack_char *stack = (Stack_char*)malloc(sizeof(Stack_char)); // allocate memory
    if(stack) { // If malloc worked
        // Then, initialize stack with default values
        stack->top = NULL; //
        stack->count = 0;
        return stack;
    }
}

// Create double Stack
Stack_double* createStack_double()
{
    Stack_double *stack = (Stack_double*)malloc(sizeof(Stack_double)); //  allocate memory
    if(stack) { // if malloc worked
        // Then, initialize stack with default values
        stack->top = NULL;
        stack->count = 0;
        return stack;
    }
}

// Push into the double stack. We insert at the front/head/top
int push_double(Stack_double *stack, double data)
{
    Node_double * newNode = (Node_double *)malloc(sizeof(Node_double)); // allocate memory for newNode
    if(newNode) // if malloc worked
    {
        newNode->data = data; // initialize data of newNode
        newNode->next = stack->top; // Stack top is next to the newNode
        stack->top = newNode; // top becomes the newNode
        (stack->count)++; // NodeCount+1
        return 1;
    }
    return 0;
}

// Push into the character stack. We insert at the front/head/top
int push_char(Stack_char *stack, char op)
{
    Node_char * newNode = (Node_char*)malloc(sizeof(Node_char)); // allocate memory for newNde
    if(newNode) // If malloc worked
    {
        newNode->op = op; // initialize op
        newNode->next = stack->top; // the next node of newNode is top
        stack->top = newNode; // top is now newNode
        (stack->count)++; // NodeCount+1
        return 1;
    }
    return 0;
}

// Pop from the character stack
char pop_char(Stack_char* stack)
{
    char retValue = '?'; // dummy value in case the stack is empty
    if((stack->count)==0) { // if stack is empty, we cannot pop. Error
        printf("Stack is empty");
        return retValue;
    }
    Node_char* dlt = stack->top; // Top is the node we want to delete
    retValue = dlt->op; // Save the operator in the top node to return it once we pop
    stack->top = dlt->next; // top is now top->next
    free(dlt); // pop
    (stack->count)--; // NodeCount-1
    return retValue;
}

// Pop from the double stack
double pop_double(Stack_double* stack)
{
    double retValue = -1.0; // dummy value to return in case stack is empty
    if((stack->count)==0) { // if stack is empty, we cannot pop, error.
        printf("Stack is empty");
        return retValue;
    }
    Node_double* dlt = stack->top; // the node we want to delete is at the top
    retValue = dlt->data; // save data in the top node to return after pop
    stack->top = dlt->next; // Top is now the node after the current top (top->next)
    free(dlt); // pop
    (stack->count)--; // NodeCount-1
    return retValue;
}

// Classifies an operator according to the precedence (order of operations)
int classifyOp(char op)
{
    if(op=='+' || op=='-')
        return 1;
    if(op=='*' || op=='/' || op=='%')
        return 2;
    if(op=='^')
        return 3;
    // Parenthesis are -1 because we want to push values into the stack after '('. If we put that parenthesis return 4, when we try to push
    // after a parenthesis it will pop the parenthesis because the condition of the character at the top of the stack being bigger than the
    // current will not hold true. We handle the case of pushing a parenthesis separately since this is a special case
    if(op=='(' || op==')')
        return -1;
    return 0; // return 0 if op is not an operator (ex. if op='A')
}

/*void print(Stack* stack)
{
    Node* ptr = stack->top;
    while(ptr!=NULL)
    {
        printf("%c", ptr->op);
        ptr=ptr->next;
    }
    printf("\n");
}*/


// Transforms infix expression to postfix expression using a character stack
char* infixtoPostfix(char exp[])
{
    int cur=0; // we start at the first character of the infix expression
    char *postfix = (char*)malloc(400*sizeof(char)); // allocate space for postfix string
    Stack_char* stack = createStack_char(); // Create a character stack to hold the operators
    memset(postfix, '\0', 400); // Fill the postfix string with 0s

    for(int i=0; exp[i]!='\0'; i++) // Iterate through the infix string until we reach the end ('\0')
    {
        //printf("%s ", postfix);
        int opClass = classifyOp(exp[i]); // Classify the current character
        int topClass=-1; // Holds the classification of the top of the stack. Dummy value -1 in case the stack is empty
        if((stack->count)!=0){ // if the stack isn't empty
            topClass = classifyOp(stack->top->op); // classify the top of the stack
        }
        //printf("%i %i\n", opClass, topClass);
        //print(stack);

        if(opClass==0) // If current character is not an operator
            postfix[cur++] = exp[i]; // push it to the output
        else if(exp[i]=='(') // If current char is a '('
            push_char(stack, exp[i]); // push it to the stack
        else if(exp[i]==')') { // If current char is ')'
            // Pop from the stack and push to the output until we find a '(' at the top of the stack
            while ((stack->top->op) != '(') {
                postfix[cur++] = pop_char(stack);
            }
            pop_char(stack); // Pop the '('
        }
        else // current character is one of the other operators "+-*/%^"
        {
            // while the stack is not empty, and the operator at the top of the stack does not come before the current character,
            // and the top and op characters are not equal to '^' (we handle '^' differently since it has right to left precedence)
            while((stack->count) && topClass>=opClass && (opClass!=3 && topClass!=3))
            {
                postfix[cur++] = pop_char(stack); // pop the top of the stack to the output
                if(stack->count) // if stack is not empty
                    topClass = classifyOp(stack->top->op); // classify the top of the stack again since we popped
            }
            push_char(stack, exp[i]); // If current operator precedes top operator, then we push it to the stack
            // If we have multiple '^' operators next to each other, we also push to the stack since it's right to left precedence
        }
    }
    // If we have traversed through the whole expression, then we pop the remaining characters in the stack to the output
    while((stack->count)!=0)
    {
        postfix[cur++]=pop_char(stack);
    }
    return postfix;
}

// Function to evaluate an infix expression
double evalExpression(char exp[])
{
    exp = infixtoPostfix(exp); // We transform the expression to postfix first
    //printf("%s\n", exp);
    Stack_double* stack = createStack_double(); // We use a double stack to evaluate the expression, since we will be pushing just the doubles in the stack
    for(int i=0; exp[i]!='\0'; i++) // Traverse to the string until we reach the end
    {
        //print(stack);
        double a, b; // a and b are operands
        if(!classifyOp(exp[i])) // If the current operator is 0 (i.e. if it's not an operator, but a number)
            push_double(stack, exp[i]-'0'); // Typecast to double and push to the stack
        else // If current character is an operator "+-*/%^"
        {
            // Pop the top 2 elements to operate
            b=pop_double(stack);
            a=pop_double(stack);
            //printf("%i %i\n", a, b);
            if(exp[i]=='+')
                push_double(stack, a+b); // push result of a+b to the stack
            else if(exp[i]=='-')
                push_double(stack, a - b); // Push result of a-b to the stack
            else if(exp[i]=='*')
                push_double(stack, a*b); // Push result of a*b to the stack
            else if(exp[i]=='/')
                push_double(stack, a/b); // Push result of a/b to the stack
            else if(exp[i]=='%')
                push_double(stack, fmod(a, b)); // Push result of a%b to the stack
            else if(exp[i]=='^')
                    push_double(stack, pow(a, b)); // Push result of a^b to the stack
        }
    }
    double ans = pop_double(stack); // Result of expression is the only element in stack. Pop it!
    return ans;
}

int main() {
    char exp2[400] = "A+B/C*(D-A)^F^H";
    char exp[400] = "9+3/2*(5-2)^2^3";
    printf("%s", infixtoPostfix(exp2));
    printf("\n");
    printf("%s", infixtoPostfix(exp));
    printf("\n");
    printf("%f\n", evalExpression(exp));
    return 0;
}
