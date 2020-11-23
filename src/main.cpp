#include <iostream>
#include <ctime>
#include "qap.hpp"

int main()
{
	srand(time(NULL));

	QAP qap;
	qap.readData("data/bur26a.dat");
	int dim = qap.facilities.size();
	std::cout << "Rozmiar: " << dim << std::endl;

	Permutation solution;

	clock_t begin = clock();
	int l = 0;
	do
	{
		solution = qap.localGreedy(dim);
		l++;
	} while (double(clock() - begin) / CLOCKS_PER_SEC < 10);

	double func_time = (double(clock() - begin) / CLOCKS_PER_SEC) / l;

	std::cout << "Performance: " << qap.getCost(solution) << std::endl;
	std::cout << "Time: " << func_time << std::endl;
	std::cout << "l " << l;

	getchar();
	return 0;
}
