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

#ifndef SELECTION_H
#define SELECTION_H

//==============================================================

#include <vector>

#include "Genome.h"
#include "Random.h"
#include "../ConfigCore.h"
#include "../Defines.h"

//==============================================================
/**
 *  performs selection, actually by using tournamen selection
 *  implements elitism
 */

class CSelection
{
public:
  CSelection();


  // perform selection
  void Selection(std::vector<CGenome*>*act,std::vector<CGenome*>*next);


  // settings
  void SetConfigCore(CConfigCore *cc);

private:
  CConfigCore *pConfigCore;                 //!< pointer to config class

  CGenome *genome;                          //!< pointer to actually used genome
  CRandom random;                           //!< instance of number generating class

  std::vector<CGenome*> *vecGenerationAct;  //!< pointer to vector which contains actual generation of population
  std::vector<CGenome*> *vecGenerationTmp;  //!< pointer to vector for next generation

  void _Selection_01();
  void _Selection_02();
};

//==============================================================

#endif // SELECTION_H

//==============================================================

