
main:
	gcc -g -o a.out main.c hardware/lcd12864_util.c hardware/switch_util.c graphic/graphic.c graphic/matrix.c graphic/sprite.c font/ascii.c -lwiringPi
	./a.out
