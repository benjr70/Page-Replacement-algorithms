#include <iostream>
#include <string>
#include <cstdlib>
#include "Charlist.h"

using namespace std;

//prototypes
void memoryManager(int memSize, int frameSize);
int allocate(int allocSize, int pid);
int deallocate(int pid);
int write(int pid, int logical_address);
int read(int pid, int logical_address);
void printMemory();

//global varibles
char* phy_mem;
Charlist FreeFrameList;
Charlist ProcessList;

int main()
{
	string line;
	int arg1 = -99;
	int arg2 = -99;
    char temp[50];
do{
	getline(cin,line);
    int index = 2;
    int tempI = 0;
    while(isdigit(line[index]) && line[index] != '\0'){
        temp[tempI] = line[index];
        index++;
        tempI++;
    }
    temp[tempI] = '\0';
    arg1 = atoi(temp);
    index++;
    tempI = 0;
    while(isdigit(line[index]) && line[index] != '\0'){
        temp[tempI] = line[index];
        index++;
        tempI++;
    }
    temp[tempI] = '\0';
    arg2 = atoi(temp);


    switch(line[0]){
        case 'M' : memoryManager(arg1, arg2);
            break;
        case 'A' : allocate(arg1, arg2);
            break;
        case 'W' : write(arg1, arg2);
            break;
        case 'R' : read(arg1, arg2);
            break;
        case 'D' : deallocate(arg1);
            break;
        case 'P' : printMemory();
            break;
        case 'E' :
            break;
        default  : cout << "command dose not exist \n";
    }
}while(line != "Exit");
delete [] phy_mem;
return 0;
}

//*******************************************
// input is memSize and FrameSize from the user
// creates the physical memory space based on the users input
// also creates a full free frame list
//*******************************************
void memoryManager(int memSize, int frameSize){

    //cout << "in Memory Manger\nmemSize: " << memSize << "\nFramSize: " << frameSize << "\n";
	memSize = memSize/frameSize;
    phy_mem = new char[memSize];
    for(int x = 0; x < memSize; x++){
        phy_mem[x] = '0';
	FreeFrameList.appendNode(x);
    }
	phy_mem[memSize + 1] = '\0'; //sizeof() does not work when dynamic so this marks the array end with \0
}
//*******************************************
// inputs are allocsize and pid from user
// allocates random frames from the free frame list based of the allocsize
//*******************************************
int allocate(int allocSize, int pid){

	//cout << "In allocate\nallocSize: " << allocSize << "\npid: " << pid << "\n";
	if(allocSize > FreeFrameList.getNumofFreeFrames()){
		return -1;
	}
	ListNode *ProcessNode;
	ProcessList.appendNode(pid);
	ProcessNode = ProcessList.getnode(pid);
	ProcessNode->Size = allocSize; 

	for(int x = 0; x < allocSize; x++){
		ProcessNode->PT[x] = FreeFrameList.getRand();
		//phy_mem[ProcessNode->PT[x]] = '1';
		FreeFrameList.deleteNode(ProcessNode->PT[x]);
	}
	return 1;
}
//*******************************************
// inputs pid from user
// deallocates the process this pid from user
// gives frames back to the free frame list
//*******************************************
int deallocate(int pid){

	//cout << "in deallocate\npid: " << pid << "\n";
	ListNode *ProcessNode;
	ProcessNode = ProcessList.getnode(pid);
	if(ProcessNode == NULL){
		return -1;
	}
	for(int x = 0; x < ProcessNode->Size; x++){
		FreeFrameList.appendNode(ProcessNode->PT[x]);
	}
	ProcessList.deleteNode(pid);
	return 1;
}

//*******************************************
// inputs ipd and logical address from user
// writes a 1 to the phyical memory base on the logical address translated to physical address
//*******************************************
int write(int pid, int logical_address){
	//cout << "in write\npid: " << pid << "\nlogical_address" << logical_address << "\n";
	ListNode *ProcessNode;
	ProcessNode = ProcessList.getnode(pid);
	if(ProcessNode == NULL){
		return -1;
	}
	phy_mem[ProcessNode->PT[logical_address]] = '1';	
	return 1;
}

//*******************************************
// inputs ipd and logical address from user
// prints the values in the physical memory based on the pid and logical address given
//*******************************************
int read(int pid, int logical_address){
	//cout << "in read\npid: " << pid << "logical_address: " << logical_address << "\n";
	ListNode *ProcessNode;
	ProcessNode = ProcessList.getnode(pid);
	if(ProcessNode == NULL){
		return -1;
	}
	cout << phy_mem[ProcessNode->PT[logical_address]] << "\n";
	return 1;	
}
//*******************************************
// prints out phyical memory, free frame list and process list
//
//*******************************************
void printMemory(){
	//cout << "Physical memory space\n";
	int x = 0;
	while(phy_mem[x] != '\0'){
	cout <<phy_mem[x] << " ";
	x++;
	}
	cout << "\nFree Frame List\n";
	FreeFrameList.displayList();
	cout << "\nProcess List\n";
	ProcessList.displayList();
	cout << "\n";
}

