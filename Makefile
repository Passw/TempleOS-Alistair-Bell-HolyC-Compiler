COMPILER 	:= nasm
LINKER		:= ld
FLAGS 		:= -f elf64 -F dwarf -g
OBJECTS		:= *.o
TARGET		:= Compiler

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINKER) $(OBJECTS) -o $(TARGET)

%.o : %.s
	$(COMPILER) $(FLAGS) -o $@ $<

clean:
	rm *.o
	rm $(TARGET)