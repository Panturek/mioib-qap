#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include "qap.hpp"

enum Algorithm
{
	randomSearch, randomWalk, localSteepest, localGreedy, heuristics
};


void time_experiment(const std::string filename, QAP &qap, Algorithm algo, const std::string dirout);
void random_experiment(const std::string filename, QAP &qap, Algorithm algo, const std::string dirout);
void heuristics_experiment(const std::string filename, QAP &qap, const std::string dirout);