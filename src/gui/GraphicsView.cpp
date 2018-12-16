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

#include "GraphicsView.h"

//==============================================================
/**
 *  class constructor
 *
 *  @param *parent      parent widget
 */

CGraphicsView::CGraphicsView(QWidget *parent) : QWidget(parent)
{
  //setFrameStyle(Sunken | StyledPanel);

  // create view
  graphicsView = new QGraphicsView;
  graphicsView->setRenderHint(QPainter::Antialiasing, false);
  graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
  graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
  graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);


  // zoom in button
  QToolButton *buttonZoomIn = new QToolButton;
  buttonZoomIn->setAutoRepeat(true);
  buttonZoomIn->setAutoRepeatInterval(33);
  buttonZoomIn->setAutoRepeatDelay(0);
  //buttonZoomIn->setIcon(QPixmap(":/zoomin.png"));
  //buttonZoomIn->setIconSize(iconSize);

  // zoom out button
  QToolButton *buttonZoomOut = new QToolButton;
  buttonZoomOut->setAutoRepeat(true);
  buttonZoomOut->setAutoRepeatInterval(33);
  buttonZoomOut->setAutoRepeatDelay(0);
  //buttonZoomOut->setIcon(QPixmap(":/zoomout.png"));
  //buttonZoomOut->setIconSize(iconSize);

  // zoom slider
  sliderZoom = new QSlider;
  sliderZoom->setMinimum(20);
  sliderZoom->setMaximum(100);
  sliderZoom->setValue(40);
  sliderZoom->setTickPosition(QSlider::TicksRight);

  // Zoom slider layout
  QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
  zoomSliderLayout->addWidget(buttonZoomIn);
  zoomSliderLayout->addWidget(sliderZoom);
  zoomSliderLayout->addWidget(buttonZoomOut);


  QGridLayout *topLayout = new QGridLayout;
  topLayout->addWidget(graphicsView, 0, 0);
  topLayout->addLayout(zoomSliderLayout, 0, 1);
  setLayout(topLayout);


  connect(sliderZoom,    SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
  connect(buttonZoomIn,  SIGNAL(clicked()),         this, SLOT(zoomIn()));
  connect(buttonZoomOut, SIGNAL(clicked()),         this, SLOT(zoomOut()));


  setupMatrix();
}

//==============================================================
//==============================================================
/**
 *  returns pointer to graphics view
 */

QGraphicsView *CGraphicsView::view() const
{
  return graphicsView;
}

//==============================================================
/**
 *  sets minimum size of view widget
 */

QSize CGraphicsView::minimumSizeHint() const
{
  return QSize(400,250);
}

//==============================================================
//==============================================================
/**
 *  scene zooming
 */

void CGraphicsView::setupMatrix()
{
  qreal scale = (sliderZoom->value() / qreal(100));

  QMatrix matrix;
  matrix.scale(scale, scale);
  matrix.rotate(0);

  graphicsView->setMatrix(matrix);
  //setResetButtonEnabled();
}

//==============================================================
/**
 *  sets zoom slider when zoom in button is pressed
 */

void CGraphicsView::zoomIn()
{
  sliderZoom->setValue(sliderZoom->value() + 1);
}

//==============================================================
/**
 *  sets zoom slider when zoom out button is pressed
 */

void CGraphicsView::zoomOut()
{
  sliderZoom->setValue(sliderZoom->value() - 1);
}

//==============================================================

