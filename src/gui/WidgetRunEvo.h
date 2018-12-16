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

#ifndef WIDGETRUNEVO_H
#define WIDGETRUNEVO_H

//==============================================================

#include <QWidget>

//==============================================================

namespace Ui
{
  class CWidgetRunEvo;
}

//==============================================================
/**
 *  simulator current chromosome widget
 */

class CWidgetRunEvo : public QWidget
{
  Q_OBJECT

public:
  CWidgetRunEvo(QWidget *parent = 0);
  ~CWidgetRunEvo();

  void SetGenerationID(int gen);
  void SetChromosomeID(int chrom);
  void SetAncestorsCount(int anc);
  void SetFitnessMax(double fit);
  void SetDifferentionMin(int diff);
  void SetFitMaxStepCA(int step);
  void SetSameChromosomesCount(int chroms);
  void SetSameChromosomesGenerationAvarage(double avarage);

  void InitRun();
  void DeleteRun();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::CWidgetRunEvo *ui;  //!< pointer to widget (gui of this class)
};

//==============================================================

#endif // WIDGETRUNEVO_H

//==============================================================

