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
void double_bimodal(vector<Branch>,int);
int move_state(Branch, int);
string change_state(string, string);
void gshare(vector<Branch>, int);
int main(int argc, char *argv[]) {

  // Temporary variables
  unsigned long long addr;
  string behavior;
  unsigned long long target;
  //vector of branches
  vector<Branch> branches;

  // Open file for reading
  ifstream infile(argv[1]);

  // The following loop will read a hexadecimal number and
  // a string each time and then output them
  while(infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    //cout << addr;
    Branch temp = Branch();
    temp.setTarget(target);
    if(behavior == "T") {
      //cout << " -> taken, ";
      //char* var = (char*) behavior;
      temp.setBehavior(behavior);
    }else {
      //cout << " -> not taken, ";
    }
    	temp.setAddress(addr);
	//cout << "target=" << target << endl;
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
  //single bimodal
  single_bimodal(branches,16);
  single_bimodal(branches,32);
  single_bimodal(branches,128);
  single_bimodal(branches,256);
  single_bimodal(branches,512);
  single_bimodal(branches,1024);
  single_bimodal(branches,2048);
  //double bimodal
  double_bimodal(branches,16);
  double_bimodal(branches,32);
  double_bimodal(branches,128);
  double_bimodal(branches,256);
  double_bimodal(branches,512);
  double_bimodal(branches,1024);
  double_bimodal(branches,2048);
  //gshare
  gshare(branches,3);
	
  return 0;
}
void always_taken(vector<Branch> v){
	int accurate = 0;
       for (int i = 0; i< v.size(); i++){
	       if (v[i].getBehavior() == "T"){
		       accurate++;
	       }
       }
       //will be changed to writing to output file, just printing for now...
       cout<<"Always Taken: "<<accurate<<","<<v.size()<<endl;
}
void always_nonTaken(vector<Branch> v){
	int accurate = 0;
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
	int accurate = 0;
	//creating table

	string table[size];
	for (int i = 0; i<size;i++){
		table[i] = "T"; // initialize all values in table to "T" - taken
	}

	unsigned long long index = 0;
	switch(size){
		case 16:
			for (int i = 0; i<v.size();i++){
				index = v[i].getAddress() & 0x0000000F; //15 in hex
				if (v[i].getBehavior() == table[index]){
					accurate++;
				}
				
				table[index] = v[i].getBehavior();
				
			}
		break;
		case 32:
			for (int i=0;i<v.size();i++){
				index = v[i].getAddress() & 0x0000001F; //31 in hex
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index] = v[i].getBehavior();
			}
		break;
		case 128:
			for(int i=0;i<v.size();i++){
				index = v[i].getAddress()&0x0000007F; //127 in hex
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;
		case 256:
			for (int i=0;i<v.size();i++){
				index = v[i].getAddress()&0x000000FF; //255
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;
		case 512:
			for(int i=0;i<v.size();i++){
				index=v[i].getAddress()&0x000001FF;//511
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;
		case 1024:
			for(int i=0;i<v.size();i++){
				index=v[i].getAddress()&0x000003FF;
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;
		case 2048:
			for(int i=0;i<v.size();i++){
				index=v[i].getAddress()&0x000007FF;
				if(v[i].getBehavior()==table[index]){
					accurate++;
				}
				table[index]=v[i].getBehavior();
			}
		break;

	}
	cout<<"Single bimodal"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
}
void double_bimodal(vector<Branch>v, int size){
	int predictions[size];
	//initialize all values in table to strongly taken:
	for(int i = 0;i<size;i++){
		predictions[i] = 11;
	}
	int accurate = 0;
	unsigned long long index = 0;
	switch(size){
		case 16:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x0000000F;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 32:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x0000001F;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 128:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x0000007F;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 256:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x000000FF;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 512:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x000001FF;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 1024:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x000003FF;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
		case 2048:
			for(int i = 0; i<v.size();i++){
				index = v[i].getAddress()&0x000007FF;
				if (v[i].getBehavior() == "T"){
					if(predictions[index] == 11 || predictions[index]==10){
						accurate++;
					}
				}
				else if(v[i].getBehavior() == "NT"){
					if(predictions[index] == 0 || predictions[index] == 1){
						accurate++;
					}
				}
				predictions[index] = move_state(v[i],predictions[index]);
			}
		break;
			

	}
		
	cout<<"Double bimodal"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
		


}




int move_state(Branch b,int state){
	switch(state){
		case 11: //strongly taken
			if(b.getBehavior() == "T"){
				return 11;//stay at strongly taken
			}
			else{
				return 10;//move to weakly taken
			}
		break;
		case 10: //weakly taken
			if(b.getBehavior() == "T"){ 
				return 11;//move to strongly taken
			}
			else{
				return 1;//move to weakly non-taken
			}
		break;
		case 1: //weakly non-taken
			if(b.getBehavior() == "T"){
				return 10;//move to weakly taken
			}
			else{
				return 0;//move to strongly non-taken
			}
		break;
		case 0: //strongly non-taken
			if(b.getBehavior() == "T"){
				return 1;//move to weakly non-taken
			}
			else{
				return 0;//stay at strongly non-taken
			}
		break;
	}

}
string change_state(string pred, string outcome){
	if (pred == "TT"){//strongly taken
		if (outcome == "T"){
			return "TT";//stay at strongly taken
		}
		else if (outcome == "NT"){
			return "T"; //go to weakly taken
		}
	}
	else if(pred == "T"){//weakly taken
		if(outcome == "T"){
			return "TT"; //go to strongly taken 
		}
		else if(outcome == "NT"){
			return "NT"; //go to weakly non-taken 
		}
	}
	else if(pred == "NT"){//weakly non-taken
		if(outcome == "T"){
			return "T"; //go to weakly taken
		}
		else if(outcome == "NT"){
			return "NTNT";// go to strongly non-taken
		}
	}
	else if(pred == "NTNT"){ //strongly non-taken
		if (outcome == "T"){
			return "NT"; // go to weakly non-taken
		}
		else if(outcome =="NT"){
			return "NTNT"; //stay at strongly non-taken
		}
	}


}


	

void gshare(vector<Branch>v, int size){
	int accurate  = 0;
	string predictions[2048];
	int index = 0;
	unsigned long long GHR = 0;
	//initialize all table values to strongly taken
	for (int i = 0; i<2048; i++){
		predictions[i] = "TT";
	}
	switch (size){
		case 3:
			for(int i = 0; i<v.size(); i++){
				int addr_mod = v[i].getAddress() % 2048;
				index = addr_mod^GHR;
				if(v[i].getBehavior() == "T"){ //branch is taken
					if(predictions[index] == "TT" ||predictions[index] == "T"){//if the branch is taken, and the prediction is right
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					else if(predictions[index] == "NTNT" || predictions[index] =="NT"){// branch is taken, and the prediction is wrong
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
					}
					unsigned long long temp = GHR<<1;
					unsigned long long temp2 = temp | 0x00000001;
					GHR =temp2 & 0x00000007;
				}
				else if(v[i].getBehavior() == "NT"){//branch is not taken
					if(predictions[index] == "NTNT" || predictions[index] =="NT"){
						accurate++;
						predictions[index] = change_state(predictions[index],v[i].getBehavior());
			
					}
					else if(predictions[index] == "TT" || predictions[index] == "T"){
						predictions[index] = change_state(predictions[index],v[i].getBehavior());


					}
					unsigned long long temp = GHR<<1;
					GHR= temp & 0x00000007;
				}
			}
			cout<<"gshare"<<"("<<size<<"): "<<accurate<<","<<v.size()<<endl;
	}


}




			




