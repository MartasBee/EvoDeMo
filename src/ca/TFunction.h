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

#ifndef TFUNCTION_H
#define TFUNCTION_H

//==============================================================

#include "RulesTable.h"
#include "space/Space.h"
#include "../Defines.h"
#include "../ConfigCore.h"

//==============================================================
/**
 *  transition function performs all calculations of CA
 *  for all cell in space it calculates index to genome, gets gene
 *  using CRulesTable class and writes new value of cell into next-gen space
 */

class CTFunction
{
public:
  CTFunction();


  // settings
  void SetRulesTable(CRulesTable *rt);
  void SetConfigCore(CConfigCore *cc);


  // calculate next space
  void NextSpace(CSpace *sa, CSpace *sn);


  // get error flag
  int GetErrorFlag();

private:
  CRulesTable *rules;         //!< pointer to rules table
  CConfigCore *pConfigCore;   //!< pointer to config class


  int iErrFlag;               //!< error flag


  // next space
  void NextSpaceGenomeStandard(CSpace *sa, CSpace *sn);
  void NextSpaceGenomeInstruction(CSpace *sa, CSpace *sn);


  // calcelate index to rules table
  int CalculateIndexGrid(CSpace *s, int x, int y);
  int CalculateIndexTorus(CSpace *s, int x, int y);
};

//==============================================================

#endif // TFUNCTION_H

//==============================================================

