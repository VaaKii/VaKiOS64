//
// Created by VaKi on 29.06.2023.
//

#ifndef VAKIOS64_KEYBOARD_H
#define VAKIOS64_KEYBOARD_H

extern void keyboard_init();
extern uint8_t keyboard_enabled();
extern char keyboard_get_key();
extern uint8_t keyboard_to_ascii(uint8_t key);


#endif //VAKIOS64_KEYBOARD_H
