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

#include "WindowMain.h"
#include "ui_WindowMain.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *parent      pointer to parent widget
 */

CWindowMain::CWindowMain(QWidget *parent) : QMainWindow(parent), ui(new Ui::CWindowMain)
{
  bSimInitDone = false;
  bEvoRunning  = false;
  bCaRunning   = false;

  bWidgetInputApplyed     = false;
  bWidgetOutputApplyed    = false;
  bWidgetEvolutionApplyed = false;
  bWidgetExportApplyed    = false;

  bOutputDone         = false;

  iGuiDisplayModeCaTimeout = GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_DEFAULT;

  core = NULL;

  timer = NULL;

  widgetI   = NULL;
  widgetO   = NULL;
  widgetE   = NULL;
  widgetEx  = NULL;
  widgetRCA = NULL;


  ui->setupUi(this);

  if(!CheckUiLayouts())
  {
    QMessageBox::warning(this,
                         tr("GUI"),
                         tr("Gui initialization failed"),
                         QMessageBox::Ok);

    close();
  }


  // input widget
  widgetI = new CWidgetInput(this);
  if(widgetI == NULL)
  {
    QMessageBox::warning(this,
                         tr("GUI"),
                         tr("Gui initialization failed"),
                         QMessageBox::Ok);

    close();
  }
  ui->gridLayout_tabSet_tabIn->addWidget(widgetI);


  // output widget
  widgetO = new CWidgetOutput(this);
  if(widgetO == NULL)
  {
    QMessageBox::warning(this,
                         tr("GUI"),
                         tr("Gui initialization failed"),
                         QMessageBox::Ok);

    close();
  }
  ui->gridLayout_tabSet_tabOut->addWidget(widgetO);


  // evolution widget
  widgetE = new CWidgetEvolution(this);
  if(widgetE == NULL)
  {
    QMessageBox::warning(this,
                         tr("GUI"),
                         tr("Gui initialization failed"),
                         QMessageBox::Ok);

    close();
  }
  ui->gridLayout_tabSet_tabEvo->addWidget(widgetE);


  // export widget
  widgetEx = new CWidgetExport(this);
  if(widgetEx == NULL)
  {
    QMessageBox::warning(this,
                         tr("GUI"),
                         tr("Gui initialization failed"),
                         QMessageBox::Ok);

    close();
  }
  ui->gridLayout_tabSet_tabEx->addWidget(widgetEx);


  // run CA widget
  widgetRCA = new CWidgetRunCA(this);
  if(widgetRCA == NULL)
  {
    QMessageBox::warning(this,
                         tr("GUI"),
                         tr("Gui initialization failed"),
                         QMessageBox::Ok);

    close();
  }
  ui->gridLayout_tabRun_tabCA->addWidget(widgetRCA);


  // run evo widget
  widgetREvo = new CWidgetRunEvo(this);
  if(widgetREvo == NULL)
  {
    QMessageBox::warning(this,
                         tr("GUI"),
                         tr("Gui initialization failed"),
                         QMessageBox::Ok);

    close();
  }
  ui->gridLayout_tabRun_tabEvo->addWidget(widgetREvo);


  statusBar()->showMessage("Settings not applyed");


  // buttons
  ui->buttonDel->setEnabled(false);
  ui->buttonEvoStart->setEnabled(false);
  ui->buttonRun->setEnabled(false);
  ui->buttonStep->setEnabled(false);
  ui->buttonStop->setEnabled(false);
  ui->buttonTerminate->setEnabled(false);


  // signals & slots
  connect(ui->buttonInit,      SIGNAL(pressed()), this, SLOT(InitPressed()));
  connect(ui->buttonDel,       SIGNAL(pressed()), this, SLOT(DeletePressed()));
  connect(ui->buttonEvoStart,  SIGNAL(pressed()), this, SLOT(EvoStartPressed()));
  connect(ui->buttonRun,       SIGNAL(pressed()), this, SLOT(RunPressed()));
  connect(ui->buttonStep,      SIGNAL(pressed()), this, SLOT(StepPressed()));
  connect(ui->buttonStop,      SIGNAL(pressed()), this, SLOT(StopPressed()));
  connect(ui->buttonTerminate, SIGNAL(pressed()), this, SLOT(TerminatePressed()));

  connect(widgetI,  SIGNAL(SignalWidgetInputApplyed(bool)),  this, SLOT(WidgetInputApplyed(bool)));
  connect(widgetO,  SIGNAL(SignalWidgetOutputApplyed(bool)), this, SLOT(WidgetOutputApplyed(bool)));
  connect(widgetE,  SIGNAL(SignalWidgetEvoApplayed(bool)),   this, SLOT(WidgetEvolutionApplyed(bool)));
  connect(widgetEx, SIGNAL(SignalWidgetExportApplyed(bool)), this, SLOT(WidgetExportApplayed(bool)));

  connect(ui->actionExit,  SIGNAL(triggered()), this, SLOT(close()));
  connect(ui->actionExport,SIGNAL(triggered()), this, SLOT(MenuActionExportRunConfig()));
  connect(ui->actionImport,SIGNAL(triggered()), this, SLOT(MenuActionImportRunConfig()));
  connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(MenuActionAbout()));
}

//==============================================================
/**
 *  class destructor
 */

CWindowMain::~CWindowMain()
{
  if(timer != NULL)
    delete timer;

  if(core != NULL)
    delete core;

  if(widgetREvo != NULL)
    delete widgetREvo;
  if(widgetRCA != NULL)
    delete widgetRCA;
  if(widgetO != NULL)
    delete widgetO;
  if(widgetE != NULL)
    delete widgetE;
  if(widgetEx != NULL)
    delete widgetEx;
  if(widgetI != NULL)
    delete widgetI;
  delete ui;
}

//==============================================================
//==============================================================
/**
 *  change event happened
 *
 *  @param e            event
 */

void CWindowMain::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type())
  {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
      break;

    default:
      break;
  }
}

//==============================================================
//==============================================================
/**
 *  sets input widget apply state
 *
 *  @param a            input widget apply state
 */

void CWindowMain::WidgetInputApplyed(bool a)
{
  bWidgetInputApplyed = a;

  if(bWidgetInputApplyed)
  {
    widgetO->SetInputSizeX(widgetI->GetGrid()->GetWidth());
    widgetO->SetInputSizeY(widgetI->GetGrid()->GetHeight());

    widgetO->SetInputApplyed(true);
  }
  else
  {
    widgetO->SetInputApplyed(false);
  }

  CheckSettingApplyValidity();
}

//==============================================================
/**
 *  sets output widget apply state
 *
 *  @param a            output widget apply state
 */

void CWindowMain::WidgetOutputApplyed(bool a)
{
  bWidgetOutputApplyed = a;

  if(bWidgetOutputApplyed)
  {
    widgetI->SetOutputSizeX(widgetO->GetOutputGridSizeX());
    widgetI->SetOutputSizeY(widgetO->GetOutputGridSizeY());
    widgetI->SetOutputMapPosX(widgetO->GetOutputMapPosX());
    widgetI->SetOutputMapPosY(widgetO->GetOutputMapPosY());

    widgetI->SetOutputApplyed(true);
  }
  else
  {
    widgetI->SetOutputApplyed(false);
  }

  CheckSettingApplyValidity();
}

//==============================================================
/**
 *  sets evolution widget apply state
 *
 *  @param a            evolution widget apply state
 */

void CWindowMain::WidgetEvolutionApplyed(bool a)
{
  bWidgetEvolutionApplyed = a;

  CheckSettingApplyValidity();
}

//==============================================================
/**
 *  sets export widget apply state
 *
 *  @param a            export widget apply state
 */

void CWindowMain::WidgetExportApplayed(bool a)
{
  bWidgetExportApplyed = a;

  CheckSettingApplyValidity();
}

//==============================================================
//==============================================================
/**
 *  init button os pressed
 */

void CWindowMain::InitPressed()
{
  // check if all widgets are applyed

  if(!bWidgetInputApplyed)
  {
    QMessageBox::information(this,
                             tr("Run"),
                             tr("Input Settings not applyed."),
                             QMessageBox::Ok);
    return;
  }

  if(!bWidgetOutputApplyed)
  {
    QMessageBox::information(this,
                             tr("Run"),
                             tr("Output Settings not applyed"),
                             QMessageBox::Ok);

    return;
  }

  if(!bWidgetEvolutionApplyed)
  {
    QMessageBox::information(this,
                             tr("Run"),
                             tr("Evolution Settings not applyed"),
                             QMessageBox::Ok);

    return;
  }

  if(!bWidgetExportApplyed)
  {
    QMessageBox::information(this,
                             tr("Run"),
                             tr("Export Settings not applyed"),
                             QMessageBox::Ok);

    return;
  }

  if(!bSimInitDone)
  {
    ui->buttonInit->setEnabled(false);

    ui->statusbar->clearMessage();

    // init
    EvolutionInit();
  }
}

//==============================================================
/**
 *  delete button is pressed
 */

void CWindowMain::DeletePressed()
{
  if(bSimInitDone)
  {
    bSimInitDone = false;
    bEvoRunning  = false;
    bCaRunning   = false;

    CellularAutomatonRunning(false);
    EvolutionRunning(false);
    SimulationDelete();

    ui->buttonInit->setEnabled(true);
    ui->buttonEvoStart->setEnabled(false);
    ui->buttonRun->setEnabled(false);
    ui->buttonStep->setEnabled(false);
    ui->buttonStop->setEnabled(false);
    ui->buttonDel->setEnabled(false);
    ui->buttonTerminate->setEnabled(false);

    ui->statusbar->showMessage("Evolution was terminated",4000);
  }
}

//==============================================================
//==============================================================
/**
 *  evolve button is pressed
 */

void CWindowMain::EvoStartPressed()
{
  // check if init is done
  if(!bSimInitDone)
  {
    QMessageBox::warning(this,
                         tr("Evolution Starter"),
                         tr("Initialization not done"),
                         QMessageBox::Ok);

    return;
  }

  if(!bEvoRunning)
  {
    EvolutionRunning(true);

    ui->buttonEvoStart->setEnabled(false);
    ui->buttonDel->setEnabled(true);

    ui->statusbar->showMessage("Evolution is running...");
  }
}

//==============================================================
//==============================================================
/**
 *  run button is pressed
 *  start animation in simulator
 */

void CWindowMain::RunPressed()
{
  if(!bCaRunning)
  {
    // animation in simulator
    CellularAutomatonRunning(true);

    ui->buttonRun->setEnabled(false);
    ui->buttonStep->setEnabled(false);
    ui->buttonStop->setEnabled(true);
    ui->buttonTerminate->setEnabled(false);
  }
}

//==============================================================
/**
 *  step button is pressed
 *  do 1 step of ca in simulator
 */

void CWindowMain::StepPressed()
{
  CellularAutomatonStep();
}

//==============================================================
/**
 *  stop button is pressed
 *  interrupt animation in simualtor
 */

void CWindowMain::StopPressed()
{
  if(bCaRunning)
  {
    CellularAutomatonRunning(false);

    ui->buttonRun->setEnabled(true);
    ui->buttonStep->setEnabled(true);
    ui->buttonStop->setEnabled(false);
    ui->buttonTerminate->setEnabled(true);
  }
}

//==============================================================
/**
 *  terminate button is pressed
 *  terminate simulation
 */

void CWindowMain::TerminatePressed()
{
  CellularAutomatonRunning(false);

  ui->buttonRun->setEnabled(false);
  ui->buttonStep->setEnabled(false);
  ui->buttonStop->setEnabled(false);
  ui->buttonTerminate->setEnabled(false);

  core->SetCaRunTermination();
}

//==============================================================
//==============================================================
/**
 *  reaction to init button - inits evolution
 */

void CWindowMain::EvolutionInit()
{
  bool tmp = InitCore();

  if(tmp)
  {
    // init simulator
    widgetREvo->InitRun();
    widgetRCA->InitRunGrid(widgetO->GetOutputGridSizeX(),
                           widgetO->GetOutputGridSizeY(),
                           widgetI->GetGrid()->GetCellConfig()->GetStatesCount());

    CoreDataMapToGui();

    bSimInitDone = true;

    // tell all widgets, that init is done
    widgetI->SetInitDone(true);
    widgetO->SetInitDone(true);
    widgetE->SetInitDone(true);
    widgetEx->SetInitDone(true);

    //ui->statusbar->showMessage("Initialization is done", 4000);
  }
  else
  {
    bSimInitDone = false;

    ui->buttonInit->setEnabled(true);

    ui->statusbar->showMessage("Initialization failed", 4000);
  }
}

//==============================================================
/**
 *  reaction to evolve/delete button - starts evolution
 *
 *  @param r            is evolution running?
 */

void CWindowMain::EvolutionRunning(bool r)
{
  bEvoRunning = r;

  if(bEvoRunning)
  {
    core->SetSimulationRunning(true);
  }
  else
  {
    core->SetSimulationRunning(false);
  }
}

//==============================================================
/**
 *  reaction to run/stop button - starts animation in simualtor
 *
 *  @param r            is animation running?
 */

void CWindowMain::CellularAutomatonRunning(bool r)
{
  if(r)
  {
    // create timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(GuiDisplayCaMove()));
    timer->start(iGuiDisplayModeCaTimeout);

    bCaRunning  = true;
  }
  else
  {
    if(timer != NULL)
    {
      timer->stop();
      delete timer;
      timer = NULL;
    }

    bCaRunning  = false;
  }
}

//==============================================================
/**
 *  reaction to step button
 */

void CWindowMain::CellularAutomatonStep()
{
  if(core != NULL)
  {
    if(bOutputDone)
    {
      bOutputDone = false;
      core->SetCoreDataExpiration(true);
    }
  }
}

//==============================================================
/**
 *  reaction to delete button
 */

void CWindowMain::SimulationDelete()
{
  DeleteCore();
  widgetRCA->DeleteRun();
  widgetREvo->DeleteRun();

  bSimInitDone = false;
  bEvoRunning  = false;
  bCaRunning   = false;

  widgetI->SetInitDone(false);
  widgetO->SetInitDone(false);
  widgetE->SetInitDone(false);
  widgetEx->SetInitDone(false);
}

//==============================================================
//==============================================================
/**
 *  checks core initialization state
 */

void CWindowMain::CoreCheckInitDone(int ccid)
{
  // init OK
  if(ccid == THREAD_CORE_SIGNAL_INIT_DONE)
  {
    /*
    QMessageBox::information(this,
                             tr("Core Initialization"),
                             tr("Initialization is done"),
                             QMessageBox::Ok);
    */

    ui->statusbar->showMessage("Core Initialization is done");

    ui->buttonDel->setEnabled(true);
    ui->buttonEvoStart->setEnabled(true);
  }
  // init FAILED 1
  else if(ccid == THREAD_CORE_SIGNAL_SIM_DONE)
  {
    EvolutionRunning(false);

    ui->buttonDel->setEnabled(true);

    /*
    QMessageBox::information(this,
                             tr("Core Calculation"),
                             tr("Simulation is done"),
                             QMessageBox::Ok);
    */

    ui->statusbar->showMessage("Evolution is done");
  }
  // init FAILED 2
  else if(ccid == THREAD_CORE_SIGNAL_BEST_READY)
  {
    ui->buttonRun->setEnabled(true);
    ui->buttonStep->setEnabled(true);
    ui->buttonStop->setEnabled(false);
    ui->buttonTerminate->setEnabled(true);

    QMessageBox::information(this,
                             tr("Core Compute Thread"),
                             tr("Best solution is ready"),
                             QMessageBox::Ok);

    ui->statusbar->clearMessage();
  }
  // init FAILED 3
  else if(ccid == THREAD_CORE_SIGNAL_TOTAL_BEST_READY)
  {
    ui->buttonRun->setEnabled(true);
    ui->buttonStep->setEnabled(true);
    ui->buttonStop->setEnabled(false);
    ui->buttonTerminate->setEnabled(true);

    QMessageBox::information(this,
                             tr("Core Compute Thread"),
                             tr("Total best solution is ready"),
                             QMessageBox::Ok);

    ui->statusbar->clearMessage();
  }
  // init FAILED 4
  else if(ccid == THREAD_CORE_SIGNAL_IMPORT_READY)
  {
    ui->buttonRun->setEnabled(true);
    ui->buttonStep->setEnabled(true);
    ui->buttonStop->setEnabled(false);
    ui->buttonTerminate->setEnabled(true);

    ui->buttonDel->setEnabled(true);

    /*
    QMessageBox::information(this,
                             tr("Core Compute Thread"),
                             tr("Imported solution is ready"),
                             QMessageBox::Ok);
    */

    ui->statusbar->showMessage("Imported Genome is ready", 4000);
  }
  // init FAILED n
  else
  {
    if(ccid == THREAD_CORE_SIGNAL_ERR_INIT_THREAD)
      QMessageBox::critical(this,
                            tr("Core Initialization"),
                            tr("Thread initialization failed"),
                            QMessageBox::Ok);
    else if(ccid == THREAD_CORE_SIGNAL_ERR_INIT_GENOTYPE)
      QMessageBox::critical(this,
                            tr("Core Initialization"),
                            tr("Genotype initialization failed"),
                            QMessageBox::Ok);
    else if(ccid == THREAD_CORE_SIGNAL_ERR_INPUT_CA_SPACE)
      QMessageBox::critical(this,
                            tr("Core Initialization"),
                            tr("No object found in input CA space"),
                            QMessageBox::Ok);
    else if(ccid == THREAD_CORE_SIGNAL_ERR_IMPORT_FAILED)
    {
      QMessageBox::critical(this,
                            tr("Core Initialization"),
                            tr("Genome import failed"),
                            QMessageBox::Ok);
    }
    else
      QMessageBox::critical(this,
                            tr("Core Initialization"),
                            tr("Unknown error"),
                            QMessageBox::Ok);

    ui->statusbar->clearMessage();

    DeletePressed();
  }
}

//==============================================================
/**
 *  maps data from CCore class into widgets/gui
 */

void CWindowMain::CoreDataMapToGui()
{
    // maps ca space
  if(core->GetConfigCore()->GetSpaceType() == SPACE_TYPE_GRID)
  {
    for(int j = 0; j < core->GetSpace()->GetHeight(); j++)
      for(int i = 0; i < core->GetSpace()->GetWidth(); i++)
        widgetRCA->GetGrid()->GetCell(i,j)->SetState(core->GetSpace()->atGrid(i,j));
  }
  else if(core->GetConfigCore()->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    for(int j = 0; j < core->GetSpace()->GetHeight(); j++)
      for(int i = 0; i < core->GetSpace()->GetWidth(); i++)
        widgetRCA->GetGrid()->GetCell(i,j)->SetState(core->GetSpace()->atTorus(i,j));
  }

  // maps chromosome values
  widgetREvo->SetGenerationID(core->GetSimCoreDataStruct()->iGeneration);
  widgetREvo->SetChromosomeID(core->GetSimCoreDataStruct()->iChromosome);
  widgetREvo->SetAncestorsCount(core->GetSimCoreDataStruct()->iAncestorsCount);
  widgetREvo->SetFitnessMax(core->GetSimCoreDataStruct()->dFitnessMaxNorm);
  widgetREvo->SetDifferentionMin(core->GetSimCoreDataStruct()->iDifferentionMin);
  widgetREvo->SetFitMaxStepCA(core->GetSimCoreDataStruct()->iFitMaxStepCA);
  widgetREvo->SetSameChromosomesCount(core->GetSimCoreDataStruct()->iSameGenomesCount);
  widgetREvo->SetSameChromosomesGenerationAvarage(core->GetSimCoreDataStruct()->dSameGenomesGenerationAvarage);

  bOutputDone = true;
}

//==============================================================
//==============================================================
/**
 *  about from menu is pressed - show about dialog
 */

void CWindowMain::MenuActionAbout()
{
  QString msg = "";

  msg += "Application EvoDeMo deals with the utilization of evolutionary techniques ";
  msg += "to find such environment characteristics, that allow the object ";
  msg += "in this environment to perform the movement according to specified ";
  msg += "parameters.";
  msg += "\n";
  msg += "The presented work tends to the area of theoretical biology. ";
  msg += "Its main objective is to create a simple simulator of life of artificial organisms. ";
  msg += "For this purpose the application allows the designer to define an organism at the level ";
  msg += "of cells of the cellular automaton and apply the genetic algorithm to design the ";
  msg += "transition function specifying the behavior of the organism according to given parameters.";
  msg += "\n\n";
  msg += "Author:   Martin Balaz\n";
  msg += "Contacts: \n";
  msg += "  balaz.marti@gmail.com\n";
  msg += "  xbalaz00@stud.fit.vutbr.cz";
  msg += "\n\n";
  msg += "Copyright (c) 2010 by Martin Balaz";

  QMessageBox::information(this,
                           tr("About EvoDeMo"),
                           msg,
                           QMessageBox::Ok);
}

//==============================================================
/**
 *  export from menu is pressed - export all settings
 */

void CWindowMain::MenuActionExportRunConfig()
{
  QString tmp = "";

  // get file to export
  tmp = QFileDialog::getSaveFileName(this,
                                     "Save EvoDeMo Config",
                                     "evodemo_config.ecs",
                                     // .ecs = Evodemo Complete Settings
                                     "EvoDeMo Config file (*.ecs)");

  if(tmp.isEmpty())
  {
    return;
  }

  ui->statusbar->showMessage("Exporting run config ...");

  // export settings
  exportConfig.ExportConfig(tmp,
                            widgetI,
                            widgetO,
                            widgetE,
                            widgetEx);

  if(exportConfig.GetErrorFlag() != EXPORT_CONFIG_OK)
  {
    QMessageBox::critical(this,
                          "Export Config",
                          "Error while exporting config",
                          QMessageBox::Ok);
  }
  else
  {
    QMessageBox::information(this,
                             "Export Config",
                             "Export successful",
                             QMessageBox::Ok);

    CheckSettingApplyValidity();
    //ui->statusbar->showMessage("");
  }
}

//==============================================================
/**
 *  import from menu is pressed - import all settings
 */

void CWindowMain::MenuActionImportRunConfig()
{
  if((bWidgetInputApplyed) ||
     (bWidgetOutputApplyed) ||
     (bWidgetEvolutionApplyed) ||
     (bWidgetExportApplyed))
  {
    QMessageBox::warning(this,
                         "Import Config",
                         "Some of settings are already applyed.\nCancel all applyed settings first.",
                         QMessageBox::Ok);
    return;
  }

  QString tmp = "";

  // get file to export
  tmp = QFileDialog::getOpenFileName(this,
                                     "Load EvoDeMo Config",
                                     QDir::currentPath(),
                                     "EvoDeMo Config file (*.ecs)");

  if(tmp.isEmpty())
  {
    return;
  }

  ui->statusbar->showMessage("Importing run config ...");

  // export settings
  importConfig.ImportConfig(tmp,
                            widgetI,
                            widgetO,
                            widgetE,
                            widgetEx);

  if(importConfig.GetErrorFlag() != IMPORT_CONFIG_OK)
  {
    QMessageBox::critical(this,
                          "Import Config",
                          "Error while importing config",
                          QMessageBox::Ok);
  }
  else
  {
    QMessageBox::information(this,
                             "Import Config",
                             "Import successful",
                             QMessageBox::Ok);

    CheckSettingApplyValidity();
    //ui->statusbar->showMessage("");
  }
}

//==============================================================
//==============================================================
/**
 *  i am not sure, but i thing, that this is called when data
 *  from CCore are written into widgets, so it's possible
 *  to write new data into CCore from app kernel
 */

void CWindowMain::GuiDisplayCaMove()
{
  if(bOutputDone)
  {
    bOutputDone = false;
    core->SetCoreDataExpiration(true);
  }
}

//==============================================================
//==============================================================
/**
 *  inits app core - creates CCore class, writes all settings into it
 *  CCore then creates app kernel class - CThreadCore
 */

bool CWindowMain::InitCore()
{
  DeleteCore();

  // create core
  core = new CCore();
  if(core == NULL)
  {
    QMessageBox::critical(this,
                          tr("Core Initialization"),
                          tr("Memory allocation failed\nTry again"),
                          QMessageBox::Ok);

    return false;
  }

  // space settings
  core->GetConfigCore()->SetSpaceType(widgetO->GetOutputArrayType());
  core->GetConfigCore()->SetSpaceSizeX(widgetO->GetOutputGridSizeX());
  core->GetConfigCore()->SetSpaceSizeY(widgetO->GetOutputGridSizeY());

  // states
  core->GetConfigCore()->SetStatesCount(widgetI->GetGrid()->GetCellConfig()->GetStatesCount());
  core->GetConfigCore()->SetDefaultState(CELL_STATE_EMPTY);

  // ga
  core->GetConfigCore()->SetEvolutionRepetitionsCount(widgetE->GetRepetitionsCount());
  core->GetConfigCore()->SetGenerationsCount(widgetE->GetGenerationsCount());
  core->GetConfigCore()->SetPopulationSize(widgetE->GetPopulationSize());
  core->GetConfigCore()->SetStepsCountCA(widgetE->GetStepsCount());

  // ga operators
  //core->GetConfigCore()->SetCrossoverProbability(widgetE->GetCrossoverProbability());
  //core->GetConfigCore()->SetCrossoverCount(widgetE->GetCrossoverCount());
  core->GetConfigCore()->SetMutationProbability(widgetE->GetMutationProbability());
  core->GetConfigCore()->SetMutationCount(widgetE->GetMutationCount());

  // motion direction
  core->GetConfigCore()->SetMoveDirection(widgetE->GetMoveDirection());
  core->GetConfigCore()->SetMoveDistance(widgetE->GetMoveDistance());

  // display mode settings
  core->GetConfigCore()->SetGuiDisplayModeCA(widgetEx->GetGuiDataDisplayModeCA());
  core->GetConfigCore()->SetGuiDisplayModeCATimeout(widgetEx->GetGuiDataDisplayModeTimeout());

  // export file path
  core->GetConfigCore()->SetExportFilePath(widgetEx->GetFileExportPath().toStdString());
  core->GetConfigCore()->SetExportFileModeCa(widgetEx->GetFileExportModeCA());
  core->GetConfigCore()->SetExportFileModeGa(widgetEx->GetFileExportModeGA());

  // import genome file settings
  core->GetConfigCore()->SetImportGenomeEnabledSimulation(widgetE->IsImportGenomeEnabledSimulation());
  core->GetConfigCore()->SetImportGenomeEnabledReevolve(widgetE->IsImportGenomeEnabledReevolve());

  if(widgetE->IsImportGenomeEnabledSimulation() || widgetE->IsImportGenomeEnabledReevolve())
    core->GetConfigCore()->SetImportGenomeFile(widgetE->GetImportGenomeFile().toStdString());

  // set gui timeout
  iGuiDisplayModeCaTimeout = core->GetConfigCore()->GetGuiDisplayModeCATimeout();

  // decide which genome type will be used from states count and neighborhood type
  switch(core->GetConfigCore()->GetStatesCount())
  {
    case 2:
      if(widgetE->GetGenomeType() == GENOME_TYPE_EVO_WID_9N)
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_2_9N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_2_9N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_2_9N);
      }
      else if(widgetE->GetGenomeType() == GENOME_TYPE_EVO_WID_5N)
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_2_5N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_2_5N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_2_5N);
      }
      //else if(widgetE->GetGenomeType() == GENOME_TYPE_EVO_WID_INS)
      //  core->GetConfigCore()->SetGenomeType(GENOME_TYPE_2_INS);
      else
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_2_9N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_2_9N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_2_9N);
      }
      break;

    case 3:
      if(widgetE->GetGenomeType() == GENOME_TYPE_EVO_WID_9N)
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_3_9N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_3_9N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_3_9N);
      }
      else if(widgetE->GetGenomeType() == GENOME_TYPE_EVO_WID_5N)
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_3_5N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_3_5N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_3_5N);
      }
      else
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_3_9N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_3_9N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_3_9N);
      }
      break;

    case 4:
      if(widgetE->GetGenomeType() == GENOME_TYPE_EVO_WID_9N)
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_4_9N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_4_9N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_4_9N);
      }
      else if(widgetE->GetGenomeType() == GENOME_TYPE_EVO_WID_5N)
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_4_5N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_4_5N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_4_5N);
      }
      else
      {
        core->GetConfigCore()->SetGenomeType(GENOME_TYPE_4_9N);

        if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_4_9N)
          core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_4_9N);
      }
      break;

    default:
      core->GetConfigCore()->SetGenomeType(GENOME_TYPE_2_9N);
      if(core->GetConfigCore()->GetMutationCount() > GENOME_SIZE_TYPE_2_9N)
        core->GetConfigCore()->SetMutationCount(GENOME_SIZE_TYPE_2_9N);
  }


  // init simulator's core
  core->InitGuiCore();

  if(!core->IsInitDone())
  {
    QMessageBox::critical(this,
                          tr("Core Initialization"),
                          tr("Core initalization failed\nTry again"),
                          QMessageBox::Ok);

    DeleteCore();

    return false;
  }


  connect(core, SIGNAL(SignalThreadCoreErr(int)),   this, SLOT(CoreCheckInitDone(int)));
  connect(core, SIGNAL(SignalThreadCoreState(int)), this, SLOT(CoreCheckInitDone(int)));
  connect(core, SIGNAL(SignalNewDataAvailable()),   this, SLOT(CoreDataMapToGui()));


  // propagate input space from gui into core
  if(core->GetConfigCore()->GetSpaceType() == SPACE_TYPE_TORUS)
  {
    for(int j = 0; j < widgetI->GetGrid()->GetHeight(); j++)
      for(int i = 0; i < widgetI->GetGrid()->GetWidth(); i++)
        core->GetSpace()->atTorus(widgetO->GetOutputMapPosX() + i, widgetO->GetOutputMapPosY() + j) = \
          widgetI->GetGrid()->GetCell(i,j)->GetState();
  }
  else if(core->GetConfigCore()->GetSpaceType() == SPACE_TYPE_GRID)
  {
    for(int j = 0; j < widgetI->GetGrid()->GetHeight(); j++)
      for(int i = 0; i < widgetI->GetGrid()->GetWidth(); i++)
        core->GetSpace()->atGrid(widgetO->GetOutputMapPosX() + i, widgetO->GetOutputMapPosY() + j) = \
          widgetI->GetGrid()->GetCell(i,j)->GetState();
  }


  // start core thread - do init of something
  core->SetSimulationRunning(false);
  core->StartThreadCore();


  return true;
}

//==============================================================
/**
 *  deletes CCore class
 */

void CWindowMain::DeleteCore()
{
  if(core != NULL)
    delete core;

  core = NULL;
}

//==============================================================
//==============================================================
/**
 *  checks, if all widgets are applyed
 */

void CWindowMain::CheckSettingApplyValidity()
{
  QString msg = "These settings are not applyed: ";

  if(!bWidgetInputApplyed)
    msg += "Input ";
  if(!bWidgetOutputApplyed)
    msg += "Output ";
  if(!bWidgetEvolutionApplyed)
    msg += "Evolution ";
  if(!bWidgetExportApplyed)
    msg += "Export";

  if(bWidgetInputApplyed && bWidgetOutputApplyed &&
     bWidgetEvolutionApplyed && bWidgetExportApplyed)
    statusBar()->showMessage("All settings are applyed");
  else
    statusBar()->showMessage(msg);
}

//==============================================================
//==============================================================
/**
 *  checks if all widget layout was correctly allocated
 */

bool CWindowMain::CheckUiLayouts()
{
  if(ui == NULL)
    return false;

  if(//(ui->gridLayoutCentral == NULL) ||
     //(ui->gridLayoutTabS == NULL) ||
     //(ui->gridLayoutTabR == NULL) ||
     (ui->gridLayout_tabSet_tabIn == NULL) ||
     (ui->gridLayout_tabSet_tabOut == NULL) ||
     (ui->gridLayout_tabSet_tabEvo == NULL) ||
     (ui->gridLayout_tabSet_tabEx == NULL) ||
     (ui->gridLayout_tabRun_tabCA == NULL) ||
     (ui->gridLayout_tabRun_tabEvo == NULL))
    return false;

  return true;
}

//==============================================================
//==============================================================

