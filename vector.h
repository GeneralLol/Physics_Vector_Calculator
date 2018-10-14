/*
 * vector
 *
 *  Created on: Oct 4, 2018
 *      Author: sam
 */

#ifndef VECTOR_H_
#define VECTOR_H_

class Vectors{
public:

	double mag;  //magnitude
	double dir;  //direction (degrees)
	double coef; //coefficient
	char name;

	const double PI = 3.14159265358979323846;

	Vectors();
	Vectors(char);
	Vectors(double, double);

	Vectors operator = (Vectors);
	Vectors operator + (Vectors);
	Vectors operator +=(Vectors);
	Vectors operator - (Vectors);
	Vectors operator -=(Vectors);
	Vectors operator * (double);
	Vectors operator *=(double);
	Vectors operator / (double);
	Vectors operator /=(double);
	double  quad_id (double, double); //Identifies the quadrant and spits out the offset angle.

	double dx ();
	double dy ();
};

//Checks the quadrant that the vector is in and helps fixing the angles.
//Takes in two arguments, resultant delta x and resultant delta y from the calculations.
//int check_quadrant(double, double);

#endif /* VECTOR_H_ */
