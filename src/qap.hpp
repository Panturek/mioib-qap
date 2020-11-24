#include <string>
#include <vector>

typedef std::vector<int> Permutation;

class QAP{
	int cost;

public:
	std::vector<Permutation> facilities;
	std::vector<Permutation> locations;

	Permutation generatePermutation(unsigned const int &n);
	void readData( const std::string filename );
	int getCost(const Permutation &perm );
	int updateCost(const Permutation &, const Permutation &, const int& i, const int& j);
	Permutation randomSearch(unsigned const int &n, const double &time_seconds);
	Permutation randomWalk(unsigned const int &n, const double &time_seconds);
	std::pair<Permutation, int> localGreedy(unsigned const int &n);
	std::pair<Permutation, int> localSteepest(unsigned const int &n);
	Permutation heuristics(unsigned const int &n);
};