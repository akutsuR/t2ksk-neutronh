include $(SKOFL_ROOT)/config.gmk

LOCAL_LIBS += -L$(ANAT2KSK_ROOT)/lib -lntagh -lcc0pinumu
LOCAL_LIBS += -L$(ATMPD_ROOT)/lib -lThreeProb
LOCAL_INC += -I$(ANAT2KSK_ROOT)/include
LOCAL_INC += -I./../include

CXXFLAGS += -std=c++11

OBJS_1	=CmdLineArgParser.o \
		 NominalDist.o \
		 AltMCDist.o \
		 VertexDistributions.o \
		 MCTruthDistributions.o \
		 ToyTagging.o \
		 AltMCReducTree.o


EXEC_FILES = NeutronCount.exe\
		     mrgExtraCC0PiNumuBrkDwn.exe\
			 measureNeutrons.exe
			 
all: $(EXEC_FILES)

NeutronCount.exe: NeutronCount.o $(OBJS_1) 
	$(RM) ./../bin/$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)
	$(MV) $@ ./../bin/

mrgExtraCC0PiNumuBrkDwn.exe: mrgExtraCC0PiNumuBrkDwn.o copyFiles.o VertexDistributions.o MCTruthDistributions.o
	$(RM) ./../bin/$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)
	$(MV) $@ ./../bin/

measureNeutrons.exe: measureNeutrons.o
	$(RM) ./../bin/$@
	LD_RUN_PATH=$(LIBDIR):$(SKOFL_LIBDIR) $(CXX) -g $(CXXFLAGS) -o $@ $^ $(LDLIBS)
	$(MV) $@ ./../bin/

clean:
	$(RM) *.o ./../bin/*.exe $(OBJS) $(EXEC_FILES)
