/********************************************************************
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
Stack300::Stack300():MAX_STACK(100),stackArray(NULL)
{
    top = -1;
    stackArray = new stackNode[MAX_STACK];

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
/*
Stack300::Stack300(const int x):MAX_STACK(x),stackArray(NULL)
{
    top = -1;
    stackArray = new stackNode[MAX_STACK]; 

    if( stackArray == NULL){
        cout<<"Error creating stack";
    }
}
*/
/********************************************************************
***  FUNCTION Stack300                                            ***
*********************************************************************
***  DESCRIPTION   : copy constructor for stack                   ***
***  INPUT ARGS    : pointer to stack object                      ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
/*
Stack300::Stack300(Stack300& old):MAX_STACK(old.MAX_STACK),stackArray(NULL)
{
    stackArray = new stackNode[MAX_STACK];
    top = -1;

Stack300 t(old.MAX_STACK);
//Element300 x = 0;

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
*/
/********************************************************************
***  FUNCTION Stack300                                            ***
*********************************************************************
***  DESCRIPTION   : destructor for stack                         ***
***  INPUT ARGS    : none                                         ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
/*
Stack300::~Stack300()
{

while(top != -1)
    {
        pop300();
    }

delete stackArray;
}
*/
/********************************************************************
***  FUNCTION push300                                             ***
*********************************************************************
***  DESCRIPTION   : pushes a new value onto the stack            ***
***  INPUT ARGS    : none                                         ***
***  OUTPUT ARGS   : none                                         ***
***  IN/OUT ARGS   : none                                         ***
***  RETURN        : none                                         ***
********************************************************************/
void Stack300::push300(int pid, int logicaladdress)
{


if(top < MAX_STACK - 1){
	top++;
	stackArray[top].pid = pid;
	stackArray[top].logicalAddress = logicaladdress;
}
else{
    //cout<<"stack is full";
}

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
stackNode* Stack300::pop300()
{
stackNode *tempNode;

    if(top != -1){
     	tempNode->pid = stackArray[top].pid;
		tempNode->logicalAddress = stackArray[top].logicalAddress;
		top = top - 1;
    }
    else{
       // cout<<"stack empty";
	}

return tempNode;
}


void Stack300::getLRU(int &pid, int &logicaladdress){
int tophold = top;
Stack300 temp;
stackNode *tempNode;

while(top + 1 > 0)//while loop that puts stacks into temp stack
    {
    tempNode = pop300();
    temp.push300(tempNode->pid, tempNode->logicalAddress);

    }

	tempNode = temp.pop300();
	pid = tempNode->pid;
	logicaladdress = tempNode->logicalAddress;

while(top < tophold)//puts temp back into stack while printing the stack
    {

    tempNode = temp.pop300();
    push300(tempNode->pid, tempNode->logicalAddress);

    }


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

int tophold = top;
 stackNode *x;


for(int x = 0; x <= top; x++){

cout << "pid: " << stackArray[x].pid << " logaddress: " << stackArray[x].logicalAddress <<"\n";
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
/*
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
*/

