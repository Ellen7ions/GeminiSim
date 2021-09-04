CROSS_COMPILER = mips-sde-elf-
SRC_FILE = trace.S

trace.o:
	${CROSS_COMPILER}gcc -c -EL ${SRC_FILE} -o trace.o

trace.bin: trace.o
	${CROSS_COMPILER}objcopy -O binary -j .text $< $@

all: trace.bin
	del *.o
clean:
	del *.bin *.o