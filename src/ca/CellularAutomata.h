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

#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

//==============================================================

#include "TFunction.h"
#include "RulesTable.h"
#include "../ConfigCore.h"
#include "space/Space.h"
#include "../Defines.h"

//==============================================================
/**
 *  main class of cellular automaton
 *  this class creates instances of ca space and manages ca computations
 *  for computations themself is used class CTFunction, which calculates
 *  index to genome (at this index is gene of BYTE data type which represents
 *  value of cell in next step), genome itself is mapped into instance of TRulesTable
 */

class CCellularAutomata
{
public:
  CCellularAutomata(CConfigCore *configCore);
  ~CCellularAutomata();


  // perform one step of CA
  void Step();
  void StepGoL();


  // initialization
  void InitMemory();
  void InitSpace();
  void ReInit();


  // get config & rules table
  CRulesTable *GetRulesTable();

  // set "upper" level config class pointer
  void SetConfigCore(CConfigCore *ccc);


  // get CA spaces
  CSpace *GetSpace();
  CSpace *GetInitSpace();


  // get number of steps done
  int GetStepsDone();
  // get error flag
  int GetErrorFlag();
  // check if initialization is done
  bool IsInitDone();

private:
  CRulesTable rules;          //!< instance of rules table
  CTFunction  tfunction;      //!< instance of transition function

  CConfigCore *pConfigCore;   //!< pointer to config class

  CSpace      *spaceInit;     //!< init space - this class containes init ca space definated by user
  CSpace      *spaceAct;      //!< sa space in actual step of computation
  CSpace      *spaceTmp;      //!< tmp space is used for saving next step result
  CSpace      *spaceTmpX;     //!< pointer used for switching pointers between act and tmp instances

  unsigned int iStepsDone;    //!< number of steps done

  bool bInitDone;             //!< is init done?

  int iErrFlag;               //!< error flag


  // delete CA spaces
  void DeleteSpace();
  void DeleteSpaceInit();


  // do one step of GoL algorithm
  void GoL();
};

//==============================================================

#endif // CELLULARAUTOMATA_H

//==============================================================

