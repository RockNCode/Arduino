// OSEPP IR Line Sensor Example Sketch 
// by OSEPP
// This sketch demonstrates interactions with the IR Line Sensor 
#include <Wire.h>

// Possible sensor addresses (suffix correspond to DIP switch positions) 
#define SENSOR_ADDR_OFF_OFF (0x4B) 
#define SENSOR_ADDR_OFF_ON (0x4A) 
#define SENSOR_ADDR_ON_OFF (0x49) 
#define SENSOR_ADDR_ON_ON (0x48) 

// Set the sensor address here 
const uint8_t sensorAddr = SENSOR_ADDR_ON_ON; 

// One-time setup 
void setup() 
{ 
  // Start the serial port for output 
  Serial.begin(9600); 
  // Join the I2C bus as master 
  Wire.begin(); 
  // Set up the ADC on the sensor (reset everything) 
  WriteByte(sensorAddr, 0x0, 0x0); 
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
}

// Main program loop 
void loop() 
{ 
  uint8_t left;
  uint8_t right;
  // Get the value from the sensors; left sensor is at register 0, and the right 
  // sensor is at register 1 
  if ((ReadByte(sensorAddr, 0x0, &left) == 0) &&
     (ReadByte(sensorAddr, 0x1, &right) == 0)) { 
     // Use a threshold (value from 0-255) to determine if sensor detected a dark 
     // or light surface; the threshold should be modified according to the 
     // environment on which the sensor will be used 
     if (left >= 200) { 
       Serial.println("L: DARK"); 
       digitalWrite(13, LOW);
     } else { 
       Serial.println("L: LIGHT"); 
       digitalWrite(13, HIGH);
     } 
     if (right >= 200) { 
       Serial.println("R: DARK"); 
       digitalWrite(13, LOW);
     } else { 
       Serial.println("R: LIGHT"); 
       digitalWrite(13, HIGH);
     } 
   
   } else { 
     Serial.println("Failed to read from sensor"); 
   } 
   // Run again in 1 s (1000 ms) 
   delay(100); 
}

// Read a byte on the i2c interface 
int ReadByte(uint8_t addr, uint8_t reg, uint8_t *data) 
{ 
  // Do an i2c write to set the register that we want to read from 
  Wire.beginTransmission(addr); 
  Wire.write(reg); 
  Wire.endTransmission(); 
  // Read a byte from the device 
  Wire.requestFrom(addr, (uint8_t)1); 
  if (Wire.available()) { 
    *data = Wire.read(); 
  } else { 
    // Read nothing back 
    return -1; 
  } 
  return 0; 
} 
// Write a byte on the i2c interface 
void WriteByte(uint8_t addr, uint8_t reg, byte data) 
{ 
  // Begin the write sequence 
  Wire.beginTransmission(addr); 
  // First byte is to set the register pointer 
  Wire.write(reg); 
  // Write the data byte 
  Wire.write(data); 
  // End the write sequence; bytes are actually transmitted now 
  Wire.endTransmission(); 
}
