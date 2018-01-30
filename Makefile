
main:
	gcc -o a.out main.c hardware/lcd12864_util.c graphic/graphic.c graphic/sprite.c font/ascii.c -lwiringPi
	./a.out
