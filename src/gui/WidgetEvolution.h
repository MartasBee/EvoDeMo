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

#ifndef WIDGETEVOLUTION_H
#define WIDGETEVOLUTION_H

//==============================================================

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

#include "../Defines.h"

//==============================================================

namespace Ui
{
  class CWidgetEvolution;
}

//==============================================================
/**
 *  settings of evolution and movement of object
 */

class CWidgetEvolution : public QWidget
{
  Q_OBJECT

public:
  CWidgetEvolution(QWidget *parent = 0);
  ~CWidgetEvolution();

  int GetRepetitionsCount();
  int GetGenerationsCount();
  int GetPopulationSize();
  int GetGenomeType();

  int GetCrossoverProbability();
  int GetCrossoverCount();
  int GetMutationProbability();
  int GetMutationCount();

  int GetMoveDirection();
  int GetStepsCount();
  int GetMoveDistance();

  bool    IsImportGenomeEnabledSimulation();
  bool    IsImportGenomeEnabledReevolve();
  QString GetImportGenomeFile();

  void SetRepetitionsCount(int rc);
  void SetGenerationsCount(int gc);
  void SetPopulationSize(int ps);
  void SetGenomeType(int gt);

  void SetCrossoverProbability(int cp);
  void SetCrossoverCount(int cc);
  void SetMutationProbability(int mp);
  void SetMutationCount(int mc);

  void SetMoveDirection(int md);
  void SetStepsCount(int sc);
  void SetMoveDistance(int md);

  bool IsApplyed();
  void SetInitDone(bool id);

signals:
  void SignalWidgetEvoApplayed(bool);

protected:
  void changeEvent(QEvent *e);

private slots:
  void RepetitionsChanged(int r);
  void GenerationsChanged(int g);
  void PopulationChanged(int p);
  void GenomeTypeChanged(int g);

  void DirectionChanged(int d);
  void StepsChanged(int s);
  void DistanceChanged(int d);

  void CrossoverProbChanged(int cp);
  void CrossoverCountChanged(int cc);

  void MutationProbChanged(int mp);
  void MutationCountChanged(int mc);

  void ImportFileButtonPressed();
  void ImportFileEnableSimulation(int ifes);
  void ImportFileEnableReevolve(int ifer);

  void ApplyPressed();
  void CancelPressed();

private:
  Ui::CWidgetEvolution *ui;             //!< pointer to widget (gui of this class)

  int iRepetitions;                     //!< repetitions - independent runs of evolution
  int iGenerations;                     //!< generations count
  int iPopulation;                      //!< population size
  int iStepsCount;                      //!< ca steps count
  int iCrossoverProb;                   //!< crossover probability
  int iCrossoverCount;                  //!< crossovers count
  int iMutationProb;                    //!< mutation probability
  int iMutationCount;                   //!< mutations count
  int iMoveDir;                         //!< movement direction
  int iMoveDis;                         //!< movement distance
  int iGenomeType;                      //!< genome type - 5nbh || 9nbh

  bool bApplyed;                        //!< is this widget applyed?
  bool bInitDone;                       //!< is app core init?

  QString importFile;                   //!< path/name to ga import file
  bool bImportFileEnabledSimulation;    //!< should be imported genome used for simulation?
  bool bImportFileEnabledReevolve;      //!< should be imported genome used for reevolution?
};

//==============================================================

#endif // WIDGETEVOLUTION_H

//==============================================================

