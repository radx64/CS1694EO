#include "CS1694EO.hpp"
#include "DVD_4350_panel.hpp"

#define CLOCK_PIN 12
#define STB_PIN 11
#define DATA_PIN 10

CS1694EO driver(CLOCK_PIN, DATA_PIN, STB_PIN);
DVD_4350_panel lcd_panel(driver);

int counter = 0;
char counter_str[10];

void setup() 
{
  driver.init(CS1694EO::InitMode::M7_GRIDS_10_SEGS);
  driver.set_brightness(CS1694EO::BrightnessLevel::BRIGHTNESS_LEVEL_3);
}
  
void loop() 
{
  itoa(counter, counter_str, 10);
  write_text_on_display(counter_str, 7); //actualy write to local buffer and then (in a loop below) send it
  for(int i=0x00; i<CS1694EO::DISPLAY_RAM_SIZE ; ++i) driver.write_to_ram(i, data[i]);
  counter+=1;
}
