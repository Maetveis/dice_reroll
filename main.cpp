#include <iostream>
#include <sstream>
#include <cmath>


//Helper functions for C-style arrays

void clear(double* b, unsigned size)
{
	for(unsigned i = 0; i < size; ++i)
	{
		b[i] = 0;
	}
}
void copy(double* a, double* b, unsigned size)
{
	for(unsigned i = 0; i < size; ++i)
	{
		a[i] = b[i];
	}
}

double rerollProbAll(unsigned faces, unsigned count, unsigned rerolls)
{
	double a[count + 1];
	double b[count + 1];

	//Initialize the probabilities
	for(unsigned hit = 0; hit <= count; ++hit)
	{
		a[count - hit] = 1.0 / pow(faces, hit) * pow((faces - 1.0) / faces, count - hit);
	}

	//Use the previous level to calculate the next
	for(unsigned reroll = 1; reroll < rerolls; ++reroll)
	{
		//The next level is a Linear combination of the previous
		//So this double loop is actually a product of a triangle matrix and the previous layer as a vector
		clear(b, count + 1);
		b[0] = a[0];
		for(unsigned i = 1; i <= count; ++i)
		{
			for(unsigned hit = 0; hit <= i; ++hit)
			{
				b[i - hit] += a[i] / pow(faces, hit) * pow((faces - 1.0) / faces, i - hit);
			}
		}
		copy(a, b, count + 1);
	}

	return a[0];
}

int main(int argv, char** args)
{
	unsigned a, b, c;

	//Takes the paramaters from the command line
	// Usage: ./dice_reroll   faces   number_of_dice   rerolls
	std::stringstream ss;
	ss << args[1] << " " << args[2] << " " << args[3];
	ss >> a;
	ss >> b;
	ss >> c;

	std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;
	std::cout << rerollProbAll(a, b, c);

	return 0;
}
