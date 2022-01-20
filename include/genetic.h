#ifndef GENETIC_H
#define GENETIC_H

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
// 根据判断返回0或1，当有新的最佳适应值时返回1，否则返回0
int FindBest();
// 若当前最佳适应值小于上一代，将当前最差适应值替换为上一代最佳适应值，避免未成熟收敛
void Elitist();
// 轮盘赌选择
void Select_RouletteWheel();
// 随机联赛选择
void Select_Tournament();
// 单点交叉
void OnePointCrossover(double probability_crossover);
// 均匀交叉
void UniformCrossover(double probability_crossover);
// 均匀变异
void UniformMutate(double probability_mutation);
// 差别变异，适应值越差的个体变异几率越大
void DiscriminateMutate();
void ReportSingleVarGenertation(int generation);
void ReportPcPm(double pc, double pm, double fitness);

#endif