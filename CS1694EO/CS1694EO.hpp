#pragma once

class CS1694EO
{
public:
  enum class InitMode : char
  {
    M6_GRIDS_11_SEGS = 0b00000010,
    M7_GRIDS_10_SEGS = 0b00000011
  };
  
  enum class BrightnessLevel : char
  {
    BRIGHTNESS_LEVEL_1 = 0b000,
    BRIGHTNESS_LEVEL_2 = 0b001,
    BRIGHTNESS_LEVEL_3 = 0b010,
    BRIGHTNESS_LEVEL_4 = 0b011,
    BRIGHTNESS_LEVEL_5 = 0b100,
    BRIGHTNESS_LEVEL_6 = 0b101,
    BRIGHTNESS_LEVEL_7 = 0b110,
    BRIGHTNESS_LEVEL_8 = 0b111    
  };

  CS1694EO(const char clock_pin, const char data_pin, const char stb_pin);
  void init(const CS1694EO::InitMode& mode);
  void set_brightness(const CS1694EO::BrightnessLevel& brightness_level);
  void write_to_ram(const char value);
  void write_to_ram(const char address, const char value);
  void set_ram_address(const char address);
  static const char DISPLAY_RAM_SIZE;

protected:
  void toggle_stb();
  void write_byte(const char& byte);
    
  static const char BRIGHTNESS_OPCODE, WRITE_OPCODE, SET_RAM_ADDRESS_OPCODE, DELAY_US;
  const char clock_pin_;
  const char data_pin_;
  const char stb_pin_;
};

const char CS1694EO::DISPLAY_RAM_SIZE = 0xE;
const char CS1694EO::BRIGHTNESS_OPCODE  = 0b10001000;
const char CS1694EO::WRITE_OPCODE = 0b01000000;
const char CS1694EO::SET_RAM_ADDRESS_OPCODE = 0b11000000;
const char CS1694EO::DELAY_US = 4;

CS1694EO::CS1694EO(const char clock_pin, const char data_pin, const char stb_pin) : clock_pin_(clock_pin), data_pin_(data_pin), stb_pin_(stb_pin)
{}

void CS1694EO::init(const CS1694EO::InitMode& mode)
{
  pinMode(clock_pin_, OUTPUT);
  pinMode(stb_pin_, OUTPUT);
  pinMode(data_pin_, OUTPUT); 
  digitalWrite(stb_pin_, HIGH);
  delayMicroseconds(DELAY_US);
  digitalWrite(clock_pin_, HIGH);
  delayMicroseconds(DELAY_US);
  digitalWrite(stb_pin_, LOW);
  delayMicroseconds(DELAY_US);
  write_byte(static_cast<char>(mode));
  toggle_stb();
}

void CS1694EO::set_brightness(const CS1694EO::BrightnessLevel& brightness_level)
{
  write_byte(BRIGHTNESS_OPCODE | static_cast<char>(brightness_level));
  toggle_stb();
}

void CS1694EO::set_ram_address(const char address)
{
  write_byte(SET_RAM_ADDRESS_OPCODE | address);
  toggle_stb();
}

void CS1694EO::write_to_ram(const char value)
{
  write_byte(WRITE_OPCODE);
  write_byte(value);
  toggle_stb();  
}
void CS1694EO::write_to_ram(const char address, const char value)
{
  set_ram_address(address);
  write_to_ram(value);
}

void CS1694EO::write_byte(const char& byte)
{
  char byte_to_write = byte;
  for(int i = 0; i < 8; ++i)
  {
    digitalWrite(clock_pin_, LOW);
    delayMicroseconds(DELAY_US);
    digitalWrite(data_pin_, (byte_to_write & 0b00000001));  
    delayMicroseconds(DELAY_US);
    digitalWrite(clock_pin_, HIGH);
    byte_to_write >>= 1;
    delayMicroseconds(DELAY_US);
  }
  delayMicroseconds(DELAY_US*2);
}

void CS1694EO::toggle_stb()
{
  digitalWrite(stb_pin_, HIGH);
  delayMicroseconds(DELAY_US);
  digitalWrite(stb_pin_, LOW);
}
