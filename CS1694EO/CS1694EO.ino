#define CLOCK_PIN 12
#define STB_PIN 11
#define DATA_PIN 10

const int INIT_MODE_6_GRIDS_11_SEGS = 0b00000010;
const int INIT_MODE_7_GRIDS_10_SEGS = 0b00000011;

const int init_command =  INIT_MODE_6_GRIDS_11_SEGS;
const int write_command = 0b01000000;
const int brightness_command = 0b10001100;
const int init_display_ram = 0b11000000;

const int default_delay = 32;


void toggle_stb()
{
  digitalWrite(STB_PIN, HIGH);
  delayMicroseconds(default_delay);
  digitalWrite(STB_PIN, LOW);
}

void write_byte(int byte_to_send)
{
  Serial.write("\n\t");
  Serial.print(byte_to_send, BIN);
  for(int i=0; i<8; ++i)
  {
    digitalWrite(CLOCK_PIN, LOW);
    delayMicroseconds(default_delay);
    digitalWrite(DATA_PIN, (byte_to_send & 0b00000001));  
    delayMicroseconds(default_delay);
    digitalWrite(CLOCK_PIN, HIGH);
    byte_to_send >>= 1;
    delayMicroseconds(default_delay);
  }
  delayMicroseconds(default_delay*2);
}

void setup() {
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(STB_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  Serial.begin(9600);

  
  digitalWrite(STB_PIN, HIGH);
  delayMicroseconds(default_delay);
  digitalWrite(CLOCK_PIN, HIGH);
  delayMicroseconds(default_delay);
  digitalWrite(STB_PIN, LOW);
  delayMicroseconds(default_delay);
  
  write_byte(init_command);
  toggle_stb();

  write_byte(brightness_command);
  toggle_stb();
}

void loop() {
  Serial.write("\nNEW ITERATION!\n");
  
  write_byte(init_display_ram);
  toggle_stb();
  
  for(int i=0x00; i<=0xE ; ++i)
  {
      write_byte(write_command);
      write_byte(0xFF);
      toggle_stb();
      delay(100);
  }
  delay(100);

while(true)
{
  write_byte(init_display_ram);
  toggle_stb();
  
  for(int i=0x00; i<=0xE ; ++i)
  {
      write_byte(write_command);
      write_byte(0x00);
      toggle_stb();
      delay(50);
  }

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
 const int f_segmnet_address = 0x0A;
 const int g_segment_address = 0x0C;
 const int digit_1 = 0x01;
 const int digit_2 = 0x02;
 const int digit_3 = 0x80;
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
 
int data[0xF] = {0};
data[left_panel_5_address] = play_icon;

write_byte(0b11000000);
toggle_stb();
  
for(int i=0x00; i<0xF ; ++i)
  {
      write_byte(write_command);
      write_byte(data[i]);
      toggle_stb();
      delay(50);
  }
} 
  digitalWrite(STB_PIN, HIGH);
  delay(1500);
}
