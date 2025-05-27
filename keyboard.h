// keyboard.h
#pragma once
// keyboard constants
#define BACKSPACE 0x08
#define ENTER 0x0a
#define E0_SIGN (1 << 0)
#define SHIFT (1 << 1)
#define CAPS_LOCK (1 << 2)
// keyboard functions
// initialize keyboard
void init_keyboard();