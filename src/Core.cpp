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

#include "Core.h"

#ifdef __DEBUG__
#include <QDebug>
#endif

//==============================================================
/**
 *  class constructor
 */

CCore::CCore()
{
  bInitDone = false;

  space  = NULL;
  genome = NULL;

  threadCore = NULL;

  bCoreDataExpired = true;
  bSimRunning      = false;

  iErrFlag = CORE_OK;

  // init ga data struct - data from this struct are send into gui
  dataGa.iGeneration        = -1;
  dataGa.iChromosome        = -1;
  dataGa.iFitnessMax        = -1;
  dataGa.dFitnessMaxNorm    = -1;
  dataGa.iDifferentionMin   = -1;
  dataGa.iFitMaxStepCA      = -1;
  dataGa.iAncestorsCount    = -1;
  dataGa.iSameGenomesCount              = -1;
  dataGa.dSameGenomesGenerationAvarage  = -1;
}

//==============================================================
/**
 *  class destructor
 */

CCore::~CCore()
{
  // kill core thread
  if(threadCore != NULL)
  {
    if(threadCore->isRunning())
    {
      threadCore->TerminateThreadLoop();
      waitCCore.wakeAll();
      threadCore->wait();
    }
    delete threadCore;
  }
  if(space != NULL)
    delete space;
  if(genome != NULL)
    delete genome;
}

//==============================================================
//==============================================================
/**
 *  inits CCore and core thread CThreadCore
 *  propagates dat from this class into CThreadCore
 *  data from gui are propagated to this class from gui functions
 */

void CCore::InitGuiCore()
{
  // create ca space, which is used by CThreadCore for sending
  // actually computed data from ca into gui
  // gui reads this space and displays it
  space = new CSpace(configCore.GetSpaceType(),
                     configCore.GetSpaceSizeX(),
                     configCore.GetSpaceSizeY(),
                     configCore.GetDefaultState());

  if(space == NULL)
  {
    std::cerr << "ERROR: " << "Class: CCore\n";
    std::cerr << " Unable to allocate Space";

    iErrFlag = CORE_ERR_MEM_FAIL;
    return;
  }

  if(space->GetErrorFlag() == SPACE_OK)
    bInitDone = true;
  else
  {
    iErrFlag = CORE_ERR_UNKNOWN;
    bInitDone = false;

    delete space;
    space = NULL;
  }

#ifdef __DEBUG_SHOW_SETTINGS__
  ShowDebugConfigCore();
#endif

  // create instance of CThreadCore - computation part of app
  threadCore = new CThreadCore();
  if(threadCore == NULL)
  {
    delete space;
    space = NULL;

    iErrFlag = CORE_ERR_MEM_FAIL;
    bInitDone = false;
  }
  else
  {
    // propagate pointers to core, which are needed for sending data to gui
    // and sync gui threads with compute thread
    threadCore->SetConfigCore(&configCore);

    threadCore->SetCoreSpace(space);
    threadCore->SetCoreDataGA(&dataGa);

    threadCore->SetMutex(&mutexCore);
    threadCore->SetWaitCondition(&waitCCore);
    threadCore->SetCoreDataExpiration(&bCoreDataExpired);
    threadCore->SetSimulationRunning(&bSimRunning);

    bInitDone = true;

    connect(threadCore, SIGNAL(SignalErrCore(int)),       this, SLOT(ThreadCoreErrorSlot(int)));
    connect(threadCore, SIGNAL(SignalInitCoreDone()),     this, SLOT(ThreadCoreCheckCoreInitDone()));
    connect(threadCore, SIGNAL(SignalNewDataAvailable()), this, SLOT(ThreadCoreNewDataAvailable()));
    connect(threadCore, SIGNAL(SignalThreadState(int)),   this, SLOT(ThreadCoreState(int)));
  }
}

//==============================================================
//==============================================================
/**
 *  sets state var, which tells core, that data from this class
 *  was already displayed in gui, so new data can be propagete to this class
 *
 *  @param e            are core's data expered? (already showed in gui)
 */

void CCore::SetCoreDataExpiration(bool e)
{
  mutexCore.lock();
  {
    bCoreDataExpired = e;

    waitCCore.wakeAll();
  }
  mutexCore.unlock();
}

//==============================================================
/**
 *  sets state var which tells core, that user pressed button "Evolve"
 *  so evolution can start
 *
 *  @param sr           set ThreadCore thread running state
 */

void CCore::SetSimulationRunning(bool sr)
{
  mutexCore.lock();
  {
    bSimRunning = sr;

    waitCCore.wakeAll();
  }
  mutexCore.unlock();
}

//==============================================================
/**
 *  sets state var shich tells core, that user pressed button "Terminate"
 *  for terminating ca simulator
 */

void CCore::SetCaRunTermination()
{
  mutexCore.lock();
  {
    if(threadCore != NULL)
      threadCore->TerminateCaRun();

    waitCCore.wakeAll();
  }
  mutexCore.unlock();
}

//==============================================================
//==============================================================
/**
 *  starts CThreadCore thread, just init part is compute, then
 *  thread waits for "Evolve" button to be pressed
 */

void CCore::StartThreadCore()
{
  if(threadCore != NULL)
    threadCore->start();
}

//==============================================================
//==============================================================
/**
 *  returns if init is done and ok
 */

bool CCore::IsInitDone()
{
  return bInitDone;
}

//==============================================================
//==============================================================
/**
 *  propagates error from core thread into gui
 *
 *  @param err          error code from signal from core thread
 */

void CCore::ThreadCoreErrorSlot(int err)
{
  emit(SignalThreadCoreErr(err));
}

//==============================================================
/**
 *  propagates info about thread core init done into gui
 */

void CCore::ThreadCoreCheckCoreInitDone()
{
  emit(SignalThreadCoreState(THREAD_CORE_SIGNAL_INIT_DONE));
}

//==============================================================
/**
 *  tells gui, that new data from thread core are in this class
 */

void CCore::ThreadCoreNewDataAvailable()
{
  emit(SignalNewDataAvailable());
}

//==============================================================
/**
 *  propagates state of thread core into gui
 *
 *  @param s            core thread state
 */

void CCore::ThreadCoreState(int s)
{
  emit(SignalThreadCoreState(s));
}

//==============================================================
//==============================================================
/**
 * return pointer to config class
 */

CConfigCore* CCore::GetConfigCore()
{
  return &configCore;
}

//==============================================================
/**
 *  returns pointer to ca space class
 */

CSpace* CCore::GetSpace()
{
  return space;
}

//==============================================================
//==============================================================
/**
 *  returns pointer to ga data struct
 */

struct stThreadCoreDataGA* CCore::GetSimCoreDataStruct()
{
  return &dataGa;
}

//==============================================================
/**
 *  return ga data - genome's generation id
 */

int CCore::GetSimCoreGenerationID()
{
  return dataGa.iGeneration;
}

//==============================================================
/**
 *  return ga data - genome's id
 */

int CCore::GetSimCoreChromosomeID()
{
  return dataGa.iChromosome;
}

//==============================================================
/**
 *  return ga data - genome's ancestor count
 */

int CCore::GetSimCoreAncestorsCount()
{
  return dataGa.iAncestorsCount;
}

//==============================================================
/**
 *  return ga data - genome's maximum fitness
 */

int CCore::GetSimCoreFitnessMax()
{
  return dataGa.iFitnessMax;
}

//==============================================================
/**
 *  return ga data - genome's maximum fitness
 */

double CCore::GetSimCoreFitnessMaxNorm()
{
  return dataGa.dFitnessMaxNorm;
}

//==============================================================
/**
 *  return ga data - genome's minimum differention
 */

int CCore::GetSimCoreDifferentionMin()
{
  return dataGa.iDifferentionMin;
}

//==============================================================
/**
 *  return ga data - ca step with max fitness
 */

int CCore::GetSimCoreFitMaxStepCA()
{
  return dataGa.iFitMaxStepCA;
}

//==============================================================
/**
 *  return ga data - count of genomes with same fitness
 */

int CCore::GetSimCoreSameChromosomesCount()
{
  return dataGa.iSameGenomesCount;
}

//==============================================================
/**
 *  return ga data - avarage generation of "same" genomes
 */

double CCore::GetSimCoreSameChromosomesGenerationAvarage()
{
  return dataGa.dSameGenomesGenerationAvarage;
}

//==============================================================
//==============================================================
/**
 *  returns erro flag
 */

int CCore::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================
/**
 *  debug INFO
 */

void CCore::ShowDebugConfigCore()
{
#ifdef __DEBUG__

  switch(configCore.GetSpaceType())
  {
  case SPACE_TYPE_GRID:
    qDebug() << "GetSpaceType" << "\t= " << "SPACE_TYPE_GRID";
    break;

  case SPACE_TYPE_TORUS:
    qDebug() << "GetSpaceType" << "\t= " << "SPACE_TYPE_TORUS";
    break;

  default:
    qDebug() << "GetSpaceType" << "\t= " << "other = " << configCore.GetSpaceType();
  }

  qDebug() << "GetSpaceSizeX"  << "\t= " << configCore.GetSpaceSizeX();
  qDebug() << "GetSpaceSizeY"  << "\t= " << configCore.GetSpaceSizeY();

  qDebug() << "";

  qDebug() << "GetStatesCount" << "\t= "   << configCore.GetStatesCount();

  switch(configCore.GetDefaultState())
  {
    case CELL_STATE_EMPTY:
      qDebug() << "GetDefaultState" << "\t= " << "CELL_STATE_EMPTY";
      break;

    case CELL_STATE_LIVE_1:
      qDebug() << "GetDefaultState" << "\t= " << "CELL_STATE_LIVE_1";
      break;

    case CELL_STATE_LIVE_2:
      qDebug() << "GetDefaultState" << "\t= " << "CELL_STATE_LIVE_2";
      break;

    case CELL_STATE_LIVE_3:
      qDebug() << "GetDefaultState" << "\t= " << "CELL_STATE_LIVE_3";
      break;

    case CELL_STATE_ERR:
      qDebug() << "GetDefaultState" << "\t= " << "CELL_STATE_ERR";
      break;

    default:
      qDebug() << "GetDefaultState" << "\t= " << "other = " << configCore.GetDefaultState();
  }

  qDebug() << "";

  qDebug() << "GetRepetitionsCount"    << "\t= " << configCore.GetEvolutionRepetitionsCount();
  qDebug() << "GetGenerationsCount"    << "\t= " << configCore.GetGenerationsCount();
  qDebug() << "GetPopulationSize"      << "\t= " << configCore.GetPopulationSize();

  switch(configCore.GetGenomeType())
  {
    case GENOME_TYPE_2_9N:
      qDebug() << "GetGenomeType" << "\t= " << "GENOME_TYPE_2_9N";
      break;

    case GENOME_TYPE_3_9N:
      qDebug() << "GetGenomeType" << "\t= " << "GENOME_TYPE_3_9N";
      break;

    case GENOME_TYPE_4_9N:
      qDebug() << "GetGenomeType" << "\t= " << "GENOME_TYPE_4_9N";
      break;

    case GENOME_TYPE_2_5N:
      qDebug() << "GetGenomeType" << "\t= " << "GENOME_TYPE_2_5N";
      break;

    case GENOME_TYPE_3_5N:
      qDebug() << "GetGenomeType" << "\t= " << "GENOME_TYPE_3_5N";
      break;

    case GENOME_TYPE_4_5N:
      qDebug() << "GetGenomeType" << "\t= " << "GENOME_TYPE_4_5N";
      break;

    default:
      qDebug() << "GetGenomeType" << "\t= " << configCore.GetGenomeType();
  }

  qDebug() << "";

  qDebug() << "GetCrossoverProbability" << "\t= " << configCore.GetCrossoverProbability();
  qDebug() << "GetCrossoverCount"       << "\t= " << configCore.GetCrossoverCount();

  qDebug() << "";

  qDebug() << "GetMutationProbability" << "\t= " << configCore.GetMutationProbability();
  qDebug() << "GetMutationCount"       << "\t= " << configCore.GetMutationCount();

  qDebug() << "";

  switch(configCore.GetMoveDirection())
  {
    case MOVE_DIR_ANY:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_ANY (any)";
      break;

    case MOVE_DIR_N:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_N (up)";
      break;

    case MOVE_DIR_NW:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_NW (up left)";
      break;

    case MOVE_DIR_W:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_W (left)";
      break;

    case MOVE_DIR_SW:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_SW (down left)";
      break;

    case MOVE_DIR_S:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_S (down)";
      break;

    case MOVE_DIR_SE:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_SE (down right)";
      break;

    case MOVE_DIR_E:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_E (right)";
      break;

    case MOVE_DIR_NE:
      qDebug() << "GetMoveDirection" << "\t= " << "MOVE_DIR_NE (up right)";
      break;

    default:
      qDebug() << "GetMoveDirection" << "\t= " << "other = " << configCore.GetMoveDirection();
  }

  qDebug() << "GetStepsCountCA" << "\t= " << configCore.GetStepsCountCA();
  qDebug() << "GetMoveDistance" << "\t= " << configCore.GetMoveDistance();

  qDebug() << "";

#endif

}

//==============================================================
//==============================================================

