################################################################
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
################################################################

ifeq ($(OS), Windows_NT)
  REMOVE_FI = del /q
  REMOVE_FO = del /s /q
  PACKER    =
else
  REMOVE_FI = rm -f
  REMOVE_FO = rm -f -r
  PACKER    = tgz
endif

################################################################

all: release

################################################################

release: clean-all
	cd src && qmake "CONFIG+=release" && make

dev-release: clean-qt clean-bin
	cd src && qmake "CONFIG+=release" && make

################################################################

debug: clean-all
	cd src && qmake "CONFIG+=debug" && make

dev-debug: clean-qt clean-bin
	cd src && qmake "CONFIG+=debug" && make

################################################################

clean-qt:  clean-makefile clean-proj-files

clean:     clean-build clean-qt

clean-all: clean-bin clean

################################

clean-bin:
	$(REMOVE_FO) bin

clean-build:
	$(REMOVE_FO) build

clean-doc:
	$(REMOVE_FO) doc

clean-makefile:
	cd src && $(REMOVE_FI) Makefile Makefile*

clean-proj-files:
	cd src && $(REMOVE_FI) object_script* *.user

clean-tmp:
	cd src && $(REMOVE_FI) *~

clean-arch:
	cd ../ && $(REMOVE_FI) evodemo.zip evodemo.tar evodemo.tar.gz

################################################################

doxy:
	cd src && doxygen EvoDeMoDoxygenConfig.cnf

################################################################

pack: clean-arch clean-bin $(PACKER)

################################

zip: clean
	cd ../ && zip -r evodemo.zip EvoDeMo

tar: clean
	cd ../ && tar -cvf evodemo.tar EvoDeMo

tgz: clean
	cd ../ && tar -cvzf evodemo.tar.gz EvoDeMo

################################################################

