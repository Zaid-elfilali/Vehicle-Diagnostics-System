void lcd_chr(unsigned char chr);
void lcd_cmd(unsigned char cmd);
void lcd_str(const unsigned char *str);
void lcd_intial_4bits();
#define shift_left 0x18
#define shift_right 0x1C
#define first_line 0x80
#define second_line 0xC0
#define move_left 0x10
#define move_right 0x14