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

#include "GeneticAlgorithm.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *configCore  pointer config class
 */

CGeneticAlgorithm::CGeneticAlgorithm(CConfigCore *configCore)
{
  pConfigCore = configCore;

  // propagate config class into ga sub-classes
  fitness.SetConfigCore(pConfigCore);
  select.SetConfigCore(pConfigCore);
  crossover.SetConfigCore(pConfigCore);
  mutate.SetConfigCore(pConfigCore);

  // clear population vectors
  ClearVectors();

  iGenerationActID   = 0;
  iGenerationActSize = 0;

  // create error genome
  genomeErr = new CGenome(pConfigCore->GetGenomeType(),0,0,pConfigCore);
  if(genomeErr == NULL)
    iErrFlag = GA_ERR_MEMORY_FAIL;
  else
    iErrFlag = GA_OK;

  genomeTmp  = NULL;
  bestGenome = NULL;
}

//==============================================================
/**
 *  class destructor
 */

CGeneticAlgorithm::~CGeneticAlgorithm()
{
  if(genomeErr != NULL)
    delete genomeErr;

  ClearVectors();
}

//==============================================================
//==============================================================
/**
 *  creates init population of genomes
 */

void CGeneticAlgorithm::InitGenotype()
{
  /*
  if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_INS)
    InitGenotypeInstruction();
  else
    */
  InitGenonetypeStandard();
}

//==============================================================
/**
 *  creates init population of genomes from given genome
 *
 *  @param *genomeInit  init genome which should be re-evolved
 */

void CGeneticAlgorithm::InitGenotypeReevolve(CGenome *genomeInit)
{
  if(genomeInit == NULL)
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: InitGenotypeReevolve()\n";
      msgErr += "Pointer to CGenome is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_UNKNOWN;
    return;
  }
  // check genome compatibility
  if(genomeInit->GetGenomeType() != pConfigCore->GetGenomeType())
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: ImportGenomeToPopulation()\n";
      msgErr += "Incompatibile genome type";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_UNKNOWN;
    return;
  }

  iGenerationActID = 0;
  ClearVectors();

  iErrFlag = GA_OK;

  // create population of copies of given genome
  for(int i = 0; i < pConfigCore->GetPopulationSize(); i++)
  {
    genomeTmp = new CGenome(*genomeInit,GENOME_CONSTRUCT_COPY_MODE_NEXT_GEN,pConfigCore);
    if(genomeTmp == NULL)
    {
      {
        std::string msgErr  = "Class:    CGeneticAlgorithm\n";
        msgErr += "Function: ImportGenomeToPopulation()\n";
        msgErr += "Memory allocation for CGenome class failed";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = GA_ERR_UNKNOWN;
      ClearVectors();
      return;
    }
    // check if no error happend during creation of genome (during run of genomes's constructor code)
    else if(genomeTmp->GetErrorFlag() != GENOME_OK)
    {
      iErrFlag = GA_ERR_MEMORY_FAIL;
      ClearVectors();
      return;
    }

    vecGenerationAct->push_back(genomeTmp);
  }

  iGenerationActSize = vecGenerationAct->size();

  RenumberActualGeneration();
  // mutated generation - all genomes are actually same (!!!)
  Mutation();
}

//==============================================================
/**
 *  imports given genome in actual population
 *
 *  @param *genomeImport  genome which will be imported into actual gen
 */

void CGeneticAlgorithm::ImportGenomeToPopulation(CGenome *genomeImport)
{
  if(genomeImport == NULL)
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: ImportGenomeToPopulation()\n";
      msgErr += "Pointer to CGenome is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_UNKNOWN;
    return;
  }
  // check genome compatibility
  if(genomeImport->GetGenomeType() != pConfigCore->GetGenomeType())
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: ImportGenomeToPopulation()\n";
      msgErr += "Incompatibile genome type";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_UNKNOWN;
    return;
  }

  iErrFlag = GA_OK;

  // create copy of given genome
  genomeTmp = new CGenome(*genomeImport,GENOME_CONSTRUCT_COPY_MODE_DEEP,pConfigCore);
  if(genomeTmp == NULL)
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: ImportGenomeToPopulation()\n";
      msgErr += "Memory allocation for CGenome class failed";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_UNKNOWN;
    ClearVectors();
    return;
  }
  // check if no error happend during creation of genome (during run of genomes's constructor code)
  else if(genomeTmp->GetErrorFlag() != GENOME_OK)
  {
    iErrFlag = GA_ERR_MEMORY_FAIL;
    ClearVectors();
    return;
  }

  // import it into genereation
  vecGenerationAct->push_back(genomeTmp);

  iGenerationActSize = vecGenerationAct->size();
}

//==============================================================
//==============================================================
/**
 *  computes fitness usig CFitness class, this fc checking if actual
 *  step of ca is final step in which object shifting should be done
 *  if this is final step, this function maximalizes fitness of given genome
 *  in case, that this genome is "good" (has relative fitness higher that 0.9)
 *  if this is not final step, but fitness is "good", it also maximalizes fitness
 *  but the maximalization is smaller in comparition to final step case
 *
 *  @param *genome      pointer to actually used genome
 *  @param *spaceInit   pointer to init space of ca needed be CFitness class
 *  @param *spaceAct    pointer to actual space of ca
 *  @param caStepAct    actual step of ca
 */

void CGeneticAlgorithm::Fitness(CGenome *genome, CSpace *spaceInit, CSpace *spaceAct, int caStepAct)
{
  if((genome == NULL) || (spaceInit == NULL) || (spaceAct == NULL) || (pConfigCore == NULL))
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: Fitness()\n";
      msgErr += "Pointer to CGenome or CSpace or CConfigCore is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_NULL_POINTER;
    return;
  }

  // calculate fitness using CFitness class
  int fit = fitness.Fitness(spaceInit,spaceAct);
  if(fitness.GetErrorFlag() != FITNESS_OK)
    iErrFlag = GA_ERR_UNKNOWN;
  else
  {
    if(!fitness.IsLiveOrganismInSpace(spaceAct))
    {
      iErrFlag = GA_OK;
      genome->SetFitness(0,pConfigCore->GetSpaceSizeX() * pConfigCore->GetSpaceSizeY(),caStepAct);
      return;
    }

    iErrFlag = GA_OK;

    // calculate maximum fitness which can CFitness class return
    int fitMax    = pConfigCore->GetSpaceSizeX() * pConfigCore->GetSpaceSizeY();
    // calculate differention
    int diff      = fitMax - fit;
    // calculate relative maximum fitness
    int relFitMax = int(fitMax * float(float(pConfigCore->GetCrossoverProbability()) / 100));


    // peform fitness maximalization, if relative fitness of genome is higher than 0.9 of
    // maximum fitness
    if((fit > relFitMax))// && (fit >= oldFitMax))
    {
      if(caStepAct == pConfigCore->GetStepsCountCA())
        fit += ((fitMax / 2) * caStepAct);
      else if(caStepAct > pConfigCore->GetStepsCountCA())
        fit += ((fitMax / 2) / caStepAct);
    }

    genome->SetFitness(fit,diff,caStepAct);
    genome->SetFitnessNorm(double((double)fit/(fitMax + ((fitMax) / 2 * pConfigCore->GetStepsCountCA()))));
  }
}

//==============================================================
//==============================================================
/**
 *  creates new generation of population of genomes
 *  SELECTs genomes to next gen
 *  RE-FILLs population from selected genomes
 *  MUTATE all genomes (with exception of best one, explained in Mutation fc)
 *  RE-NUMBER population - sets new generation id and genome id
 *
 *  CROSSOVER is NOT USED
 *
 *  @param genID        sets generation id to given value
 */

void CGeneticAlgorithm::CreateNextGeneration(int genID)
{
  iGenerationActID = genID;

  Selection();

  RefillPopulation();

  Mutation();

  RenumberActualGeneration();
}

//==============================================================
/**
 *  same is previous fc
 */

void CGeneticAlgorithm::CreateNextGeneration()
{
  iGenerationActID += 1;

  Selection();

  RefillPopulation();

  Mutation();

  RenumberActualGeneration();
}

//==============================================================
//==============================================================
/**
 *  performs selection using CSelection class
 */

void CGeneticAlgorithm::Selection()
{
  select.Selection(vecGenerationAct,vecGenerationTmp);

  // exchange pointers to act and tmp generation
  vecGenerationTmpX = vecGenerationAct;
  vecGenerationAct  = vecGenerationTmp;
  vecGenerationTmp  = vecGenerationTmpX;
  vecGenerationTmpX = NULL;

  vecGenerationTmp->clear();

  iGenerationActSize = vecGenerationAct->size();
}

//==============================================================
/**
 *  performs crossover - NOT IMPLEMENTED
 */

void CGeneticAlgorithm::Crossover()
{

}

//==============================================================
/**
 *  performs mutation using CMutate class
 *  best genome from population is selected twice - one copy which
 *  is on 1st position of population vector is NOT MUTATED - ALGORITHM USING ELITISM !!!
 */

void CGeneticAlgorithm::Mutation()
{
  // mutated all genomes except 1st one
  for(unsigned int i = 1; i < vecGenerationAct->size(); i++)
  {
    if(!ExistsGenomeId(i))
    {
      {
        std::string msgErr  = "Class:    CGeneticAlgorithm\n";
        msgErr += "Function: Mutation()\n";
        msgErr += "Genome index out of range";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = GA_ERR_OUT_OF_RANGE;
      continue;
    }

    genomeTmp = vecGenerationAct->at(i);

    mutate.Mutation(genomeTmp);

    if(mutate.GetErrorFlag() != MUTATION_OK)
      iErrFlag = GA_ERR_UNKNOWN;
    else
      iErrFlag = GA_OK;
  }
}

//==============================================================
//==============================================================
/**
 *  founds corners of object in ca space using CFitness class
 *
 *  @param *s           pointer to ca space
 */

void CGeneticAlgorithm::IdentifyCorners(CSpace *s)
{
  if(s == NULL)
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: IdentifyCorners()\n";
      msgErr += "Pointer to CSpace is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_NULL_POINTER;
    return;
  }

  fitness.IdentifyCorners(s);
  if(fitness.GetErrorFlag() == FITNESS_OK)
    iErrFlag = GA_OK;
  else
    iErrFlag = GA_ERR_NO_INPUT;
}

//==============================================================
/**
 *  returns object's x-position of selected corner
 */

int CGeneticAlgorithm::GetCornerPosX(int corn)
{
  return fitness.GetCornerPosX(corn);
}

//==============================================================
/**
 *  returns object's y-position of selected corner
 */

int CGeneticAlgorithm::GetCornerPosY(int corn)
{
  return fitness.GetCornerPosY(corn);
}

//==============================================================
//==============================================================
/**
 * sets config class
 */

void CGeneticAlgorithm::SetConfigCore(CConfigCore *ccc)
{
  pConfigCore = ccc;
}

//==============================================================
/**
 *  returns pointer to genome with given id
 *
 *  @param id           id of genome from actual population
 */

CGenome* CGeneticAlgorithm::GetGenome(int id)
{
  if(vecGenerationAct == NULL)
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: GetGenome()\n";
      msgErr += "Pointer to vector with actual generation is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_NULL_POINTER;
    return genomeErr;
  }
  // check if genome with this id exists
  if(!ExistsGenomeId(id))
  {
    iErrFlag = GA_ERR_OUT_OF_RANGE;
    return genomeErr;
  }

  if(vecGenerationAct->at(id) == NULL)
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: GetGenome()\n";
      msgErr += "Genome with required id is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = GA_ERR_NULL_POINTER;
    return genomeErr;
  }
  else
    return vecGenerationAct->at(id);
}

//==============================================================
/**
 *  returns pointer to best genome
 */

CGenome* CGeneticAlgorithm::GetBestGenome()
{
  return bestGenome;
}

//==============================================================
/**
 *  returns pointer to vector with actual generation
 */

std::vector<CGenome*> * CGeneticAlgorithm::GetActualPopulation()
{
  return vecGenerationAct;
}

//==============================================================
/**
 *  returns size of actual generation
 */

int CGeneticAlgorithm::GetActualPopulationSize()
{
  return iGenerationActSize;
}

//==============================================================
/**
 *  checks if genome with given id exists
 *
 *  @param id           id of genome in actual population
 */

bool CGeneticAlgorithm::ExistsGenomeId(int id)
{
  if(vecGenerationAct == NULL)
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: ExistsGenomeId()\n";
      msgErr += "Pointer to vector with actual generation is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return false;
  }

  if((id < 0) || (id >= (signed)vecGenerationAct->size()))
  {
    {
      std::string msgErr  = "Class:    CGeneticAlgorithm\n";
      msgErr += "Function: ExistsGenomeId()\n";
      msgErr += "Genome with required id does not exist";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return false;
  }
  else
  {
    if(vecGenerationAct->at(id) == NULL)
    {
      {
        std::string msgErr  = "Class:    CGeneticAlgorithm\n";
        msgErr += "Function: ExistsGenomeId()\n";
        msgErr += "Genome at required position is NULL";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      return false;
    }
    else
      return true;
  }
}

//==============================================================
/**
 *  returns error flag
 */

int CGeneticAlgorithm::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================
/**
 *  clears vectors which carring actual generation and tmp (next) gen
 */

void CGeneticAlgorithm::ClearVectors()
{
  vecGenerationAct = NULL;

  if(vecGenerationX.size() > 0)
  {
    for(unsigned int i = 0; i < vecGenerationX.size(); i++)
    {
      delete vecGenerationX.at(i);
      vecGenerationX.at(i) = NULL;
    }
  }

  if(vecGenerationY.size() > 0)
  {
    for(unsigned int i = 0; i < vecGenerationY.size(); i++)
    {
      delete vecGenerationY.at(i);
      vecGenerationY.at(i) = NULL;
    }
  }

  vecGenerationX.clear();
  vecGenerationY.clear();

  vecGenerationAct  = &vecGenerationX;
  vecGenerationTmp  = &vecGenerationY;
  vecGenerationTmpX = NULL;

 iGenerationActSize = vecGenerationAct->size();
}

//==============================================================
//==============================================================
/**
 *  refills population - after selection is important to create new genomes
 *  for refilling population to init size, because no croosover to creation
 *  child genomes is used
 *  population is refilled from genomes selected into next gen
 */

void CGeneticAlgorithm::RefillPopulation()
{
  CGenome *tmpG  = NULL;
  int      tmpId = 0;

  // loop while population is not full
  while((pConfigCore->GetPopulationSize() - iGenerationActSize) > 0)
  {
    // randomly choose "parent" genome
    tmpId = static_cast<int>(random.Uniform(0ul,(iGenerationActSize * 100)) / 100);

    if(!ExistsGenomeId(tmpId))
      continue;

    genomeTmp = vecGenerationAct->at(tmpId);

    // create copy of this genome
    tmpG = new CGenome(*genomeTmp,GENOME_CONSTRUCT_COPY_MODE_NEXT_GEN,pConfigCore);

    // import it into population
    if((tmpG != NULL) && (tmpG->GetErrorFlag() == GENOME_OK))
    {
      tmpG->SetThisGenomeId(iGenerationActID,vecGenerationAct->size());
      tmpG->SetThisInitGenomeId(iGenerationActID,vecGenerationAct->size());

      vecGenerationAct->push_back(tmpG);
    }
    else
    {
      {
        std::string msgErr  = "Class:    CGeneticAlgorithm\n";
        msgErr += "Function: RefillPopulation()\n";
        msgErr += "Memory allocation for genome failed or other error happedned";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      continue;
    }

    iGenerationActSize += 1;
  }
}

//==============================================================
/**
 *  renumbers genomes in population - sets actual generation id
 *  and genome id, which depends in index of genome in vector
 */

void CGeneticAlgorithm::RenumberActualGeneration()
{
  for(unsigned int i = 0; i < vecGenerationAct->size(); i++)
  {
    genomeTmp = vecGenerationAct->at(i);
    genomeTmp->SetThisGenomeId(iGenerationActID,i);
  }
}

//==============================================================
//==============================================================
/**
 *  creates init population of genomes
 */

void CGeneticAlgorithm::InitGenonetypeStandard()
{
  iErrFlag = GA_OK;

  iGenerationActID = 0;

  int indexG = 0;
  int randL  = 0; // min gene value
  int randH  = 0; // max gene value
  int iRand  = 0; // randomly choosed gene value

  ClearVectors();

  for(int i = 0; i < pConfigCore->GetPopulationSize(); i++)
  {
    // 9-neighborhood 2 states genomes are used
    if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_9N)
    {
      genomeTmp = new CGenome(GENOME_TYPE_2_9N,iGenerationActID,i,pConfigCore);
      if(genomeTmp == NULL)
      {
        {
          std::string msgErr  = "Class:    CGeneticAlgorithm\n";
          msgErr += "Function: InitGenonetypeStandard()\n";
          msgErr += "Memory allocation for genome failed";

          if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
            pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
          else
            std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = GA_ERR_MEMORY_FAIL;
        ClearVectors();
        return;
      }

      indexG = GENOME_SIZE_TYPE_2_9N;
      randH  = 199;
    }
    // 9-neighborhood 3 states genomes are used
    else if(pConfigCore->GetGenomeType() == GENOME_TYPE_3_9N)
    {
      genomeTmp = new CGenome(GENOME_TYPE_3_9N,iGenerationActID,i,pConfigCore);
      if(genomeTmp == NULL)
      {
        {
          std::string msgErr  = "Class:    CGeneticAlgorithm\n";
          msgErr += "Function: InitGenonetypeStandard()\n";
          msgErr += "Memory allocation for genome failed";

          if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
            pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
          else
            std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = GA_ERR_MEMORY_FAIL;
        ClearVectors();
        return;
      }

      indexG = GENOME_SIZE_TYPE_3_9N;
      randH  = 299;
    }
    // 9-neighborhood 4 states genomes are used
    else if(pConfigCore->GetGenomeType() == GENOME_TYPE_4_9N)
    {
      genomeTmp = new CGenome(GENOME_TYPE_4_9N,iGenerationActID,i,pConfigCore);
      if(genomeTmp == NULL)
      {
        {
          std::string msgErr  = "Class:    CGeneticAlgorithm\n";
          msgErr += "Function: InitGenonetypeStandard()\n";
          msgErr += "Memory allocation for genome failed";

          if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
            pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
          else
            std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = GA_ERR_MEMORY_FAIL;
        ClearVectors();
        return;
      }

      indexG = GENOME_SIZE_TYPE_4_9N;
      randH  = 399;
    }
    // 5-neighborhood 2 states genomes are used
    else if(pConfigCore->GetGenomeType() == GENOME_TYPE_2_5N)
    {
      genomeTmp = new CGenome(GENOME_TYPE_2_5N,iGenerationActID,i,pConfigCore);
      if(genomeTmp == NULL)
      {
        {
          std::string msgErr  = "Class:    CGeneticAlgorithm\n";
          msgErr += "Function: InitGenonetypeStandard()\n";
          msgErr += "Memory allocation for genome failed";

          if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
            pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
          else
            std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = GA_ERR_MEMORY_FAIL;
        ClearVectors();
        return;
      }

      indexG = GENOME_SIZE_TYPE_2_5N;
      randH  = 199;
    }
    // 5-neighborhood 3 states genomes are used
    else if(pConfigCore->GetGenomeType() == GENOME_TYPE_3_5N)
    {
      genomeTmp = new CGenome(GENOME_TYPE_3_5N,iGenerationActID,i,pConfigCore);
      if(genomeTmp == NULL)
      {
        {
          std::string msgErr  = "Class:    CGeneticAlgorithm\n";
          msgErr += "Function: InitGenonetypeStandard()\n";
          msgErr += "Memory allocation for genome failed";

          if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
            pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
          else
            std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = GA_ERR_MEMORY_FAIL;
        ClearVectors();
        return;
      }

      indexG = GENOME_SIZE_TYPE_3_5N;
      randH  = 299;
    }
    // 5-neighborhood 4 states genomes are used
    else if(pConfigCore->GetGenomeType() == GENOME_TYPE_4_5N)
    {
      genomeTmp = new CGenome(GENOME_TYPE_4_5N,iGenerationActID,i,pConfigCore);
      if(genomeTmp == NULL)
      {
        {
          std::string msgErr  = "Class:    CGeneticAlgorithm\n";
          msgErr += "Function: InitGenonetypeStandard()\n";
          msgErr += "Memory allocation for genome failed";

          if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
            pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
          else
            std::cerr << "ERROR: " << msgErr;
        }


        iErrFlag = GA_ERR_MEMORY_FAIL;
        ClearVectors();
        return;
      }

      indexG = GENOME_SIZE_TYPE_4_5N;
      randH  = 399;
    }
    // unknown genomes - error
    else
    {
      {
        std::string msgErr  = "Class:    CGeneticAlgorithm\n";
        msgErr += "Function: InitGenonetypeStandard()\n";
        msgErr += "Unknown CGenome type required";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      iErrFlag = GA_ERR_UNKNOWN;
      return;
    }

    // check if no error happend during creation of genome (during run of genomes's constructor code)
    if(genomeTmp->GetErrorFlag() != GENOME_OK)
    {
      iErrFlag = GA_ERR_MEMORY_FAIL;
      ClearVectors();
      return;
    }

    // randomly init genes in genome
    for(int j = 0; j < indexG; j++)
    {
      // choose gene value
      iRand = static_cast<int>(random.Uniform((unsigned long)randL,(unsigned long)randH) / 100);

      genomeTmp->SetGene(j,(BYTE)iRand);
    }

    // import genome into population
    vecGenerationAct->push_back(genomeTmp);

    genomeTmp = NULL;
  }

  iGenerationActSize = vecGenerationAct->size();
}

//==============================================================
/**
 *  inits population with instruction genomes - NOT IMPLEMENTED
 */

void CGeneticAlgorithm::InitGenotypeInstruction()
{

}

//==============================================================

