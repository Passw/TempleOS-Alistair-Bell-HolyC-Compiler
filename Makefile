COMPILER 	:= nasm
LINKER		:= ld
FLAGS 		:= -f elf64 -F dwarf -g
OUTPUT		:= Build
OBJECTS		:= $(OUTPUT)/IO.o $(OUTPUT)/Main.o $(OUTPUT)/Grammer.o
TARGET		:= Compiler

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINKER) $(OBJECTS) -o $(TARGET)

$(OUTPUT)/%.o : x64/%.s
	$(COMPILER) $(FLAGS) -o $@ $<

clean:
	rm $(OUTPUT)/*.o
	rm $(TARGET)
