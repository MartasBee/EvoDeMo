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

#ifndef RULESTABLE_H
#define RULESTABLE_H

//==============================================================

#include "../ConfigCore.h"
#include "../Defines.h"
#include "../ga/Genome.h"

//==============================================================
/**
 *  rules table is touching point between CA and GA,
 *  contains pointer to genome and return genes from it
 */

class CRulesTable
{
public:
  CRulesTable(CGenome *gen = 0);

  void     SetGenome(CGenome *gen);
  CGenome *GetGenome();

  BYTE at(int index);

  void SetConfigCore(CConfigCore *pCC);

private:
  CGenome *genome;            //!< pointer to genome

  CConfigCore *pConfigCore;   //!< pointer to config class
};

//==============================================================

#endif // RULESTABLE_H

//==============================================================

