# -------------------------------------------------
#
#  Project:      EvoDeMo - Bachelor Thesis
#  Date:         May 10, 2010 (estimated)
##
#  Author:       Martin Balaz
#  Contact:      balaz.marti@gmail.com
#                xbalaz00@stud.fit.vutbr.cz
##
#  Institution:  Brno University of Technology
#                Faculty of Information Technology
#                www.fit.vutbr.cz
##
#  Copyright (c) 2010 by Martin Balaz
#
# -------------------------------------------------

TARGET = EvoDeMo

# -------------------------------------------------

TEMPLATE = app

# -------------------------------------------------

DESTDIR = ../bin
OBJECTS_DIR = ../build/
MOC_DIR = ../build/moc
UI_DIR = ../build/ui

# -------------------------------------------------
# __DEBUG__
# __DEBUG_SHOW_SETTINGS__

#debug {
#  DEFINES +=
#}

# -------------------------------------------------

SOURCES += Application.cpp \
    gui/WindowMain.cpp \
    gui/GraphicsItem.cpp \
    gui/GraphicsItemConfig.cpp \
    gui/GraphicsScene.cpp \
    gui/GraphicsView.cpp \
    gui/WidgetInput.cpp \
    gui/WidgetOutput.cpp \
    gui/WidgetEvolution.cpp \
    gui/WidgetExport.cpp \
    gui/WidgetRunCA.cpp \
    gui/WidgetRunEvo.cpp \
    ca/space/Array2d.cpp \
    ca/space/Space.cpp \
    ca/CellularAutomata.cpp \
    ca/TFunction.cpp \
    ca/RulesTable.cpp \
    ga/genome/GenomeType2.cpp \
    ga/genome/GenomeType3.cpp \
    ga/genome/GenomeType4.cpp \
    ga/genome/GenomeType2_Nbh5.cpp \
    ga/genome/GenomeType3_Nbh5.cpp \
    ga/genome/GenomeType4_Nbh5.cpp \
    ga/genome/GenomeType2_Ins.cpp \
    ga/Genome.cpp \
    ga/GeneticAlgorithm.cpp \
    ga/Crossover.cpp \
    ga/Mutation.cpp \
    ga/Fitness.cpp \
    ga/Random.cpp \
    ga/Selection.cpp \
    Core.cpp \
    ConfigCore.cpp \
    ThreadCore.cpp \
    ExportGA.cpp \
    ExportCA.cpp \
    ExportLog.cpp \
    ExportConfig.cpp \
    ImportGA.cpp \
    ImportConfig.cpp \
    InputCA.cpp
HEADERS += Defines.h \
    gui/WindowMain.h \
    gui/GraphicsItem.h \
    gui/GraphicsItemConfig.h \
    gui/GraphicsScene.h \
    gui/GraphicsView.h \
    gui/WidgetInput.h \
    gui/WidgetOutput.h \
    gui/WidgetEvolution.h \
    gui/WidgetExport.h \
    gui/WidgetRunCA.h \
    gui/WidgetRunEvo.h \
    ca/space/Array2d.h \
    ca/space/Space.h \
    ca/CellularAutomata.h \
    ca/TFunction.h \
    ca/RulesTable.h \
    ga/genome/GenomeType2.h \
    ga/genome/GenomeType3.h \
    ga/genome/GenomeType4.h \
    ga/genome/GenomeType2_Nbh5.h \
    ga/genome/GenomeType3_Nbh5.h \
    ga/genome/GenomeType4_Nbh5.h \
    ga/genome/GenomeType2_Ins.h \
    ga/Genome.h \
    ga/GeneticAlgorithm.h \
    ga/Crossover.h \
    ga/Mutation.h \
    ga/Fitness.h \
    ga/Random.h \
    ga/Selection.h \
    Core.h \
    ConfigCore.h \
    ThreadCore.h \
    ExportGA.h \
    ExportCA.h \
    ExportLog.h \
    ExportConfig.h \
    ImportGA.h \
    ImportConfig.h \
    InputCA.h
FORMS += gui/forms/WindowMain.ui \
    gui/forms/WidgetInput.ui \
    gui/forms/WidgetOutput.ui \
    gui/forms/WidgetEvolution.ui \
    gui/forms/WidgetExport.ui \
    gui/forms/WidgetRunCA.ui \
    gui/forms/WidgetRunEvo.ui

