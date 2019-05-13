#include "CS1694EO.hpp"
#include "DVD_4350_panel.hpp"

#define CLOCK_PIN 12
#define STB_PIN 11
#define DATA_PIN 10

CS1694EO driver(CLOCK_PIN, DATA_PIN, STB_PIN);
DVD_4350_panel lcd_panel(driver);

const int DISPLAY_RAM_SIZE = 0xD;

const int WRITE_OPCODE = 0b01000000;

const char write_command = WRITE_OPCODE;

/* LEFT PANEL PART 1 */
const int left_panel_1_address = 0x01;
const int dvd_icon = 0x2;
const int spinner_icon = 0x1;

const int left_panel_2_address = 0x03;
const int spinner_icon_1 = 0x01;
const int vcd_icon = 0x02;

const int left_panel_3_address = 0x05;
const int spinner_icon_2 = 0x01;
const int mp3_icon = 0x02;

const int left_panel_4_address = 0x07;
const int spinner_icon_3 = 0x01;
const int pbc_icon = 0x02;

const int left_panel_5_address = 0x09;
const int spinner_icon_4 = 0x01;
const int play_icon = 0x02;

const int left_panel_6_address = 0x0B;
const int spinner_icon_5 = 0x01;
const int pause_icon = 0x02;

const int left_panel_7_address = 0x0D;
const int spinner_icon_6 = 0x01;
const int spinner_icon_7 = 0x02;

/*   SEGMENTS DESCRIPTION 
 *      a
 *    f   b
 *      g
 *    e   c
 *      d
 */

const int a_segment_address = 0x00;
const int b_segment_address = 0x02;
const int c_segment_address = 0x04;
const int d_segment_address = 0x06;
const int e_segment_address = 0x08;
const int f_segment_address = 0x0A;
const int g_segment_address = 0x0C;
const int digit_1 = 0x01;
const int digit_2 = 0x02;
const int digit_3 = 0x80; // yea third digit is way further then rest
const int digit_4 = 0x04;
const int digit_5 = 0x08;
const int digit_6 = 0x10;
const int digit_7 = 0x20;

const int middle_semicolon_address = 0x02;
const int middle_semicolon_bit = 0x40;
const int right_semicolon_address = 0x04;
const int right_semicolon_bit = 0x40;
const int dolby_icon_address = 0x04;
const int dolby_icon_bit = 0x40;
const int dts_icon_address = 0x06;
const int dts_icon_bit = 0x40;
const int repeat_icon_address = 0x00;
const int repeat_icon_bit = 0x40;

const int default_delay = 8;

int data[0xF] = {0};


/*   SEGMENTS DESCRIPTION 
 *      a
 *    f   b
 *      g
 *    e   c
 *      d
 */
                      //a,b,c,d,e,f,g,
const bool segs_0[7] = {1,1,1,1,1,1,0};
const bool segs_1[7] = {0,1,1,0,0,0,0};
const bool segs_2[7] = {1,1,0,1,1,0,1};
const bool segs_3[7] = {1,1,1,1,0,0,1};
const bool segs_4[7] = {0,1,1,0,0,1,1};
const bool segs_5[7] = {1,0,1,1,0,1,1};
const bool segs_6[7] = {1,0,1,1,1,1,1};
const bool segs_7[7] = {1,1,1,0,0,0,0};
const bool segs_8[7] = {1,1,1,1,1,1,1};
const bool segs_9[7] = {1,1,1,1,0,1,1};

void write_(const bool segs[7], const int index)
{
  int digit_mask = 0x00;
  switch (index)
  {
    case 0 : digit_mask = digit_1; break;
    case 1 : digit_mask = digit_2; break;
    case 2 : digit_mask = digit_3; break;
    case 3 : digit_mask = digit_4; break;
    case 4 : digit_mask = digit_5; break;
    case 5 : digit_mask = digit_6; break;
    case 6 : digit_mask = digit_7; break;
    default : digit_mask = 0x00;
  }
  
  if (segs[0]) data[a_segment_address] |= digit_mask;
  if (segs[1]) data[b_segment_address] |= digit_mask;
  if (segs[2]) data[c_segment_address] |= digit_mask;
  if (segs[3]) data[d_segment_address] |= digit_mask;
  if (segs[4]) data[e_segment_address] |= digit_mask;
  if (segs[5]) data[f_segment_address] |= digit_mask;
  if (segs[6]) data[g_segment_address] |= digit_mask;
}

void write_text_on_display(char* text, int len)
{
  for(int index = 0; index < len; ++index)
  {
    switch(text[index])
    {
      case '0' : write_(segs_0, index); break;
      case '1' : write_(segs_1, index); break;
      case '2' : write_(segs_2, index); break;
      case '3' : write_(segs_3, index); break;
      case '4' : write_(segs_4, index); break;
      case '5' : write_(segs_5, index); break;
      case '6' : write_(segs_6, index); break;
      case '7' : write_(segs_7, index); break;
      case '8' : write_(segs_8, index); break;
      case '9' : write_(segs_9, index); break;
      default : continue;
    }
  }
}

void setup() {
  driver.init(CS1694EO::InitMode::M7_GRIDS_10_SEGS);
  driver.set_brightness(CS1694EO::BrightnessLevel::BRIGHTNESS_LEVEL_3);
}

void loop() { 
  driver.set_ram_to_begining();
  
  for(int i=0x00; i<=DISPLAY_RAM_SIZE ; ++i)
  {
      driver.write_byte(write_command);
      driver.write_byte(0xFF);
      driver.toggle_stb();
      delay(10);
  }
  delay(100);

  driver.set_ram_to_begining();
  
  for(int i=0x00; i<=DISPLAY_RAM_SIZE ; ++i)
  {
      driver.write_byte(write_command);
      driver.write_byte(0x00);
      driver.toggle_stb();
      delay(25);
  }

driver.set_ram_to_begining();

write_text_on_display("0123456", 7); //actualy write to local buffer and then (in a loop below) send it
for(int i=0x00; i<=DISPLAY_RAM_SIZE ; ++i)
  {
      driver.write_byte(write_command);
      driver.write_byte(data[i]);
      driver.toggle_stb();
      delay(25);
  }
  delay(2000);

  digitalWrite(STB_PIN, HIGH);
  delay(500);
}
