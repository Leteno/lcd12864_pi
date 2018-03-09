
CC = gcc -g

basic_objects = hardware/lcd12864_util.o hardware/switch_util.o graphic/graphic.o graphic/canvas.o graphic/matrix.o graphic/sprite.o font/ascii.o

cat_game_objects = game/cat/cat_main_frame.o game/cat/scene1/cat_welcome_frame.o game/cat/scene2/cat_game_frame.o game/cat/scene2/game_sprite.o main.o

lcd_echo_objects = game/lcd_echo/lcd_echo.o

cat: $(basic_objects) $(cat_game_objects)
	$(CC) -o cat $(basic_objects) $(cat_game_objects) -lwiringPi

lcd_echo: $(basic_objects) $(lcd_echo_objects)
	$(CC) -o lcd_echo $(basic_objects) $(lcd_echo_objects) -lwiringPi

$(cat_game_objects): $(basic_objects)
$(lcd_echo_objects): $(basic_objects)

font/ascii.o: font/font5x7.h font/font8x7.h
graphic/graphic.o: font/ascii.o graphic/sprite.o

posible_outputs = cat lcd_echo
.PHONY: clean
clean:
	rm -f $(basic_objects) $(cat_game_objects) $(lcd_echo_objects) $(posible_outputs) 2>&1 1>/dev/null
