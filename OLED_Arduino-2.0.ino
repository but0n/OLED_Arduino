/* 
 * OLED_Arduino.ino
 * 
 * Created by Jack, March 30, 2015.
 * 
 * FUNCTION: This is a driver program to display some pics or words
 *                    on the OLED screen.
 *
 * OLED INFORMATION:
 *             96`    128*64,
 *        driver chip: SSD1306,
 *
 * INTERFACE: 4-wire SPI.
 * 
 */
#define SDIN 9  //D1
#define SCLK 10  //D0
#define DC 11  
#define RST 13
#define CS 12
void OLED_INIT ();
void w_cmd (uint8_t c);
void w_data (uint8_t d);
void refresh_GRAM ();
void draw_point (uint8_t x, uint8_t y, uint8_t t);
void draw_lineX (uint8_t x1, uint8_t y1, uint8_t L);
void clear_display ();
void DISPLAY1 (uint8_t page, uint8_t start);
void oprint(uint8_t da, uint8_t page, uint8_t start);
uint8_t OLED_GRAM[8][128];
uint8_t number_1[2][16] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x02, 
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
uint8_t a[2][8] = {
0x00, 0xA0, 0xA0, 0xA0, 0xE0, 0XC0, 0X00, 0x00, 
0x07, 0x0F, 0x08, 0x08, 0x07, 0X0F, 0x08, 0x00
};

//0x00, 0xE0, 0x05, 0xF0, 0x05, 0x10, 0x05, 0x10, 
//0x07, 0xE0, 0X03, 0XF0, 0X00, 0x10, 0x00, 0x00
    void setup (){
      
      OLED_INIT ();
    
    }

    void loop (){

//w_cmd (0x81); // 9.Set Contrast Control   0x66
//                  w_cmd (0x00); // 0xCF
//      uint8_t light;
//      for (light = 0; light < 0x66; light++){
//                  w_cmd (0x81); // 9.Set Contrast Control   0x66
//                  w_cmd (light); // 0xCF
//                  delay (100);
//      }           
//      delay (1500);
      //        Display Logo

                    clear_display ();
                    DISPLAY1 (0, 58);
                    w_cmd (0xAF);
                    delay (1500);
                    //
                    w_cmd (0xAE);
                    delay (1000);
                    clear_display ();
                    DISPLAY1 (0, 0);
                    DISPLAY1 (2, 16);
                    DISPLAY1 (4, 32);
                    DISPLAY1 (6, 48);
                    DISPLAY1 (0, 112);
                    DISPLAY1 (2, 96);
                    DISPLAY1 (4, 80);
                    DISPLAY1 (6, 64);
                    w_cmd (0xAF);
                    delay (1500);
                    
                    w_cmd (0xAE);
                    delay (1000);
                    clear_display ();
                    oprint ('a', 2, 56);
                    w_cmd (0xAF);
                    delay (1500);
                    
                    w_cmd (0xAE);
                    delay (1000);
                    clear_display ();
                    oprint ('a', 0, 56);
                    w_cmd (0xAF);
                    delay (1500);
                    
                    w_cmd (0xAE);
                    delay (1000);
                    clear_display ();
                    oprint ('a', 6, 0);
                    oprint ('a', 6, 8);
                    oprint ('a', 6, 16);
                    oprint ('a', 6, 24);
                    oprint ('a', 6, 32);
                    oprint ('a', 6, 40);
                    
                    w_cmd (0xAF);
                    delay (1000);
                                         
      
    }

          void OLED_INIT (){
                  pinMode (SDIN, OUTPUT); 
                  pinMode (SCLK, OUTPUT);   
                  pinMode (DC, OUTPUT); 
                  pinMode (RST, OUTPUT);
                  pinMode (CS, OUTPUT); 
// You can find  Initial Sequence on the datasheet
                  
                  digitalWrite (RST, HIGH);  // Set RES# as High
                  delay (1);                           // 3us Delay Recommended
                  
                  digitalWrite (RST, LOW);  // Reset
                  delay(10);
                  
                  digitalWrite (RST, HIGH); 
                  
                  w_cmd (0xAE);  // 1.Set Display Off
                  
                  w_cmd (0xD5); // 2.Set display Clock Divide Ratio/Oscillator Frequency
                  w_cmd (0x80); 
                  
                  w_cmd (0xA8); // 3.Set Multiplex Ratio
                  w_cmd (0x3F);
                  
                  w_cmd (0xD3); // 4.Set Display Offset
                  w_cmd (0x00);
                  
                  w_cmd (0x40); // 5.Set Display Start Line
                  
  // 6.Set Segment Re-Map     0xA1     ***
  // 7.Set COM Output Scan Direction     0xC8      ***
  // 8.Set COM Pins Hardware Configurartion     0xDA, 0x12      ***
  // 9.Set Contrast Control     0x81, 0x66      **^
  // 10.Set Pre-Charge Period     0xD9, 0xF1       ***
  // 11.Set VCOMH Deselect Level      0xDB, 0x30      **^
  // 12.Set Entire Display On/Off      0xA4      ***
  // 13.Set Normal/Inverse Display     0xA6    ***
  // Clear Screen
  
//                  w_cmd (0x8D);// 14.Set Charge Pump
//                  w_cmd (0x14);
                  
 // 15.Set Display On    0xAF     ***
                  w_cmd (0x20);
                  w_cmd (0x10); //0x00
                  
                  w_cmd (0xA1); // 6.Set Segment Re-Map
                  
                  w_cmd (0xC8); // 7.Set COM Output Scan Direction
                  
                  w_cmd (0xDA); // 8.Set COM Pins Hardware Configurartion
                  w_cmd (0x12);
                  
                  w_cmd (0x81); // 9.Set Contrast Control   0x66
                  w_cmd (0x66); // 0xCF
                  
                  w_cmd (0xD9); // 10.Set Pre-Charge Period
                  w_cmd (0xF1);
                  
                  w_cmd (0xDB); // 11.Set VCOMH Deselect Level  0x30
                  w_cmd (0x30); // 0x40 
                  
                  w_cmd (0xA4); // 12.Set Entire Display On/Off 
                  
                  w_cmd (0xA6); // 13.Set Normal/Inverse Display
                  
                  w_cmd (0x8D);// 14.Set Charge Pump
                  w_cmd (0x14);
                  
                  w_cmd (0xAF); // 15.Set Display On
                  
                  
          }
              void w_cmd (uint8_t c){
                digitalWrite (CS, HIGH);
                digitalWrite (DC, LOW); // Command
                digitalWrite (CS, LOW);
                    shiftOut (SDIN, SCLK, MSBFIRST, c);
                digitalWrite (CS, HIGH);
              }
              
              void w_data (uint8_t d){
                digitalWrite (CS, HIGH);
                digitalWrite (DC, HIGH); // Data
                digitalWrite (CS, LOW);
                    shiftOut (SDIN, SCLK, MSBFIRST, d);
                digitalWrite (CS, HIGH);
              }
                    
                    void refresh_GRAM (){
                     
                            uint8_t x, y; // x = SEG  [0:127]    y = PAGE  [0:7]
                            for (y = 0; y < 8; y++){
                                    w_cmd (0xB0 + y);  // Set Page Number 
                                    w_cmd (0x00);  //  Set Low  (4bit)
                                    w_cmd (0x10);  //  Set High (4bit)
                                    for (x = 0; x<128; x++)
                                            w_data (OLED_GRAM[y][x]);
                            
                            }
                    }
                    void clear_display (){
                      memset (OLED_GRAM, 0x00, sizeof (OLED_GRAM));
                      refresh_GRAM ();
                    }
                    
                    void DISPLAY1 (uint8_t page, uint8_t start){
                                    uint8_t t, n;
                                    for (t = 0; t < 2; t++){
                                          w_cmd (0xB0 + page + t);
                                          w_cmd (start & 0x0F);
                                          w_cmd (((start >> 4) & 0x0F) | 0x10);
                                          for (n = 0; n < 16; n++){
                                          w_data (number_1[t][n]);}
                                    
                                    }
                    
                    }
                    
    void oprint(uint8_t da, uint8_t page, uint8_t start){
      
                uint8_t t, n;
                for (t = 0; t < 2; t++){
                            w_cmd (0xB0 + page + t);
                            w_cmd (start & 0x0F);
                            w_cmd (((start >> 4) & 0x0F) | 0x10);
                            for (n = 0; n < 8; n++){
                                            switch (da){
                                              case 'a':  
                                              w_data (a[t][n]);
                                              break;
                                            }  
                            }
                  }
    
    }

                                          
