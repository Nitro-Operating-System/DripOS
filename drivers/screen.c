#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"
#include "colors.h"

int get_cursor_offset() {
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8;

    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);

    return offset * 2;
}

void set_cursor_offset(int offset) {
    offset /= 2;

    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (uint8_t) (offset >> 8));
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, (uint8_t) (offset & 0xFF));
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_offset_col(int offset) {
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}

int print_char(char c, int col, int row, uint8_t color) {
    uint8_t *vidmem = (uint8_t*) VIDEO_ADDRESS;
    if(!color) color = get_color(WHITE, BLACK);

    if(col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2 * MAX_COLS * MAX_ROWS - 2] = 'E';
        vidmem[2 * MAX_COLS * MAX_ROWS - 1] = get_color(RED, WHITE);

        return get_offset(col, row);
    }

    int offset;
    if(col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor_offset();
    }

    if(c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    } else if(c == 0x08){ // Backspace
        vidmem[offset] = ' ';
        vidmem[offset + 1] = color;
    } else {
        vidmem[offset] = c;
        vidmem[offset + 1] = color;
        offset += 2;
    }

    if(offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;

        for(i = 1; i < MAX_ROWS; i++) {
            memcpy((uint8_t*)(get_offset(0, i) + VIDEO_ADDRESS), (uint8_t*)(get_offset(0, i - 1) + VIDEO_ADDRESS), MAX_COLS * 2);
        }

        char *last_line = (char*) (get_offset(0, MAX_ROWS - 1) + (uint8_t) VIDEO_ADDRESS);
        for(i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= MAX_COLS * 2;
    }

    set_cursor_offset(offset);
    return offset;
}

int logo[16][16] = {
        {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 3, 1, 1, 3, 3, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 1, 2, 2, 1, 3, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 3, 1, 2, 2, 1, 3, 3, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 1, 2, 2, 2, 2, 1, 3, 0, 0, 0, 0},
        {0, 0, 0, 3, 3, 1, 2, 2, 2, 2, 1, 3, 3, 0, 0, 0},
        {0, 0, 0, 3, 1, 2, 2, 2, 2, 2, 2, 1, 3, 0, 0, 0},
        {0, 0, 3, 3, 1, 2, 2, 2, 2, 2, 2, 1, 3, 3, 0, 0},
        {0, 0, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 0, 0},
        {0, 0, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 0, 0},
        {0, 0, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 0, 0},
        {0, 0, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 0, 0},
        {0, 0, 3, 3, 1, 2, 2, 2, 2, 2, 2, 1, 3, 3, 0, 0},
        {0, 0, 0, 3, 3, 1, 2, 2, 2, 2, 1, 3, 3, 0, 0, 0},
        {0, 0, 0, 0, 3, 3, 1, 1, 1, 1, 3, 3, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0}
};

void clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;

    uint8_t *screen = (uint8_t*) VIDEO_ADDRESS;

    for(i = 0; i < screen_size; i++) {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = get_color(WHITE, BLACK);
    }

    set_cursor_offset(get_offset(0, 0));
}

void kprint_at(char *message, int col, int row) {
    int offset;

    if(col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;

    while(message[i] != 0) {
        offset = print_char(message[i++], col, row, get_color(WHITE, BLACK));

        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint_at_color(char *message, int col, int row, uint8_t color) {
    int offset;

    if(col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;

    while(message[i] != 0) {
        offset = print_char(message[i++], col, row, color);

        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *message) {
    kprint_at(message, -1, -1);
}

void kprint_color(char *message, uint8_t color) {
    kprint_at_color(message, -1, -1, color);
}

void kprint_backspace() {
    int offset = get_cursor_offset() - 2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, get_color(WHITE, BLACK));
}

void logoDraw() {
    char text[] = "DripOS";
    int xOff = (MAX_COLS - 16) / 2;
    int textOff = (MAX_COLS - 6) / 2;

    for(int y = 0; y < 16; y++) {
        for(int x = 0; x < 16; x++) {
            if(logo[y][x] == 1) {
                kprint_at_color(" ", x + xOff, y, get_color(BLACK, BLACK));
            } else if(logo[y][x] == 2) {
                kprint_at_color(" ", x + xOff, y, get_color(CYAN, CYAN));
            } else if(logo[y][x] == 3) {
                kprint_at_color(" ", x + xOff, y, get_color(WHITE, WHITE));
            } else {
                kprint_at_color(" ", x + xOff, y, get_color(WHITE, BLACK));
            }
        }
    }

    kprint_at_color(text, textOff, 17, get_color(WHITE, BLACK));
}