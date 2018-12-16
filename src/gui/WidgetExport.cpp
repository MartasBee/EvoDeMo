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

#include "WidgetExport.h"
#include "ui_WidgetExport.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *parent      pointer to parent widget
 */

CWidgetExport::CWidgetExport(QWidget *parent) : QWidget(parent), ui(new Ui::CWidgetExport)
{
  bApplyed  = false;
  bInitDone = false;

  iGuiModeCA_Timeout     = GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_DEFAULT;
  iGuiModeCA_DisplayMode = GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP;

  actPath = QDir::currentPath();
  tmpPath = actPath;

  iExportModeCA = FILE_EX__CA_MODE__INIT_SPACE;
  iExportModeGA = FILE_EX__GA_MODE__RUN_E__CHROM_B;


  ui->setupUi(this);


  ui->spinBoxGuiCATimeout->setMinimum(GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MIN);
  ui->spinBoxGuiCATimeout->setMaximum(GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MAX);
  ui->spinBoxGuiCATimeout->setToolTip("Timeout Between 2 Steps of CA in \"Run\" Mode\n(miliseconds)");
  ui->spinBoxGuiCATimeout->setSingleStep(100);
  ui->spinBoxGuiCATimeout->setValue(iGuiModeCA_Timeout);

  ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__NONE,                      "None");
  ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__RUN_E__BEST_CHROM__E_STEP, "Best Genome - Every Evolution Run");
  ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP, "Best Genome - Best Evolution Run");

  //ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__RUN_A__BEST_CHROM__E_STEP, "Best genome - Every & Best run");
  //ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__BEST_CHROM__B_STEP,     "Best genome - Best step");
  //ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__BEST_CHROM__E_STEP,     "Best genome - Every step");
  //ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__B_STEP, "Every genome - Best step");
  //ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__L_STEP, "Every genome - Last step");
  //ui->comboBoxGuiCAMode->insertItem(GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__E_STEP, "Every genome - Every step");
  ui->comboBoxGuiCAMode->setCurrentIndex(iGuiModeCA_DisplayMode);

  ui->lineEditFile->setText(actPath);

  ui->comboBoxFileCA->insertItem(FILE_EX__CA_MODE_NONE,                    "None");
  ui->comboBoxFileCA->insertItem(FILE_EX__CA_MODE__INIT_SPACE,             "Initial Space");
  ui->comboBoxFileCA->insertItem(FILE_EX__CA_MODE__IMPORT_SPACE,           "Imported Space");
  //ui->comboBoxFileCA->insertItem(FILE_EX__CA_MODE__RUN_E__CHROM_B__STEP_E, "Best Genome - Every Evolution Run");
  //ui->comboBoxFileCA->insertItem(FILE_EX__CA_MODE__RUN_B__CHROM_B__STEP_E, "Best Genome - Best Evolution Run");
  ui->comboBoxFileCA->setCurrentIndex(iExportModeCA);

  ui->comboBoxFileGA->insertItem(FILE_EX__GA_MODE_NONE,            "None");
  ui->comboBoxFileGA->insertItem(FILE_EX__GA_MODE__RUN_E__CHROM_A, "Every Evolution Run - All Genomes");
  ui->comboBoxFileGA->insertItem(FILE_EX__GA_MODE__RUN_E__CHROM_B, "Every Evolution Run - Best Genome");
  ui->comboBoxFileGA->insertItem(FILE_EX__GA_MODE__RUN_B__CHROM_B, "Best Evolution Run - Best Genome");
  ui->comboBoxFileGA->setCurrentIndex(iExportModeGA);


  ui->buttonCancel->setEnabled(false);


  connect(ui->spinBoxGuiCATimeout, SIGNAL(valueChanged(int)),        this, SLOT(GuiModeCATimeoutChanged(int)));
  connect(ui->comboBoxGuiCAMode,   SIGNAL(currentIndexChanged(int)), this, SLOT(GuiModeCADisplayModeChanged(int)));

  connect(ui->buttonFilePath, SIGNAL(pressed()),                this, SLOT(FileExportPathChanged()));
  connect(ui->comboBoxFileCA, SIGNAL(currentIndexChanged(int)), this, SLOT(FileExportCAChanged(int)));
  connect(ui->comboBoxFileGA, SIGNAL(currentIndexChanged(int)), this, SLOT(FileExportGAChanged(int)));

  connect(ui->buttonApply,  SIGNAL(pressed()), this, SLOT(ApplyPressed()));
  connect(ui->buttonCancel, SIGNAL(pressed()), this, SLOT(CancelPressed()));
}

//==============================================================
/**
 *  class destructor
 */

CWidgetExport::~CWidgetExport()
{
  delete ui;
}

//==============================================================
//==============================================================
/**
 *  returns animation timeout
 */

int CWidgetExport::GetGuiDataDisplayModeTimeout()
{
  return iGuiModeCA_Timeout;
}

//==============================================================
/**
 *  returns simulatior gddm
 */

int CWidgetExport::GetGuiDataDisplayModeCA()
{
  return iGuiModeCA_DisplayMode;
}

//==============================================================
/**
 *  returns path to export folder
 */

QString CWidgetExport::GetFileExportPath()
{
  return actPath;
}

//==============================================================
/**
 *  returns ca export mode
 */

int CWidgetExport::GetFileExportModeCA()
{
  return iExportModeCA;
}

//==============================================================
/**
 *  returns ga export mode
 */

int CWidgetExport::GetFileExportModeGA()
{
  return iExportModeGA;
}

//==============================================================
/**
 *  was apply button pressed?
 */

bool CWidgetExport::IsApplyed()
{
  return bApplyed;
}

//==============================================================
/**
 *  button init changed state - enable/disable any changes in widget
 */

void CWidgetExport::SetInitDone(bool id)
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
 *  sets animation timeout - used as extern call - when settings are loaded from file
 *
 *  @param to           new animation timeout
 */

void CWidgetExport::SetGuiDataDisplayModeTimeout(int to)
{
  if((to < GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MIN) ||
     (to > GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MAX))
    return;

  ui->spinBoxGuiCATimeout->setValue(to);

  GuiModeCATimeoutChanged(ui->spinBoxGuiCATimeout->value());
}

//==============================================================
/**
 *  sets simulatior gddm - used as extern call - when settings are loaded from file
 *
 *  @param dm           new gddm ca
 */

void CWidgetExport::SetGuiDataDisplayModeCA(int dm)
{
  if((dm != GUI_DISPLAY_MODE_CA__NONE) &&
     (dm != GUI_DISPLAY_MODE_CA__RUN_E__BEST_CHROM__E_STEP) &&
     (dm != GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP) &&
     (dm != GUI_DISPLAY_MODE_CA__RUN_A__BEST_CHROM__E_STEP))
    return;

  ui->comboBoxGuiCAMode->setCurrentIndex(dm);

  GuiModeCADisplayModeChanged(ui->comboBoxGuiCAMode->currentIndex());
}

//==============================================================
//==============================================================
/**
 *  sets ca export mode - used as extern call - when settings are loaded from file
 *
 *  @param mca          new ca export mode
 */

void CWidgetExport::SetFileExportModeCA(int mca)
{
  if((mca != FILE_EX__CA_MODE_NONE) &&
     (mca != FILE_EX__CA_MODE__INIT_SPACE) &&
     (mca != FILE_EX__CA_MODE__IMPORT_SPACE) &&
     (mca != FILE_EX__CA_MODE__RUN_E__CHROM_B__STEP_E) &&
     (mca != FILE_EX__CA_MODE__RUN_B__CHROM_B__STEP_E))
    return;

  ui->comboBoxFileCA->setCurrentIndex(mca);

  FileExportCAChanged(ui->comboBoxFileCA->currentIndex());
}

//==============================================================
/**
 *  sets ga export mode - used as extern call - when settings are loaded from file
 *
 *  @param mga          new ga export mode
 */

void CWidgetExport::SetFileExportModeGA(int mga)
{
  if((mga != FILE_EX__GA_MODE_NONE) &&
     (mga != FILE_EX__GA_MODE__RUN_E__CHROM_A)  &&
     (mga != FILE_EX__GA_MODE__RUN_E__CHROM_B) &&
     (mga != FILE_EX__GA_MODE__RUN_B__CHROM_B))
    return;

  ui->comboBoxFileGA->setCurrentIndex(mga);

  FileExportGAChanged(ui->comboBoxFileGA->currentIndex());
}

//==============================================================
//==============================================================
/**
 *  change event happened
 *
 *  @param e            event
 */

void CWidgetExport::changeEvent(QEvent *e)
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
/**
 *  simulatior animation timeout changed
 *
 *  @param t            new timeout
 */

void CWidgetExport::GuiModeCATimeoutChanged(int t)
{
  if(iGuiModeCA_Timeout != (unsigned)t)
  {
    iGuiModeCA_Timeout = (unsigned)t;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  simulatior display mode was changed
 *
 *  @param ca           new simualtor dispaly mode from combobox
 */

void CWidgetExport::GuiModeCADisplayModeChanged(int ca)
{
  if(iGuiModeCA_DisplayMode != ca)
  {
    iGuiModeCA_DisplayMode = ca;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  export path button was pressed - get new export path
 */

void CWidgetExport::FileExportPathChanged()
{
  // get export path
  tmpPath = QFileDialog::getExistingDirectory(this,
                                              tr("Select export directory"),
                                              actPath,
                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  // export path is empty - cancel in file dialog was pressed
  if(tmpPath.isEmpty())
    tmpPath = actPath;
  else
    actPath = tmpPath;

  ui->lineEditFile->setText(tmpPath);

  if(!ui->buttonApply->isEnabled())
    ui->buttonApply->setEnabled(true);
}

//==============================================================
/**
 *  ca export mode was changed
 *
 *  @param index        new mode from combobox
 */

void CWidgetExport::FileExportCAChanged(int index)
{
  if(iExportModeCA != index)
  {
    iExportModeCA = index;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
/**
 *  ga export mode was changed
 *
 *  @param index        new mode from combobox
 */

void CWidgetExport::FileExportGAChanged(int index)
{
  if(iExportModeGA != index)
  {
    iExportModeGA = index;

    if(!ui->buttonApply->isEnabled())
      ui->buttonApply->setEnabled(true);
  }
}

//==============================================================
//==============================================================
/**
 *  when apply is pressed disable all functional tools in widget
 */

void CWidgetExport::ApplyPressed()
{
  if(!bInitDone)
  {
    if(!bApplyed)
    {
      bApplyed = true;

      ui->spinBoxGuiCATimeout->setEnabled(false);
      ui->comboBoxGuiCAMode->setEnabled(false);

      ui->lineEditFile->setEnabled(false);
      ui->buttonFilePath->setEnabled(false);
      ui->comboBoxFileCA->setEnabled(false);
      ui->comboBoxFileGA->setEnabled(false);

      ui->buttonCancel->setEnabled(true);
      ui->buttonApply->setEnabled(false);

      emit(SignalWidgetExportApplyed(true));
    }
  }
}

//==============================================================
/**
 *  when cancel is pressed, enable all functional tools in widget
 */

void CWidgetExport::CancelPressed()
{
  if(!bInitDone)
  {
    if(bApplyed)
    {
      bApplyed = false;

      ui->spinBoxGuiCATimeout->setEnabled(true);
      ui->comboBoxGuiCAMode->setEnabled(true);

      ui->lineEditFile->setEnabled(true);
      ui->buttonFilePath->setEnabled(true);
      ui->comboBoxFileCA->setEnabled(true);
      ui->comboBoxFileGA->setEnabled(true);

      ui->buttonCancel->setEnabled(false);
      ui->buttonApply->setEnabled(true);

      emit(SignalWidgetExportApplyed(false));
    }
  }
}

//==============================================================

