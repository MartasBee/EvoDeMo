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

#include "WidgetEvolution.h"
#include "ui_WidgetEvolution.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *parent      pointer to parent widget
 */

CWidgetEvolution::CWidgetEvolution(QWidget *parent) : QWidget(parent), ui(new Ui::CWidgetEvolution)
{
  iRepetitions    = EVOLUTION_REPEATITIONS_DEFAULT;
  iGenerations    = GENERATIONS_COUNT_DEFAULT;
  iPopulation     = POPULATION_INIT_DEFAULT;
  iGenomeType     = GENOME_TYPE_EVO_WID_9N;

  iCrossoverProb  = CROSSOVER_PROB_DEFAULT;
  iCrossoverCount = CROSSOVER_COUNT_DEFAULT;
  iMutationProb   = MUTATION_PROB_DEFAULT;
  iMutationCount  = MUTATION_COUNT_DEFAULT;

  iMoveDir        = MOVE_DIR_W;//ANY;
  iStepsCount     = STEPS_COUNT_DEFAULT;
  iMoveDis        = MOVE_DIS_DEFAULT;

  importFile      = "";
  bImportFileEnabledSimulation = false;
  bImportFileEnabledReevolve   = false;

  bApplyed  = false;
  bInitDone = false;


  ui->setupUi(this);


  ui->spinBoxRepeats->setMinimum(EVOLUTION_REPEATITIONS_MIN);
  ui->spinBoxRepeats->setMaximum(EVOLUTION_REPEATITIONS_MAX);
  ui->spinBoxRepeats->setValue(iRepetitions);
  ui->spinBoxRepeats->setToolTip("Independet Runs of Evolution");

  ui->spinBoxGen->setMinimum(GENERATIONS_COUNT_MIN);
  ui->spinBoxGen->setMaximum(GENERATIONS_COUNT_MAX);
  ui->spinBoxGen->setValue(iGenerations);

  ui->spinBoxPop->setMinimum(POPULATION_INIT_MIN);
  ui->spinBoxPop->setMaximum(POPULATION_INIT_MAX);
  ui->spinBoxPop->setValue(iPopulation);

  ui->comboBoxGenType->insertItem(GENOME_TYPE_EVO_WID_9N,  "9-neighbors");
  ui->comboBoxGenType->insertItem(GENOME_TYPE_EVO_WID_5N,  "5-neighbors");
  //ui->comboBoxGenType->insertItem(GENOME_TYPE_EVO_WID_INS, "Instructions");
  ui->comboBoxGenType->setCurrentIndex(iGenomeType);
  //ui->comboBoxGenType->setEnabled(false);


  ui->comboBoxDir->insertItem(MOVE_DIR_NE,  "Up Right");
  ui->comboBoxDir->insertItem(MOVE_DIR_N,   "Up");
  ui->comboBoxDir->insertItem(MOVE_DIR_NW,  "Up Left");
  ui->comboBoxDir->insertItem(MOVE_DIR_W,   "Left");
  ui->comboBoxDir->insertItem(MOVE_DIR_SW,  "Down Left");
  ui->comboBoxDir->insertItem(MOVE_DIR_S,   "Down");
  ui->comboBoxDir->insertItem(MOVE_DIR_SE,  "Down Right");
  ui->comboBoxDir->insertItem(MOVE_DIR_E,   "Right");
  //ui->comboBoxDir->insertItem(MOVE_DIR_ANY, "Any");
  ui->comboBoxDir->setCurrentIndex(iMoveDir);

  ui->spinBoxSteps->setMinimum(STEPS_COUNT_MIN);
  ui->spinBoxSteps->setMaximum(STEPS_COUNT_MAX);
  ui->spinBoxSteps->setValue(iStepsCount);
  ui->spinBoxSteps->setToolTip("Steps needed for transformation");

  ui->spinBoxDistance->setMinimum(MOVE_DIS_MIN);
  ui->spinBoxDistance->setMaximum(MOVE_DIS_MAX);
  ui->spinBoxDistance->setValue(iMoveDis);


  //ui->spinBoxCProb->setMinimum(CROSSOVER_PROB_MIN);
  //ui->spinBoxCProb->setMaximum(CROSSOVER_PROB_MAX);
  //ui->spinBoxCProb->setValue(iCrossoverProb);
  //ui->spinBoxCProb->setEnabled(false);
  //ui->spinBoxCProb->setToolTip("Crossover is NOT used");

  //ui->spinBoxCCount->setMinimum(CROSSOVER_COUNT_MIN);
  //ui->spinBoxCCount->setMaximum(CROSSOVER_COUNT_MAX);
  //ui->spinBoxCCount->setValue(iCrossoverCount);
  //ui->spinBoxCCount->setEnabled(false);
  //ui->spinBoxCCount->setToolTip("Crossover is NOT used");

  ui->spinBoxCProb->setEnabled(false);
  ui->spinBoxCCount->setEnabled(false);
  ui->frameCross->setVisible(false);


  ui->spinBoxMProb->setMinimum(MUTATION_PROB_MIN);
  ui->spinBoxMProb->setMaximum(MUTATION_PROB_MAX);
  ui->spinBoxMProb->setValue(iMutationProb);

  ui->spinBoxMCount->setMinimum(MUTATION_COUNT_MIN);
  ui->spinBoxMCount->setMaximum(MUTATION_COUNT_MAX);
  ui->spinBoxMCount->setValue(iMutationCount);
  QString toolMsg = "Maximum values:\n";
  toolMsg += " 9-neighbors:\n";
  toolMsg += "  2-state CA - 512\n  3-state CA - 19683\n  4-state CA - 262144\n";
  toolMsg += " 5-neighbors:\n";
  toolMsg += "  2-state CA - 32\n";
  toolMsg += "  3-state CA - 243\n";
  toolMsg += "  4-state CA - 1024";
  ui->spinBoxMCount->setToolTip(toolMsg);


  ui->checkBoxImportSim->setEnabled(false);
  ui->checkBoxImportSim->setCheckState(Qt::Unchecked);
  ui->checkBoxImportSim->setToolTip("When ENABLED, evolution will not run");

  ui->checkBoxImportReevo->setEnabled(false);
  ui->checkBoxImportReevo->setCheckState(Qt::Unchecked);
  ui->checkBoxImportReevo->setToolTip("When ENABLED, imported chromosome will be reevolved");

  ui->lineEditImportFile->setEnabled(false);
  ui->lineEditImportFile->setText("none file selected");


  ui->buttonCancel->setEnabled(false);


  connect(ui->spinBoxRepeats,   SIGNAL(valueChanged(int)),        this, SLOT(RepetitionsChanged(int)));
  connect(ui->spinBoxGen,       SIGNAL(valueChanged(int)),        this, SLOT(GenerationsChanged(int)));
  connect(ui->spinBoxPop,       SIGNAL(valueChanged(int)),        this, SLOT(PopulationChanged(int)));
  connect(ui->comboBoxGenType,  SIGNAL(currentIndexChanged(int)), this, SLOT(GenomeTypeChanged(int)));

  connect(ui->comboBoxDir,      SIGNAL(currentIndexChanged(int)), this, SLOT(DirectionChanged(int)));
  connect(ui->spinBoxSteps,     SIGNAL(valueChanged(int)),        this, SLOT(StepsChanged(int)));
  connect(ui->spinBoxDistance,  SIGNAL(valueChanged(int)),        this, SLOT(DistanceChanged(int)));

  //connect(ui->spinBoxCProb,     SIGNAL(valueChanged(int)), this, SLOT(CrossoverProbChanged(int)));
  //connect(ui->spinBoxCCount,    SIGNAL(valueChanged(int)), this, SLOT(CrossoverCountChanged(int)));

  connect(ui->spinBoxMProb,     SIGNAL(valueChanged(int)), this, SLOT(MutationProbChanged(int)));
  connect(ui->spinBoxMCount,    SIGNAL(valueChanged(int)), this, SLOT(MutationCountChanged(int)));

  connect(ui->checkBoxImportSim,   SIGNAL(stateChanged(int)), this, SLOT(ImportFileEnableSimulation(int)));
  connect(ui->checkBoxImportReevo, SIGNAL(stateChanged(int)), this, SLOT(ImportFileEnableReevolve(int)));
  connect(ui->buttonLoad,          SIGNAL(pressed()),         this, SLOT(ImportFileButtonPressed()));

  connect(ui->buttonApply,      SIGNAL(pressed()), this, SLOT(ApplyPressed()));
  connect(ui->buttonCancel,     SIGNAL(pressed()), this, SLOT(CancelPressed()));
}

//==============================================================
/**
 *  class destructor
 */

CWidgetEvolution::~CWidgetEvolution()
{
  delete ui;
}

//==============================================================
//==============================================================
/**
 *  returns repetitions count
 */

int CWidgetEvolution::GetRepetitionsCount()
{
  return iRepetitions;
}

//==============================================================
/**
 *  returns generations count
 */

int CWidgetEvolution::GetGenerationsCount()
{
  return iGenerations;
}

//==============================================================
/**
 *  returns population size
 */

int CWidgetEvolution::GetPopulationSize()
{
  return iPopulation;
}

//==============================================================
/**
 *  returns genome type
 */

int CWidgetEvolution::GetGenomeType()
{
  return iGenomeType;
}

//==============================================================
//==============================================================
/**
 *  returns movement direction
 */

int CWidgetEvolution::GetMoveDirection()
{
  return iMoveDir;
}

//==============================================================
/**
 *  returns steps count
 */

int CWidgetEvolution::GetStepsCount()
{
  return iStepsCount;
}

//==============================================================
/**
 *  returns movement distance
 */

int CWidgetEvolution::GetMoveDistance()
{
  return iMoveDis;
}

//==============================================================
//==============================================================
/**
 *  returns crossover probability
 */

int CWidgetEvolution::GetCrossoverProbability()
{
  return iCrossoverProb;
}

//==============================================================
/**
 *  returns crossover count
 */

int CWidgetEvolution::GetCrossoverCount()
{
  return iCrossoverCount;
}

//==============================================================
/**
 *  returns mutation probability
 */

int CWidgetEvolution::GetMutationProbability()
{
  return iMutationProb;
}

//==============================================================
/**
 *  returns mutation count
 */

int CWidgetEvolution::GetMutationCount()
{
  return iMutationCount;
}

//==============================================================
//==============================================================
/**
 *  should be imported genome used in simulation?
 */

bool CWidgetEvolution::IsImportGenomeEnabledSimulation()
{
  return bImportFileEnabledSimulation;
}

//==============================================================
/**
 *  should be imported genome used for reevolution?
 */

bool CWidgetEvolution::IsImportGenomeEnabledReevolve()
{
  return bImportFileEnabledReevolve;
}

//==============================================================
/**
 *  returns path/name of imported file
 */

QString CWidgetEvolution::GetImportGenomeFile()
{
  return importFile;
}

//==============================================================
//==============================================================
/**
 *  are settings from this widget applyed
 */

bool CWidgetEvolution::IsApplyed()
{
  return bApplyed;
}

//==============================================================
/**
 *  button init changed state - enable/disable any changes in widget
 */

void CWidgetEvolution::SetInitDone(bool id)
{
  bInitDone = id;

  if(bInitDone)
  {
    ui->buttonApply->setEnabled(false);
    ui->buttonCancel->setEnabled(false);
  }
  else
  {
    ui->buttonCancel->setEnabled(true);
  }
}

//==============================================================
//==============================================================
/**
 *  sets repetitions - used as extern call - when settings are loaded from file
 *
 *  @param rc           new repetitions count
 */

void CWidgetEvolution::SetRepetitionsCount(int rc)
{
  if((rc < EVOLUTION_REPEATITIONS_MIN) ||
     (rc > EVOLUTION_REPEATITIONS_MAX))
    return;

  ui->spinBoxRepeats->setValue(rc);

  RepetitionsChanged(ui->spinBoxRepeats->value());
}

//==============================================================
/**
 *  sets generations count - used as extern call - when settings are loaded from file
 *
 *  @param gc           new generation count
 */

void CWidgetEvolution::SetGenerationsCount(int gc)
{
  if((gc < GENERATIONS_COUNT_MIN) ||
     (gc > GENERATIONS_COUNT_MAX))
    return;

  ui->spinBoxGen->setValue(gc);

  GenerationsChanged(ui->spinBoxGen->value());
}

//==============================================================
/**
 *  sets population size - used as extern call - when settings are loaded from file
 *
 *  @param ps           new population size
 */

void CWidgetEvolution::SetPopulationSize(int ps)
{
  if((ps < POPULATION_INIT_MIN) ||
     (ps > POPULATION_INIT_MAX))
    return;

  ui->spinBoxPop->setValue(ps);

  PopulationChanged(ui->spinBoxPop->value());
}

//==============================================================
/**
 *  sets genome type - used as extern call - when settings are loaded from file
 *
 *  @param gt           new genome type
 */

void CWidgetEvolution::SetGenomeType(int gt)
{
  if((gt != GENOME_TYPE_EVO_WID_9N) &&
     (gt != GENOME_TYPE_EVO_WID_5N))
    return;

  ui->comboBoxGenType->setCurrentIndex(gt);

  GenomeTypeChanged(ui->comboBoxGenType->currentIndex());
}

//==============================================================
//==============================================================
/**
 *  sets crossover probability - used as extern call - when settings are loaded from file
 *
 *  @param cp           new crossover probability
 */

void CWidgetEvolution::SetCrossoverProbability(int cp)
{
  if((cp < CROSSOVER_PROB_MIN) ||
     (cp > CROSSOVER_PROB_MAX))
    return;

  ui->spinBoxCProb->setValue(cp);

  CrossoverProbChanged(ui->spinBoxCProb->value());
}

//==============================================================
/**
 *  sets crossover count - used as extern call - when settings are loaded from file
 *
 *  @param cc           new crossover count
 */

void CWidgetEvolution::SetCrossoverCount(int cc)
{
  if((cc < CROSSOVER_COUNT_MIN) ||
     (cc > CROSSOVER_COUNT_MAX))
    return;

  ui->spinBoxCCount->setValue(cc);

  CrossoverCountChanged(ui->spinBoxCCount->value());
}

//==============================================================
/**
 *  sets mutation probability - used as extern call - when settings are loaded from file
 *
 *  @param mp           new mutation probability
 */

void CWidgetEvolution::SetMutationProbability(int mp)
{
  if((mp < MUTATION_PROB_MIN) ||
     (mp > MUTATION_PROB_MAX))
    return;

  ui->spinBoxMProb->setValue(mp);

  MutationProbChanged(ui->spinBoxMProb->value());
}

//==============================================================
/**
 *  sets mutation count - used as extern call - when settings are loaded from file
 *
 *  @param mc           new mutation count
 */

void CWidgetEvolution::SetMutationCount(int mc)
{
  if((mc < MUTATION_COUNT_MIN) ||
     (mc > MUTATION_COUNT_MAX))
    return;

  ui->spinBoxMCount->setValue(mc);

  MutationCountChanged(ui->spinBoxMCount->value());
}

//==============================================================
//==============================================================
/**
 *  sets direction - used as extern call - when settings are loaded from file
 *
 *  @param md           new direction
 */

void CWidgetEvolution::SetMoveDirection(int md)
{
  if((md != MOVE_DIR_ANY) &&
     (md != MOVE_DIR_N) &&
     (md != MOVE_DIR_NW) &&
     (md != MOVE_DIR_W) &&
     (md != MOVE_DIR_SW) &&
     (md != MOVE_DIR_S) &&
     (md != MOVE_DIR_SE) &&
     (md != MOVE_DIR_E) &&
     (md != MOVE_DIR_NE))
    return;

  ui->comboBoxDir->setCurrentIndex(md);

  DirectionChanged(ui->comboBoxDir->currentIndex());
}

//==============================================================
/**
 *  sets steps count - used as extern call - when settings are loaded from file
 *
 *  @param sc           new steps count
 */

void CWidgetEvolution::SetStepsCount(int sc)
{
  if((sc < STEPS_COUNT_MIN) ||
     (sc > STEPS_COUNT_MAX))
    return;

  ui->spinBoxSteps->setValue(sc);

  StepsChanged(ui->spinBoxSteps->value());
}

//==============================================================
/**
 *  sets distance - used as extern call - when settings are loaded from file
 *
 *  @param md           new distance
 */

void CWidgetEvolution::SetMoveDistance(int md)
{
  if((md < MOVE_DIS_MIN) ||
     (md > MOVE_DIS_MAX))
    return;

  ui->spinBoxDistance->setValue(md);

  DistanceChanged(ui->spinBoxDistance->value());
}

//==============================================================
//==============================================================
/**
 *  change event happened
 *
 *  @param e            event
 */

void CWidgetEvolution::changeEvent(QEvent *e)
{
  QWidget::changeEvent(e);
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
 *  repetitions spinbox was changed - set new repetitions
 *
 *  @param r            new value from spinbox
 */

void CWidgetEvolution::RepetitionsChanged(int r)
{
  if(iRepetitions != r)
  {
    iRepetitions = r;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  generation count spinbox was changed - set new generation count
 *
 *  @param g            new value from spinbox
 */

void CWidgetEvolution::GenerationsChanged(int g)
{
  if(iGenerations != g)
  {
    iGenerations = g;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  population size spinbox was changed - set new popluation size
 *
 *  @param p            new value from spinbox
 */

void CWidgetEvolution::PopulationChanged(int p)
{
  if(iPopulation != p)
  {
    iPopulation = p;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  genome type spinbox was changed - set new genome type
 *
 *  @param g            new value from combobox
 */

void CWidgetEvolution::GenomeTypeChanged(int g)
{
  if(iGenomeType != g)
  {
    iGenomeType = g;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  direction combobox was changed - set new direction
 *
 *  @param d            new value from combobox
 */

void CWidgetEvolution::DirectionChanged(int d)
{
  if(iMoveDir != d)
  {
    iMoveDir = d;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  steps count spinbox was changed - set new steps count
 *
 *  @param s            new value from spinbox
 */

void CWidgetEvolution::StepsChanged(int s)
{
  if(iStepsCount != s)
  {
    iStepsCount = s;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  distance spinbox was changed - set new distance
 *
 *  @param d            new value from spinbox
 */

void CWidgetEvolution::DistanceChanged(int d)
{
  if(iMoveDis != d)
  {
    iMoveDis = d;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  crossover probability spinbox was changed - set new crossover prob
 *
 *  @param cp           new value from spinbox
 */

void CWidgetEvolution::CrossoverProbChanged(int cp)
{
  if(iCrossoverProb != cp)
  {
    iCrossoverProb = cp;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  crossover count spinbox was changed - set new crossover count
 *
 *  @param cc           new value from spinbox
 */

void CWidgetEvolution::CrossoverCountChanged(int cc)
{
  if(iCrossoverCount != cc)
  {
    iCrossoverCount = cc;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  mutation probability spinbox was changed - set new mutation prob
 *
 *  @param mp           new value from spinbox
 */

void CWidgetEvolution::MutationProbChanged(int mp)
{
  if(iMutationProb != mp)
  {
    iMutationProb = mp;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  mutation count spinbox was changed - set new mutation count
 *
 *  @param mc           new value from spinbox
 */

void CWidgetEvolution::MutationCountChanged(int mc)
{
  if(iMutationCount != mc)
  {
    iMutationCount = mc;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  import genome button is pressed
 */

void CWidgetEvolution::ImportFileButtonPressed()
{
  // open file dialog to set path/name of imported file
  importFile = QFileDialog::getOpenFileName(this,
                                            tr("Open file with chromosome"),
                                            QDir::currentPath(),
                                            tr("EvoDeMo Best Genome file (*.ebg)"));

  // path/name is empty - cancel in file dialog was pressed
  if(importFile.isEmpty())
  {
    ui->lineEditImportFile->setEnabled(false);
    ui->lineEditImportFile->setText("none file selected");

    ui->checkBoxImportSim->setEnabled(false);
    ui->checkBoxImportSim->setCheckState(Qt::Unchecked);

    ui->checkBoxImportReevo->setEnabled(false);
    ui->checkBoxImportReevo->setCheckState(Qt::Unchecked);

    bImportFileEnabledSimulation = false;
    bImportFileEnabledReevolve   = false;
  }
  else
  {
    ui->lineEditImportFile->setEnabled(true);
    ui->lineEditImportFile->setText(importFile);

    ui->checkBoxImportSim->setEnabled(true);
    ui->checkBoxImportSim->setCheckState(Qt::Checked);

    ui->checkBoxImportReevo->setEnabled(true);
    ui->checkBoxImportReevo->setCheckState(Qt::Unchecked);

    bImportFileEnabledSimulation = true;
    bImportFileEnabledReevolve   = false;
  }
}

//==============================================================
/**
 *  simulation checkbox changed it's state
 *
 *  @param ifes         current check state of simulation checkbox
 */

void CWidgetEvolution::ImportFileEnableSimulation(int ifes)
{
  // simulation is checked, so uncheck reevolve checkbox
  if(ifes == Qt::Checked)
  {
    bImportFileEnabledSimulation = true;

    if(bImportFileEnabledReevolve)
    {
      bImportFileEnabledReevolve = false;
      ui->checkBoxImportReevo->setCheckState(Qt::Unchecked);
    }
  }
  else
  {
    bImportFileEnabledSimulation = false;
  }
}

//==============================================================
/**
 *  re-evolve checkbox changed it's state
 *
 *  @param ifer         current check state of reevolve checkbox
 */

void CWidgetEvolution::ImportFileEnableReevolve(int ifer)
{
  // reevolution is checked, so uncheck simulation checkbox
  if(ifer == Qt::Checked)
  {
    bImportFileEnabledReevolve = true;

    if(bImportFileEnabledSimulation)
    {
      bImportFileEnabledSimulation = false;
      ui->checkBoxImportSim->setCheckState(Qt::Unchecked);
    }
  }
  else
  {
    bImportFileEnabledReevolve = false;
  }
}

//==============================================================
/**
 *  when apply is pressed disable all functional tools in widget
 */

void CWidgetEvolution::ApplyPressed()
{
  if(!bInitDone)
  {
    if(!bApplyed)
    {
      bApplyed = true;

      ui->spinBoxRepeats->setEnabled(false);
      ui->spinBoxGen->setEnabled(false);
      ui->spinBoxPop->setEnabled(false);
      ui->comboBoxGenType->setEnabled(false);

      ui->comboBoxDir->setEnabled(false);
      ui->spinBoxSteps->setEnabled(false);
      ui->spinBoxDistance->setEnabled(false);

      //ui->spinBoxCProb->setEnabled(false);
      //ui->spinBoxCCount->setEnabled(false);

      ui->spinBoxMProb->setEnabled(false);
      ui->spinBoxMCount->setEnabled(false);

      ui->checkBoxImportSim->setEnabled(false);
      ui->checkBoxImportReevo->setEnabled(false);
      ui->lineEditImportFile->setEnabled(false);
      ui->buttonLoad->setEnabled(false);

      ui->buttonCancel->setEnabled(true);
      ui->buttonApply->setEnabled(false);

      emit(SignalWidgetEvoApplayed(true));
    }
  }
  else
  {
    QMessageBox::information(this,
                             tr("Apply"),
                             tr("Initialization of Cellular Automata is done.\nDelete Cellular Automata first."),
                             QMessageBox::Ok);
  }
}

//==============================================================
/**
 *  when cancel is pressed, enable all functional tools in widget
 */

void CWidgetEvolution::CancelPressed()
{
  if(!bInitDone)
  {
    if(bApplyed)
    {
      bApplyed = false;

      ui->spinBoxRepeats->setEnabled(true);
      ui->spinBoxGen->setEnabled(true);
      ui->spinBoxPop->setEnabled(true);
      ui->comboBoxGenType->setEnabled(true);

      ui->comboBoxDir->setEnabled(true);
      ui->spinBoxSteps->setEnabled(true);
      ui->spinBoxDistance->setEnabled(true);

      //ui->spinBoxCProb->setEnabled(true);
      //ui->spinBoxCCount->setEnabled(true);

      ui->spinBoxMProb->setEnabled(true);
      ui->spinBoxMCount->setEnabled(true);

      if(importFile == "")
      {
        ui->checkBoxImportSim->setEnabled(false);
        ui->checkBoxImportReevo->setEnabled(false);
        ui->lineEditImportFile->setEnabled(false);
      }
      else
      {
        ui->checkBoxImportSim->setEnabled(true);
        ui->checkBoxImportReevo->setEnabled(true);
        ui->lineEditImportFile->setEnabled(true);
      }
      ui->buttonLoad->setEnabled(true);

      ui->buttonCancel->setEnabled(false);
      ui->buttonApply->setEnabled(true);

      emit(SignalWidgetEvoApplayed(false));
    }
  }
  else
  {
    QMessageBox::information(this,
                             tr("Cancel"),
                             tr("Initialization of Cellular Automata is done.\nDelete Cellular Automata first."),
                             QMessageBox::Ok);
  }
}

//==============================================================

