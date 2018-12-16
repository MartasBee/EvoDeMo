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

#ifndef MUTATION_H
#define MUTATION_H

//==============================================================

#include "Genome.h"
#include "Random.h"
#include "../ConfigCore.h"
#include "../Defines.h"

//==============================================================
/**
 *  this class performs mutation of genome
 */

class CMutation
{
public:
  CMutation();


  // perform mutation
  void Mutation(CGenome *g);


  // settings
  void SetConfigCore(CConfigCore *cc);


  // check if any error happened
  int GetErrorFlag();

private:
  CConfigCore *pConfigCore;   //!< pointer to config class

  CRandom    random;          //!< instance of pseudo-random numbers generator

  int iErrFlag;               //!< error flag

  void _Mutation_01(CGenome *g);
  void _Mutation_02(CGenome *g);

  void _Mutation_Ins_01(CGenome *g);
};

//==============================================================

#endif // MUTATION_H

//==============================================================

