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


void memoryManager(int memSize, int frameSize){

    cout << "in Memory Manger\nmemSize: " << memSize << "\nFramSize: " << frameSize << "\n";
    phy_mem = new char[memSize];
    for(int x = 0; x < sizeof(phy_mem); x++){
        phy_mem[x] = '0';
	FreeFrameList.appendNode(x);
    }

}

int allocate(int allocSize, int pid){

cout << "In allocate\nallocSize: " << allocSize << "\npid: " << pid << "\n";
phy_mem[0] = '1';

}

int deallocate(int pid){

cout << "in deallocate\npid: " << pid << "\n";

}

int write(int pid, int logical_address){

cout << "in write\npid: " << pid << "logical_address" << logical_address << "\n";


}


int read(int pid, int logical_address){

cout << "in read\npid: " << pid << "logical_address: " << logical_address << "\n";

}

void printMemory(){

    cout << "Physical memory space\n";
    for(int x = 0; x < sizeof(phy_mem); x++){
        cout <<phy_mem[x] << " ";
    }
    cout << "\nFree Frame List\n";
    FreeFrameList.displayList();
    cout << "\nProcess List\n";
    ProcessList.displayList();
    cout << "\n";
}

