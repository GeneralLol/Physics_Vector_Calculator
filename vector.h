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

	float mag;
	float dir;

	const double PI = 3.14159265358979323846;

	Vectors();
	Vectors(float, float);

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

	float dx ();
	float dy ();
};

//Checks the quadrant that the vector is in and helps fixing the angles.
//Takes in two arguments, resultant delta x and resultant delta y from the calculations.
//int check_quadrant(double, double);

#endif /* VECTOR_H_ */
