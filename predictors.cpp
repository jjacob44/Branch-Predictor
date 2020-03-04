/* Example
 * Parsing Branch Traces
 */

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Branch.h"

using namespace std;

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
	cout << "target=" << target << endl;
        branches.push_back(temp);
  }
  cout<<"-------Testing branch class-------"<<endl;
  for (int i=0; i<branches.size();i++){
	  cout<<"Branch #: "<<i+1<<" behavior: "<<branches[i].getBehavior()<<" target: "<<branches[i].getTarget()<<endl;
  }

  return 0;
}
