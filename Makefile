COMPILER 	:= nasm
LINKER		:= ld
FLAGS 		:= -f elf64
OBJECTS		:= Main.o
TARGET		:= Compiler

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINKER) $(OBJECTS) -o $(TARGET)

%.o : %.s
	$(COMPILER) $(FLAGS) -o $@ $<

clean:
	rm *.o
	rm $(TARGET)