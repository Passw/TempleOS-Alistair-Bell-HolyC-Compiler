COMPILER 	:= nasm
LINKER		:= ld
FLAGS 		:= -f elf64 -F dwarf -g
OUTPUT		:= Build
OBJECTS		:= $(OUTPUT)/IO.o $(OUTPUT)/Compiler.o
TARGET		:= Compiler

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINKER) $(OBJECTS) -o $(TARGET)

$(OUTPUT)/%.o : x64-linux/%.asm
	$(COMPILER) $(FLAGS) -o $@ $<

clean:
	rm $(OUTPUT)/*.o
	rm $(TARGET)
