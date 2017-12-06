#include <iostream>
#include <string>
#include <cstdlib>
#include "Charlist.h"
#include <sys/time.h>
#include <time.h>
#include "rolfb2.h" 

using namespace std;

//prototypes
void memoryManager(int memSize, int frameSize);
int allocate(int allocSize, int pid);
int deallocate(int pid);
int write(int pid, int logical_address);
int read(int pid, int logical_address);
void printMemory();
void PrintPageFaults();

//global varibles
char* phy_mem;
Charlist FreeFrameList;
Charlist ProcessList;
Stack300 LRUstack;
int PageFaults = 0;
bool FIFO = false;
bool LRU =false;
struct timeval start, end;

int main()
{
	string line;
	int arg1 = -99;
	int arg2 = -99;
	char temp[50];
gettimeofday(&start, NULL);
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

        if(line[0] == 'M'){
	memoryManager(arg1, arg2);
	}
	else if(line[0] =='A'){
	 allocate(arg1, arg2);
	}            
        else if(line[0] == 'W'){
	write(arg1, arg2);
        }    
       	else if(line[0] == 'R'){
	read(arg1, arg2);
        }    
        else if(line[0] == 'D'){
	deallocate(arg1);
        }    
        else if(line[0] == 'P' && line != "PRINT PF" ){
	printMemory();
        }
	else if(line == "SET FIFO"){
		LRU = false;
		FIFO = true;
		cout << "FIFO algorithm has been set\n";
		
	}	
	else if(line == "SET LRU"){
		FIFO = false;
		LRU = true;
		cout << "LRU algorithm has been set\n";

	}
	else if(line == "PRINT PF"){
		PrintPageFaults();
	}    
        else{ 
		if(line != "Exit"){   
        		cout << "command dose not exist \n";
		}
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

ListNode *ProcessNode;

	//cout << "In allocate\nallocSize: " << allocSize << "\npid: " << pid << "\n";
	if(allocSize > FreeFrameList.getNumofFreeFrames()){
		if(FIFO){
			for(int x = FreeFrameList.getNumofFreeFrames(); x < allocSize; x++){
			int pid, Freeframe;
			ProcessList.getoldestPage(pid, Freeframe);	
			ProcessNode = ProcessList.getnode(pid);	
			FreeFrameList.appendNode(ProcessNode->PT[Freeframe]);
			cout << "frame removed" << ProcessNode->PT[Freeframe] << "pid" << pid << "\n";
			ProcessNode->PT[Freeframe] = -99;
			PageFaults++;
			}
		}
		else if(LRU){
			for(int x = FreeFrameList.getNumofFreeFrames(); x < allocSize; x++){	
			int pid, Freeframe;
			LRUstack.getLRU(pid, Freeframe);	
			ProcessNode = ProcessList.getnode(pid);	
			FreeFrameList.appendNode(ProcessNode->PT[Freeframe]);
			cout << "frame removed" << ProcessNode->PT[Freeframe] << "pid" << pid << "\n";
			ProcessNode->PT[Freeframe] = -99;
			PageFaults++;
			}
		}
		else{
			return -1;
		}
	}
	//ListNode *ProcessNode;
	ProcessList.appendNode(pid);
	ProcessNode = ProcessList.getnode(pid);
	ProcessNode->Size = allocSize; 

	for(int x = 0; x < allocSize; x++){
		ProcessNode->PT[x] = FreeFrameList.getRand();
		phy_mem[ProcessNode->PT[x]] = '1';
		gettimeofday(&end, NULL);	
		ProcessNode->time[x] = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		LRUstack.push300(pid,x);
		//cout << ProcessNode->time[x] << " ";
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
		if( ProcessNode->PT[x] != -99){
			FreeFrameList.appendNode(ProcessNode->PT[x]);
		}
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
//*******************************************
// prints out page faults
//
//*******************************************
void PrintPageFaults(){

cout << "Page Faults: " << PageFaults <<"\n";

}

