#include <cstdlib>
#include <iostream>
#include <string>
#include "vector.h"

using namespace std;

int operator_sel(string);

int main(){
	//mag for magnitude, dir for direction(in degrees)
	float mag, dir;
	int amount; //amount for the amount of vectors
	cout << "Please input amount of vectors: \n>";
	cin  >> amount;
	//Set for maximum amount of vectors allowed.
	const int MAX_VECTORS = amount;
	Vectors* vector_list[MAX_VECTORS];//vector_list used to save all the vectors.
	Vectors* vecaddr = nullptr;		//vecaddr used as a cache for dynamically allocated new vectors.
	Vectors tempVector(0, 0);		//tempVector used to save results of calculations.
	string  operators[MAX_VECTORS]; //operators string array used to save the operators.

	for (int i = 0; i < amount; i ++){
		cout << "Please input the magnitude for vector:" << i << "\n>";
		cin  >> mag;
		cout << "Please input the direction for vector:" << i << "\n>";
		cin  >> dir;

		vecaddr = new Vectors(mag, dir);
		vector_list[i] = vecaddr;
	}
	//Prints out the information for the vectors in case there is an error
	for (int i = 0; i < amount; i ++){
		cout << "Vector " << i << ":\n>"
				<< "Magnitude: " << vector_list[i]->mag << "\n>"
				<< "Direction: " << vector_list[i]->dir << "\n";
	}

	//Calculations
	int operator_id = 0;
	float multiplier = 0;
	for (int i = 0; i < amount; i ++){
		//A little messy over here: If the operator inputed is * or /, it only modifies the vector the
		//cycle is currently on. If the operator inputed is + or -, it goes into the storage variable.
		//TODO: Smooth it up so it makes more logical sense.
		cout << "Please input the operation for the vector " << i << ":\n>";
		cin  >> operators[i];
		//Feeds operators into operator_sel to figure out the operators. 1-4 correlates to +, -, *, /.
		operator_id = operator_sel(operators[i]);
		if (operator_id == 1){
			tempVector += *vector_list[i];
		}else if (operator_id == 2){
			tempVector -= *vector_list[i];
		}else if (operator_id == 3){
			//* and /: change the vectors, then reduce index by 1 so that it can be added later.
			cout << "Please input the multiples desired:\n>";
			cin  >> multiplier;
			*vector_list[i] *= multiplier;
			i --;
		}else if (operator_id == 4){
			cout << "Please input the divisor desired:\n>";
			cin  >> multiplier;
			*vector_list[i] /= multiplier;
			i --;
		}else{
			//If wrong operator, reduce i by 1 and retry.
			cout << "Wrong operator. Try again.\n";
			i --;
		}
	}

	cout << "Result is: \n>"
			<< "Magnitude: "<< tempVector.mag << "\n>"
			<< "Direction: "<< tempVector.dir << "\n";

	//Clean-up.
	for (int i = 0; i < amount; i ++){
		delete vector_list[i];
	}
}

int operator_sel (string op){
	if (op == "+"){
		return 1;
	}else if (op == "-"){
		return 2;
	}else if (op == "*"){
		return 3;
	}else if (op == "/"){
		return 4;
	}
	return 5;
}
