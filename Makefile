
CC = gcc -g

hardware_objs = hardware/lcd12864_util.o hardware/switch_util.o

graphic_objs =  graphic/graphic.o graphic/canvas.o graphic/matrix.o graphic/sprite.o font/ascii.o

basic_objects = $(hardware_objs) $(graphic_objs)

widget_objects = widget/label.o widget/frame.o

cat_game_objects = game/cat/cat_main_frame.o game/cat/scene1/cat_welcome_frame.o game/cat/scene2/cat_game_frame.o game/cat/scene2/game_sprite.o game/cat/scene2/map.o game/cat/main.o

lcd_echo_objects = game/lcd_echo/lcd_echo.o

fresh_rate_objects = game/fresh_rate_check/main.o

clock_objects = game/clock/clock.o game/clock/get_weather.o

cat: $(basic_objects) $(cat_game_objects)
	$(CC) -o cat $(basic_objects) $(cat_game_objects) -lwiringPi -lpthread

lcd_echo: $(basic_objects) $(lcd_echo_objects)
	$(CC) -o lcd_echo $(basic_objects) $(lcd_echo_objects) -lwiringPi

fresh_rate_check: $(fresh_rate_objects)
	$(CC) -o fresh_rate $(basic_objects) $(fresh_rate_objects) -lwiringPi

clock: $(basic_objects) $(widget_objects) $(clock_objects)
	$(CC) -o clock $(basic_objects) $(widget_objects) $(clock_objects) -lwiringPi -lpthread

$(widget_objects): $(basic_objects)
$(cat_game_objects): $(basic_objects)
$(lcd_echo_objects): $(basic_objects)

$(graphic_objs): $(hardware_objs)

font/ascii.o: font/font5x7.h font/font8x7.h
graphic/graphic.o: font/ascii.o graphic/sprite.o
graphic/matrix.o: graphic/graphic.o

posible_outputs = cat lcd_echo
.PHONY: clean
clean:
	rm -f $(basic_objects) $(cat_game_objects) $(lcd_echo_objects) $(posible_outputs) 2>&1 1>/dev/null
