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

#include "ThreadCore.h"

//==============================================================
/**
 *  class constructor
 */

CThreadCore::CThreadCore()
{
  bInitDone = false;
  bEvoExit  = false;
  bCaRunTermination = false;

  ga = NULL;
  ca = NULL;

  pConfigCore = NULL;
  pCoreSpace  = NULL;

  pMutexCore = NULL;
  pWaitCCore = NULL;
  bCoreDataExpired = NULL;
  bCoreSimRunning  = NULL;

  iErrFlag = THREAD_CORE_OK;

  pCoreDataGa = NULL;

  bestGenome      = NULL;
  bestGenomeTotal = NULL;
  actGenome       = NULL;
  importGenome    = NULL;

  vecTmpCAs.clear();
}

//==============================================================
/**
 *  class destructor
 */

CThreadCore::~CThreadCore()
{
  TerminateThreadLoop();

  if(ga != NULL)
    delete ga;
  if(ca != NULL)
    delete ca;

  if(bestGenome != NULL)
    delete bestGenome;
  if(bestGenomeTotal != NULL)
    delete bestGenomeTotal;
  if(importGenome != NULL)
    delete importGenome;

  ClearTmpCAs();
}

//==============================================================
//==============================================================
/**
 *  main compute function, runs in own thread
 *  1st of all, init part of thread is done
 *  if any error occurs, this error is send into gui and thread
 *  is then abord
 *  after successful init thread wait to "Evolve" button in gui is pressed
 *  then evolution will begin
 */

void CThreadCore::run()
{
  //============================================================
  // init dynamic allocated data structs, copy data from CCore class
  InitCore();
  // check if init is done
  if((!bInitDone) || (iErrFlag != THREAD_CORE_OK))
  {
    if(iErrFlag == THREAD_CORE_ERR_IMPORT_FAILED)
      emit(SignalErrCore(THREAD_CORE_SIGNAL_ERR_IMPORT_FAILED));
    else
      emit(SignalErrCore(THREAD_CORE_SIGNAL_ERR_INIT_THREAD));
    return;
  }

  // is genome import enabled?
  if(pConfigCore->IsImportGenomeEnabledSimulation())
  {
    // export steps of ca
    if(pConfigCore->GetExportFileModeCa() == FILE_EX__CA_MODE__IMPORT_SPACE)
    {
      //pConfigCore->SetStepsCountCA(importGenome->GetFitnessMaxStepCA());

      exportFileCa  = pConfigCore->GetExportFilePath().c_str();
      exportFileCa += "/ca_import";

      FileExportCaSteps(importGenome);
    }

    // run imported genome in ca simulator
    RunGuiMode(7);

    // emit signal that comutation is done
    emit(SignalThreadState(THREAD_CORE_SIGNAL_SIM_DONE));

    return;
  }


  // export ca init and input spaces
  FileExportCaInit();


  //============================================================
  // set display mode
  // init data structs for evolution
  StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_INIT);
  StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_MAX);
  StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_MAX_TOT);

  // max to gui
  if((pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__RUN_E__BEST_CHROM__E_STEP) ||
     (pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__RUN_A__BEST_CHROM__E_STEP))
    StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_MAX_GUI);
  // total to gui
  else if(pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP)
    StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_TOT_GUI);
  // act to gui
  else
    StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_GUI);


  //============================================================
  // export file settings
  QString exportPath     = pConfigCore->GetExportFilePath().c_str();
  QString export_evo_run = "_run_0000";

  exportPath   += "/";

  exportFileGa  = exportPath;
  exportFileCa  = exportPath;
  // .ebg = Evodemo Best Genome
  exportFileGa += "ga_ex_total_best.ebg";
  exportFileCa += "ca_ex_total_best";


  bool bSameGenomeMaxNextFound  = false;
  int  iSameGenomeMaxLastEvoRun = 0;



  //============================================================
  // initialization part of core thread is now done - inform gui
  emit(SignalInitCoreDone());


  // wait while "Evolve" button in gui is pressed
  pMutexCore->lock();
  {
    if(!*bCoreSimRunning)
      pWaitCCore->wait(pMutexCore);
  }
  pMutexCore->unlock();


  //============================
  // simulation was canceled
  if(bEvoExit)
    return;



  //============================================================
  // repeat for m repetitions
  for(int evo_run = 0; evo_run < pConfigCore->GetEvolutionRepetitionsCount(); evo_run++)
  {
    //==========================
    // simulation was canceled
    if(bEvoExit)
      return;


    // init data structs for evolution
    StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_INIT);
    StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_MAX);


    // reinit ga
    if(evo_run > 0)
    {
      ReinitCore();
      // check if init is done
      if((!bInitDone) || (iErrFlag != THREAD_CORE_OK))
      {
        emit(SignalErrCore(THREAD_CORE_SIGNAL_ERR_INIT_THREAD));
        return;
      }
    }


    //==========================================================
    // export file settings
    //if(pConfigCore->GetExportFileModeGa() != FILE_EX__GA_MODE_NONE)
    {
      if(evo_run < 10)
        export_evo_run = "_run_000";
      else if(evo_run < 100)
        export_evo_run = "_run_00";
      else if(evo_run < 1000)
        export_evo_run = "_run_0";
      else
        export_evo_run = "_run_";

      export_evo_run += QString("%1").arg(evo_run);
    }
    if(pConfigCore->GetExportFileModeGa() == FILE_EX__GA_MODE__RUN_E__CHROM_B)
    {
      exportFileGa  = exportPath;
      exportFileGa += "export_best_ga";
      exportFileGa += export_evo_run;
      // .ebg = Evodemo Best Genome
      exportFileGa += ".ebg";
    }
    if(pConfigCore->GetExportFileModeCa() == FILE_EX__CA_MODE__RUN_E__CHROM_B__STEP_E)
    {
      exportFileCa  = exportPath;
      exportFileCa += "ca_ex_best";
      exportFileCa += export_evo_run;
    }


    //==========================================================
    // calculate for n generations
    for(int gen = 0; gen < pConfigCore->GetGenerationsCount(); gen++)
    {
      //==========================
      // simulation was canceled
      if(bEvoExit)
        return;


      //========================================================
      // export file settings
      if(pConfigCore->GetExportFileModeGa() == FILE_EX__GA_MODE__RUN_E__CHROM_A)
      {
        exportFileGa  = exportPath;
        exportFileGa += "export_ga";
        exportFileGa += export_evo_run;

        if(gen < 10)
          exportFileGa += "_gen_000";
        else if(gen < 100)
          exportFileGa += "_gen_00";
        else if(gen < 1000)
          exportFileGa += "_gen_0";
        else
          exportFileGa += "_gen_";

        exportFileGa += QString("%1").arg(gen);
        // .ewg = Evodemo Whole Generation
        exportFileGa += ".ewg";
      }


      //========================================================
      // perform ca calculations with every chromosome in population
      for(int chrom = 0; chrom < ga->GetActualPopulationSize(); chrom++)
      {
        //========================
        // simulation was canceled
        if(bEvoExit)
          return;


        // check if genome exists
        if(!ga->ExistsGenomeId(chrom))
          continue;


        // get actual genome
        actGenome = ga->GetGenome(chrom);


        // set genome into cellular automaton
        ca->GetRulesTable()->SetGenome(actGenome);


        bSameGenomeMaxNextFound = false;

        //======================================================
        // perform ca calculations
        for(int step = 0; step < (pConfigCore->GetStepsCountCA() * 2); step++)
        {
          //======================
          // simulation was canceled
          //if(bEvoExit)
          //  return;


          // do one step with ca
          ca->Step();


          // calculate fitness
          ga->Fitness(actGenome, ca->GetInitSpace(), ca->GetSpace(), ca->GetStepsDone());

          // check for errors
          if(ga->GetErrorFlag() != GA_OK)
          {
          }
          else
          {
            // find best chromosome from whole population
            if(actGenome->GetFitnessMax() > dataGaMax.iFitnessMax)
            {
              // backup data of act chromosome
              StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_SET_GENOME);
              StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_MAX);


              if(bestGenome != NULL)
              {
                delete bestGenome;
                bestGenome = NULL;
              }

              // backup best chromosome
              bestGenome = new CGenome(*actGenome,
                                       GENOME_CONSTRUCT_COPY_MODE_DEEP,
                                       pConfigCore);
              if(bestGenome == NULL)
              {
                {
                  std::string msgErr  = "Class:    CThreadCore\n";
                  msgErr += "Function: run()\n";
                  msgErr += "Memory allocation for CGenome failed";

                  if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
                    pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
                  else
                    std::cerr << "ERROR: " << msgErr;
                }
              }


              // check if current top chromosome ist'n best in all runs
              if(dataGaMax.iFitnessMax > dataGaTot.iFitnessMax)
              {
                // backup data of act max chromosome
                StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_MAX_TOT);

                if(bestGenomeTotal != NULL)
                {
                  delete bestGenomeTotal;
                  bestGenomeTotal = NULL;
                }

                // back new total best chromosome
                bestGenomeTotal = new CGenome(*bestGenome,
                                              GENOME_CONSTRUCT_COPY_MODE_DEEP,
                                              pConfigCore);
                if(bestGenomeTotal == NULL)
                {
                  {
                    std::string msgErr  = "Class:    CThreadCore\n";
                    msgErr += "Function: run()\n";
                    msgErr += "Memory allocation for CGenome failed";

                    if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
                      pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
                    else
                      std::cerr << "ERROR: " << msgErr;
                  }
                }
              }
            }
            if(actGenome->GetFitnessMax() == dataGaTot.iFitnessMax)
            {
              if(iSameGenomeMaxLastEvoRun != evo_run)
              {
                bSameGenomeMaxNextFound  = true;
                iSameGenomeMaxLastEvoRun = evo_run;
              }
            }
          }

        } // END LOOP - step


        if(bSameGenomeMaxNextFound)
        {
          double tmp = 0;

          dataGaTot.iSameGenomesCount += 1;

          tmp  = dataGaTot.dSameGenomesGenerationAvarage;
          tmp  = tmp * (dataGaTot.iSameGenomesCount - 1);
          tmp += actGenome->GetThisGenerationId();
          tmp /= dataGaTot.iSameGenomesCount;

          dataGaTot.dSameGenomesGenerationAvarage   = tmp;

          /*
          tmp  = dataGaTot.iSameGenomesMutatedGenesAvarage;
          tmp  = tmp * (dataGaTot.iSameGenomesCount - 1);
          tmp += actGenome->GetMutatedGenesAllAncestors();
          tmp /= dataGaTot.iSameGenomesCount;

          dataGaTot.iSameGenomesMutatedGenesAvarage = tmp;
          */
        }


        // calculations with actual chromosome is done, reinit ca
        ca->ReInit();

      } // END LOOP - chrom


      // export actual generation of chromosomes
      FileExportGa(0);


      //========================================================
      // create new population
      ga->CreateNextGeneration(gen + 1);

    } // END LOOP - gen


    // export best ga solution from population
    FileExportGa(1);
    // export ca steps
    if(pConfigCore->GetExportFileModeCa() == FILE_EX__CA_MODE__RUN_E__CHROM_B__STEP_E)
      FileExportCaSteps(bestGenome);

    // run best solution in ca simulator
    RunGuiMode(5);


  } // END LOOP - evo_run


  StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_TOT_GUI);

  // export total best ga
  FileExportGa(2);
  // export ca steps with total best genome
  if(pConfigCore->GetExportFileModeCa() == FILE_EX__CA_MODE__RUN_B__CHROM_B__STEP_E)
    FileExportCaSteps(bestGenomeTotal);

  // run total best solution in ca simulator
  RunGuiMode(6);


  // emit signal that comutation is done
  emit(SignalThreadState(THREAD_CORE_SIGNAL_SIM_DONE));
}

//==============================================================
//==============================================================
/**
 *  this function inits thread core
 *  init must be done before evolution starts
 */

void CThreadCore::InitCore()
{
  // check if all pointers are set up
  if(!CheckCorePointers())
  {
    iErrFlag  = THREAD_CORE_ERR_POINTERS;
    bInitDone = false;
    return;
  }

  iErrFlag = THREAD_CORE_OK;


  //====================================
  // init compute parts of core thread
  InitCoreGeneticAlgorithm();
  if(!bInitDone)
  {
    iErrFlag = THREAD_CORE_ERR_INIT_GA;
    return;
  }

  InitCoreCellularAutomata();
  if(!bInitDone)
  {
    iErrFlag = THREAD_CORE_ERR_INIT_CA;
    return;
  }

  InitCoreCAMemory();
  if(!bInitDone)
  {
    iErrFlag = THREAD_CORE_ERR_INIT_CA_M;
    return;
  }

  InitExport();

  iErrFlag = THREAD_CORE_OK;


  //====================================
  // check dynamic allocated data structs
  if((!bInitDone) || (iErrFlag != THREAD_CORE_OK))
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: InitCore()\n";
      msgErr += "Unknown error occured";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return;
  }
  if((ga == NULL) || (ca == NULL))
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: InitCore()\n";
      msgErr += "Pointer to CGeneticAlgorithm or CCellularAutomata is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = THREAD_CORE_ERR_MEM_FAIL;
    return;
  }


  //====================================
  // gui space into ca
  WriteCASpaceFromCoreIntoCA();

  // find corners of given input space
  ga->IdentifyCorners(ca->GetInitSpace());

  // check if corner identification is done
  if(ga->GetErrorFlag() != GA_OK)
  {
    iErrFlag = THREAD_CORE_ERR_SPACE_NO_NON_EMPTY_CELL;
    bInitDone = false;
    return;
  }


  //====================================
  // import genome from file for simulation purpose
  if(pConfigCore->IsImportGenomeEnabledSimulation())
  {
    importGenome = new CGenome(pConfigCore->GetGenomeType(),0,0,pConfigCore);
    if(importGenome == NULL)
    {
      {
        std::string msgErr  = "Class:    CThreadCore\n";
        msgErr += "Function: InitCore()\n";
        msgErr += "Memory allocation for CGenome class failed";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }

      iErrFlag = THREAD_CORE_ERR_IMPORT_FAILED;
      return;
    }
    // load genome from file given in gui
    importGa.ImportChromosome(pConfigCore->GetImportGenomeFile().c_str(),importGenome);
    if(importGa.GetErrorFlag() != IMPORT_GA_OK)
    {
      iErrFlag = THREAD_CORE_ERR_IMPORT_FAILED;
      return;
    }
    //ga->ImportGenomeToPopulation(importGenome);
  }
  // import genome from file for reevolve purpose
  else if(pConfigCore->IsImportGenomeEnabledReevolve())
  {
    importGenome = new CGenome(pConfigCore->GetGenomeType(),0,0,pConfigCore);
    if(importGenome == NULL)
    {
      {
        std::string msgErr  = "Class:    CThreadCore\n";
        msgErr += "Function: InitCore()\n";
        msgErr += "Memory allocation for CGenome class failed";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }

      iErrFlag = THREAD_CORE_ERR_IMPORT_FAILED;
      return;
    }
    // load genome from file given in gui
    importGa.ImportChromosome(pConfigCore->GetImportGenomeFile().c_str(),importGenome);
    if(importGa.GetErrorFlag() != IMPORT_GA_OK)
    {
      iErrFlag = THREAD_CORE_ERR_IMPORT_FAILED;
      return;
    }
    ga->InitGenotypeReevolve(importGenome);
  }
  // genotype initialization
  //if(!pConfigCore->IsImportGenomeEnabledSimulation() && !pConfigCore->IsImportGenomeEnabledReevolve())
  else
  {
    // init genotype
    ga->InitGenotype();
  }

  // check if init is done
  if(ga->GetErrorFlag() != GA_OK)
  {
    iErrFlag = THREAD_CORE_ERR_CORE_GA;
    bInitDone = false;
    return;
  }
  else
  {
    iErrFlag = THREAD_CORE_OK;
    bInitDone = true;
  }
}

//==============================================================
/**
 *  reinits thread - used when evolution repetition occurs
 *  evolution repetitions = independet runs of evolution
 *  GA needs to be reinit
 */

void CThreadCore::ReinitCore()
{
  // check if all pointers are set up
  if(!CheckCorePointers())
  {
    iErrFlag  = THREAD_CORE_ERR_POINTERS;
    bInitDone = false;
    return;
  }

  iErrFlag = THREAD_CORE_OK;


  //====================================
  // init compute parts of core thread
  InitCoreGeneticAlgorithm();
  if(!bInitDone)
  {
    iErrFlag = THREAD_CORE_ERR_INIT_GA;
    return;
  }


  //====================================
  // reinit ca space
  ca->ReInit();


  //====================================
  // import genome from file for reevolve purpose
  if(pConfigCore->IsImportGenomeEnabledReevolve())
    ga->InitGenotypeReevolve(importGenome);
  // genotype initialization
  else
    ga->InitGenotype();


  // check if init is done
  if(ga->GetErrorFlag() != GA_OK)
  {
    iErrFlag = THREAD_CORE_ERR_CORE_GA;
    bInitDone = false;
    return;
  }
  else
  {
    iErrFlag = THREAD_CORE_OK;
    bInitDone = true;
  }
}

//==============================================================
/**
 *  creates new GA instance used in evolution
 */

void CThreadCore::InitCoreGeneticAlgorithm()
{
  if(!CheckCorePointers())
  {
    iErrFlag = THREAD_CORE_ERR_POINTERS;
    bInitDone = false;
    return;
  }

  if(ga != NULL)
    delete ga;

  // create new GA instance
  ga = new CGeneticAlgorithm(pConfigCore);
  if(ga == NULL)
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: InitCoreGeneticAlgorithm()\n";
      msgErr += "Memory allocation for CGeneticAlgorithm failed";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = THREAD_CORE_ERR_MEM_FAIL;
    bInitDone = false;
  }
  else
  {
    bInitDone = true;
  }
}

//==============================================================
/**
 *  creates instance of CA used in evolution
 */

void CThreadCore::InitCoreCellularAutomata()
{
  if(!CheckCorePointers())
  {
    iErrFlag = THREAD_CORE_ERR_POINTERS;
    bInitDone = false;
    return;
  }

  if(ca != NULL)
    delete ca;

  // create new instance of ca
  ca = new CCellularAutomata(pConfigCore);
  if(ca == NULL)
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: InitCoreCellularAutomata()\n";
      msgErr += "Memory allocation for CCellularAutomata failed";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = THREAD_CORE_ERR_MEM_FAIL;
    bInitDone = false;
  }
  else
  {
    bInitDone = true;
  }
}

//==============================================================
/**
 *  inits ca classes
 */

void CThreadCore::InitCoreCAMemory()
{
  if(!CheckCorePointers())
  {
    iErrFlag = THREAD_CORE_ERR_POINTERS;
    bInitDone = false;
    return;
  }
  if(ca == NULL)
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: InitCoreCAMemory()\n";
      msgErr += "Pointer to CCellularAutomata is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = THREAD_CORE_ERR_POINTERS;
    bInitDone = false;
    return;
  }

  // init ca memory - alloc ca spaces
  ca->InitMemory();
  if(ca->GetErrorFlag() != CA_OK)
  {
    delete ca;
    ca = NULL;

    iErrFlag = THREAD_CORE_ERR_INIT_CA_M;
    bInitDone = false;
    return;
  }
  else
  {
    iErrFlag = THREAD_CORE_OK;
    bInitDone = true;
  }
}

//==============================================================
/**
 *  inits export classes
 */

void CThreadCore::InitExport()
{
  exportGa.SetConfigCore(pConfigCore);
  exportCa.SetConfigCore(pConfigCore);

  importGa.SetConfigCore(pConfigCore);

  exportLog.SetFilePath(pConfigCore->GetExportFilePath().c_str());
  exportLog.SetFileName("log_core.txt");
  exportLog.OpenLogFile();

  pConfigCore->SetExportLogCore(&exportLog);
}

//==============================================================
/**
 *  inits tmp CAs which are used for evolving vseo chromosomes
 */

void CThreadCore::InitTmpCAs()
{
  configTmpCAs.SetSpaceType(pConfigCore->GetSpaceType());
  configTmpCAs.SetSpaceSizeX(5);
  configTmpCAs.SetSpaceSizeY(5);
  configTmpCAs.SetStatesCount(pConfigCore->GetStatesCount());
  configTmpCAs.SetDefaultState(pConfigCore->GetDefaultState());
  configTmpCAs.SetEvolutionRepetitionsCount(pConfigCore->GetEvolutionRepetitionsCount());
  configTmpCAs.SetGenerationsCount(pConfigCore->GetGenerationsCount());
  configTmpCAs.SetPopulationSize(pConfigCore->GetPopulationSize());
  configTmpCAs.SetGenomeType(pConfigCore->GetGenomeType());
  configTmpCAs.SetMoveDirection(pConfigCore->GetMoveDirection());
  configTmpCAs.SetStepsCountCA(pConfigCore->GetStepsCountCA());
  configTmpCAs.SetMoveDistance(pConfigCore->GetMoveDistance());
  configTmpCAs.SetCrossoverProbability(pConfigCore->GetCrossoverProbability());
  configTmpCAs.SetCrossoverCount(pConfigCore->GetCrossoverCount());
  configTmpCAs.SetMutationProbability(pConfigCore->GetMutationProbability());
  configTmpCAs.SetMutationCount(pConfigCore->GetMutationCount());
  configTmpCAs.SetExportLogCore(pConfigCore->GetExportLogCore());

  unsigned long rndLow  = 0;
  unsigned long rndHigh = 0;

  switch(configTmpCAs.GetStatesCount())
  {
    case 2:
      rndHigh = 199;
      break;

    case 3:
      rndHigh = 299;
      break;

    case 4:
      rndHigh = 399;
      break;

    default:
      rndHigh = 199;
  }

  CRandom rnd;

  for(int i = 0; i < 10; i++)
  {
    tmpVecCA = new CCellularAutomata(&configTmpCAs);
    if(tmpVecCA == NULL)
    {
      {
        std::string msgErr  = "Class:    CThreadCore\n";
        msgErr += "Function: InitTmpCAs()\n";
        msgErr += "Memory allocation failed";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }

      ClearTmpCAs();
      iErrFlag = THREAD_CORE_ERR_MEM_FAIL;
      return;
    }
    if(tmpVecCA->GetErrorFlag() != CA_OK)
    {
      ClearTmpCAs();
      iErrFlag = THREAD_CORE_ERR_UNKNOWN;
      return;
    }

    for(int y = 1; y <= 3; y++)
      for(int x = 1; x <= 3; x++)
        tmpVecCA->GetInitSpace()->at(x,y) = BYTE(rnd.Uniform(rndLow,rndHigh) / 100);

    vecTmpCAs.push_back(tmpVecCA);
  }

  iErrFlag = THREAD_CORE_OK;
}

//==============================================================
/**
 *  clears tmp CAs which are used for evolving vseo chromosomes
 */

void CThreadCore::ClearTmpCAs()
{
  if(vecTmpCAs.size() > 0)
  {
    for(int i = 0; i < (signed)vecTmpCAs.size(); i++)
    {
      tmpVecCA = vecTmpCAs.at(i);
      if(tmpVecCA != NULL)
      {
        delete tmpVecCA;
        vecTmpCAs.at(i) = NULL;
      }
    }
    vecTmpCAs.clear();
  }
}

//==============================================================
//==============================================================
/**
 *  checks if all pointers to CCore var are correctly set
 */

bool CThreadCore::CheckCorePointers()
{
  bool tmp = true;

  if(pConfigCore == NULL)
    tmp = false;

  if(pCoreSpace == NULL)
    tmp = false;

  if(pCoreDataGa == NULL)
    tmp = false;

  if((pMutexCore == NULL) || (pWaitCCore == NULL))
    tmp = false;

  if((bCoreDataExpired == NULL) || (bCoreSimRunning == NULL))
    tmp = false;

  if(!tmp)
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: CheckCorePointers()\n";
      msgErr += "One or more pointers from CCore needed in CThreadCore is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return false;
  }

  return true;
}

//==============================================================
//==============================================================
/**
 *  this function reads data from CCore class (ca space init config)
 *  and propagates them into ca class
 */

void CThreadCore::WriteCASpaceFromCoreIntoCA()
{
  if(!CheckCorePointers())
  {
    iErrFlag = THREAD_CORE_ERR_POINTERS;
    bInitDone = false;
    return;
  }
  if(ca == NULL)
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: WriteCASpaceFromCoreIntoCA()\n";
      msgErr += "Pointer to CCellularAutomata is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    iErrFlag = THREAD_CORE_ERR_POINTERS;
    bInitDone = false;
    return;
  }

  pMutexCore->lock();
  {
    if(pConfigCore->GetSpaceType() == SPACE_TYPE_TORUS)
    {
      for(unsigned int j = 0; j < (unsigned)pConfigCore->GetSpaceSizeY(); j++)
        for(unsigned int i = 0; i < (unsigned)pConfigCore->GetSpaceSizeX(); i++)
          ca->GetInitSpace()->atTorus(i,j) = pCoreSpace->atTorus(i,j);
    }
    else if(pConfigCore->GetSpaceType() == SPACE_TYPE_GRID)
    {
      for(unsigned int j = 0; j < (unsigned)pConfigCore->GetSpaceSizeY(); j++)
        for(unsigned int i = 0; i < (unsigned)pConfigCore->GetSpaceSizeX(); i++)
          ca->GetInitSpace()->atGrid(i,j) = pCoreSpace->atGrid(i,j);
    }
    else
    {
      {
        std::string msgErr  = "Class:    CThreadCore\n";
        msgErr += "Function: WriteCASpaceFromCoreIntoCA()\n";
        msgErr += "Unknown space type";

        if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
          pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
        else
          std::cerr << "ERROR: " << msgErr;
      }


      bInitDone = false;
      return;
    }

    ca->InitSpace();
  }
  pMutexCore->unlock();
}

//==============================================================
/**
 *  sends ca space into CCore
 */

void CThreadCore::WriteDataCAToCore()
{
  // data from CCore are now in gui classes, we can write new data
  if(pConfigCore->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    for(unsigned int j = 0; j < (unsigned)pConfigCore->GetSpaceSizeY(); j++)
      for(unsigned int i = 0; i < (unsigned)pConfigCore->GetSpaceSizeX(); i++)
        pCoreSpace->atTorus(i,j) = ca->GetSpace()->atTorus(i,j);
  }
  else if(pConfigCore->GetSpaceType() == SPACE_TYPE_GRID)
  {
    for(unsigned int j = 0; j < (unsigned)pConfigCore->GetSpaceSizeY(); j++)
      for(unsigned int i = 0; i < (unsigned)pConfigCore->GetSpaceSizeX(); i++)
        pCoreSpace->atGrid(i,j) = ca->GetSpace()->atGrid(i,j);
  }
  else
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: WriteDataCAToCore()\n";
      msgErr += "Unknown space type";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }
  }
}

//==============================================================
/**
 *  sends ga data struct into CCore
 */

void CThreadCore::WriteDataGAToCore()
{
  pCoreDataGa->iGeneration                      = dataGaToGui->iGeneration;
  pCoreDataGa->iChromosome                      = dataGaToGui->iChromosome;
  pCoreDataGa->iAncestorsCount                  = dataGaToGui->iAncestorsCount;

  pCoreDataGa->iFitnessMax                      = dataGaToGui->iFitnessMax;
  pCoreDataGa->dFitnessMaxNorm                  = dataGaToGui->dFitnessMaxNorm;
  pCoreDataGa->iDifferentionMin                 = dataGaToGui->iDifferentionMin;
  pCoreDataGa->iFitMaxStepCA                    = dataGaToGui->iFitMaxStepCA;

  pCoreDataGa->iSameGenomesCount                = dataGaTot.iSameGenomesCount;
  pCoreDataGa->dSameGenomesGenerationAvarage    = dataGaTot.dSameGenomesGenerationAvarage;
}

//==============================================================
/**
 *  sends data into CCore class from which they are send into gui
 */

void CThreadCore::SyncDataWithCore()
{
  pMutexCore->lock();
  {
    if(!*bCoreDataExpired)
      pWaitCCore->wait(pMutexCore);

    //========================
    // thread was terminated when it was waiting in WaitCondition
    if(bEvoExit)
    {
      pMutexCore->unlock();
      return;
    }
    //========================

    WriteDataCAToCore();
    WriteDataGAToCore();
  }
  pMutexCore->unlock();
}

//==============================================================
/**
 *  sets if data in gui (CCore class) are valid or not
 *
 *  @param dve          data validity
 */

void CThreadCore::SetCoreDataValidity(bool dve)
{
  pMutexCore->lock();
  {
    // data in core are valid - show them in gui
    if(dve)
    {
      *bCoreDataExpired = false;
      emit(SignalNewDataAvailable());
    }
    // data are not valid
    else
    {
      *bCoreDataExpired = true;
    }
  }
  pMutexCore->unlock();
}

//==============================================================
/**
 *  this function is used for sending data from this thread class
 *  into gui
 *
 *  @param call_pos     teremines which data will be send
 */

void CThreadCore::RunGuiMode(int call_pos)
{
  switch(call_pos)
  {
    //==========================================================
    case 0:
      // if gui mode BEST & BEST, synch data with gui
      if(pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__BEST_CHROM__B_STEP)
        SyncDataWithCore();
      break;


    //==========================================================
    case 1:
      // every step will be displayed in gui
      if(pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__E_STEP)
      {
        SyncDataWithCore();
        SetCoreDataValidity(true);
      }
      else if(pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__B_STEP)
      {
        if(actGenome->GetFitness() == actGenome->GetFitnessMax())
          SyncDataWithCore();
      }
      break;


    //==========================================================
    case 2:
      // display last / best step in gui
      if(pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__L_STEP)
      {
        // LAST STEP
        SyncDataWithCore();
        SetCoreDataValidity(true);
      }
      else if(pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__B_STEP)
        // BEST STEP - data are already in core - just say core to send them into gui
        SetCoreDataValidity(true);
      break;


    //==========================================================
    case 5:
      // show BEST solution of evolution in gui
      if((pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__RUN_E__BEST_CHROM__E_STEP) ||
         (pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__RUN_A__BEST_CHROM__E_STEP))
      {
        emit(SignalThreadState(THREAD_CORE_SIGNAL_BEST_READY));
        RunGenomeCaSimulation(bestGenome);
      }
      break;


    //==========================================================
    case 6:
      // show TOTAL BEST solution of evolution in gui
      if((pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP) ||
         (pConfigCore->GetGuiDisplayModeCA() == GUI_DISPLAY_MODE_CA__RUN_A__BEST_CHROM__E_STEP))
      {
        emit(SignalThreadState(THREAD_CORE_SIGNAL_TOTAL_BEST_READY));
        RunGenomeCaSimulation(bestGenomeTotal);
      }
      break;


    //==========================================================
    case 7:
      // run imported genome in ca simulator

      // load ga data from imported genome file
      dataGaAct.iGeneration                     = importGenome->GetThisGenerationId();
      dataGaAct.iChromosome                     = importGenome->GetThisGenomeId();

      dataGaAct.iFitnessMax                     = importGenome->GetFitnessMax();
      dataGaAct.dFitnessMaxNorm                 = importGenome->GetFitnessMaxNorm();
      dataGaAct.iDifferentionMin                = importGenome->GetDifferentionMin();
      dataGaAct.iFitMaxStepCA                   = importGenome->GetFitnessMaxStepCA();

      dataGaAct.iAncestorsCount                 = importGenome->GetAncestorsCount();

      dataGaAct.iSameGenomesCount               = 1;
      dataGaAct.dSameGenomesGenerationAvarage   = importGenome->GetThisGenerationId();

      dataGaTot.iSameGenomesCount               = 1;
      dataGaTot.dSameGenomesGenerationAvarage   = importGenome->GetThisGenerationId();

      // send ga data into gui
      StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_GUI);

      // emit signal for gui, that simulation is ready
      emit(SignalThreadState(THREAD_CORE_SIGNAL_IMPORT_READY));
      RunGenomeCaSimulation(importGenome);
      break;
  }
}

//==============================================================
/**
 *  exports genome from actual run, call_pos determines, which
 *  data will be exported - whole actual population, best genome
 *  from actual population or best genome from all evolution runs
 */

void CThreadCore::FileExportGa(int call_pos)
{
  // export actual chromosomes generation
  if((call_pos == 0) && (pConfigCore->GetExportFileModeGa() == FILE_EX__GA_MODE__RUN_E__CHROM_A))
    exportGa.ExportGeneration(exportFileGa,ga->GetActualPopulation());
  // export best ga solution
  else if((call_pos == 1) && (pConfigCore->GetExportFileModeGa() == FILE_EX__GA_MODE__RUN_E__CHROM_B))
    exportGa.ExportChromosome(exportFileGa,bestGenome);
  // export total best solution
  else if((call_pos == 2) && (pConfigCore->GetExportFileModeGa() == FILE_EX__GA_MODE__RUN_B__CHROM_B))
    exportGa.ExportChromosome(exportFileGa,bestGenomeTotal);
}

//==============================================================
/**
 *  exports init ca configuration into png (using CExportCA class)
 */

void CThreadCore::FileExportCaInit()
{
  // export ca input space
  QString caEx = pConfigCore->GetExportFilePath().c_str();
  caEx        += "/input_ca_space.png";

  exportCa.ExportCellularAutomatonInput(caEx,ca->GetInitSpace());


  // export ca init space
  if(pConfigCore->GetExportFileModeCa() == FILE_EX__CA_MODE__INIT_SPACE)
  {
    caEx  = pConfigCore->GetExportFilePath().c_str();
    caEx += "/export_ca_init_space.png";

    exportCa.ExportCellularAutomaton(caEx,ca->GetInitSpace());
  }
}

//==============================================================
/**
 *  exports all steps (from period) of ca run of object with
 *  selected genome
 *  for export space into png is used CExportCA class
 *  example:  exports 4 png-s of glider with game of life rules
 *
 *  @param *gen         pointer to genome
 */

void CThreadCore::FileExportCaSteps(CGenome *gen)
{
  if(gen == NULL)
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: FileExportCaSteps()\n";
      msgErr += "Pointer to CGenome is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return;
  }


  // calculations with actual chromosome is done, reinit ca
  ca->ReInit();


  // set genome
  ca->GetRulesTable()->SetGenome(gen);


  // create path and begin of file name
  QString caExFile = "";


  //========================================================
  // perform ca calculations
  for(int step = 0; step < (pConfigCore->GetStepsCountCA() + 1); step += 1)
  {
    // finish file name
    caExFile = exportFileCa;
    if(step < 10)
      caExFile += "_step_0";
    else
      caExFile += "_step_";
    caExFile += QString("%1").arg(step);
    caExFile += ".png";


    exportCa.ExportCellularAutomaton(caExFile,ca->GetSpace());


    // do one step with ca
    ca->Step();
  }


  // reinit ca and send space into gui
  ca->ReInit();
}

//==============================================================
//==============================================================
/**
 *  this function is ca run simulator
 *  given genome is used for for this simulation
 *  simulation data (ca space0 are send into gui
 *
 *  @param *gen         genome used in simualtion
 */

void CThreadCore::RunGenomeCaSimulation(CGenome *gen)
{
  if(gen == NULL)
  {
    {
      std::string msgErr  = "Class:    CThreadCore\n";
      msgErr += "Function: RunGenomeCaSimulation()\n";
      msgErr += "Pointer to CGenome is NULL";

      if((pConfigCore != NULL) && (pConfigCore->GetExportLogCore() != NULL))
        pConfigCore->GetExportLogCore()->WriteErrorLog(msgErr.c_str());
      else
        std::cerr << "ERROR: " << msgErr;
    }


    return;
  }


  // calculations with actual chromosome is done, reinit ca
  ca->ReInit();
  *bCoreDataExpired = true;
  SyncDataWithCore();
  SetCoreDataValidity(true);


  // set genome
  ca->GetRulesTable()->SetGenome(gen);


  //========================================================
  // perform ca calculations
  for(int step = 0; step < STEPS_COUNT_INF; step += 1)
  {
    // check terimination
    if(bEvoExit)
      return;
    if(bCaRunTermination)
      break;


    // do one step with ca
    ca->Step();


    SyncDataWithCore();
    SetCoreDataValidity(true);
  }

  // reinit ca and send space into gui
  ca->ReInit();
  *bCoreDataExpired = true;
  SyncDataWithCore();
  SetCoreDataValidity(true);


  // set ca run interrupt back to false
  bCaRunTermination = false;
}

//==============================================================
//==============================================================
/**
 *  this function is used for initializing data struct "dataGaAct"
 *  which holds information about ga computations which will be send
 *  into gui
 *  also this fc sets pointer to that data struct, from which ga data will
 *  be send into gui
 *
 *  @param mode         sets mode (way of if condition)
 */

void CThreadCore::StoreGenomeDataForGui(int mode)
{
  if(mode == THREAD_CORE_STORE_GA_DATA_MODE_ACT_INIT)
  {
    dataGaAct.iGeneration                     = -1;
    dataGaAct.iChromosome                     = -1;
    dataGaAct.iAncestorsCount                 = -1;

    dataGaAct.iFitnessMax                     = -1;
    dataGaAct.dFitnessMaxNorm                 = -1;
    dataGaAct.iDifferentionMin                = -1;
    dataGaAct.iFitMaxStepCA                   = -1;

    dataGaAct.iSameGenomesCount               = -1;
    dataGaAct.dSameGenomesGenerationAvarage   = -1;
  }
  else if(mode == THREAD_CORE_STORE_GA_DATA_MODE_ACT_SET_GENOME)
  {
    if(actGenome == NULL)
      StoreGenomeDataForGui(THREAD_CORE_STORE_GA_DATA_MODE_ACT_INIT);
    else
    {
      // fitness calc is ok - store data of chromosome
      dataGaAct.iGeneration                     = actGenome->GetThisGenerationId();
      dataGaAct.iChromosome                     = actGenome->GetThisGenomeId();
      dataGaAct.iAncestorsCount                 = actGenome->GetAncestorsCount();

      dataGaAct.iFitnessMax                     = actGenome->GetFitnessMax();
      dataGaAct.dFitnessMaxNorm                 = actGenome->GetFitnessMaxNorm();
      dataGaAct.iDifferentionMin                = actGenome->GetDifferentionMin();
      dataGaAct.iFitMaxStepCA                   = actGenome->GetFitnessMaxStepCA();

      dataGaAct.iSameGenomesCount               = 1;
      dataGaAct.dSameGenomesGenerationAvarage   = actGenome->GetThisGenerationId();
    }
  }
  else if(mode == THREAD_CORE_STORE_GA_DATA_MODE_ACT_MAX)
  {
    // act to max
    dataGaMax.iGeneration                     = dataGaAct.iGeneration;
    dataGaMax.iChromosome                     = dataGaAct.iChromosome;
    dataGaMax.iAncestorsCount                 = dataGaAct.iAncestorsCount;

    dataGaMax.iFitnessMax                     = dataGaAct.iFitnessMax;
    dataGaMax.dFitnessMaxNorm                 = dataGaAct.dFitnessMaxNorm;
    dataGaMax.iDifferentionMin                = dataGaAct.iDifferentionMin;
    dataGaMax.iFitMaxStepCA                   = dataGaAct.iFitMaxStepCA;

    dataGaMax.iSameGenomesCount               = dataGaAct.iSameGenomesCount;
    dataGaMax.dSameGenomesGenerationAvarage   = dataGaAct.dSameGenomesGenerationAvarage;
  }
  else if(mode == THREAD_CORE_STORE_GA_DATA_MODE_MAX_TOT)
  {
    // max to total max
    dataGaTot.iGeneration                     = dataGaMax.iGeneration;
    dataGaTot.iChromosome                     = dataGaMax.iChromosome;
    dataGaTot.iAncestorsCount                 = dataGaMax.iAncestorsCount;

    dataGaTot.iFitnessMax                     = dataGaMax.iFitnessMax;
    dataGaTot.dFitnessMaxNorm                 = dataGaMax.dFitnessMaxNorm;
    dataGaTot.iDifferentionMin                = dataGaMax.iDifferentionMin;
    dataGaTot.iFitMaxStepCA                   = dataGaMax.iFitMaxStepCA;

    dataGaTot.iSameGenomesCount               = dataGaMax.iSameGenomesCount;
    dataGaTot.dSameGenomesGenerationAvarage   = dataGaMax.dSameGenomesGenerationAvarage;
  }
  else if(mode == THREAD_CORE_STORE_GA_DATA_MODE_ACT_GUI)
  {
    // act to gui
    dataGaToGui = &dataGaAct;
  }
  else if(mode == THREAD_CORE_STORE_GA_DATA_MODE_MAX_GUI)
  {
    // max to gui
    dataGaToGui = &dataGaMax;
  }
  else if(mode == THREAD_CORE_STORE_GA_DATA_MODE_TOT_GUI)
  {
    // total to gui
    dataGaToGui = &dataGaTot;
  }
}

//==============================================================
//==============================================================
/**
 *  sets pointer to config class
 *
 *  @param *cc          pointer to config class
 */

void CThreadCore::SetConfigCore(CConfigCore *cc)
{
  pConfigCore = cc;
}

//==============================================================
//==============================================================
/**
 *  sets pointer to ca space in CCore - this ca space is used to
 *  write ca data from this thread class into gui
 *
 *  @param *ca          pointer to ca space in CCore
 */

void CThreadCore::SetCoreSpace(CSpace *cs)
{
  pCoreSpace = cs;
}

//==============================================================
/**
 *  sets pointer to data struct in CCore which is used to send
 *  GA data from this thread class into gui
 *
 *  @param *tcdga       pointer to ga data struct
 */

void CThreadCore::SetCoreDataGA(stThreadCoreDataGA *tcdga)
{
  pCoreDataGa = tcdga;
}

//==============================================================
//==============================================================
/**
 *  sets pointer to mutex from CCore class
 *
 *  @param *mc          pointer to mutex class
 */

void CThreadCore::SetMutex(QMutex *mc)
{
  pMutexCore = mc;
}

//==============================================================
/**
 *  sets pointer to wait condition class from CCore
 *
 *  @param *wcc         pointer to wait condition class
 */

void CThreadCore::SetWaitCondition(QWaitCondition *wcc)
{
  pWaitCCore = wcc;
}

//==============================================================
/**
 *  sets pointer to CCore var which determining, if data in CCore
 *  was already written into gui
 *
 *  @param *be          pointer to CCore bool var
 */

void CThreadCore::SetCoreDataExpiration(bool *be)
{
  bCoreDataExpired = be;
}

//==============================================================
/**
 *  sets if thread core would start simulation/evolution
 *  thread core is paused after init part of thread is done
 *
 *  @param *sr          pointer to CCore bool var
 */

void CThreadCore::SetSimulationRunning(bool *sr)
{
  bCoreSimRunning = sr;
}

//==============================================================
//==============================================================
/**
 *  returns pointer to actual ca space
 */

CSpace* CThreadCore::GetSpace()
{
  return ca->GetSpace();
}

//==============================================================
/**
 *  returns pointer to init ca space
 */

CSpace* CThreadCore::GetInitSpace()
{
  return ca->GetInitSpace();
}

//==============================================================
//==============================================================
/**
 *  returns core init state
 */

bool CThreadCore::IsInitDone()
{
  return bInitDone;
}

//==============================================================
//==============================================================
/**
 *  sets var for thread core termination
 */

void CThreadCore::TerminateThreadLoop()
{
  //pMutexCore->lock();
  {
    bEvoExit = true;
  }
  //pMutexCore->unlock();
}

//==============================================================
/**
 *  checks if app/thread core was terminated
 */

bool CThreadCore::CheckThreadLoopTermination()
{
  //pMutexCore->lock();
  {
    return bEvoExit;
  }
  //pMutexCore->unlock();
}

//==============================================================
/**
 *  sets var for ca simulator termination
 */

void CThreadCore::TerminateCaRun()
{
  //pMutexCore->lock();
  {
    bCaRunTermination = true;
  }
  //pMutexCore->unlock();
}

//==============================================================
/**
 *  checks, if ca simulator was abord from gui
 */

bool CThreadCore::CheckCaRunTermination()
{
  //pMutexCore->lock();
  {
    return bCaRunTermination;
  }
  //pMutexCore->unlock();
}

//==============================================================
//==============================================================
/**
 *  returns error flag
 */

int CThreadCore::GetErrorFlag()
{
  return iErrFlag;
}

//==============================================================
//==============================================================

