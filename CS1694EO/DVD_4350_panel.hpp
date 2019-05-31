#pragma once
#include "CS1694EO.hpp"

/* below part of code is a good base for a nice refactor :) */
int data[0xF] = {0};

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

                                // abcdefg
const unsigned char segs_space = 0b0000000;
const unsigned char segs_0 = 0b1111110;
const unsigned char segs_1 = 0b0110000;
const unsigned char segs_2 = 0b1101101;
const unsigned char segs_3 = 0b1111001;
const unsigned char segs_4 = 0b0110011;
const unsigned char segs_5 = 0b1011011;
const unsigned char segs_6 = 0b1011111;
const unsigned char segs_7 = 0b1110000;
const unsigned char segs_8 = 0b1111111;
const unsigned char segs_9 = 0b1111011;
const unsigned char segs_a = 0b1110111;
const unsigned char segs_b = 0b0011111;
const unsigned char segs_c = 0b1001110;
const unsigned char segs_d = 0b0111101;
const unsigned char segs_e = 0b1001111;
const unsigned char segs_f = 0b1000111;
const unsigned char segs_g = 0b1011110;
const unsigned char segs_h = 0b0110111;
const unsigned char segs_i = 0b0110000;
const unsigned char segs_j = 0b0111000;
const unsigned char segs_k = 0b0110111;
const unsigned char segs_l = 0b0001110;
const unsigned char segs_m = 0b0010101;
const unsigned char segs_n = 0b0010101;
const unsigned char segs_o = 0b0011101;
const unsigned char segs_p = 0b1100111;
const unsigned char segs_q = 0b1110011;
const unsigned char segs_r = 0b0000101;
const unsigned char segs_s = 0b1011011;
const unsigned char segs_t = 0b0001111;
const unsigned char segs_u = 0b0011100;
const unsigned char segs_v = 0b0011100;
const unsigned char segs_w = 0b0011100;
const unsigned char segs_x = 0b0110111;
const unsigned char segs_y = 0b0111011;
const unsigned char segs_z = 0b1101101;

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

void write_(const unsigned char segs, const int index)
{
  unsigned int digit_mask = 0x00;
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
  
  if (segs & 0b1000000) {data[a_segment_address] |= digit_mask;} else {data[a_segment_address] &= (~digit_mask);}
  if (segs & 0b0100000) {data[b_segment_address] |= digit_mask;} else {data[b_segment_address] &= (~digit_mask);}
  if (segs & 0b0010000) {data[c_segment_address] |= digit_mask;} else {data[c_segment_address] &= (~digit_mask);}
  if (segs & 0b0001000) {data[d_segment_address] |= digit_mask;} else {data[d_segment_address] &= (~digit_mask);}
  if (segs & 0b0000100) {data[e_segment_address] |= digit_mask;} else {data[e_segment_address] &= (~digit_mask);}
  if (segs & 0b0000010) {data[f_segment_address] |= digit_mask;} else {data[f_segment_address] &= (~digit_mask);}
  if (segs & 0b0000001) {data[g_segment_address] |= digit_mask;} else {data[g_segment_address] &= (~digit_mask);}
}

void write_text_on_display(char* text, int len)
{
  for(int index = 0; index < len; ++index)
  {
    switch(tolower(text[index]))
    {
      case ' ' : write_(segs_space, index); break;
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
      case 'a' : write_(segs_a, index); break;
      case 'b' : write_(segs_b, index); break;
      case 'c' : write_(segs_c, index); break;
      case 'd' : write_(segs_d, index); break;
      case 'e' : write_(segs_e, index); break;
      case 'f' : write_(segs_f, index); break;
      case 'g' : write_(segs_g, index); break;
      case 'h' : write_(segs_h, index); break;
      case 'i' : write_(segs_i, index); break;
      case 'j' : write_(segs_j, index); break;
      case 'k' : write_(segs_k, index); break;
      case 'l' : write_(segs_l, index); break;
      case 'm' : write_(segs_m, index); break;
      case 'n' : write_(segs_n, index); break;
      case 'o' : write_(segs_o, index); break;
      case 'p' : write_(segs_p, index); break;
      case 'q' : write_(segs_q, index); break;
      case 'r' : write_(segs_r, index); break;
      case 's' : write_(segs_s, index); break;
      case 't' : write_(segs_t, index); break;
      case 'u' : write_(segs_u, index); break;
      case 'v' : write_(segs_v, index); break;
      case 'w' : write_(segs_w, index); break;
      case 'x' : write_(segs_x, index); break;
      case 'y' : write_(segs_y, index); break;
      case 'z' : write_(segs_z, index); break;
      default : continue;
    }
  }
}

class DVD_4350_panel
{
public:
  DVD_4350_panel(CS1694EO& driver){}
};
