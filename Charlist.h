//*********************************************
// Ben Rolf
// CSC 250
// Program #8
//*********************************************
#ifndef Charlist_H
#define Charlist_H


class Charlist
{
    private:
   // Declare a structure for the list
   struct ListNode
   {
      int value;           // The value in this node
      struct ListNode *next;  // To point to the next node
   };

   ListNode *head;

   public:
       // Constructor
        Charlist();


       // Destructor
        ~Charlist();

   // Linked list operations
   void appendNode(int);
   void insertNode(int);
   void deleteNode(int);
   void displayList() const;
};
#endif // Charlist_H
