//
//	./for.out
//
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <vector>
	
using namespace std;
int main(){
	int num_ancestors = 2;
	int counter = 0;
	int counter2 = 0;

		int counter = 0;
		int counter2 = 0;
		for(int i = 0; i < frontier.size(); i++){	//Entire Frontier
			vector<int> temporary_use = frontier[i]; 
			site my_site = lattice[temporary_use[0]temporary_use[1]];	
	 		if(my_site.label == 0){
			counter++;
			} else if (my_site.label == 1){
				counter2++;
			}

		}
		cout << "Counter 1: " << counter << " at timestep: " << time << endl;
		cout << "Counter 2: " << counter2 << " at timestep: " << time << endl;
}
