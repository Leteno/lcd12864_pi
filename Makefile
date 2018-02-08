
basic_objects = hardware/lcd12864_util.o hardware/switch_util.o graphic/graphic.o graphic/matrix.o graphic/sprite.o font/ascii.o

cat: $(basic_objects)
	gcc -g -o cat $(basic_objects) game/cat/cat_main_frame.c game/cat/cat_welcome_frame.c main.c -lwiringPi

hardware/lcd12864_util.o: hardware/lcd12864_util.c hardware/lcd12864_util.h
	gcc -o hardware/lcd12864_util.o  -c hardware/lcd12864_util.c -lwiringPi

hardware/switch_util.o: hardware/switch_util.c hardware/switch_util.h
	gcc -o hardware/switch_util.o -c hardware/switch_util.c -lwiringPi

.PHONY: clean
clean:
	-rm $(basic_objects) cat 2>&1 >/dev/null
