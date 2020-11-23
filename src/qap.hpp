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
	int updateCost(const Permutation &, const Permutation &);
	Permutation randomSearch(unsigned const int &n, const double &time_seconds);
	Permutation randomWalk(unsigned const int &n, const double &time_seconds);
	Permutation localGreedy(unsigned const int &n);
	Permutation localSteepest(unsigned const int &n);
};