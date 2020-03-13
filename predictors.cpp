/* Example
 * Parsing Branch Traces
 */

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Branch.h"


using namespace std;
//function declarations:
void always_taken(vector<Branch>);
void always_nonTaken(vector<Branch>);
void single_bimodal(vector<Branch>,int);

int main(int argc, char *argv[]) {

  // Temporary variables
  unsigned long long addr;
  string behavior;
  unsigned long long target;
  //vector of branches
  vector<Branch> branches;

  // Open file for reading
  ifstream infile("test_input.txt");

  // The following loop will read a hexadecimal number and
  // a string each time and then output them
  while(infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    cout << addr;
    Branch temp = Branch();
    temp.setTarget(target);
    if(behavior == "T") {
      cout << " -> taken, ";
      //char* var = (char*) behavior;
      temp.setBehavior(behavior);
    }else {
      cout << " -> not taken, ";
    }
    	temp.setAddress(addr);
	cout << "target=" << target << endl;
        branches.push_back(temp);
	

  }
   //this is just to test branch class....
 /* cout<<"-------Testing branch class-------"<<endl;
  for (int i=0; i<branches.size();i++){
	  cout<<"Address: "<<branches[i].getAddress()<<" Branch #: "<<i+1<<" behavior: "<<branches[i].getBehavior()<<" target: "<<branches[i].getTarget()<<endl;
  }*/
  cout<<"-------Predictor Outputs-------"<<endl;
  //function calls:
  always_taken(branches);
  always_nonTaken(branches);
  single_bimodal(branches);
  

  return 0;
}
void always_taken(vector<Branch> v){
	int accurate;
       for (int i = 0; i< v.size(); i++){
	       if (v[i].getBehavior() == "T"){
		       accurate++;
	       }
       }
       //will be changed to writing to output file, just printing for now...
       cout<<"Always Taken: "<<accurate<<","<<v.size()<<endl;
}
void always_nonTaken(vector<Branch> v){
	int accurate;
	for (int i = 0; i<v.size(); i++){
		if (v[i].getBehavior() == "NT"){
			accurate++;
		}
	}
	//will be changed to writing to output file, just printing for now...
	cout<<"Always Non-Taken: "<<accurate<<","<<v.size()<<endl;
}
void single_bimodal(vector<Branch> v, int size){
	//string previous = "T";
	int accurate;
	/*for (int i = 0; i<v.size(); i++){
		if(v[i].getBehavior() == previous){
			accurate++;
		}
		previous = v[i].getBehavior();
	}*/
	//creating table
	vector<string>table;
	for (int i = 0; i<size;i++){
		table.push_back("T"); // initialize all values in table to "T" - taken
	}
	unsigned long long index = 0;
	switch(size){
		case 16:
			for (int i = 0; i<size;i++){
				index = v[i].getAddress() & 0x0000000F; //15 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}
		case 32:
			for (int i = 0; i<size;i++){
				index = v[i].getAddress() & 0x0000001F; //31 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}
		
		case 128:
			for (int i = 0; i<size;i++){
				index = v[i].getAddress() & 0x0000007F; //127 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}

		case 256:
			for (int i = 0; i<size;i++){
				index = v[i].getAddress() & 0x000000FF; //255 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}
		
		case 512:
			for (int i = 0; i<size;i++){
				index = v[i].getAddress() & 0x000001FF; //511 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}
		
		case 1024:
			for (int i = 0; i<size;i++){
				index = v[i].getAddress() & 0x000003FF; //1023 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}
	
		case 2048:
			for (int i = 0; i<size;i++){
				index = v[i].getAddress() & 0x000007FF; //2047 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}
	}
}



