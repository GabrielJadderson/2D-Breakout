#include "pch.h"

//Newton's second law:
//Acceleration = Force / Mass	| a = F / m
//Velocity = Acceleration x Time	| v = a * t
//Distance = 1/2 ( Acceleration x (Time^2) )	| d = 1/2 * a * t^2
//Force = ((Mass_of_object_1 Mass_of_object_2) / d^2) * G	| F = (( m1 * m2 ) / d^2)*G | we'll let Force be a vector2D or Vector3D
//Gravitational Constant G = 6.67408 × 10^-11 m3 kg^-1 s^-2 | G = 6.67408 x 10^-11 | we can assign "const double G = 6.67e-11;" or set it to "const double G = 667" we will loose precision, but it's enough.
//we can multiply G by 100 billion or 10^11 to eliminate rounding errors, which would be prevalent.
//check wikipedia for more info.

//https://en.wikipedia.org/wiki/Equations_of_motion#Uniform_acceleration
void AddForce()
{

}
/*
float timeBetweenSpawns;
void FixedUpdate()
{
	float timeSinceLastSpawn;

	timeSinceLastSpawn += game::deltaTime;
	if (timeSinceLastSpawn >= timeBetweenSpawns) {
		timeSinceLastSpawn -= timeBetweenSpawns;
	}
}
*/


Movement::Movement()
{
}




Movement::~Movement()
{
}