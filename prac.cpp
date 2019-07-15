#include <iostream>
#include <vector>
using namespace std;

int main(){
	int ro = 2;
	int rp = 1;

	int n = 2;
	int m = 1;

	
	for(int i = 0; int i < 10; i++){
		int rtot = (n*ro) + (m*rp);
		cout << "The rtot is: " << rtot << endl;

		int check_equal_to_one = (n*ro)/rtot + (m*rp/rtot); 
		int rate =  (n*rp)/rtot;

		cout << "This should be one --> " << check_equal_to_one << endl;
		cout << "The rate of this instance: " << rate << endl;

	    srand((unsigned int)time(NULL));    
	    int temp = (drand48()*2);  //get a random integer from 0 to (FACTOR NUMBER - 1)
	    cout << "Randomization: " << temp << endl;
	    if(rate > temp){
	    	//choose population n
	    	return 0;
	    } else {
	    	//choose population m
	    	return 1;
	    }
	    if(rate == 0){
	    	//rate is subpopulation 0.
	    	//Randomly pick a cell in this subpopulation.
	    } else if (rate == 1){
	    	//rate is subpopulation 1
	   		
	    }

	}

}
