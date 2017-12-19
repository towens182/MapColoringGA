#include "Map.h"

Map::Map()
{
	int temp = 0;
	for (int i = 0; i < 50; i++)
	{
		temp = rand() % 4;

		gene[i] = temp;
	}

	fitness = 0;
}

Map::Map(std::string g)
{
	for (int i = 0; i < 50; i++)
	{
		gene[i] = 5; //Just fill gene with 5 to make easier for testing
	}
	fitness = 0;
}