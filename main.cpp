#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "vector.h"

using namespace std;

int vec_count (string);
int op_count  (string);
void separation (string, const int, Vectors*);
Vectors* calculate(string, const int, Vectors*); //Calculates the expression and returns a pointer to the resultant vector.
Vectors* usr_input(string, int); //Prompts the user to input the information, and returns a pointer to the first vector.
void print_vectors(Vectors*, int); //Function dedicated to printing the information of the vectors.

int main(){
	string vectorExp;
	cout << "Please input the vector expression: \n>";
	cin.ignore(0);		//Set cin to ignore whitespaces and start from the 0th number.
	getline(cin, vectorExp);
	cout << vectorExp << "\n";

	int vecCount = vec_count(vectorExp);
	Vectors* vecs = usr_input (vectorExp, vecCount);

	int opCount  = op_count(vectorExp);
	const int MAX_OP   = opCount;
	string opList[MAX_OP];

	separation (vectorExp, vecCount, vecs);
	print_vectors (vecs, vecCount);
	Vectors* rstVec = calculate (vectorExp, vecCount, vecs);
	cout << "Result is: \n";
	print_vectors (rstVec, 1);

	return 1;

}

//vec_count: goes through the string and figures out how many vectors there are.
int vec_count(string exp){

	int varCount = 0;
	for (char i: exp){
		bool varflag = isalpha(i);
		if (varflag){
			varCount += 1;
		}
	}

	return varCount;
}

//int_count: goes through the string and counts how many operators there are.
int op_count(string exp){
	int opCount = 0;

	for (char i: exp){
		bool opFlag = ispunct(i);
		if (opFlag){
			opCount += 1;
		}
	}

	return opCount;
}

//separation: separates the vector vars and operators.
//Multiplication and divisions are considered as coefficients and are processed here.
void separation(string vecExp, const int vecCount, Vectors* vecList){
	//A stringstream is used here to separate the expression whitespace by whitespace.
	stringstream vecExpStream;
	vecExpStream << vecExp;
	string wordCache = "";		//Stores the stuff in between the whitespaces.
	string coefCache = "";		//Constructs and stores the coefficient in string.
	char   charCache = ' ';		//Stores individual chars being parsed.

	bool divFlag = 0;  			//signal for division.

	//The while loop separates the expressions by whitespaces.
	while (vecExpStream >> wordCache){
		//The for loop goes through the words to separate vecs and operators.
		int wordLength = wordCache.length();
		for (int i = 0; i < wordLength; i ++){
			charCache  = wordCache[i];
			coefCache = ""; //Clear coefficient cache before entering the separation process.
			//if current character is /, the next number it finds needs to be divided from the coefficient.
			if (charCache == '/'){
				divFlag = 1;
			}
			if (isalpha(charCache)){
				//if charCache is a letter, it is a vector.
				//nothing happens here because the vectors were already separated in usr_input function.
			}else if (isdigit(charCache)){
				//if charCache is a digit, it is a part of a coefficient.
				//First time the code is executed, it is the first digit of the coefficient.
				//The coefficient is assembled and stored in the vector class, and then the
				//coefficient within the wordCache string is destroyed so that the program
				//does not record the digits multiple times. Subtraction is not processed as
				//a coefficient here.
				for (int j = i; j < wordLength; j ++){
					if (isdigit(wordCache[j]) or wordCache[j] == '.'){
						coefCache += wordCache [j];
					}else{
						break;
					}
				}
				//Check divFlag, then store the coefficient in the coefficient cache.
				if (divFlag){
					vecList->coef = vecList->coef / stof(coefCache);
					//Reset the divFlag.
					divFlag = 0;
				}else {
					vecList->coef = vecList->coef * stof(coefCache);
				}

				//Destroy the coefficient in the wordCache string.
				//1. Search for the first index at which the coefficient substring exists.
				int coefPos = wordCache.find(coefCache);
				//2. Erase the part of the wordCache string starting from the coefPos for
				//		coefCache.len() chars.
				wordCache.erase(coefPos, coefCache.length());
				//3. Recalculate the wordLength for the main word loop.
				wordLength = wordCache.length();
			}else if (ispunct(charCache) && charCache != '.' && charCache != '*' && charCache != '/'){
				//If charCache is an operator that is not * or /, update vector pointer.
				vecList ++;
			}
		}
	}

}

//calculate: parses through the expression and calculates the vectors.
Vectors* calculate(string vecExp, const int vecCount, Vectors* vecList){
	//Set reference point for the vecList pointer.
	Vectors* vecListRef = vecList;
	//Makes a new vector to store the result.
	Vectors* rstVec = new Vectors('R');

	int vecLength = vecExp.length();
	//First order of business: go through the vector list and multiply all the coefficients.
	for (int i = 0; i < vecCount; i ++){
		*vecList *= vecList->coef;
		vecList->coef = 1;
		vecList ++;
	}
	//Reset the vecList pointer to be used later.
	vecList = vecListRef;

	//Add a + sign to the vecExp so that the program will not skip the first vector.
	vecExp = "+" + vecExp;
	//refresh length
	vecLength = vecExp.length();
	//Main for loop goes through the expression to look for + and -.
	//After finding the operators, a loop goes from current position forward to look for
	//		vectors in the rest of expression. This loop is immediately broken once the
	//		next vector is found. The found vector is going to be added to/subtracted from
	//		rstVec. i is set to the breakpoint to skip irrelevant portions of expression.
	for (int i = 0; i < vecLength; i ++){
		//If a sign is detected, start looking for letters from there.
		if ((vecExp[i] == '+') | (vecExp[i] == '-')){
			for (int j = i; j < vecLength; j ++){
				//reset the vecList var because calculation is about to start.
				vecList = vecListRef;
				//if the current char is a letter, go search for the corresponding vector in vectorList.
				//Search is sequential because I am way too tired to do anything outside of that.
				if (isalpha(vecExp[j])){
					//This for loop sequentially goes through the vector list, and is broken once a match is found.
					for (int k = 0; k < vecCount; k ++){
						//if the name of the current vector matches the record, do the calculation, break the cycle.
						if (vecList->name == vecExp[j]){
							if (vecExp[i] == '+'){
								*rstVec += *vecList;
							}else if (vecExp[i] == '-'){
								*rstVec -= *vecList;
							}
							break;
						}
						vecList ++;
					}
					//Break j loop.
					break;
				}
			}
		}
	}
	return rstVec;
}

//usr_input: prompts the user to input the information for each vector and returns a pointer to the first element.
Vectors* usr_input(string exp, int vecCount){
	//create a new series of empty vectors.
	Vectors* vecAddr = new Vectors[vecCount];
	Vectors* vecAddrRef = vecAddr; //Reference to the first object.
	//cache for the vector info.
	float mag = 0;
	float dir = 0;
	for (char i: exp){
		if (isalpha(i)){
			//if i is a letter, it is a vector.
			//prompt the user input:
			cout << "Please input the magnitude for vector " << i << " :\n>";
			cin  >> mag;
			cout << "Please input the direction for vector " << i << " :\n>";
			cin  >> dir;

			//Set values.
			vecAddr->mag = mag;
			vecAddr->dir = dir;
			vecAddr->name= i  ;
			//Move pointer.
			vecAddr ++;
		}
	}
	//Returns the pointer to the first element.
	return vecAddrRef;
}

//print_vectors: prints vectors info in an organized manner.
void print_vectors(Vectors* vecPtr, int vecCount){
	Vectors* vecPtrRef = vecPtr; //Pointer to the first element of the vector array.

	for (Vectors* i = vecPtrRef; i < vecPtr + vecCount; i ++){
		cout << "Vector " << i->name << ": \n"
				<< "Coefficient: " << i->coef << "\n"
				<< "Magnitude: "   << i->mag  << "\n"
				<< "Direction: "   << i->dir  << "\n";
		cout << "\n";
	}
}
