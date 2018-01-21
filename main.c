#include "lcd12864_util.h"

int main(int argc, char** argv) {
    init_env();
    clear_graphic_mem();
    set_graphic_on(0);
    set_gdram_address(0x1, 0x0);
    write_on_ram(0xFF);
    write_on_ram(0x00);
    write_on_ram(0xFF);
    write_on_ram(0x00);
    write_on_ram(0xFF);
    write_on_ram(0xFF);
    write_on_ram(0xFF);
    write_on_ram(0xFF);
    set_graphic_on(1);
    return 0;
}
