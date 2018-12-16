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

#ifndef THREADCORE_H
#define THREADCORE_H

//==============================================================

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <iostream>
#include <string>
#include <vector>

#include "ConfigCore.h"
#include "ga/GeneticAlgorithm.h"
#include "ca/CellularAutomata.h"

#include "ExportGA.h"
#include "ExportCA.h"
#include "ImportGA.h"

#include "ExportLog.h"

//==============================================================

#define THREAD_CORE_STORE_GA_DATA_MODE_ACT_INIT         0
#define THREAD_CORE_STORE_GA_DATA_MODE_ACT_SET_GENOME   1
#define THREAD_CORE_STORE_GA_DATA_MODE_ACT_MAX          2
#define THREAD_CORE_STORE_GA_DATA_MODE_ACT_GUI          3
#define THREAD_CORE_STORE_GA_DATA_MODE_MAX_TOT          4
#define THREAD_CORE_STORE_GA_DATA_MODE_MAX_GUI          5
#define THREAD_CORE_STORE_GA_DATA_MODE_TOT_GUI          6

//==============================================================
/**
 *  this struct is used for sending GA data from this compute class
 *  into gui
 */

struct stThreadCoreDataGA
{
  int     iGeneration;                        //!< generation id of send genome
  int     iChromosome;                        //!< id of send genome in population

  int     iFitnessMax;                        //!< maximum fitness
  double  dFitnessMaxNorm;                    //!< normalized max fitness
  int     iDifferentionMin;                   //!< minimum differention
  int     iFitMaxStepCA;                      //!< step of ca with maximum fitness

  int     iAncestorsCount;                    //!< number of ancestors

  int     iSameGenomesCount;                  //!< count of genomes with same fitness
  double  dSameGenomesGenerationAvarage;      //!< avarage generation of "same" genomes
};

//==============================================================
/**
 *  main compute class of evolution
 *  this class is using classes of GA and CA
 */

class CThreadCore : public QThread
{
  Q_OBJECT

public:
  CThreadCore();
  ~CThreadCore();


  // run GA thread
  void run();


  // settings
  void SetConfigCore(CConfigCore *cc);

  void SetCoreSpace(CSpace *cs);
  void SetCoreDataGA(struct stThreadCoreDataGA *tcdga);

  void SetMutex(QMutex *mc);
  void SetWaitCondition(QWaitCondition *wcc);
  void SetCoreDataExpiration(bool *be);
  void SetSimulationRunning(bool *sr);


  // get CA spaces
  CSpace *GetSpace();
  CSpace *GetInitSpace();


  // check if initialization is done
  bool IsInitDone();
  // terminating thread
  void TerminateThreadLoop();
  // check thread loop termination
  bool CheckThreadLoopTermination();
  // terminate ca run
  void TerminateCaRun();
  // check ca run termination
  bool CheckCaRunTermination();


  // get error flag
  int GetErrorFlag();

signals:
  void SignalErrCore(int);
  void SignalInitCoreDone();
  void SignalNewDataAvailable();

  void SignalThreadState(int);

private:
  bool bInitDone;               //!< init done var
  bool bEvoExit;                //!< evolution (thread) termination var
  bool bCaRunTermination;       //!< ca simulator terminated var

  CGeneticAlgorithm *ga;        //!< pointer to instance of main GA class
  CCellularAutomata *ca;        //!< pointer to instance of main CA class

  CConfigCore *pConfigCore;     //!< pointer to config class
  CSpace      *pCoreSpace;      //!< pointer to CCore ca space used for sending data into gui

  CExportGA exportGa;           //!< instance of export ga class
  CExportCA exportCa;           //!< instance of export ca class
  CImportGA importGa;           //!< instance of import genome class

  CExportLog exportLog;         //!< instance of export error log class

  CGenome *bestGenome;          //!< best genome in actual evolution run
  CGenome *bestGenomeTotal;     //!< pointer to total best genome class (best genome of all independet evolution runs)
  CGenome *actGenome;           //!< pointer to actual genome class
  CGenome *importGenome;        //!< pointer to import genome class

  QMutex         *pMutexCore;               //!< pointer to CCore var used for threads sync
  QWaitCondition *pWaitCCore;               //!< pointer to CCore var used for threads sync
  bool           *bCoreDataExpired;         //!< pointer to CCore var defining if data send into CCore are displayed in gui
  bool           *bCoreSimRunning;          //!< pointer to CCore var defining if this thread should start compute

  std::string gol;                          //!< i am not sure .. probably from very early version for GoL genome

  int iErrFlag;                             //!< error flag

  struct stThreadCoreDataGA dataGaAct;      //!< actually used genome
  struct stThreadCoreDataGA dataGaMax;      //!< best genome of this run
  struct stThreadCoreDataGA dataGaTot;      //!< ga data of total best genome (best genome of all independent runs)
  struct stThreadCoreDataGA *dataGaToGui;   //!< pointer to data struct from which data to gui will be send
  struct stThreadCoreDataGA *pCoreDataGa;   //!< pointer to CCore ga data struct

  QString exportFileGa;                     //!< name of ga export file
  QString exportFileCa;                     //!< name of ca export file

  CCellularAutomata               *tmpVecCA;    //!< pointer to CA class
  std::vector<CCellularAutomata*> vecTmpCAs;    //!< vector with cellular automatons
  CConfigCore                     configTmpCAs; //!< config core for tmp CAs

  // initialization
  void InitCore();
  void ReinitCore();

  // init functions
  void InitCoreGeneticAlgorithm();
  void InitCoreCellularAutomata();
  void InitCoreCAMemory();
  void InitExport();
  void InitTmpCAs();
  void ClearTmpCAs();


  // check pointers to CCore's data
  bool CheckCorePointers();


  // propagate CA space from CCore into CA
  void WriteCASpaceFromCoreIntoCA();
  // propagate data into CCore
  void WriteDataCAToCore();
  void WriteDataGAToCore();
  // synchronize data with core
  void SyncDataWithCore();
  void SetCoreDataValidity(bool dve);
  // export and gui
  void RunGuiMode(int call_pos);
  // export ga
  void FileExportGa(int call_pos);
  // export init & input ca
  void FileExportCaInit();
  // export ca steps
  void FileExportCaSteps(CGenome *gen);


  // run ca with chromosome
  void RunGenomeCaSimulation(CGenome *gen);


  // store ga data for gui
  void StoreGenomeDataForGui(int mode);
};

//==============================================================

#endif // THREADCORE_H

//==============================================================

