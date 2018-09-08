P = beer-thermometer 

SRCDIR = src
HDIR = include
BINDIR = bin
OBJDIR = obj
DOCDIR = doc
EASYMSPDIR = easymsp
EASYMSP = $(EASYMSPDIR)/bin/libeasymsp.a

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(HDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

AR = ar
CC = gcc
CROSS = msp430
CROSS_COMPILE = ${CROSS}-${CC}
CROSS_AR = ${CROSS}-${AR}
MACHINEFLAGS=-mmcu=msp430g2553
CFLAGS = -Os -g -Iinclude -Ieasymsp/include -Wextra -std=c99 $(MACHINEFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CROSS_COMPILE) -c -o $@ $< $(CFLAGS)

$(EASYMSP):
	cd $(EASYMSPDIR); make
	
$(BINDIR)/$(P) : folders $(OBJECTS) $(EASYMSP)
	$(CROSS_COMPILE) $(OBJDIR)/main.o $(EASYMSP) $(MACHINEFLAGS) -o $(BINDIR)/$(P)
		
$(BINDIR):
	mkdir $(BINDIR)
			
$(OBJDIR):
	mkdir $(OBJDIR)
				
$(DOCDIR):
	mkdir $(DOCDIR)
					
folders : $(BINDIR) $(OBJDIR)

firmware : $(BINDIR)/$(P)

install : $(BINDIR)/$(P)
	mspdebug rf2500 "prog bin/$(P)"


clean : $(BINDIR)/$(P) $(FOLDERS)
	rm -f $(OBJDIR)/*.o $(BINDIR)/*.hex $(BINDIR)/*.elf
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)
	rm -rf $(DOCDIR)
													
serial : $(BINDIR)/$(P)
	screen /dev/ttyACM0 115200 
								
												
documentation : $(DOCDIR) $(SOURCES) $(INCLUDES)
	doxygen Doxyfile

git : 
	git add include/*.h src/*.c Makefile .gitignore Doxyfile
	git status
