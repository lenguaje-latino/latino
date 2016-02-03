##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=src
ConfigurationName      :=Debug
WorkspacePath          := "C:\Users\proman02\latino\src"
ProjectPath            := "C:\Users\proman02\latino\src"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=proman02
Date                   :=03/02/2016
CodeLitePath           :="C:\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
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
ObjectsFileList        :="src.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -std=c++11 -std=c99 -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=C:\CodeLite
Objects0=$(IntermediateDirectory)/linenoise_example.c$(ObjectSuffix) $(IntermediateDirectory)/linenoise_linenoise.c$(ObjectSuffix) $(IntermediateDirectory)/linenoise_utf8.c$(ObjectSuffix) $(IntermediateDirectory)/ast.c$(ObjectSuffix) $(IntermediateDirectory)/latino.c$(ObjectSuffix) $(IntermediateDirectory)/lex.c$(ObjectSuffix) $(IntermediateDirectory)/libio.c$(ObjectSuffix) $(IntermediateDirectory)/libmath.c$(ObjectSuffix) $(IntermediateDirectory)/libmem.c$(ObjectSuffix) $(IntermediateDirectory)/libstring.c$(ObjectSuffix) \
	$(IntermediateDirectory)/object.c$(ObjectSuffix) $(IntermediateDirectory)/parse.c$(ObjectSuffix) $(IntermediateDirectory)/utils.c$(ObjectSuffix) $(IntermediateDirectory)/vm.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/linenoise_example.c$(ObjectSuffix): linenoise/example.c $(IntermediateDirectory)/linenoise_example.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/linenoise/example.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/linenoise_example.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/linenoise_example.c$(DependSuffix): linenoise/example.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/linenoise_example.c$(ObjectSuffix) -MF$(IntermediateDirectory)/linenoise_example.c$(DependSuffix) -MM "linenoise/example.c"

$(IntermediateDirectory)/linenoise_example.c$(PreprocessSuffix): linenoise/example.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/linenoise_example.c$(PreprocessSuffix) "linenoise/example.c"

$(IntermediateDirectory)/linenoise_linenoise.c$(ObjectSuffix): linenoise/linenoise.c $(IntermediateDirectory)/linenoise_linenoise.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/linenoise/linenoise.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/linenoise_linenoise.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/linenoise_linenoise.c$(DependSuffix): linenoise/linenoise.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/linenoise_linenoise.c$(ObjectSuffix) -MF$(IntermediateDirectory)/linenoise_linenoise.c$(DependSuffix) -MM "linenoise/linenoise.c"

$(IntermediateDirectory)/linenoise_linenoise.c$(PreprocessSuffix): linenoise/linenoise.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/linenoise_linenoise.c$(PreprocessSuffix) "linenoise/linenoise.c"

$(IntermediateDirectory)/linenoise_utf8.c$(ObjectSuffix): linenoise/utf8.c $(IntermediateDirectory)/linenoise_utf8.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/linenoise/utf8.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/linenoise_utf8.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/linenoise_utf8.c$(DependSuffix): linenoise/utf8.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/linenoise_utf8.c$(ObjectSuffix) -MF$(IntermediateDirectory)/linenoise_utf8.c$(DependSuffix) -MM "linenoise/utf8.c"

$(IntermediateDirectory)/linenoise_utf8.c$(PreprocessSuffix): linenoise/utf8.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/linenoise_utf8.c$(PreprocessSuffix) "linenoise/utf8.c"

$(IntermediateDirectory)/ast.c$(ObjectSuffix): ast.c $(IntermediateDirectory)/ast.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/ast.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ast.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ast.c$(DependSuffix): ast.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ast.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ast.c$(DependSuffix) -MM "ast.c"

$(IntermediateDirectory)/ast.c$(PreprocessSuffix): ast.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ast.c$(PreprocessSuffix) "ast.c"

$(IntermediateDirectory)/latino.c$(ObjectSuffix): latino.c $(IntermediateDirectory)/latino.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/latino.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/latino.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/latino.c$(DependSuffix): latino.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/latino.c$(ObjectSuffix) -MF$(IntermediateDirectory)/latino.c$(DependSuffix) -MM "latino.c"

$(IntermediateDirectory)/latino.c$(PreprocessSuffix): latino.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/latino.c$(PreprocessSuffix) "latino.c"

$(IntermediateDirectory)/lex.c$(ObjectSuffix): lex.c $(IntermediateDirectory)/lex.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/lex.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lex.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lex.c$(DependSuffix): lex.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lex.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lex.c$(DependSuffix) -MM "lex.c"

$(IntermediateDirectory)/lex.c$(PreprocessSuffix): lex.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lex.c$(PreprocessSuffix) "lex.c"

$(IntermediateDirectory)/libio.c$(ObjectSuffix): libio.c $(IntermediateDirectory)/libio.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/libio.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/libio.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/libio.c$(DependSuffix): libio.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/libio.c$(ObjectSuffix) -MF$(IntermediateDirectory)/libio.c$(DependSuffix) -MM "libio.c"

$(IntermediateDirectory)/libio.c$(PreprocessSuffix): libio.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/libio.c$(PreprocessSuffix) "libio.c"

$(IntermediateDirectory)/libmath.c$(ObjectSuffix): libmath.c $(IntermediateDirectory)/libmath.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/libmath.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/libmath.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/libmath.c$(DependSuffix): libmath.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/libmath.c$(ObjectSuffix) -MF$(IntermediateDirectory)/libmath.c$(DependSuffix) -MM "libmath.c"

$(IntermediateDirectory)/libmath.c$(PreprocessSuffix): libmath.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/libmath.c$(PreprocessSuffix) "libmath.c"

$(IntermediateDirectory)/libmem.c$(ObjectSuffix): libmem.c $(IntermediateDirectory)/libmem.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/libmem.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/libmem.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/libmem.c$(DependSuffix): libmem.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/libmem.c$(ObjectSuffix) -MF$(IntermediateDirectory)/libmem.c$(DependSuffix) -MM "libmem.c"

$(IntermediateDirectory)/libmem.c$(PreprocessSuffix): libmem.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/libmem.c$(PreprocessSuffix) "libmem.c"

$(IntermediateDirectory)/libstring.c$(ObjectSuffix): libstring.c $(IntermediateDirectory)/libstring.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/libstring.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/libstring.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/libstring.c$(DependSuffix): libstring.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/libstring.c$(ObjectSuffix) -MF$(IntermediateDirectory)/libstring.c$(DependSuffix) -MM "libstring.c"

$(IntermediateDirectory)/libstring.c$(PreprocessSuffix): libstring.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/libstring.c$(PreprocessSuffix) "libstring.c"

$(IntermediateDirectory)/object.c$(ObjectSuffix): object.c $(IntermediateDirectory)/object.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/object.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/object.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/object.c$(DependSuffix): object.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/object.c$(ObjectSuffix) -MF$(IntermediateDirectory)/object.c$(DependSuffix) -MM "object.c"

$(IntermediateDirectory)/object.c$(PreprocessSuffix): object.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/object.c$(PreprocessSuffix) "object.c"

$(IntermediateDirectory)/parse.c$(ObjectSuffix): parse.c $(IntermediateDirectory)/parse.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/parse.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/parse.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/parse.c$(DependSuffix): parse.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/parse.c$(ObjectSuffix) -MF$(IntermediateDirectory)/parse.c$(DependSuffix) -MM "parse.c"

$(IntermediateDirectory)/parse.c$(PreprocessSuffix): parse.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/parse.c$(PreprocessSuffix) "parse.c"

$(IntermediateDirectory)/utils.c$(ObjectSuffix): utils.c $(IntermediateDirectory)/utils.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/utils.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utils.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utils.c$(DependSuffix): utils.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utils.c$(ObjectSuffix) -MF$(IntermediateDirectory)/utils.c$(DependSuffix) -MM "utils.c"

$(IntermediateDirectory)/utils.c$(PreprocessSuffix): utils.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utils.c$(PreprocessSuffix) "utils.c"

$(IntermediateDirectory)/vm.c$(ObjectSuffix): vm.c $(IntermediateDirectory)/vm.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/proman02/latino/src/vm.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vm.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vm.c$(DependSuffix): vm.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vm.c$(ObjectSuffix) -MF$(IntermediateDirectory)/vm.c$(DependSuffix) -MM "vm.c"

$(IntermediateDirectory)/vm.c$(PreprocessSuffix): vm.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vm.c$(PreprocessSuffix) "vm.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


