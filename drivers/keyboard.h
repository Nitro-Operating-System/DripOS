#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../libc/types.h"

#define BACKSPACE 0x0E
#define ENTER     0x1C
#define LSHIFT    0x2A
#define RSHIFT    0x36
#define DELETE    0x00

#define SCAN_MAX  57

extern bool keydown[256];

const char *scode_name[] = {
        "ERR", "Esc",
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
        "-", "=", "BACKSPACE", "TAB",
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "[", "]", "ENTER", "L_CTRL",
        "A", "S", "D", "F", "G", "H", "J", "K", "L",
        ";", "'", "`", "L_SHIFT", "\\",
        "Z", "X", "C", "V", "B", "N", "M",
        ",", ".", "/", "R_SHIFT", "Keypad *", "L_ALT", "SPACE"
};

const char scode_ascii[] = {
        ' ', ' ',
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
        '-', '=', ' ', ' ',
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
        '[', ']', ' ', ' ',
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
        ';', '\'', '`', ' ', '\\',
        'z', 'x', 'c', 'v', 'b', 'n', 'm',
        ',', '.', '/', ' ', ' ', ' ', ' '
};

const chat scode_ascii_upper[] = {
        ' ', ' ',
        '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
        '_', '+', ' ', ' ',
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        '{', '}', ' ', ' ',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
        ':', '|', '~', ' ', '\\',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M',
        '<', '>', '?', ' ', ' ', ' ', ' '
};

void init_keyboard();

#endif //KEYBOARD_H
