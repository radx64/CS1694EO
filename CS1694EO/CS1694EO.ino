#include "CS1694EO.hpp"
#include "DVD_4350_panel.hpp"

#define CLOCK_PIN 12
#define STB_PIN 11
#define DATA_PIN 10

CS1694EO driver(CLOCK_PIN, DATA_PIN, STB_PIN);
DVD_4350_panel lcd_panel(driver);

const char TEXT_SIZE = 58;
const char BUFFER_SIZE = 7;
char text_marquee[TEXT_SIZE] = "LCD DEMO BY RADX64 abcdefghijklmnopqrstuvwxyz 0123456789";
char text_buffer[7] = {};
int position = 0;

void setup() 
{
  driver.init(CS1694EO::InitMode::M7_GRIDS_10_SEGS);
  driver.set_brightness(CS1694EO::BrightnessLevel::BRIGHTNESS_LEVEL_7);
}
  
void loop() 
{
  memcpy(text_buffer, text_marquee + position, position+BUFFER_SIZE>=TEXT_SIZE-1?0:BUFFER_SIZE);
  write_text_on_display(text_buffer, BUFFER_SIZE); //actualy write to local buffer and then (in a loop below) send it
  for(int i=0x00; i<CS1694EO::DISPLAY_RAM_SIZE ; ++i) driver.write_to_ram(i, data[i]);
  position+=1;
  if (position >= TEXT_SIZE-1) position = 0;
  delay(250);
}
