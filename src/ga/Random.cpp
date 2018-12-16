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

#include "Random.h"

//==============================================================
/**
 *  class constructor
 */

CRandom::CRandom()
{
  seed = time(NULL);

  ix = seed;

  srand(seed);

  iErrFlag = RANDOM_OK;
}

//==============================================================
//==============================================================
/**
 *  returns pseudo-random number <0,1)
 */

double CRandom::Random()
{
  return LCG();
}

//==============================================================
/**
 *  returns pseudo-random floating point number <l,h)
 */

double CRandom::Uniform(double l, double h)
{
  if (l == h)
  {
    return LCG();
  }
  if(l > h)
  {
    double tmp = l;
    l = h;
    h = tmp;
  }

  return (l + ((h - l) * LCG()));
}

//==============================================================
/**
 *  returns pseudo-random int number <l,h)
 */

unsigned long CRandom::Uniform(unsigned long l, unsigned long h)
{
  if (l == h)
  {
    return static_cast<unsigned long>(LCG());
  }
  else if(l > h)
  {
    l = l ^ h;
    h = l ^ h;
    l = l ^ h;
  }

  return static_cast<unsigned long>(l + ((h - l) * LCG()));
}

//==============================================================
/**
 *  returns pseudo-random int number <low,high) using standard generator
 */

int CRandom::UniformStdLib(int low, int high)
{
  return (low + high * (rand() / (RAND_MAX + 1.0)));
}

//==============================================================
//==============================================================
/**
 *  returns pseudo-random floating point number <0,1) using
 *  custom Linear Congruent Generator
 */

double CRandom::LCG()
{
  ix = (ix * 69069L) + 1;
  return static_cast<double>(ix / ((double)ULONG_MAX + 1));
}

//==============================================================
//==============================================================
/**
 *  return error flag
 */

int CRandom::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================

