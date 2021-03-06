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

void print(double* b, unsigned size)
{
	for(unsigned i = 0; i < size; ++i)
	{
		std::cout << b[i] << " ";
	}
}

//Ha valaki megtalalja az angol kifejezést erre írjon vagy küldjün pull requestet
double nAllatK(unsigned n, unsigned k)
{
	double prod = 1;
	for(unsigned i = k + 1; i <= n; ++i)
	{
		prod *= i;
	}
	for(unsigned i=2; i <= n-k; ++i)
	{
		prod /= i;
	}
	return prod;
}

double rerollProbAll(unsigned faces, unsigned count, unsigned rerolls)
{
	double a[count + 1];
	double b[count + 1];

	//Initialize the probabilities
	for(unsigned hit = 0; hit <= count; ++hit)
	{
		a[count - hit] = nAllatK(count, hit) / pow(faces, hit) * pow((faces - 1.0) / faces, count - hit);
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
				b[i - hit] += nAllatK(i, hit) * a[i] / pow(faces, hit) * pow((faces - 1.0) / faces, i - hit);
			}
		}
		copy(a, b, count + 1);
	}

	//print(a, count+1);
	//std::cout << std::endl;
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

	std::cout << rerollProbAll(a, b, c) << std::endl;

	return 0;
}
