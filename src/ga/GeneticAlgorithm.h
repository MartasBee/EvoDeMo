/*
 *  Project:      EvoDeMo - Bachelor Thesis
 *  Date:         May 10, 2010 (estimated)
 **
 *  Author:       Martin Balaz
 *  Contact:      balaz.marti@gmail.com
 *                xbalaz00@stud.fit.vutbr.cz
 **
 *  Institution:  Brno University of Technology
 *                Faculty of Information Technology
 *                www.fit.vutbr.cz
 **
 *  Copyright (c) 2010 by Martin Balaz
 */

//==============================================================

#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

//==============================================================

#include <vector>
#include <string>

#include "Genome.h"
#include "Crossover.h"
#include "Mutation.h"
#include "Fitness.h"
#include "Random.h"
#include "Selection.h"
#include "../ConfigCore.h"
#include "../ca/space/Space.h"
#include "../Defines.h"

//==============================================================
/**
 *  main class of genetic algorithm - manages all ga computation
 *  using specialized classes for partial tasks - CFitness, CMutation, CSelection, CGenome
 */

class CGeneticAlgorithm
{
public:
  CGeneticAlgorithm(CConfigCore *configCore);
  ~CGeneticAlgorithm();


  // genotype initialization
  void InitGenotype();
  void InitGenotypeReevolve(CGenome *genomeInit);
  void ImportGenomeToPopulation(CGenome *genomeImport);


  // ga operaions
  void Fitness(CGenome *genome, CSpace *spaceInit, CSpace *spaceAct, int caStepAct);

  void CreateNextGeneration();
  void CreateNextGeneration(int genID);

  void Selection();
  void Crossover();
  void Mutation();


  // identify corness of ___ in init space
  void IdentifyCorners(CSpace *s);

  // get corner's position
  int GetCornerPosX(int corn);
  int GetCornerPosY(int corn);


  // set "upper level" config class pointer
  void SetConfigCore(CConfigCore *ccc);

  CGenome *GetGenome(int id);
  CGenome *GetBestGenome();

  // get actual population
  std::vector<CGenome*> *GetActualPopulation();
  // get size of actual generation
  int GetActualPopulationSize();

  // check if genome with id exists in vector
  bool ExistsGenomeId(int id);


  // check if any error happened
  int GetErrorFlag();

private:
  CConfigCore *pConfigCore;                   //!< pointer to config class

  CFitness   fitness;                         //!< instance of fitness class
  CSelection select;                          //!< instance of selection class
  CCrossover crossover;                       //!< instance of crossover class
  CMutation  mutate;                          //!< instance of mutation class

  CRandom    random;                          //!< instance of pseudo-random number generator class

  CGenome *genomeTmp;                         //!< tmp pointer used for creating new genomes
  CGenome *bestGenome;                        //!< pointer to best genome
  CGenome *genomeErr;                         //!< pointer to error genome

  std::vector<CGenome*> vecGenerationX;       //!< vector which contains pointer for genomes
  std::vector<CGenome*> vecGenerationY;       //!< vector which contains pointer for genomes

  // pointer to population X and Y vectors
  std::vector<CGenome*> *vecGenerationAct;    //!< act population vector - contains pointers to genomes from act generation
  std::vector<CGenome*> *vecGenerationTmp;    //!< vector used for savig pointer of genomes for next gen
  std::vector<CGenome*> *vecGenerationTmpX;   //!< just tmp var using for exchange pointers between act and tmp vectors

  int iGenerationActID;                       //!< actual generation id
  int iGenerationActSize;                     //!< actual generation size

  int iErrFlag;                               //!< error flag


  // delete allocated memory for genotype
  void ClearVectors();


  // refill population to init size
  void RefillPopulation();
  // renumber chromosomes in act vector
  void RenumberActualGeneration();


  // init standard genotype
  void InitGenonetypeStandard();
  // init instruction genotype
  void InitGenotypeInstruction();
};

//==============================================================

#endif // GENETICALGORITHM_H

//==============================================================

