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

#ifndef CORE_H
#define CORE_H

//==============================================================

#include <QObject>
#include <QMutex>
#include <QWaitCondition>

#include "ThreadCore.h"
#include "ConfigCore.h"
#include "ca/space/Space.h"
#include "ga/Genome.h"

#include "Defines.h"

//==============================================================
/**
 *  this is special class - is used as mediator between gui classes and CThreadCore -
 *  computation class
 *  this class solves thread sync between gui and core
 *  core send data from ga and ca to this class, this class then tell gui, that new data arrived
 *  and gui then copy this data and displays them, last step is, that gui tells this class,
 *  that data are displayed, this class send this info to core, so core will know, that can send
 *  new data
 *
 *  this class is created when "Init" button is pressed and deleted when "Delete" button is pressed
 *  when init button is pressed, this class creates CThreadCore and propagate sync pointers to it
 *  when delete is pressed this class kills compute core thread
 */

class CCore : public QObject
{
  Q_OBJECT

public:
  CCore();
  ~CCore();


  // init data structs and threads
  void InitGuiCore();


  // synchronization with gui
  void SetCoreDataExpiration(bool e);
  void SetSimulationRunning(bool sr);
  void SetCaRunTermination();


  // start core thread
  void StartThreadCore();


  // check if init is done
  bool IsInitDone();


  // get pointer to config class
  CConfigCore *GetConfigCore();

  // get pointer to ca space classes from core
  CSpace *GetSpace();


  // ga statistical data
  int GetSimCoreGenerationID();
  int GetSimCoreChromosomeID();
  int GetSimCoreAncestorsCount();
  int GetSimCoreFitnessMax();
  double GetSimCoreFitnessMaxNorm();
  int GetSimCoreDifferentionMin();
  int GetSimCoreFitMaxStepCA();
  int GetSimCoreSameChromosomesCount();
  double GetSimCoreSameChromosomesGenerationAvarage();

  struct stThreadCoreDataGA *GetSimCoreDataStruct();

  // get error flag
  int GetErrorFlag();


  // print CConfigCore debug informations
  void ShowDebugConfigCore();

signals:
  void SignalThreadCoreErr(int);
  void SignalThreadCoreState(int);
  void SignalNewDataAvailable();

private slots:
  void ThreadCoreErrorSlot(int err);
  void ThreadCoreCheckCoreInitDone();
  void ThreadCoreNewDataAvailable();

  void ThreadCoreState(int s);

private:
  CConfigCore  configCore;            //!< config class

  bool bCoreDataExpired;              //!< are data from this class already displayed in gui?
  bool bSimRunning;                   //!< should be evolution running?

  bool bInitDone;                     //!< is init done?

  CSpace  *space;                     //!< pointer to ca space class
  CGenome *genome;                    //!< pointer to genome class

  struct stThreadCoreDataGA dataGa;   //!< ga data struct used for propagating data from thread core into gui

  QMutex mutexCore;                   //!< mutex used for sync gui thread (in which this class runs) with CThreadCore thread
  QWaitCondition waitCCore;           //!< wait cond used for sync gui thread (in which this class runs) with CThreadCore thread

  CThreadCore *threadCore;            //!< pointer to instance of thread core class

  int iErrFlag;                       //!< error flag
};

//==============================================================

#endif // CORE_H

//==============================================================

