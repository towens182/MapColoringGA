#include "Map.h"

Map::Map()
{
	for (int i = 0; i < 50; i++)
	{
		int temp = rand() % 4;

		gene += std::to_string(temp);
	}

	fitness = 100;
}

Map::Map(std::string g)
{
	gene = g;
	fitness = 100;
}

void Map::setFitness(int v)
{
	fitness = v;
}

//std::string Map::getGene()
//{
//	return gene;
//}
//
//int Map::getFitness()
//{
//	return fitness;
//}
