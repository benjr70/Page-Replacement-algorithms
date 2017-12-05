/********************************************************************
***  NAME       :  Ben Rolf      ***
***  CLASS      :  CSc 300       ***
***  ASSIGNMENT :  Assignment 2  ***
***  DUE DATE   :  10/7/15       ***
***  INSTRUCTOR :  GAMRADT       ***
*********************************************************************
***  DESCRIPTION :This class creates a dynamic array stack with functions               ***
*** for push, pop , view from top from bottom, view bottom to top, destructor, default  ***
*** constructor, parameterized constructor, copy constructor.                           ***
********************************************************************/
#ifndef rolfb2_H
#define rolfb2_H

struct stackNode{
	int pid;
	int logicalAdress;
};

class Stack300{

public:
    Stack300();                     //constructor, creates a new stack with default size.
    Stack300(const int);            //user defined size, creates a new stack with any size, you input.
    Stack300(Stack300 &);           //copy constructor, accepts stack300 object and creates a new stack with the same values as the input object.
    ~Stack300();                    //destructor, deletes the stack.

    void push300(const stackNode); // requires an input of element300 type, then pushes that to the top of the stack.
    stackNode* pop300();            // pops of the top element of the stack and then returns that value.
    void viewTB300();               // displays the stack from top to bottom.
    void viewBT300();               // displays the stack from bottom to top.

private:
    const int MAX_STACK;
    stackNode *stackArray;
    int top;

};
#endif // rolfb2_H
