#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC = -IF:\\Program\\wxWidgets\\include -IF:\\Program\\cpptcl-1.1.3 -IF:\\Program\\Tcl\\include
CFLAGS = -Wall -std=gnu++11 -pipe -mthreads -D__GNUWIN32__ -D__WXMSW__ -DWXUSINGDLL -DwxUSE_UNICODE
RESINC = 
LIBDIR = -LF:\\Program\\Tcl\\lib
LIB = 
LDFLAGS = -mthreads -ltcl86

INC_DEBUG = $(INC) -IF:\Program\wxWidgets\lib\gcc_dll\mswud
CFLAGS_DEBUG = $(CFLAGS) -g -D__WXDEBUG__
RESINC_DEBUG = $(RESINC) -IF:\Program\wxWidgets\lib\gcc_dll\mswud
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR) -LF:\Program\wxWidgets\lib\gcc_dll
LIB_DEBUG = $(LIB)libwxmsw30ud.a
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG = 
OUT_DEBUG = bin\\Debug\\reversi_gui.exe

INC_RELEASE = $(INC) -IF:\Program\wxWidgets\lib\gcc_dll\mswu
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC) -IF:\Program\wxWidgets\lib\gcc_dll\mswu
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR) -LF:\Program\wxWidgets\lib\gcc_dll
LIB_RELEASE = $(LIB)libwxmsw30u.a
LDFLAGS_RELEASE =  -s $(LDFLAGS)
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\reversi_gui.exe

OBJ_DEBUG = $(OBJDIR_DEBUG)\\reversi_guiApp.o $(OBJDIR_DEBUG)\\type.o $(OBJDIR_DEBUG)\\tree.o $(OBJDIR_DEBUG)\\search.o $(OBJDIR_DEBUG)\\reversi_guiMain.o $(OBJDIR_DEBUG)\\cpptcl.o $(OBJDIR_DEBUG)\\reversi_gui.o $(OBJDIR_DEBUG)\\reversi.o $(OBJDIR_DEBUG)\\resource.o $(OBJDIR_DEBUG)\\pattern.o $(OBJDIR_DEBUG)\\flip.o

OBJ_RELEASE = $(OBJDIR_RELEASE)\\reversi_guiApp.o $(OBJDIR_RELEASE)\\type.o $(OBJDIR_RELEASE)\\tree.o $(OBJDIR_RELEASE)\\search.o $(OBJDIR_RELEASE)\\reversi_guiMain.o $(OBJDIR_RELEASE)\\cpptcl.o $(OBJDIR_RELEASE)\\reversi_gui.o $(OBJDIR_RELEASE)\\reversi.o $(OBJDIR_RELEASE)\\resource.o $(OBJDIR_RELEASE)\\pattern.o $(OBJDIR_RELEASE)\\flip.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG) md $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) -mwindows $(LIB_DEBUG)

$(OBJDIR_DEBUG)\\reversi_guiApp.o: reversi_guiApp.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c reversi_guiApp.cpp -o $(OBJDIR_DEBUG)\\reversi_guiApp.o

$(OBJDIR_DEBUG)\\type.o: type.cc
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c type.cc -o $(OBJDIR_DEBUG)\\type.o

$(OBJDIR_DEBUG)\\tree.o: tree.cc
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c tree.cc -o $(OBJDIR_DEBUG)\\tree.o

$(OBJDIR_DEBUG)\\search.o: search.cc
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c search.cc -o $(OBJDIR_DEBUG)\\search.o

$(OBJDIR_DEBUG)\\reversi_guiMain.o: reversi_guiMain.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c reversi_guiMain.cpp -o $(OBJDIR_DEBUG)\\reversi_guiMain.o

$(OBJDIR_DEBUG)\\cpptcl.o: cpptcl.cc
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c cpptcl.cc -o $(OBJDIR_DEBUG)\\cpptcl.o

$(OBJDIR_DEBUG)\\reversi_gui.o: reversi_gui.cc
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c reversi_gui.cc -o $(OBJDIR_DEBUG)\\reversi_gui.o

$(OBJDIR_DEBUG)\\reversi.o: reversi.cc
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c reversi.cc -o $(OBJDIR_DEBUG)\\reversi.o

$(OBJDIR_DEBUG)\\resource.o: resource.rc
	$(WINDRES) -i resource.rc -J rc -o $(OBJDIR_DEBUG)\\resource.o -O coff $(INC_DEBUG)

$(OBJDIR_DEBUG)\\pattern.o: pattern.cc
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c pattern.cc -o $(OBJDIR_DEBUG)\\pattern.o

$(OBJDIR_DEBUG)\\flip.o: flip.cc
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c flip.cc -o $(OBJDIR_DEBUG)\\flip.o

clean_debug: 
	cmd /c del /f $(OBJ_DEBUG) $(OUT_DEBUG)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG)

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE) md $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) -mwindows $(LIB_RELEASE)

$(OBJDIR_RELEASE)\\reversi_guiApp.o: reversi_guiApp.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c reversi_guiApp.cpp -o $(OBJDIR_RELEASE)\\reversi_guiApp.o

$(OBJDIR_RELEASE)\\type.o: type.cc
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c type.cc -o $(OBJDIR_RELEASE)\\type.o

$(OBJDIR_RELEASE)\\tree.o: tree.cc
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c tree.cc -o $(OBJDIR_RELEASE)\\tree.o

$(OBJDIR_RELEASE)\\search.o: search.cc
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c search.cc -o $(OBJDIR_RELEASE)\\search.o

$(OBJDIR_RELEASE)\\reversi_guiMain.o: reversi_guiMain.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c reversi_guiMain.cpp -o $(OBJDIR_RELEASE)\\reversi_guiMain.o

$(OBJDIR_RELEASE)\\cpptcl.o: cpptcl.cc
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c cpptcl.cc -o $(OBJDIR_RELEASE)\\cpptcl.o

$(OBJDIR_RELEASE)\\reversi_gui.o: reversi_gui.cc
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c reversi_gui.cc -o $(OBJDIR_RELEASE)\\reversi_gui.o

$(OBJDIR_RELEASE)\\reversi.o: reversi.cc
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c reversi.cc -o $(OBJDIR_RELEASE)\\reversi.o

$(OBJDIR_RELEASE)\\resource.o: resource.rc
	$(WINDRES) -i resource.rc -J rc -o $(OBJDIR_RELEASE)\\resource.o -O coff $(INC_RELEASE)

$(OBJDIR_RELEASE)\\pattern.o: pattern.cc
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c pattern.cc -o $(OBJDIR_RELEASE)\\pattern.o

$(OBJDIR_RELEASE)\\flip.o: flip.cc
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c flip.cc -o $(OBJDIR_RELEASE)\\flip.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

