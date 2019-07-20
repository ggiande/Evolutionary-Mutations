#include <iostream>
using namespace std;

int main(){
	/* Design a program that will take in data at every 100 timesteps and have it save in a csv file.
	Once saved, have that data open in either python or R, whatever is quicker. ASAP send the figures to the 
	poster and complete the entire poster.*/

	if(t % 100 == 0){ //if divisible by 100, take data, else skip over this iteration.
		float dat = counter/counter2;
		d << t << "," << dat << endl; //Saving time, and rates
		
	} else {
		continue;
	}
}





