#include <string>
#include <time.h>
class Map {

	public:
		Map();
		Map(std::string); //Constructor for the child

		int fitness;	//Number of violations. 0 = optimal
		int gene[50];
};