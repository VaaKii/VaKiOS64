#include <sys/stdio.h>
#include <stdint.h>
#include <memory/pic.h>
#include <memory/memory.h>
#include <memory/idt.h>
#include <drivers/keyboard.h>

struct interrupt_frame;

uint8_t lastkey = 0;
uint8_t *keycache = 0;
uint16_t key_loc = 0;
uint8_t __kbd_enabled = 0;

__attribute__((interrupt))
void keyboard_irq(struct interrupt_frame* frame)
{
    keycache[key_loc++] = keyboard_to_ascii(inportb(0x60));
    pic_send_eoi(1);
}


enum KEYCODE {
    NULL_KEY = 0,
    Q_PRESSED = 0x10,
    Q_RELEASED = 0x90,
    W_PRESSED = 0x11,
    W_RELEASED = 0x91,
    E_PRESSED = 0x12,
    E_RELEASED = 0x92,
    R_PRESSED = 0x13,
    R_RELEASED = 0x93,
    T_PRESSED = 0x14,
    T_RELEASED = 0x94,
    Z_PRESSED = 0x15,
    Z_RELEASED = 0x95,
    U_PRESSED = 0x16,
    U_RELEASED = 0x96,
    I_PRESSED = 0x17,
    I_RELEASED = 0x97,
    O_PRESSED = 0x18,
    O_RELEASED = 0x98,
    P_PRESSED = 0x19,
    P_RELEASED = 0x99,
    A_PRESSED = 0x1E,
    A_RELEASED = 0x9E,
    S_PRESSED = 0x1F,
    S_RELEASED = 0x9F,
    D_PRESSED = 0x20,
    D_RELEASED = 0xA0,
    F_PRESSED = 0x21,
    F_RELEASED = 0xA1,
    G_PRESSED = 0x22,
    G_RELEASED = 0xA2,
    H_PRESSED = 0x23,
    H_RELEASED = 0xA3,
    J_PRESSED = 0x24,
    J_RELEASED = 0xA4,
    K_PRESSED = 0x25,
    K_RELEASED = 0xA5,
    L_PRESSED = 0x26,
    L_RELEASED = 0xA6,
    Y_PRESSED = 0x2C,
    Y_RELEASED = 0xAC,
    X_PRESSED = 0x2D,
    X_RELEASED = 0xAD,
    C_PRESSED = 0x2E,
    C_RELEASED = 0xAE,
    V_PRESSED = 0x2F,
    V_RELEASED = 0xAF,
    B_PRESSED = 0x30,
    B_RELEASED = 0xB0,
    N_PRESSED = 0x31,
    N_RELEASED = 0xB1,
    M_PRESSED = 0x32,
    M_RELEASED = 0xB2,

    ZERO_PRESSED = 0xB,
    ONE_PRESSED = 0x2,
    NINE_PRESSED = 0xA,

    POINT_PRESSED = 0x34,
    POINT_RELEASED = 0xB4,

    SLASH_RELEASED = 0xB5,

    BACKSPACE_PRESSED = 0xE,
    BACKSPACE_RELEASED = 0x8E,
    SPACE_PRESSED = 0x39,
    SPACE_RELEASED = 0xB9,
    ENTER_PRESSED = 0x1C,
    ENTER_RELEASED = 0x9C,

};

#define KBD_SEND(byt) outportb(0x64, byt);

void keyboard_init(){
    printf("PS/2 Keyboard init sequence activated.\n");
    keycache = (uint8_t*)malloc(256);
    memset(keycache,0,256);
    idt_set_descriptor(33,keyboard_irq);
    __kbd_enabled = 1;
};

uint8_t keyboard_enabled(){
    return __kbd_enabled;
};

void keyboard_read_key(){
    lastkey = 0;
    if(inportb(0x64) & 0x1){
        lastkey = inportb(0x60);

    }
}

static char c = 0;
char keyboard_get_key(){
    c = 0;
    if(key_loc == 0) goto out;
    c = *keycache;
    key_loc--;
    for(int i = 0;i < 256;i++){
        keycache[i] = keycache[i+1];
    }
    out:
    return c;
}

static char* _qwertyuiop = "qwertyuiop";
static char* _asdfghjkl = "asdfghjkl";
static char* _zxcvbnm = "zxcvbnm";
static char* _num = "123456789";
uint8_t keyboard_to_ascii(uint8_t key)
{
    if(key == ENTER_PRESSED) return '\n';
    if(key == 0x39) return ' ';
    if(key == BACKSPACE_PRESSED) return '\b';
    if(key == POINT_RELEASED) return '.';
    if(key == SLASH_RELEASED) return '/';
    if(key == ZERO_PRESSED) return '0';
    if(key >= ONE_PRESSED && key <= NINE_PRESSED)
        return _num[key - ONE_PRESSED];
    if(key >= 0x10 && key <= 0x1C)
    {
        return _qwertyuiop[key - 0x10];
    } else if(key >= 0x1E && key <= 0x26)
    {
        return _asdfghjkl[key - 0x1E];
    } else if(key >= 0x2C && key <= 0x32)
    {
        return _zxcvbnm[key - 0x2C];
    }
    return 0;
}

