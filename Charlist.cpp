//*********************************************
// Ben Rolf
// CSC 250
// Program #8
//*********************************************
#include "Charlist.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

//************************************************************
//Constructor
//creates an empty list list
//************************************************************
Charlist::Charlist()
{
head = NULL;     //starts head as null
}




//************************************************************
// appendNode
// append new char to the end of the linked list
//************************************************************
void Charlist::appendNode(int value)
{
   ListNode *newNode;  // To point to a new node
   ListNode *nodePtr;  // To move through the list

   // Allocate a new node and store num there.
   newNode = new ListNode;
   newNode->value = value;
   newNode->next = NULL;

   // If there are no nodes in the list
   // make newNode the first node.
   if (head == NULL)
      head = newNode;
   else  // Otherwise, insert newNode at end.
   {


      // Initialize nodePtr to head of list.
      nodePtr = head;

      // Find the last node in the list.
      while (nodePtr->next)
         nodePtr = nodePtr->next;

      // Insert newNode as the last node.
      nodePtr->next = newNode;


   }

}

//************************************************************
//insertNode
//insert a char in order
//************************************************************
void Charlist::insertNode(int value)
{
   ListNode *newNode;					// A new node
   ListNode *nodePtr;					// To traverse the list
   ListNode *previousNode = NULL;	// The previous node

   // Allocate a new node and store num there.
   newNode = new ListNode;
   newNode->value = value;

   // If there are no nodes in the list
   // make newNode the first node
   if (!head)
   {
      head = newNode;
      newNode->next = NULL;
   }
   else  // Otherwise, insert newNode
   {
      // Position nodePtr at the head of list.
      nodePtr = head;

      // Initialize previousNode to nullptr.
      previousNode = NULL;

      // Skip all nodes whose value is less than num.
      while (nodePtr != NULL && nodePtr->value < value)
      {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If the new node is to be the 1st in the list,
      // insert it before all other nodes.
      if (previousNode == NULL)
      {
         head = newNode;
         newNode->next = nodePtr;
      }
      else  // Otherwise insert after the previous node.
      {
         previousNode->next = newNode;
         newNode->next = nodePtr;
      }
   }
}


//************************************************************
//delete Node
// delete node will delete the node that the user selected using the char value
//************************************************************
void Charlist::deleteNode(int value)
{
   ListNode *nodePtr;       // To traverse the list
   ListNode *previousNode;  // To point to the previous node

   // If the list is empty, do nothing.
   if (!head)
      return;

   // Determine if the first node is the one.
   if (head->value == value)
   {
      nodePtr = head->next;
      delete head;
      head = nodePtr;
   }
   else
   {
      // Initialize nodePtr to head of list
      nodePtr = head;

      // Skip all nodes whose value member is
      // not equal to num.
      while (nodePtr != NULL && nodePtr->value != value)
      {
         previousNode = nodePtr;
         nodePtr = nodePtr->next;
      }

      // If nodePtr is not at the end of the list,
      // link the previous node to the node after
      // nodePtr, then delete nodePtr.
      if (nodePtr)
      {
         previousNode->next = nodePtr->next;
         delete nodePtr;
      }
   }
}



//************************************************************
//display list
//displays the linked list
//************************************************************
void Charlist::displayList() const
{
   ListNode *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr points to a node, traverse
   // the list.
   while (nodePtr)
   {
      // Display the value in this node.
      cout << nodePtr->value << " ";

      // Move to the next node.
      nodePtr = nodePtr->next;
   }
}
//************************************************************
// returns node of the pid given
//************************************************************
ListNode* Charlist::getnode(int pid) {


	if (head == NULL) {
		return head;
	}
	ListNode *nodePtr = head;

	while (nodePtr != NULL) {
			
			if (nodePtr->value ==  pid) {
				return nodePtr;
			}
			nodePtr = nodePtr->next;
		}

		return NULL;
	

}
//******************************************
// finds a random free frame a page to be assigned to
//*******************************************
int  Charlist::getRand(){

	int count = 0;
	ListNode *nodePtr = head;
	while (nodePtr != NULL) {
		count++;
		nodePtr = nodePtr->next;
	}
	
	nodePtr = head;
	int randnum = rand() % count;
	for(int x = 0 ; x < randnum; x++){
	nodePtr = nodePtr->next;
	}
	
	return nodePtr->value;
	
}
//*********************************
// counts the returns the number of free frames
//************************************************
int Charlist::getNumofFreeFrames(){

	int count = 0;
	ListNode *nodePtr = head;
	while (nodePtr != NULL) {
		count++;
		nodePtr = nodePtr->next;
	}
	
return count;


}
//**************************************************
// finds the oldest page and returns the pid and logical address
// for the FIFO replacement algorthim
//**************************************************

void Charlist::getoldestPage(int &pid, int &Frame){

	ListNode *nodePtr = head;
	int smallesttime = 2147483646;

	while (nodePtr != NULL) {
		for(int x = 0; x < nodePtr->Size; x++){
			if(nodePtr->time[x] < smallesttime && nodePtr->PT[x] != -99){
			smallesttime = nodePtr->time[x];
			pid = nodePtr-> value;
			Frame = x;
			}
		}
		nodePtr = nodePtr->next;
	}

}

//************************************************************
//destructor
//this deletes the whole list
//************************************************************
Charlist::~Charlist()
{
   ListNode *nodePtr;   // To traverse the list
   ListNode *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != NULL)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}
