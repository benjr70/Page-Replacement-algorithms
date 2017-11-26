//*********************************************
// Ben Rolf
// CSC 250
// Program #8
//*********************************************
#ifndef Charlist_H
#define Charlist_H



// Declare a structure for the list
struct ListNode
{
	int value;              // The value in this node
	int Size;
	int* PT = new int[Size]; 
	struct ListNode *next;  // To point to the next node
};

class Charlist
{  
 

private:
  


   

public:
	ListNode *head;

	// Constructor
	Charlist();
	// Destructor
	~Charlist();
	// Linked list operations
	void appendNode(int);
	void insertNode(int);
	void deleteNode(int);
	void displayList() const;
	int  getRand();
	int getNumofFreeFrames();
	ListNode* getnode(int pid);
};
#endif // Charlist_H
