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

#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

//==============================================================

#include <QWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QSlider>
#include <QToolButton>
#include <QMessageBox>

#include "../Defines.h"

//==============================================================
/**
 *  class creates view to scene with cells
 */

class CGraphicsView : public QWidget
{
  Q_OBJECT

public:
  CGraphicsView(QWidget *parent = 0);

  QGraphicsView *view() const;

  QSize minimumSizeHint() const;

private slots:
  void setupMatrix();

  void zoomIn();
  void zoomOut();

private:
  QGraphicsView *graphicsView;  //!< pointer to graphics view class

  QSlider *sliderZoom;          //!< zoom slider
};

//==============================================================

#endif // GRAPHICSVIEW_H

//==============================================================

