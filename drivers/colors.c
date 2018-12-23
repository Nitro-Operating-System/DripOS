#include "colors.h"

uint8_t get_color(enum vga_color foreground, enum vga_color background) {
    return foreground | background << 4;
}