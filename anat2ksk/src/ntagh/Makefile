CXX=g++
LD=g++

CXXFLAGS += -Wall -g $(shell root-config --cflags)
CXXFLAGS += -I./inc
CXXFLAGS += -fPIC

LDFLAGS += -g $(shell root-config --ldflags) $(shell root-config --libs) -lTreePlayer -lXMLIO
LDFLAGS += -shared

TARGET=libntagh.so
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
