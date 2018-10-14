/*
 * vector.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: sam
 */

#include "vector.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

//Default vector to 0 0.
Vectors::Vectors(){
	this->mag = 0;
	this->dir = 0;
	this->coef= 1;
	this->name= ' ';
}

//Set name.
Vectors::Vectors(char name){
	this->mag = 0;
	this->dir = 0;
	this->coef= 1;
	this->name= name;
}
//Alters magnitude and direction according to the input.
Vectors::Vectors(float mag_in, float dir_in){
	this->mag = mag_in;
	this->dir = dir_in;
	this->coef= 1;
	this->name = ' ';
}

//Delta x and delta y calculated from the formulas.
//trigs use radians so they need to be converted.
float Vectors::dx(){
	float deltax = this->mag * cos(this->dir / 180 * PI);
	return deltax;
}

float Vectors::dy(){
	float deltay = this->mag * sin(this->dir / 180 * PI);
	return deltay;
}

//Overloads equal sign. Used to give value to vectors.
Vectors Vectors::operator = (Vectors v){
	this->mag = v.mag;
	this->dir = v.dir;

	Vectors rst_vector(this->mag, this->dir);
	return rst_vector;
}

Vectors Vectors::operator + (Vectors v){
	//+ overloaded to calculate the resultant vector: deltax and deltay for horizontal and vertical
	//shift and resultant magnitude is calculated through pythag and direction through arctan.
	float deltax = this->dx() + v.dx();
	float deltay = this->dy() + v.dy();
	float dir = 0;
	float quad = quad_id(deltax, deltay); //Fetches the offset of the resultant vector

	float mag = sqrt(pow(deltax, 2) + pow(deltay, 2));
	//4 different inverse functions because of the range limitations of inverse trig.
	if (quad == 0){
		//1st quad, asin
		dir = asin(deltay / mag) * 180 / PI + quad;
	}else if (quad == 90){
		//2nd quad, asin
		dir = 180 - asin(deltay / mag) * 180 / PI;
	}else if (quad == 180){
		//3rd quad, atan
		dir = atan(deltay / deltay) * 180 / PI + quad;
	}else if (quad == 270){
		//4th quad, acos
		dir = 360 - acos(deltax / mag) * 180 / PI;
	}

	//Makes a new vector object with calculated magnitude and direction to be returned.
	Vectors rst_vector(mag, dir);
	return rst_vector;
}

Vectors Vectors::operator +=(Vectors v){
	Vectors rst_vector = *this + v;
	*this = rst_vector;
	return rst_vector;
}

Vectors Vectors::operator - (Vectors v){
	float deltax = this->dx() - v.dx();
	float deltay = this->dy() - v.dy();
	float dir = 0;
	float quad = quad_id(deltax, deltay);

	float mag = sqrt(pow(deltax, 2) + pow(deltay, 2));
	//4 different inverse functions because of the range limitations of inverse trig.
	if (quad == 0){
		//1st quad, asin
		dir = asin(deltay / mag) * 180 / PI + quad;
	}else if (quad == 90){
		//2nd quad, asin
		dir = asin(deltay / mag) * 180 / PI + quad;
	}else if (quad == 180){
		//3rd quad, atan
		dir = atan(deltay / deltay) * 180 / PI + quad;
	}else if (quad == 270){
		//4th quad, acos
		dir = acos(deltax / mag) * 180 / PI + quad;
	}

	Vectors rst_vector(mag, dir);
	return rst_vector;
}

Vectors Vectors::operator -=(Vectors v){
	Vectors rst_vector = *this - v;;
	*this = rst_vector;
	return rst_vector;
}

Vectors Vectors::operator * (double mult){
	float mag = this->mag * mult;
	float dir = this->dir;

	Vectors rst_vector(mag, dir);
	return rst_vector;
}

Vectors Vectors::operator *=(double mult){

	Vectors rst_vector = *this * mult;
	*this = rst_vector;
	return rst_vector;
}

Vectors Vectors::operator / (double div){
	float mag = this->mag * div;
	float dir = this->dir;

	Vectors rst_vector(mag, dir);
	return rst_vector;
}

Vectors Vectors::operator /=(double div){

	Vectors rst_vector = *this / div;
	*this = rst_vector;
	return rst_vector;
}

double Vectors::quad_id (double dx, double dy){
	if (dx > 0 && dy >= 0){
		//if dx > 0 and dy > 0, first quadrant or pos-y.
		return 0;
	}else if (dx < 0 && dy >=0){
		//if dx < 0 and dy > 0, second quadrant or neg-x.
		return 90;
	}else if (dx < 0 && dy <= 0){
		//if dx < 0 and dy < 0, third quadrant or neg-y.
		return 180;
	}else if (dx > 0 && dy <= 0){
		//if dx > 0 and dy < 0, fourth quadrant or pos-x.
		return 270;
	}
	//If doesn't pass the tests, throw exception(which it should not)
	throw 0;
	return 0;
}



