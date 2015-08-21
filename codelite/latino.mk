##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=latino
ConfigurationName      :=Debug
WorkspacePath          := "C:\Users\proman02\Documents\GitHub\latino\codelite"
ProjectPath            := "C:\Users\proman02\Documents\GitHub\latino\codelite"
IntermediateDirectory  :=../bin
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=proman02
Date                   :=19/08/2015
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=c:/mingw/bin/g++.exe
SharedObjectLinkerName :=c:/mingw/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="latino.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=c:/mingw/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := c:/mingw/bin/ar.exe rcu
CXX      := c:/mingw/bin/g++.exe
CC       := c:/mingw/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := c:/mingw/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
Objects0=$(IntermediateDirectory)/src_eval.c$(ObjectSuffix) $(IntermediateDirectory)/src_latino.c$(ObjectSuffix) $(IntermediateDirectory)/src_lex.c$(ObjectSuffix) $(IntermediateDirectory)/src_parse.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "../bin"

PreBuild:
	@echo Executing Pre Build commands ...
	bison -y -o ../src/parse.c ../src/parse.y
	flex -o ../src/lex.c -i ../src/lex.l
	@echo Done


##
## Objects
##
$(IntermediateDirectory)/src_eval.c$(ObjectSuffix): ../src/eval.c $(IntermediateDirectory)/src_eval.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/Documents/GitHub/latino/src/eval.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_eval.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_eval.c$(DependSuffix): ../src/eval.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_eval.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_eval.c$(DependSuffix) -MM "../src/eval.c"

$(IntermediateDirectory)/src_eval.c$(PreprocessSuffix): ../src/eval.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_eval.c$(PreprocessSuffix) "../src/eval.c"

$(IntermediateDirectory)/src_latino.c$(ObjectSuffix): ../src/latino.c $(IntermediateDirectory)/src_latino.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/Documents/GitHub/latino/src/latino.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_latino.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_latino.c$(DependSuffix): ../src/latino.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_latino.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_latino.c$(DependSuffix) -MM "../src/latino.c"

$(IntermediateDirectory)/src_latino.c$(PreprocessSuffix): ../src/latino.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_latino.c$(PreprocessSuffix) "../src/latino.c"

$(IntermediateDirectory)/src_lex.c$(ObjectSuffix): ../src/lex.c $(IntermediateDirectory)/src_lex.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/Documents/GitHub/latino/src/lex.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_lex.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_lex.c$(DependSuffix): ../src/lex.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_lex.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_lex.c$(DependSuffix) -MM "../src/lex.c"

$(IntermediateDirectory)/src_lex.c$(PreprocessSuffix): ../src/lex.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_lex.c$(PreprocessSuffix) "../src/lex.c"

$(IntermediateDirectory)/src_parse.c$(ObjectSuffix): ../src/parse.c $(IntermediateDirectory)/src_parse.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/Documents/GitHub/latino/src/parse.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_parse.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_parse.c$(DependSuffix): ../src/parse.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_parse.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_parse.c$(DependSuffix) -MM "../src/parse.c"

$(IntermediateDirectory)/src_parse.c$(PreprocessSuffix): ../src/parse.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_parse.c$(PreprocessSuffix) "../src/parse.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ../bin/


