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

#ifndef CONFIGCORE_H
#define CONFIGCORE_H

//==============================================================

#include <string>

#include "ExportLog.h"
#include "Defines.h"

//==============================================================
/**
 *
 */

class CConfigCore
{
public:
  CConfigCore();


  // ca space type settings
  void SetSpaceType(int st);
  int  GetSpaceType();


  // ca space dimensions settings
  void SetSpaceSizeX(int x);
  int  GetSpaceSizeX();
  void SetSpaceSizeY(int y);
  int  GetSpaceSizeY();


  // ca states settings
  void SetStatesCount(int sc);
  int  GetStatesCount();

  void SetDefaultState(int ds);
  BYTE GetDefaultState();


  // evolution run settings
  void SetEvolutionRepetitionsCount(int rc);
  int  GetEvolutionRepetitionsCount();

  void SetGenerationsCount(int gc);
  int  GetGenerationsCount();

  void SetPopulationSize(int ips);
  int  GetPopulationSize();


  // movement settings
  void SetMoveDirection(int md);
  int  GetMoveDirection();

  void SetStepsCountCA(int sc);
  int  GetStepsCountCA();

  void SetMoveDistance(int md);
  int  GetMoveDistance();


  // crossover settings
  void SetCrossoverProbability(int cp);
  int  GetCrossoverProbability();

  void SetCrossoverCount(int cc);
  int  GetCrossoverCount();


  // mutation settings
  void SetMutationProbability(int mp);
  int  GetMutationProbability();

  void SetMutationCount(int mc);
  int  GetMutationCount();


  // genome type
  void SetGenomeType(int gt);
  int  GetGenomeType();


  // gui data display mode
  void SetGuiDisplayModeCA(int dm);
  int  GetGuiDisplayModeCA();

  void SetGuiDisplayModeCATimeout(int to);
  int  GetGuiDisplayModeCATimeout();


  // export ca, ga settings
  void        SetExportFilePath(std::string path);
  std::string GetExportFilePath();

  void SetExportFileModeCa(int mode);
  int  GetExportFileModeCa();

  void SetExportFileModeGa(int mode);
  int  GetExportFileModeGa();


  // import genome settings
  void        SetImportGenomeFile(std::string file);
  std::string GetImportGenomeFile();

  void        SetImportGenomeEnabledSimulation(bool e);
  bool        IsImportGenomeEnabledSimulation();

  void        SetImportGenomeEnabledReevolve(bool e);
  bool        IsImportGenomeEnabledReevolve();


  // log file settings
  void        SetExportLogCore(CExportLog *ex);
  CExportLog *GetExportLogCore();

private:
  unsigned int iSpaceType;                //!< ca space type - lattice or torus
  unsigned int iSizeRunArrayX;            //!< ca space width
  unsigned int iSizeRunArrayY;            //!< ca space height
  unsigned int iStatesCount;              //!< number of states in ca
  BYTE         byDefCellState;            //!< default cell state

  unsigned int iRepetitions;              //!< number of independet runs of evolution
  unsigned int iGenCount;                 //!< generations count
  unsigned int iPopulationSize;           //!< population size

  unsigned int iMoveDir;                  //!< direction of movement
  unsigned int iStepsCountCA;             //!< steps needed to move at distance
  unsigned int iDistance;                 //!< distance of movement

  unsigned int iCrossoverProb;            //!< crossover probability
  unsigned int iCrossoverCount;           //!< number of crossovers

  unsigned int iMutProb;                  //!< mutation probability
  unsigned int iMutCount;                 //!< number of genes which should be mutated

  unsigned int iGenomeType;               //!< genome type: 9-neighborhood + 2 states, etc.

  unsigned int iGuiDisplayModeCa;         //!< gui diaplay mode
  unsigned int iGuiDisplayModeCaTimeout;  //!< gui ca animation timeout (between two steps of ca in "Run" mode)

  std::string sgExportFilePath;           //!< path for files for exported

  int iExportFileModeCa;                  //!< mode for exporting ca spaces
  int iExportFileModeGa;                  //!< mode for exporting ga genomes

  std::string sgImportFileGenome;         //!< imported genome file path/name
  bool bImportFileEnabledSimulation;      //!< use imported genome just for ca simulation running
  bool bImportFileEnabledReevolve;        //!< re-evolve imported genome

  CExportLog *pExportLogCore;             //!< pointer to instance of export log file class created in CThreadCore
};

//==============================================================

#endif // CONFIGCORE_H

//==============================================================

