// keyboard.c
// handle keyboard
#include "keyboard.h"
#include "types.h"
#include "screen.h"
#include "strings.h"
#include "isr.h"
#include "ports.h"
#include "kernel.h"
// keyboard flag
static unsigned int keyflag;
// key board keys get put here
static char key_buffer[256] = "";
// this function is called when a key is pressed
static void keyboard_callback(registers_t* regs) {
    // shift codes
    unsigned char shift_code[256] = {
    [0x2A] = SHIFT,[0x36] = SHIFT,[0xAA] = SHIFT,[0xB6] = SHIFT
    };
    // Caps Lock codes
    unsigned char lock_code[256] = {
    [0x3A] = CAPS_LOCK
    };
    // keys
    char key_map[256] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    '-', '=', '\b', 0, 'q', 'w', 'e', 'r', 't', 'y', 'u',
    'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f',
    'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
    };
    // shift keys
    char shift_key_map[256] = {
    0, 1, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U',
    'I', 'O', 'P', '{', '}', '\n', 0, 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C',
    'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
    };
    // scancode read from keyboard
    unsigned char scancode;
    // mapped char
    char ch;
    // read scan code from keyboard
    scancode = port_byte_in(0x60);
    //print_hex(scancode);

    // set escaped keys
    if (scancode == 0xE0) {
        keyflag |= E0_SIGN;
        return;
    }
    // unset escaped keys
    if (keyflag & E0_SIGN) {
        keyflag &= ~E0_SIGN;
        return;
    }
    // un shift
    if (scancode & 0x80) {
        keyflag &= ~(shift_code[scancode]);
        return;
    }
    // set shift
    keyflag |= shift_code[scancode];

    // toggle lock
    keyflag ^= lock_code[scancode];
    // get shift keys
    if (keyflag & SHIFT) {
        ch = shift_key_map[scancode];
    }
    // get key
    else {
        ch = key_map[scancode];
    }

    //print_hex(scancode);

    // check for caps
    if (keyflag & CAPS_LOCK) {
        if ('a' <= ch && ch <= 'z')
        ch -= 32;
        else if ('A' <= ch && ch <= 'Z')
        ch += 32;
    }
    // handle backspace
    if (ch == BACKSPACE) {
        if (backspace(key_buffer)) {
            print_backspace();
        }
    }
    // handle enter key
    else if (ch == ENTER) {
        execute_command(key_buffer); // execute command
        key_buffer[0] = '\0'; // clear key buffer
    }
    // any other key store in buffer
    else {
        append(key_buffer, ch);
        // print out letter
        char str[2] = { ch, '\0' };
        printf(str);
    }
}
// register keyboard handler at IRQ1
void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
    keyflag=0;
}