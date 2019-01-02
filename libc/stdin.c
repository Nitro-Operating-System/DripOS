#include "stdin.h"
#include "string.h"

#include "../kernel/kernel.h"

#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

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

const char scode_ascii_upper[] = {
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

int key_timeout[256];
static char key_buffer[2560];

void key_handler() {
    for(int i = 0; i < 58; i++) {
        if(strcmp(scode_name[i], "Enter") == 0
        && keydown[i] == true
        && key_timeout[i] <= 0) {
            key_timeout[i] = DELETE;
            kprint("\n");

        }
    }
}