#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <tuple>
#include "qap.hpp"

void time_experiment(const std::string filename, QAP &qap, Algorithm algo, const std::string dirout);
void random_experiment(const std::string filename, QAP &qap, Algorithm algo, const std::string dirout, const double algotime);
void heuristics_experiment(const std::string filename, QAP &qap, const std::string dirout);