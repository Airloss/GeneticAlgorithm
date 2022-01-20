#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "..\include\genetic.h"
#include "..\include\randfunc.h"
#include "..\include\testfunc.h"

void Initialize()
{
    FILE *rfile;
    double lower = 0.0, upper = 0.0;
    if ((rfile = open("range.txt","r")) == NULL)
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

int main() {
    int generation = 0;
    double fitness = 0.0;
    srand((unsigned)time(NULL));
    if ((result_file = fopen("result_%d.csv","w")) == NULL)
    {
        printf("Failed open file\n");
        exit(1);
    }
    for (double crossover = 0.1; crossover <= 1.0; crossover += 0.1)
    {
        /* code */
    }
    
    
}