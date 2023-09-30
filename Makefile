main:
	gcc -o main pwm.h pwm.c main.c
clean:
	rm main
all: clean main
