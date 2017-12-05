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
#include "rolfb2.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/********************************************************************
***  FUNCTION Stack300                                            ***
*********************************************************************
***  DESCRIPTION   : default constructor for stack                ***
***  INPUT ARGS    : none                                         ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
Stack300::Stack300():MAX_STACK(3),stackArray(NULL)
{
    top = -1;
    stackArray = new Element300[MAX_STACK];

    if( stackArray == NULL){
        cout<<"Error creating stack";
        }
}

/********************************************************************
***  FUNCTION Stack300                                            ***
*********************************************************************
***  DESCRIPTION   : parameterized constructor for stack          ***
***  INPUT ARGS    : const int for size of array                  ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
Stack300::Stack300(const int x):MAX_STACK(x),stackArray(NULL)
{
    top = -1;
    stackArray = new Element300[MAX_STACK]; 

    if( stackArray == NULL){
        cout<<"Error creating stack";
    }
}

/********************************************************************
***  FUNCTION Stack300                                            ***
*********************************************************************
***  DESCRIPTION   : copy constructor for stack                   ***
***  INPUT ARGS    : pointer to stack object                      ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
Stack300::Stack300(Stack300& old):MAX_STACK(old.MAX_STACK),stackArray(NULL)
{
    stackArray = new Element300[MAX_STACK];
    top = -1;

Stack300 t(old.MAX_STACK);
Element300 x = 0;

while(old.top != -1)
    {
    x = old.pop300();
    t.push300(x);
    }

while( t.top != -1)
    {
    x = t.pop300();
    old.push300(x);
    push300(x);
    }


    if( stackArray == NULL){
        cout<<"Error creating stack";
    }

}

/********************************************************************
***  FUNCTION Stack300                                            ***
*********************************************************************
***  DESCRIPTION   : destructor for stack                         ***
***  INPUT ARGS    : none                                         ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
Stack300::~Stack300()
{

while(top != -1)
    {
        pop300();
    }

delete stackArray;
}

/********************************************************************
***  FUNCTION push300                                             ***
*********************************************************************
***  DESCRIPTION   : pushes a new value onto the stack            ***
***  INPUT ARGS    : none                                         ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
void Stack300::push300(const Element300 item)
{

if(top < MAX_STACK - 1)
    {
    top++;
    stackArray[top] = item;
    }
else
    cout<<"stack is full";

}

/********************************************************************
***  FUNCTION pop300                                              ***
*********************************************************************
***  DESCRIPTION   : pops the top value off of stack(deletes top value)***
***  INPUT ARGS    : none                                         ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : the popped value                             ***
********************************************************************/
Element300 Stack300::pop300()
{
Element300 x = 0;

    if(top != -1)
    {
        x = stackArray[top];
        top = top - 1;
    }
    else
        cout<<"stack empty";

return x;
}

/********************************************************************
***  FUNCTION viewTB300                                           ***
*********************************************************************
***  DESCRIPTION   : views stack from top to bottom               ***
***  INPUT ARGS    : none                                         ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
void Stack300 :: viewTB300()
{
Stack300 temp(MAX_STACK);
int tophold = top;
Element300 x = 0;

cout<<"TOP->BOTTOM"<<endl;
cout<<"TOP->";

while(top + 1 > 0)//while loop that puts the values into temp while printing the values
    {
    x = pop300();
    cout<<x<<"->";
    temp.push300(x);
    }
cout<<"BOTTOM";

while(top < tophold)//puts values of temp back into the stack
    {
    x = temp.pop300();
    push300(x);
    }

}

/********************************************************************
***  FUNCTION viewBT300                                           ***
*********************************************************************
***  DESCRIPTION   : Views stack from bottom to top               ***
***  INPUT ARGS    : none                                         ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
void Stack300::viewBT300()
{
Stack300 temp(MAX_STACK);
Element300 x = 0;
int tophold = top;

cout<<"BOTTOM<-TOP"<<endl;
while(top + 1 > 0)//while loop that puts stacks into temp stack
    {
    x = pop300();
    temp.push300(x);

    }

cout<<"BOTTOM";
while(top < tophold)//puts temp back into stack while printing the stack
    {

    x = temp.pop300();
     cout<<x<<"<-";
    push300(x);

    }
cout<<"TOP";

}
