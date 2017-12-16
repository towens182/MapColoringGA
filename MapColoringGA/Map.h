#include <string>
#include <time.h>
class Map {

	public:
		Map();

		void setFitness(int v);
		std::string gene; //Alphabetical representation of each state by color
		int fitness; //Number of violations. 0 = optimal

	private:
	
	


};