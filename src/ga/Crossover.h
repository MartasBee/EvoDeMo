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

#ifndef CROSSOVER_H
#define CROSSOVER_H

//==============================================================

#include "Genome.h"
#include "Random.h"
#include "../ConfigCore.h"
#include "../Defines.h"

//==============================================================
/**
 *  crossover class for creating child genomes using crossover
 *  NOT IMPLEMENTED
 */

class CCrossover
{
public:
  CCrossover();


  // perform crossover with genomes
  void Crossover(CGenome *g1, CGenome *g2);


  // settings
  void SetConfigCore(CConfigCore *cs);


  // check if any error happened
  int GetErrorFlag();

private:
  CConfigCore *pConfigCore;   //!< pointer to config class

  CRandom    random;          //!< instance of pseudo-random number generator class

  int iErrFlag;               //!< error flag
};

//==============================================================

#endif // CROSSOVER_H

//==============================================================

