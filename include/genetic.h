#ifndef GENETIC_FILE_H
#define GENETIC_FILE_H

#define POPULATION_SIZE 100
#define ITERATION_NUM 1000
#define VAR_NUM 2
#define PROB_CROSSOVER 0.5
#define PROB_MUTATION 0.05

typedef struct Gene
{
    double genes[VAR_NUM];
    double var_fitness;
} Gene;

typedef struct Bound
{
    double lower;
    double upper;
} Bound;

Gene population[POPULATION_SIZE + 1];
Gene new_population[POPULATION_SIZE + 1];
Bound func_bound[VAR_NUM];

FILE *result_file;

void Initialize();
void Evaluate();
int FindBest();
void Elitist();
void Select_RouletteWheel();
void Select_Tournament();
void OnePointCrossover(double probability_crossover);
void UniformCrossover(double probability_crossover);
void UniformMutate(double probability_mutation);
void DiscriminateMutate();
void ReportSingleVarGenertation(int generation);
void ReportPcPm(double pc, double pm, double fitness);

#endif