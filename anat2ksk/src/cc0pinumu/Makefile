CXX=g++
LD=g++

CXXFLAGS += -Wall -g $(shell root-config --cflags)
CXXFLAGS += -I./inc
CXXFLAGS += -I$(ANAT2KSK_ROOTANAT2KSK_ROOT)/include
CXXFLAGS += -I$(ATMPD_ROOT)/include
CXXFLAGS += -fPIC
CXXFLAGS += -std=c++11

LDFLAGS += -g $(shell root-config --ldflags) $(shell root-config --libs) -lTreePlayer -lXMLIO
LDFLAGS += -L$(ATMPD_ROOT)/lib -lThreeProb
LDFLAGS += -shared

TARGET=libcc0pinumu.so
SRCDIR = ./src
OBJDIR = ./obj

SRCS = $(wildcard $(SRCDIR)/*.cc)
OBJCTS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cc=.o)))


.PHONY: clean all

all: $(OBJCTS)
	$(LD) $(LDFLAGS) $(OBJCTS) -o $(TARGET)
	@echo "$@ done"
	@mv $(TARGET) ./../../lib/

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@[ -d $(OBJDIR) ]
	$(LD) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)
