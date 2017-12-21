//This program attempts to color the United States with four colors
//using a genetic algorithm
//Tyler Owens

#include <iostream>
#include "Map.h"
using namespace std;

void initPopulation(Map * individuals[], Map * parents[]);
void delPopulation(Map * individuals[], Map * parents[]);
bool foundOptimization(Map * individuals[]);
void calculateFitness(Map * individuals[], int incidentMatrix[][50]);
void sortParents(Map * parents[]);
void chooseParentsElite(Map * individuals[], Map * parents[]);
void chooseParentsRandom(Map * individuals[], Map * parents[]);
Map * crossover(Map * parent1, Map * parent2);
Map * mutation(Map * child);

const int SIZE = 100; //Size of individuals in population

int main()
{
	srand(time(NULL));
	
	int generations = 0;

	Map * individuals[SIZE];	
	Map * parents[SIZE];

	int incidentMatrix[50][50] = 
	{
		{ 0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0 },
		{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
		{ 0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0 }
	};

	clock_t t = clock();
	initPopulation(individuals, parents);
	calculateFitness(individuals, incidentMatrix);

	while (!foundOptimization(individuals)) 
	{
		generations++;
		//chooseParentsElite(individuals, parents);			//Change Parent selection
		chooseParentsRandom(individuals, parents);			//methods here
		calculateFitness(individuals, incidentMatrix);

		//Print out population
		/*for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < 50; j++) 
			{
				cout << individuals[i]->gene[j];
			}
			cout << " F: " << individuals[i]->fitness << endl;
		}*/
	}

	cout << "Generations: " << generations << endl;
	t = clock() - t;
	printf ("Time: (%f seconds).\n", ((float)t) / CLOCKS_PER_SEC);
	delPopulation(individuals, parents); //Free memory
	
	cin.get();
	cin.get();
	return 0;
}

void initPopulation(Map * individuals[], Map * parents[])
{
	for (int i = 0; i < SIZE; i++)
	{
		individuals[i] = new Map();
		parents[i] = NULL;
	}
}

void delPopulation(Map * individuals[], Map * parents[])
{
	for (int i = 0; i < SIZE; i++)
	{
		delete individuals[i];
		delete parents[i];
	}
}

//Check for 0 fitness
bool foundOptimization(Map * individuals[])
{
	for (int i = 0; i < SIZE; i++)
	{
		if (individuals[i]->fitness == 0)
		{
			cout << "Optimal Solution found: " << endl;
			for (int j = 0; j < 50; j++) 
			{
				
				cout << individuals[i]->gene[j];
			}
			cout << " F: " << individuals[i]->fitness
				 << endl;
			//print out time
			return true;
		}
	}
	return false;
}

//Calculate violations for each individual
void calculateFitness(Map * individuals[], int incidentMatrix[][50])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			for (int k = 0; k < 50; k++)
			{
				if (incidentMatrix[j][k] == 1 && (individuals[i]->gene[j] == individuals[i]->gene[k]))
				{
					individuals[i]->fitness++;
				}
			}
		}
	}

}

//Sort fitness from low to high to choose elite parents easier
void sortParents(Map * parents[])
{
	int j;

	for (int i = 1; i < SIZE; i++)
	{
		j = i;
		while ((j > 0) && (parents[j]->fitness < parents[j - 1]->fitness))
		{
			Map * temp = parents[j];
			parents[j] = parents[j - 1];
			parents[j - 1] = temp;
			j--;
		}
		
	}
}

//Choose a random parent with top half fitness
void chooseParentsElite(Map * individuals[], Map * parents[])
{
	for (int i = 0; i < SIZE; i++)
	{
		if (parents[i] == NULL) { delete parents[i]; }
		parents[i] = individuals[i];	//copy poulation to parent generation
	}

	sortParents(parents); //sorts by fitness to aid choosing elitest parents

	for (int j = 0; j < SIZE; j++)
	{
		Map * parent1 = NULL;
		Map * parent2 = NULL;
		Map * child = NULL;


		while (parent1 == parent2)				 //Choose top two elite parents at random
		{									     //Make sure they are different
			parent1 = parents[rand() % (SIZE / 2)];
			parent2 = parents[rand() % (SIZE / 2)];
		}
		child = crossover(parent1, parent2);
		child = mutation(child);
		individuals[j] = child;
	}
}

//Choose each parent by choosing the fittest of two random individuals
void chooseParentsRandom(Map * individuals[], Map * parents[])
{
	for (int i = 0; i < SIZE; i++)
	{
		delete parents[i];
		parents[i] = individuals[i];		//copy population to parent population
	}

	for (int j = 0; j < SIZE; j++)
	{
		Map * parent1 = NULL;
		Map * parent2 = NULL;
		Map * temp1 = NULL;
		Map * temp2 = NULL;
		Map * child = NULL;

		temp1 = parents[rand() % (SIZE)];
		temp2 = parents[rand() % (SIZE)];

		while (temp1 == temp2)			//Make sure parents are different
		{									     
			temp1 = parents[rand() % (SIZE)];
			temp2 = parents[rand() % (SIZE)];
		}

		if (temp1->fitness < temp2->fitness)
		{ 
			parent1 = temp1;
		}
		else
		{
			parent1 = temp2;
		}

		temp1 = parents[rand() % (SIZE)];

		while (temp1 == parent1)	//Make sure parents are different
		{
			temp1 = parents[rand() % (SIZE)];
		}
		parent2 = temp1;

		child = crossover(parent1, parent2);
		child = mutation(child);
		individuals[j] = child;
	}

}

Map * crossover(Map * parent1, Map * parent2)
{
	int crosspoint = rand() % 50;

	Map * child = new Map("child");
	
	for (int i = 0; i < crosspoint; i++)
	{
		child->gene[i] = parent1->gene[i];
	}
	
	for (int j = crosspoint; j < 50; j++)
	{
		child->gene[j] = parent2->gene[j];
	}

	return child;
}

//Randomly change one chromosome at a 1% chance
Map * mutation(Map * child)
{
	int prob = rand() % 100;
	int mutatedBit = rand() % 50;
	int newColor = rand() % 4;
	if (prob == 1)
	{
		while (child->gene[mutatedBit] == newColor)
		{
			newColor = rand() % 4;
		}

		child->gene[mutatedBit] = newColor;
	}
	return child;
}
