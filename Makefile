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
hall.o:
	gcc-arm -mcpu=Cortex-m0 -c -g hall.c
speeds.o: speeds.h
	gcc-arm -mcpu=Cortex-m0 -c -g speeds.c
ssd1306.o:
	gcc-arm -mcpu=Cortex-m0 -c -g ssd1306.c
font.o:
	gcc-arm -mcpu=Cortex-m0 -c -g font.c
servo.o:
	gcc-arm -mcpu=Cortex-m0 -c -g servo.c servo.h
stepper.o:
	gcc-arm -mcpu=Cortex-m0 -c -g stepper.c stepper.h 
bike: irq.o ssd1306.o thread.o libos.a font.o speeds.o hall.o stepper.o servo.o
	ld-arm -o bike -T lpc1114.ld ssd1306.o thread.o irq.o libos.a font.o speeds.o hall.o stepper.o servo.o
upload: bike
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'program bike verify reset exit'
debug:
	openocd -f interface/stlink-v2.cfg -f target/lpc11xx.cfg -c'gdb_port 3333; gdb_memory_map disable'&
clean:
	rm *.o
