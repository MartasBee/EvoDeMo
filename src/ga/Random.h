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

#ifndef RANDOM_H
#define RANDOM_H

//==============================================================

#include <ctime>
#include <cmath>
#include <climits>
#include <cstdlib>

#include "../Defines.h"

//==============================================================
/**
 *  this class implements functions for pseudo-random number generation
 *  using own LCG
 */

class CRandom
{
public:
  CRandom();


  // functions for generating double value
  double Random();
  double Uniform(double l, double h);


  // functions for generarating int value
  unsigned long Uniform(unsigned long l, unsigned long h);
  int UniformStdLib(int low, int high);


  // check if any error happened
  int GetErrorFlag();

private:
  unsigned long seed;     //!< seed for LCG
  unsigned long ix;       //!< actually generated value

  int iErrFlag;           //!< error flag


  // base generator for <0,1)
  double LCG();
};

//==============================================================

#endif // RANDOM_H

//==============================================================

