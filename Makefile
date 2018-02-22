
CC = gcc -g

basic_objects = hardware/lcd12864_util.o hardware/switch_util.o graphic/graphic.o graphic/matrix.o graphic/sprite.o font/ascii.o

cat_game_objects = game/cat/cat_main_frame.o game/cat/cat_welcome_frame.o game/cat/game_sprite.o main.o

cat: $(basic_objects) $(cat_game_objects)
	$(CC) -o cat $(basic_objects) $(cat_game_objects) -lwiringPi

lcd_echo: $(basic_objects) game/show_network/lcd_echo.o
	$(CC) -o lcd_echo $(basic_objects) game/show_network/lcd_echo.o -lwiringPi

posible_outputs = cat lcd_echo
.PHONY: clean
clean:
	rm -f $(basic_objects) $(cat_game_objects) $(posible_outputs) 2>&1 1>/dev/null
