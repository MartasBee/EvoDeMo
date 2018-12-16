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

#include "WidgetRunEvo.h"
#include "ui_WidgetRunEvo.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *parent      pointer to parent widget
 */

CWidgetRunEvo::CWidgetRunEvo(QWidget *parent) : QWidget(parent), ui(new Ui::CWidgetRunEvo)
{
  ui->setupUi(this);

  InitRun();
}

//==============================================================
/**
 *  class destructor
 */

CWidgetRunEvo::~CWidgetRunEvo()
{
  delete ui;
}

//==============================================================
//==============================================================
/**
 *  sets generation into lineEdit in gui
 *
 *  @param gen          generations
 */

void CWidgetRunEvo::SetGenerationID(int gen)
{
  ui->lineEditGen->setText(QString("%1").arg(gen));
}

//==============================================================
/**
 *  sets chromosome id into lineEdit in gui
 *
 *  @param chrom        chromosome id
 */

void CWidgetRunEvo::SetChromosomeID(int chrom)
{
  ui->lineEditChrom->setText(QString("%1").arg(chrom));
}

//==============================================================
/**
 *  sets ancestord count into lineEdit in gui
 *
 *  @param anc          ancestors count
 */

void CWidgetRunEvo::SetAncestorsCount(int anc)
{
  ui->lineEditAncestorsCount->setText(QString("%1").arg(anc));
}

//==============================================================
/**
 *  sets fitness max into lineEdit in gui
 *
 *  @param fit          fitness max
 */

void CWidgetRunEvo::SetFitnessMax(double fit)
{
  ui->lineEditFitMax->setText(QString("%1").arg(fit, 0, 'f', 3));
}

//==============================================================
/**
 *  sets differention min into lineEdit in gui
 *
 *  @param diff         differention min
 */

void CWidgetRunEvo::SetDifferentionMin(int diff)
{
  ui->lineEditDiffMin->setText(QString("%1").arg(diff));
}

//==============================================================
/**
 *  sets steps ca into lineEdit in gui
 *
 *  @param step         steps ca
 */

void CWidgetRunEvo::SetFitMaxStepCA(int step)
{
  ui->lineEditFitMaxStep->setText(QString("%1").arg(step));
}


//==============================================================
/**
 *  sets same chromosomes count into lineEdit in gui
 *
 *  @param chroms       same chromosomes count
 */

void CWidgetRunEvo::SetSameChromosomesCount(int chroms)
{
  ui->lineEditSameChromsCount->setText(QString("%1").arg(chroms));
}

//==============================================================
/**
 *  sets same chromosomes generation avarage into lineEdit in gui
 *
 *  @param avarage      same chromosomes generation avarage
 */

void CWidgetRunEvo::SetSameChromosomesGenerationAvarage(double avarage)
{
  ui->lineEditSCGensAvarage->setText(QString("%1").arg(avarage, 0, 'f', 3));
}

//==============================================================
//==============================================================
/**
 *  inits lineEdits
 */

void CWidgetRunEvo::InitRun()
{
  ui->lineEditGen->setText("-");
  ui->lineEditChrom->setText("-");
  ui->lineEditFitMax->setText("-");
  ui->lineEditDiffMin->setText("-");
  ui->lineEditFitMaxStep->setText("-");

  ui->lineEditAncestorsCount->setText("-");
  ui->lineEditSameChromsCount->setText("-");
  ui->lineEditSCGensAvarage->setText("-");
}

//==============================================================
/**
 *  clears lineEdits
 */

void CWidgetRunEvo::DeleteRun()
{
  InitRun();
  /*
  ui->lineEditGen->setText("-");
  ui->lineEditChrom->setText("-");
  ui->lineEditFitMax->setText("-");
  ui->lineEditDiffMin->setText("-");
  ui->lineEditFitMaxStep->setText("-");
  ui->lineEditMutGenTot->setText("-");
  ui->lineEditMutGenAnc->setText("-");

  ui->lineEditAncestorsCount->setText("-");
  ui->lineEditSameChromsCount->setText("-");
  ui->lineEditSCGensAvarage->setText("-");
  ui->lineEditSCMutGenAvarage->setText("-");
  */
}

//==============================================================
//==============================================================
/**
 *  change event happened
 *
 *  @param e            event
 */

void CWidgetRunEvo::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//==============================================================
//==============================================================

