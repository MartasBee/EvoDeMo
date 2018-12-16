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

#include "Selection.h"

//==============================================================
/**
 *  class constructor
 */

CSelection::CSelection()
{
  vecGenerationAct = NULL;
  vecGenerationTmp = NULL;

  pConfigCore = NULL;
}

//==============================================================
//==============================================================
/**
 *  performs selection of genomes from actual generation into next
 *
 *  @param *act         pointer to vector with pointers to genomes of actual generation
 *  @param *next        pointer to vector with pointers to genomes of next generation
 */

void CSelection::Selection(std::vector<CGenome *> *act, std::vector<CGenome *> *next)
{
  if((act == NULL) || (next == NULL))
  {
    {
      std::string msgErr  = "Class:    CSelection\n";
      msgErr += "Function: Selection()\n";
      msgErr += "Pointer to vector with actual or next generation is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return;
  }

  // set class's internal pointers
  vecGenerationAct = act;
  vecGenerationTmp = next;

  _Selection_02();
}

//==============================================================
//==============================================================
/**
 *  set config class
 */

void CSelection::SetConfigCore(CConfigCore *cc)
{
  pConfigCore = cc;
}

//==============================================================
//==============================================================
/**
 *  performs rulete selection - OLD one, actually NOT USED
 */

void CSelection::_Selection_01()
{
  if((vecGenerationAct == NULL) || (vecGenerationTmp == NULL))
  {
    {
      std::string msgErr  = "Class:    CSelection\n";
      msgErr += "Function: _Selection_01()\n";
      msgErr += "Pointer to vector with actual or next generation is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return;
  }

  long fitnessSum = 0;
  long fitnessMax = 0;

  // calculate sum of fitnesses of all chromosomes
  for(unsigned int i = 0; i < vecGenerationAct->size(); i++)
  {
    genome = NULL;

    genome = vecGenerationAct->at(i);

    fitnessSum += genome->GetFitness();

    if(genome->GetFitness() > fitnessMax)
      fitnessMax = genome->GetFitnessMax();
  }

  // calculate normalized fitnesses
  for(unsigned int i = 0; i < vecGenerationAct->size(); i++)
  {
    genome = NULL;

    genome = vecGenerationAct->at(i);

    genome->SetFitnessNorm((((double)genome->GetFitnessMax()) / ((double)fitnessMax)));//fitnessSum));
  }

  double tmp = random.Uniform((double)50,(double)95);

  tmp /= 100;

  // select genomes from act gen to next gen
  for(unsigned int i = 0; i < vecGenerationAct->size(); i++)
  {
    genome = NULL;

    genome = vecGenerationAct->at(i);

    if(genome->GetFitnessNorm() > tmp)
    {
      vecGenerationTmp->push_back(genome);
    }
    else
    {
      if(genome != NULL)
        delete genome;
      vecGenerationAct->at(i) = NULL;
    }
  }
}

//==============================================================
/**
 *  performs tournament selection of genomes
 *  ELITISM is used - first of all, best genome from whole popualtion
 *  is found, then DEEP COPY of this one is performed, and this copy
 *  is inserted into population vector at 1st position
 *  best genome is then selected 2nd time, this 2nd copy will be later
 *  mutated, first copy wont be
 */

void CSelection::_Selection_02()
{
  CGenome *genTmp_1 = vecGenerationAct->at(0);
  CGenome *genTmp_2 = genTmp_1;

  long tmp_1 = 0;
  long tmp_2 = 0;


  // find the best solution
  for(unsigned int i = 1; i < vecGenerationAct->size(); i++)
  {
    genTmp_1 = vecGenerationAct->at(i);
    if(genTmp_1->GetFitnessMax() > genTmp_2->GetFitnessMax())
      genTmp_2 = genTmp_1;
  }

  // make copy of best solution and store it as first genome
  genTmp_1 = new CGenome(*genTmp_2,GENOME_CONSTRUCT_COPY_MODE_DEEP,pConfigCore);
  if(genTmp_1 == NULL)
  {
    {
      std::string msgErr  = "Class:    CSelection\n";
      msgErr += "Function: _Selection_02()\n";
      msgErr += "Memory allocation for CGenome failed";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }
  }
  else
    // propagate best solution into next generation
    vecGenerationTmp->push_back(genTmp_1);


  // select number of genomes from act generation which will be propagate into next
  // min 10% max 90% od actual generation
  int tmp_count = static_cast<int>(((double)random.Uniform(10ul,90ul) / (double)100) * vecGenerationAct->size());


  // select tmp genomes
  for(int i = 0; i < tmp_count; i++)
  {
    if(vecGenerationAct->size() < 2)
      break;

    // randomly select 2 genomes
    tmp_1 = random.Uniform(0ul,(unsigned long)vecGenerationAct->size());
    tmp_2 = 0;

    do {
      tmp_2 = random.Uniform(0ul,(unsigned long)vecGenerationAct->size());
    }while(tmp_2 == tmp_1);

    genTmp_1 = vecGenerationAct->at(tmp_1);
    genTmp_2 = vecGenerationAct->at(tmp_2);

    // find genome with higher fitness and propagate if into next gen
    if(genTmp_1->GetFitnessMax() > genTmp_2->GetFitnessMax())
    {
      vecGenerationTmp->push_back(genTmp_1);
      vecGenerationAct->erase(vecGenerationAct->begin() + tmp_1);
    }
    else if(genTmp_1->GetFitnessMax() < genTmp_2->GetFitnessMax())
    {
      vecGenerationTmp->push_back(genTmp_2);
      vecGenerationAct->erase(vecGenerationAct->begin() + tmp_2);
    }
    // genomes with same fitness, randomly choose one
    else
    {
      long tmp = random.Uniform(0ul,99ul);
      if(tmp < 50)
      {
        vecGenerationTmp->push_back(genTmp_1);
        vecGenerationAct->erase(vecGenerationAct->begin() + tmp_1);
      }
      else
      {
        vecGenerationTmp->push_back(genTmp_2);
        vecGenerationAct->erase(vecGenerationAct->begin() + tmp_2);
      }
    }
  }

  // delete genomes, that was not propagate into next generation
  for(unsigned int i = 0; i < vecGenerationAct->size(); i++)
  {
    genTmp_1 = vecGenerationAct->at(i);
    if(genTmp_1 != NULL)
      delete genTmp_1;
    vecGenerationAct->at(i) = NULL;
  }
}

//==============================================================

