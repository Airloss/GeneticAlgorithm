#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "..\include\genetic.h"
#include "..\include\randfunc.h"
#include "..\include\testfunc.h"

int index_best = 0;

int main() 
{
  time_t start_t, end_t;
  double diff_t;
  int generation = 0;
  double fitness = 0.0;
  srand((unsigned)time(NULL));
  if ((result_file = fopen("result_%d.csv","w")) == NULL)
  {
      printf("Failed open file\n");
      exit(1);
  }
  time(&start_t);
  fitness = 0.0;
  for (int i = 0; i < 500; i++) 
  {
    generation = 0;
    Initialize();
    Evaluate();
    FindBest();
    while (generation < ITERATION_NUM)
    {
        generation++;
        Select_RouletteWheel();
        OnePointCrossover(PROB_CROSSOVER);
        UniformMutate(PROB_MUTATION);
        Evaluate();
        Elitist();
        ReportSingleVarGenertation(generation);
    }
    fitness = (fitness * i + population[POPULATION_SIZE].var_fitness) / (i + 1);
    
  }
  // ReportPcPm(PROB_CROSSOVER, PROB_MUTATION, fitness);
  
  printf("\nDiscriminateMutate Finish!\nBest Number:");
  for (int i = 0; i < VAR_NUM; i++) {
      printf("\n  x(%d) = %f", i, population[POPULATION_SIZE].genes[i]);
  }
  printf("\nbest fitness_value = %7.6f\n", population[POPULATION_SIZE].var_fitness);
  time(&end_t);
  diff_t = difftime(end_t, start_t);
  printf("\nComputate Successfully!\nUse time %3.3f(s)\n", diff_t);
  return 0;
}

void Initialize()
{
    FILE *rfile;
    double lower = 0.0, upper = 0.0;
    if ((rfile = fopen("range.txt","r")) == NULL)
    {
        printf("Failed to read range.txt\n");
        exit(1);
    }
    for (int i = 0; i < VAR_NUM; i++)
    {
        fscanf(rfile, "%lf", &lower);
        fscanf(rfile, "%lf", &upper);
        func_bound[i].lower = lower;
        func_bound[i].upper = upper;
        // printf("func_bound: %f, \t%f\n", func_bound[i].lower, func_bound[i].upper);
        for (int j = 0; j < POPULATION_SIZE; j++) 
        {
        population[j].genes[i] = DoubleRandValue(func_bound[i].lower, func_bound[i].upper);
        population[j].var_fitness = 0;
        }
        population[POPULATION_SIZE].genes[i] = 0;
        population[POPULATION_SIZE].var_fitness = 3;
    }
    fclose(rfile);
}

void Evaluate()
{
    double x[VAR_NUM];
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < VAR_NUM; j++)
        {
            x[j] = population[i].genes[j];
        }
        population[i].var_fitness = Test_Function_1(x[0], x[1]);
    }
}

int FindBest() {
  int flag = 0;
  for (int i = 0; i < POPULATION_SIZE; i++) {
    if (population[i].var_fitness < population[POPULATION_SIZE].var_fitness) {
      index_best = i;
      population[POPULATION_SIZE] = population[i];
      flag = 1;
    }
  }
  return flag;
}

void Elitist() {
  int flag = FindBest(), worst = 0;
  if (flag == 0) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
      if (population[i].var_fitness <= population[worst].var_fitness) {
        worst = i;
      }
    }
    population[worst] = population[POPULATION_SIZE];
  }
}

void Select_RouletteWheel() {
  double p, cumulative_probability[POPULATION_SIZE];
  for (int i = 0; i < POPULATION_SIZE; i++) {
    cumulative_probability[i] = population[i].var_fitness;
    if (i > 0) {
      cumulative_probability[i] += cumulative_probability[i-1];
    }
  }
  for (int i = 0; i < POPULATION_SIZE; i++) {
    cumulative_probability[i] /= cumulative_probability[POPULATION_SIZE-1];
  }
  for (int i = 0; i < POPULATION_SIZE; i++) {
    p = RandProbability();
    for (int j = 0; j < POPULATION_SIZE; j++) {
      if (p <= cumulative_probability[j]) {
        new_population[i] = population[j];
        break;
      }
    }
  }
  for (int i = 0; i < POPULATION_SIZE; i++) {
    population[i] = new_population[i];
  }
}

void Select_Tournament() {
  int select[2];
  for (int i = 0; i < POPULATION_SIZE; i++) {
    select[0] = IntRandValue(POPULATION_SIZE);
    do {
      select[1] = IntRandValue(POPULATION_SIZE);
    } while (select[0] == select[1]);
    if (population[select[0]].var_fitness > population[select[1]].var_fitness) {
      new_population[i] = population[select[0]];
    } else {
      new_population[i] = population[select[1]];
    }
  }
  for (int i = 0; i < POPULATION_SIZE; i++) {
    population[i] = new_population[i];
  }
}

void OnePointCrossover(double probability_crossover) {
  int flag_even = 0, index = 0;
  double temp = 0.0;
  for (int i = 0; i < POPULATION_SIZE; i++) {
    if (RandProbability() <= probability_crossover) {
      flag_even++;
      if (flag_even%2 == 0) {
        for (int j = 0; j < (VAR_NUM-1); j++) {
          temp = population[index].genes[j];
          population[index].genes[j] = population[i].genes[j];
          population[i].genes[j] = temp;
        }
      } else {
        index = i;
      }
    }
  }
}

void UniformCrossover(double probability_crossover) {
  int flag_even = 0, index = 0;
  double temp = 0.0;
  for (int i = 0; i < POPULATION_SIZE; i++) {
    if (RandProbability() <= probability_crossover) {
      flag_even++;
      if (flag_even%2 == 0) {
        for (int j = 0; j < (VAR_NUM-1); j++) {
          temp = population[index].genes[j];
          if (population[index].genes[j] > population[i].genes[j]) {
            population[index].genes[j] = DoubleRandValue(population[i].genes[j], temp);
            population[i].genes[j] = DoubleRandValue(population[i].genes[j], temp);
          } else {
            population[index].genes[j] = DoubleRandValue(temp, population[i].genes[j]);
            population[i].genes[j] = DoubleRandValue(temp, population[i].genes[j]);
          }
        }
      } else {
        index = i;
      }
    }
  }
}

void UniformMutate(double probability_mutation) {
  for (int i = 0; i < POPULATION_SIZE; i++) {
    for (int j = 0; j < VAR_NUM; j++) {
      if (RandProbability() <= probability_mutation) {
        population[i].genes[j] = DoubleRandValue(func_bound[j].lower, func_bound[j].upper);
      }
    }
  }
}

void DiscriminateMutate() {
  for (int i = 0; i < POPULATION_SIZE; i++) {
    if (RandProbability() <= (double)((population[i].var_fitness - population[POPULATION_SIZE].var_fitness)/population[i].var_fitness)) {
      for (int j = 0; j < VAR_NUM; j++) {
        population[i].genes[j] = DoubleRandValue(func_bound[j].lower, func_bound[j].upper);
      }
    }  
  }
}

void ReportSingleVarGenertation(int generation) {
  double sum=0.0, sum_square=0.0, averge;
  for (int i = 0; i < POPULATION_SIZE; i++) {
    sum += population[i].var_fitness;
    sum_square += population[i].var_fitness * population[i].var_fitness;
  }
  averge = sum/(double)POPULATION_SIZE;
  fprintf(result_file, "%5d,%12.6f,%12.6f\n", generation, population[POPULATION_SIZE].var_fitness, averge);
}

void ReportPcPm(double pc, double pm, double fitness) {
  fprintf(result_file, "%4.3f,%4.3f,%8.6f\n", pc, pm, fitness);
}
