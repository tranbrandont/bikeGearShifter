CC=gcc-arm
AR=ar-arm
CFLAGS=-O0 -mcpu=cortex-m0 -g
DEPS = lpc1114.h
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
libos.a: vector.o reset.o
	$(AR) crs libos.a reset.o vector.o lpc1114.h
blink.o:
	gcc-arm -c blink.c
blink: blink.o libos.a
	ld-arm -o blink -T lpc1114.ld blink.o libos.a
adservo: adservo.o libos.a
	ld-arm -o adservo -T lpc1114.ld adservo.o libos.a
irq.o :
	gcc-arm -mcpu=Cortex-m0 -c irq.s
blinky: irq.o blinky.o thread.o libos.a
	ld-arm -o blinky -T lpc1114.ld blinky.o thread.o irq.o libos.a
ssd1306.o:
	gcc-arm -mcpu=Cortex-m0 -c -g ssd1306.c
font.o:
	gcc-arm -mcpu=Cortex-m0 -c -g font.c
lcd: irq.o ssd1306.o thread.o libos.a font.o
	ld-arm -o lcd -T lpc1114.ld ssd1306.o thread.o irq.o libos.a font.o
upload: lcd
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'program lcd verify reset exit'
debug:
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'gdb_port 3333; gdb_memory_map disable'&
clean:
	rm *.o
