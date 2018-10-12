#include <iostream>
#include <sstream>
#include <cmath>

void clear(double* b, unsigned size)
{
	for(unsigned i = 0; i < size; ++i)
	{
		b[i] = 0;
	}
}

double sum(double* b, unsigned size)
{
	double sum = 0;
	for(unsigned i = 0; i < size; ++i)
	{
		sum += b[i];
	}

	return sum;
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

	for(unsigned hit = 0; hit <= count; ++hit)
	{
		a[count - hit] = 1.0 / pow(faces, hit) * pow((faces - 1.0) / faces, count - hit);
	}

	for(unsigned reroll = 1; reroll < rerolls; ++reroll)
	{
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

	std::stringstream ss;
	ss << args[1] << " " << args[2] << " " << args[3];
	ss >> a;
	ss >> b;
	ss >> c;

	std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;
	std::cout << rerollProbAll(a, b, c);

	return 0;
}
