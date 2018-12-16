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

#ifndef FITNESS_H
#define FITNESS_H

//==============================================================

#include <iostream>


#include "../ca/space/Space.h"
#include "../Defines.h"
#include "../ConfigCore.h"

//==============================================================

#define FITNESS_CORNER_LU   0
#define FITNESS_CORNER_RD   1

//==============================================================
/**
 *  this class computes base of fitness value of genome which
 *  is actually used for ca computations
 *  fitness is maximalized in CGeneticAlgorithm class in function Fitness,
 *  see comment in GeneticAlgorithm.cpp on line 250 (this line in time,
 *  when i am writing this comment...)
 *
 *  fitness computation is simple: this class just looks to INIT space,
 *  shifts object in this space in (user definated) direction to
 *  (user definated) distances, then it looks to ACT space and checks,
 *  which cells have right value.
 *  if cell have right value, it will give fitness +1 point, else 0
 */

class CFitness
{
public:
  CFitness();


  // fitness value calculation
  int Fitness(CSpace *spaceInit, CSpace *spaceAct);


  // identify corness of ___ in init space
  bool IsLiveOrganismInSpace(CSpace *s);
  void IdentifyCorners(CSpace *s);

  // get corner's position
  int GetCornerPosX(int corn);
  int GetCornerPosY(int corn);


  // settings
  void SetConfigCore(CConfigCore *cc);


  // check if any error happened
  int GetErrorFlag();

private:
  CConfigCore *pConfigCore;   //!< pointer to config class

  int iX_1;                   //!< x-coord upper left corner of object's rectangle envelope
  int iY_1;                   //!< y-coord upper left corner of object's rectangle envelope
  int iX_2;                   //!< x-coord lower right corner of object's rectangle envelope
  int iY_2;                   //!< y-coord lower right corner of object's rectangle envelope

  bool bNonEmptyCellExists;   //!< tmp var used for object corner detection

  int iErrFlag;               //!< error flag


  // calculate init space move aligement
  void _MoveA(int dir, int distance, int *iMoveDir_X, int *iMoveDir_Y);

  // intern fitness function
  int _Fitness_01(CSpace *spaceInit, CSpace *spaceAct);
  int _Fitness_02(CSpace *spaceInit, CSpace *spaceAct);
};

//==============================================================

#endif // FITNESS_H

//==============================================================

