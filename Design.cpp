//
//	./for.out
//

#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <vector>
	
using namespace std;
int main(){
 		if(mother_xy[0] > LX/2){ 
			float prob_of_success = 0.0;
			site end_game = lattice[mother_xy[0]][mother_xy[1]];
			if(end_game.label == 0){
				prob_of_success = (1./10.)*(1./2.);	//0.05
			} else if (end_game.label == 1){
				prob_of_success = (1./1.)*(2./10.);	//0.2
			}



		    float Actual = drand48();
		    
		    if(prob_of_success > Actual){
				mother = lattice[mother_xy[0]][mother_xy[1]];
				cout << "Mother was filled." << endl;
		    } else {
		    	//Rejected, do not advance t. Decrease by t-- to counteract for loop.
		    	//t--; 
		    }
		} else {
			mother = lattice[mother_xy[0]][mother_xy[1]];
		}
}


