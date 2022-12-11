OUTPUT=output
GENERATED=lib

RUNTIME=/usr/lib/x86_64-linux-gnu
INCLUDE=/usr/include/antlr4-runtime
CCARGS=-c -I $(INCLUDE) -I $(GENERATED) -std=c++11	
LDARGS=-g
LIBS=$(RUNTIME)/libantlr4-runtime.a

CC=g++
GRAMMAR=DeskLang

ANTLR4=antlr4

ANTLRGEN=BaseListener Lexer Listener Parser 
#OBJS=$(addsuffix .o,$(addprefix $(OUTPUT)/$(GRAMMAR),$(ANTLRGEN)))
OBJS=$(addsuffix .o,$(OUTPUT)/$(GRAMMAR))
#GSOURCES=$(addsuffix .cpp,$(addprefix $(GENERATED)/$(GRAMMAR),$(ANTLRGEN)))
GSOURCES=$(addsuffix .cpp,$(GENERATED)/$(GRAMMAR))

.precious: $(GSOURCES)

all: parser

parser: dirs antlr4 ./src/main.cpp $(OBJS)
	$(CC) $(CCARGS) ./src/main.cpp  -o $(OUTPUT)/main.o 
	$(CC) $(LDARGS) $(OUTPUT)/main.o $(OBJS) $(LIBS) -o main

antlr4: $(GENERATED)/.generated;
 
$(GENERATED)/.generated: $(GRAMMAR).g4
	$(ANTLR4) -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR).g4
	@touch $(GENERATED)/.generated

$(OUTPUT)/%.o : $(GENERATED)/%.cpp
	$(CC) $(CCARGS) $< -o $@

$(GENERATED)/%.cpp: $(GENERATED)/.generated;

dirs:; mkdir -p $(OUTPUT) $(GENERATED) 
clean:; rm -rf $(OUTPUT) $(GENERATED)