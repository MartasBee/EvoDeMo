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

#include "ConfigCore.h"

//==============================================================
/**
 *  class constructor
 *  initializes vars to default values
 */

CConfigCore::CConfigCore()
{
  SetSpaceType(SPACE_TYPE_GRID);

  SetSpaceSizeX(SPACE_SIZE_X_DEFAULT);
  SetSpaceSizeY(SPACE_SIZE_Y_DEFAULT);

  SetStatesCount(STATES_COUNT_DEFAULT);
  SetDefaultState(CELL_STATE_EMPTY);

  SetEvolutionRepetitionsCount(EVOLUTION_REPEATITIONS_DEFAULT);
  SetGenerationsCount(GENERATIONS_COUNT_DEFAULT);
  SetPopulationSize(POPULATION_INIT_DEFAULT);
  SetGenomeType(GENOME_TYPE_2_9N);

  SetCrossoverProbability(CROSSOVER_PROB_DEFAULT);
  SetCrossoverCount(CROSSOVER_COUNT_DEFAULT);
  SetMutationProbability(MUTATION_PROB_DEFAULT);
  SetMutationCount(MUTATION_COUNT_DEFAULT);

  SetMoveDirection(MOVE_DIR_ANY);
  SetStepsCountCA(STEPS_COUNT_MAX);
  SetMoveDistance(MOVE_DIS_DEFAULT);

  SetGuiDisplayModeCA(GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP);
  SetGuiDisplayModeCATimeout(GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_DEFAULT);

  SetExportFilePath("");
  SetExportFileModeCa(FILE_EX__CA_MODE__INIT_SPACE);
  SetExportFileModeGa(FILE_EX__GA_MODE__RUN_E__CHROM_B);

  SetImportGenomeEnabledSimulation(false);
  SetImportGenomeEnabledReevolve(false);
  SetImportGenomeFile("");

  SetExportLogCore(NULL);
}

//==============================================================
//==============================================================
/**
 *  sets ca space type
 *
 *  @param st           space type
 */

void CConfigCore::SetSpaceType(int st)
{
  if((st != SPACE_TYPE_GRID) && (st != SPACE_TYPE_TORUS))
    st = SPACE_TYPE_GRID;

  iSpaceType = (unsigned)st;
}

//==============================================================
/**
 *  returns ca space type
 */

int CConfigCore::GetSpaceType()
{
  return iSpaceType;
}

//==============================================================
//==============================================================
/**
 *  sets ca space width
 *
 *  @param x            ca space width
 */

void CConfigCore::SetSpaceSizeX(int x)
{
  if(x < SPACE_SIZE_X_MIN)
    x = SPACE_SIZE_X_MIN;
  else if(x > SPACE_SIZE_X_MAX)
    x = SPACE_SIZE_X_MAX;

  iSizeRunArrayX = (unsigned)x;
}

//==============================================================
/**
 *  returns ca space width
 */

int CConfigCore::GetSpaceSizeX()
{
  return iSizeRunArrayX;
}

//==============================================================
/**
 *  sets ca space height
 *
 *  @param y            ca space height
 */

void CConfigCore::SetSpaceSizeY(int y)
{
  if(y < SPACE_SIZE_Y_MIN)
    y = SPACE_SIZE_Y_MIN;
  else if(y > SPACE_SIZE_Y_MAX)
    y = SPACE_SIZE_Y_MAX;

  iSizeRunArrayY = (unsigned)y;
}

//==============================================================
/**
 *  returns ca space height
 */

int CConfigCore::GetSpaceSizeY()
{
  return iSizeRunArrayY;
}

//==============================================================
//==============================================================
/**
 *  sets ca states count
 *
 *  @param sc           ca states count
 */

void CConfigCore::SetStatesCount(int sc)
{
  if(sc < STATES_COUNT_MIN)
    sc = STATES_COUNT_MIN;
  else if(sc > STATES_COUNT_MAX)
    sc = STATES_COUNT_MAX;

  iStatesCount = (unsigned)sc;
}

//==============================================================
/**
 *  returns ca states count
 */

int CConfigCore::GetStatesCount()
{
  return iStatesCount;
}

//==============================================================
/**
 *  sets ca default state
 *
 *  @param ds           ca default state
 */

void CConfigCore::SetDefaultState(int ds)
{
  if((ds != CELL_STATE_EMPTY) &&
     (ds != CELL_STATE_LIVE_1) &&
     (ds != CELL_STATE_LIVE_2) &&
     (ds != CELL_STATE_LIVE_3))
    ds = CELL_STATE_EMPTY;

  byDefCellState = (BYTE)ds;
}

//==============================================================
/**
 *  returns ca default state
 */

BYTE CConfigCore::GetDefaultState()
{
  return byDefCellState;
}

//==============================================================
//==============================================================
/**
 *  sets independent runs of evolution
 *
 *  @param rc           independent runs count
 */

void CConfigCore::SetEvolutionRepetitionsCount(int rc)
{
  if(rc < EVOLUTION_REPEATITIONS_MIN)
    rc = EVOLUTION_REPEATITIONS_MIN;
  else if(rc > EVOLUTION_REPEATITIONS_MAX)
    rc = EVOLUTION_REPEATITIONS_MAX;

  iRepetitions = (unsigned)rc;
}

//==============================================================
/**
 *  returns count of independent runs of ca
 */

int CConfigCore::GetEvolutionRepetitionsCount()
{
  return iRepetitions;
}

//==============================================================
/**
 *  sets generations count
 *
 *  @param gc           generations count
 */

void CConfigCore::SetGenerationsCount(int gc)
{
  if(gc < GENERATIONS_COUNT_MIN)
    gc = GENERATIONS_COUNT_MIN;
  else if(gc > GENERATIONS_COUNT_MAX)
    gc = GENERATIONS_COUNT_MAX;

  iGenCount = (unsigned)gc;
}

//==============================================================
/**
 *  returns generations count
 */

int CConfigCore::GetGenerationsCount()
{
  return iGenCount;
}

//==============================================================
/**
 *  sets population size
 *
 *  @param ips          population size
 */

void CConfigCore::SetPopulationSize(int ips)
{
  if(ips < POPULATION_INIT_MIN)
    ips = POPULATION_INIT_MIN;
  else if(ips > POPULATION_INIT_MAX)
    ips = POPULATION_INIT_MAX;

  iPopulationSize = (unsigned)ips;
}

//==============================================================
/**
 *  returns population size
 */

int CConfigCore::GetPopulationSize()
{
  return iPopulationSize;
}

//==============================================================
//==============================================================
/**
 *  sets direction of movement
 *
 *  @param md           movement direction
 */

void CConfigCore::SetMoveDirection(int md)
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
    md = MOVE_DIR_ANY;

  iMoveDir = (unsigned)md;
}

//==============================================================
/**
 *  returns movement direction
 */

int CConfigCore::GetMoveDirection()
{
  return iMoveDir;
}

//==============================================================
/**
 *  sets number of ca steps needed to move object on given distance
 *
 *  @param sc           ca steps count
 */

void CConfigCore::SetStepsCountCA(int sc)
{
  if(sc < STEPS_COUNT_MIN)
    sc = STEPS_COUNT_MIN;
  else if(sc > STEPS_COUNT_MAX)
    sc = STEPS_COUNT_MAX;

  iStepsCountCA = (unsigned)sc;
}

//==============================================================
/**
 *  returns number of ca steps needed to move object on given distance
 */

int CConfigCore::GetStepsCountCA()
{
  return iStepsCountCA;
}

//==============================================================
/**
 *  sets distance (in cells) to which object should be moved
 *
 *  @param md           movement distance
 */

void CConfigCore::SetMoveDistance(int md)
{
  iDistance = md;
}

//==============================================================
/**
 *  returns distance (in cells) to which object should be moved
 */

int CConfigCore::GetMoveDistance()
{
  return iDistance;
}

//==============================================================
//==============================================================
/**
 *  sets crossover probability
 *
 *  @param cp           crossover probability
 */

void CConfigCore::SetCrossoverProbability(int cp)
{
  if(cp < CROSSOVER_PROB_MIN)
    cp = CROSSOVER_PROB_MIN;
  else if(cp > CROSSOVER_PROB_MAX)
    cp = CROSSOVER_PROB_MAX;

  iCrossoverProb = (unsigned)cp;
}

//==============================================================
/**
 *  returns crossover probability
 */

int CConfigCore::GetCrossoverProbability()
{
  return iCrossoverProb;
}

//==============================================================
/**
 *  sets count of crossovers between two genomes
 *
 *  @param cc           crossovers count
 */

void CConfigCore::SetCrossoverCount(int cc)
{
  if(cc < CROSSOVER_COUNT_MIN)
    cc = CROSSOVER_COUNT_MIN;
  else if(cc > CROSSOVER_COUNT_MAX)
    cc = CROSSOVER_COUNT_MAX;

  iCrossoverCount = (unsigned)cc;
}

//==============================================================
/**
 *  returns count of crossovers between two genomes
 */

int CConfigCore::GetCrossoverCount()
{
  return iCrossoverCount;
}

//==============================================================
/**
 *  sets mutation probability
 *
 *  @param mp           mutation probability
 */

void CConfigCore::SetMutationProbability(int mp)
{
  if(mp < MUTATION_PROB_MIN)
    mp = MUTATION_PROB_MIN;
  else if(mp > MUTATION_PROB_MAX)
    mp = MUTATION_PROB_MAX;

  iMutProb = (unsigned)mp;
}

//==============================================================
/**
 *  returns mutation probability
 */

int CConfigCore::GetMutationProbability()
{
  return iMutProb;
}

//==============================================================
/**
 *  sets number of genes which should be mutated
 *
 *  @param mc           mutated genes count
 */

void CConfigCore::SetMutationCount(int mc)
{
  if(mc < MUTATION_COUNT_MIN)
    mc = MUTATION_COUNT_MIN;
  else if(mc > MUTATION_COUNT_MAX)
    mc = MUTATION_COUNT_MAX;

  iMutCount = (unsigned)mc;
}

//==============================================================
/**
 *  returns number of genes which should be mutated
 */

int CConfigCore::GetMutationCount()
{
  return iMutCount;
}

//==============================================================
//==============================================================
/**
 *  sets genome type
 *
 *  @param gt           genome type
 */

void CConfigCore::SetGenomeType(int gt)
{
  if((gt != GENOME_TYPE_2_9N) &&
     (gt != GENOME_TYPE_3_9N) &&
     (gt != GENOME_TYPE_4_9N) &&
     (gt != GENOME_TYPE_2_5N) &&
     (gt != GENOME_TYPE_3_5N) &&
     (gt != GENOME_TYPE_4_5N))// &&
     //(gt != GENOME_TYPE_2_INS) &&
     //(gt != GENOME_TYPE_3_INS) &&
     //(gt != GENOME_TYPE_4_INS))
    gt = GENOME_TYPE_2_9N;

  iGenomeType = (unsigned)gt;
}

//==============================================================
/**
 *  returns genome tupe
 */

int CConfigCore::GetGenomeType()
{
  return iGenomeType;
}

//==============================================================
//==============================================================
/**
 *  sets gui display mode for ca
 *
 *  @param dm           display mode
 */

void CConfigCore::SetGuiDisplayModeCA(int dm)
{
  if((dm != GUI_DISPLAY_MODE_CA__NONE) &&
     //(dm != GUI_DISPLAY_MODE_CA__BEST_CHROM__B_STEP) &&
     //(dm != GUI_DISPLAY_MODE_CA__BEST_CHROM__E_STEP) &&
     //(dm != GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__B_STEP) &&
     //(dm != GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__L_STEP) &&
     //(dm != GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__E_STEP) &&
     (dm != GUI_DISPLAY_MODE_CA__RUN_E__BEST_CHROM__E_STEP) &&
     (dm != GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP) &&
     (dm != GUI_DISPLAY_MODE_CA__RUN_A__BEST_CHROM__E_STEP))
    dm = GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP;

  iGuiDisplayModeCa = (unsigned)dm;
}

//==============================================================
/**
 *  returns gui display mode for ca
 */

int CConfigCore::GetGuiDisplayModeCA()
{
  return iGuiDisplayModeCa;
}

//==============================================================
/**
 *  sets gui ca animation timeout (between two steps of ca in "Run" mode)
 *
 *  @param to           timeout
 */

void CConfigCore::SetGuiDisplayModeCATimeout(int to)
{
  if(to < GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MIN)
    to = GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MIN;
  else if(to > GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MAX)
    to = GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MAX;

  iGuiDisplayModeCaTimeout = (unsigned)to;
}

//==============================================================
/**
 *  returns gui ca animation timeout (between two steps of ca in "Run" mode)
 */

int CConfigCore::GetGuiDisplayModeCATimeout()
{
  return iGuiDisplayModeCaTimeout;
}

//==============================================================
//==============================================================
/**
 *  sets path to export folder
 *
 *  @param path         path to export folder
 */

void CConfigCore::SetExportFilePath(std::string path)
{
  sgExportFilePath = path;
}

//==============================================================
/**
 *  returns path to export folder
 */

std::string CConfigCore::GetExportFilePath()
{
  return sgExportFilePath;
}

//==============================================================
/**
 *  sets ca export mode
 *
 *  @param mode         ca export mode
 */

void CConfigCore::SetExportFileModeCa(int mode)
{
  if((mode != FILE_EX__CA_MODE_NONE) &&
     (mode != FILE_EX__CA_MODE__INIT_SPACE) &&
     (mode != FILE_EX__CA_MODE__IMPORT_SPACE) &&
     (mode != FILE_EX__CA_MODE__RUN_E__CHROM_B__STEP_E) &&
     (mode != FILE_EX__CA_MODE__RUN_B__CHROM_B__STEP_E))
    mode = FILE_EX__CA_MODE__INIT_SPACE;

  iExportFileModeCa = mode;
}

//==============================================================
/**
 *  returns ca export mode
 */

int CConfigCore::GetExportFileModeCa()
{
  return iExportFileModeCa;
}

//==============================================================
/**
 *  sets ga export mode
 *
 *  @param mode         ga export mode
 */

void CConfigCore::SetExportFileModeGa(int mode)
{
  if((mode != FILE_EX__GA_MODE_NONE) &&
     (mode != FILE_EX__GA_MODE__RUN_E__CHROM_A)  &&
     (mode != FILE_EX__GA_MODE__RUN_E__CHROM_B) &&
     (mode != FILE_EX__GA_MODE__RUN_B__CHROM_B))
    mode = FILE_EX__GA_MODE__RUN_E__CHROM_B;

  iExportFileModeGa = mode;
}

//==============================================================
/**
 *  returns ga export mode
 */

int CConfigCore::GetExportFileModeGa()
{
  return iExportFileModeGa;
}

//==============================================================
//==============================================================
/**
 *  sets imported genome file path/name
 *
 *  @param file         imported genome path/name
 */

void CConfigCore::SetImportGenomeFile(std::string file)
{
  sgImportFileGenome = file;
}

//==============================================================
/**
 *  returns imported genome file path/name
 */

std::string CConfigCore::GetImportGenomeFile()
{
  return sgImportFileGenome;
}

//==============================================================
/**
 *  sets if genome should be used in ca simulator
 *
 *  @param e            enable usage in ca simulator
 */

void CConfigCore::SetImportGenomeEnabledSimulation(bool e)
{
  bImportFileEnabledSimulation = e;
}

//==============================================================
/**
 *  returns if genome should be used in ca simulator
 */

bool CConfigCore::IsImportGenomeEnabledSimulation()
{
  return bImportFileEnabledSimulation;
}

//==============================================================
/**
 *  sets if imported genome should be re-evolved
 *
 *  @param e            enable re-evolution
 */

void CConfigCore::SetImportGenomeEnabledReevolve(bool e)
{
  bImportFileEnabledReevolve = e;
}

//==============================================================
/**
 *  returns if imported genome should be re-evolved
 */

bool CConfigCore::IsImportGenomeEnabledReevolve()
{
  return bImportFileEnabledReevolve;
}

//==============================================================
/**
 *  sets pointer to one and only instance of error log export class
 *
 *  @param *ex          pointer to log class
 */

void CConfigCore::SetExportLogCore(CExportLog *ex)
{
  pExportLogCore = ex;
}

//==============================================================
/**
 *  returns pointer to one and only instance of error log export class
 */

CExportLog* CConfigCore::GetExportLogCore()
{
  return pExportLogCore;
}

//==============================================================

