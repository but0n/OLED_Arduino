/* 
 * OLED_Arduino-2.2.ino
 * 
 * Created by Jack, April 5, 2015.
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

typedef struct insert {
uint8_t page;
uint8_t start;
}insert;
insert in = {0, 0};
void OLED_INIT ();
void w_cmd (uint8_t c);
void w_data (uint8_t d);
void clear_display ();
void oprint (uint8_t w, insert *in);
void oled_printf (char text[]);

//  ASCII  -  buff


uint8_t buff_0[2][8] = {
0xF0, 0xF8, 0x0C, 0xC4, 0x0C, 0xF8, 0xF0, 0x00, 
0x03, 0x07, 0x0C, 0x08, 0x0C, 0x07, 0x03, 0x00
};
uint8_t buff_1[2][8] = {
0x00, 0x10, 0x18, 0xFC, 0xFC, 0x00, 0x00, 0x00, 
0x00, 0x08, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x00
};
uint8_t buff_2[2][8] = {
0x08, 0x0C, 0x84, 0xC4, 0x64, 0x3C, 0x18, 0x00, 
0x0E, 0x0F, 0x09, 0x08, 0x08, 0x0C, 0x0C, 0x00
};
uint8_t buff_3[2][8] = {
0x08, 0x0C, 0x44, 0x44, 0x44, 0xFC, 0xB8, 0x00, 
0x04, 0x0C, 0x08, 0x08, 0x08, 0x0F, 0x07, 0x00
};
uint8_t buff_4[2][8] = {
0xC0, 0xE0, 0xB0, 0x98, 0xFC, 0xFC, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x00
};
uint8_t buff_5[2][8] = {
0x7C, 0x7C, 0x44, 0x44, 0x44, 0xC4, 0x84, 0x00, 
0x04, 0x0C, 0x08, 0x08, 0x08, 0x0F, 0x07, 0x00
};
uint8_t buff_6[2][8] = {
0xF0, 0xF8, 0x4C, 0x44, 0x44, 0xC0, 0x80, 0x00, 
0x07, 0x07, 0x08, 0x08, 0x08, 0x0F, 0x07, 0x00
};
uint8_t buff_7[2][8] = {
0x0C, 0x0C, 0x04, 0x84, 0xC4, 0x7C, 0x3C, 0x00, 
0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00
};
uint8_t buff_8[2][8] = {
0xB8, 0xFC, 0x44, 0x44, 0x44, 0xFC, 0xB8, 0x00, 
0x07, 0x0F, 0x08, 0x08, 0x08, 0x0F, 0x07, 0x00
};
uint8_t buff_9[2][8] = {
0x38, 0x7C, 0x44, 0x44, 0x44, 0xFC, 0xF8, 0x00, 
0x00, 0x08, 0x08, 0x08, 0x0C, 0x07, 0x03, 0x00
};

uint8_t buff_a[2][8] = {
0x00, 0xA0, 0xA0, 0xA0, 0xE0, 0xC0, 0x00, 0x00, 
0x07, 0x0F, 0x08, 0x08, 0x07, 0x0F, 0x08, 0x00
};
uint8_t buff_b[2][8] = {
0x04, 0xFC, 0xFC, 0x20, 0x60, 0xC0, 0x80, 0x00, 
0x00, 0x0F, 0x0F, 0x08, 0x08, 0x0F, 0x07, 0x00
};
uint8_t buff_c[2][8] = {
0xC0, 0xE0, 0x20, 0x20, 0x20, 0x60, 0x40, 0x00, 
0x07, 0x0F, 0x08, 0x08, 0x08, 0x0C, 0x04, 0x00
};
uint8_t buff_d[2][8] = {
0x80, 0xC0, 0x60, 0x24, 0xFC, 0xFC, 0x00, 0x00, 
0x07, 0x0F, 0x08, 0x08, 0x07, 0x0F, 0x08, 0x00
};
uint8_t buff_e[2][8] = {
0xC0, 0xE0, 0xA0, 0xA0, 0xA0, 0xE0, 0xC0, 0x00, 
0x00, 0x0F, 0x08, 0x08, 0x08, 0x0C, 0x04, 0x00
};
uint8_t buff_f[2][8] = {
0x40, 0xF8, 0xFC, 0x44, 0x0C, 0x18, 0x00, 0x00, 
0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x00, 0x00
};
uint8_t buff_g[2][8] = {
0xC0, 0xE0, 0x20, 0x20, 0xC0, 0xE0, 0x20, 0x00, 
0x27, 0x6F, 0x48, 0x48, 0x7F, 0x3F, 0x00, 0x00
};
uint8_t buff_h[2][8] = {
0x04, 0xFC, 0xFC, 0x40, 0x20, 0xE0, 0xC0, 0x00, 
0x08, 0x0F, 0x0F, 0x00, 0x00, 0x0F, 0x0F, 0x00
};
uint8_t buff_i[2][8] = {
0x00, 0x00, 0x20, 0xEC, 0xEC, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00
};
uint8_t buff_j[2][8] = {
0x00, 0x00, 0x00, 0x00, 0x20, 0xEC, 0xEC, 0x00, 
0x00, 0x30, 0x70, 0x40, 0x40, 0x7F, 0x3F, 0x00
};
uint8_t buff_k[2][8] = {
0x04, 0xFC, 0xFC, 0x80, 0xC0, 0x60, 0x20, 0x00, 
0x08, 0x0F, 0x0F, 0x01, 0x03, 0x0E, 0x0C, 0x00
};
uint8_t buff_l[2][8] = {
0x00, 0x00, 0x04, 0xFC, 0xFC, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00
};
uint8_t buff_m[2][8] = {
0xE0, 0xE0, 0x60, 0xC0, 0x60, 0xE0, 0xC0, 0x00, 
0x0F, 0x0F, 0x00, 0x07, 0x00, 0x0F, 0x0F, 0x00
};
uint8_t buff_n[2][8] = {
0x20, 0xE0, 0xC0, 0x20, 0x20, 0xE0, 0xC0, 0x00, 
0x00, 0x0F, 0x0F, 0x00, 0x00, 0x0F, 0x0F, 0x00
};
uint8_t buff_o[2][8] = {
0xC0, 0xE0, 0x20, 0x20, 0x20, 0xE0, 0xC0, 0x00, 
0x07, 0x0F, 0x08, 0x08, 0x08, 0x0F, 0x07, 0x00
};
uint8_t buff_p[2][8] = {
0x20, 0xE0, 0xC0, 0x20, 0x20, 0xE0, 0xC0, 0x00, 
0x40, 0x7F, 0x7F, 0x48, 0x08, 0x0F, 0x07, 0x00
};
uint8_t buff_q[2][8] = {
0xC0, 0xE0, 0x20, 0x20, 0xC0, 0xE0, 0x20, 0x00, 
0x07, 0x0F, 0x08, 0x48, 0x7F, 0x7F, 0x40, 0x00
};
uint8_t buff_r[2][8] = {
0x20, 0xE0, 0xC0, 0x60, 0x20, 0xE0, 0xC0, 0x00, 
0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00, 0x00, 0x00
};
uint8_t buff_s[2][8] = {
0x40, 0xE0, 0xA0, 0x20, 0x20, 0x60, 0x04, 0x00, 
0x04, 0x0C, 0x09, 0x09, 0x0B, 0x0E, 0x04, 0x00
};
uint8_t buff_t[2][8] = {
0x20, 0x20, 0xF8, 0xFC, 0x20, 0x20, 0x00, 0x00, 
0x00, 0x00, 0x07, 0x0F, 0x08, 0x0C, 0x04, 0x00
};
uint8_t buff_u[2][8] = {
0xE0, 0xE0, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, 
0x07, 0x0F, 0x08, 0x08, 0x07, 0x0F, 0x08, 0x00
};
uint8_t buff_v[2][8] = {
0x00, 0xE0, 0xE0, 0x00, 0x00, 0xE0, 0xE0, 0x00, 
0x00, 0x03, 0x07, 0x0C, 0x0C, 0x07, 0x03, 0x00
};
uint8_t buff_w[2][8] = {
0xE0, 0xE0, 0x00, 0x80, 0x00, 0xE0, 0xE0, 0x00, 
0x07, 0x0F, 0x0C, 0x07, 0x0C, 0x0F, 0x07, 0x00
};
uint8_t buff_x[2][8] = {
0x20, 0x60, 0xC0, 0x80, 0xC0, 0x60, 0x20, 0x00, 
0x08, 0x0C, 0x07, 0x03, 0x07, 0x0C, 0x08, 0x00
};
uint8_t buff_y[2][8] = {
0xE0, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0x00, 
0x47, 0x4F, 0x48, 0x48, 0x68, 0x3F, 0x1F, 0x00
};
uint8_t buff_z[2][8] = {
0x60, 0x60, 0x20, 0xA0, 0xE0, 0x60, 0x20, 0x00, 
0x0C, 0x0E, 0x0B, 0x09, 0x08, 0x0C, 0x0C, 0x00
};

    void setup (){
      
      OLED_INIT ();
    }

    void loop (){
      clear_display ();
oled_printf ("      but0n     ");
oled_printf ("i do not know   ");delay(1000);
oled_printf ("how many bit    ");
oled_printf ("the char is     ");





//oled_printf ("                abcdefghijklmnopqrstuvwxyz");


while (1){}
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
                    
                    void clear_display (){
                            w_cmd (0xAE);
                            in = {0, 0};
                            uint8_t x, y; // x = SEG  [0:127]    y = PAGE  [0:7]
                            for (y = 0; y < 8; y++){
                                    w_cmd (0xB0 + y);  // Set Page Number 
                                    w_cmd (0x00);  //  Set Low  (4bit)
                                    w_cmd (0x10);  //  Set High (4bit)
                                    for (x = 0; x<128; x++)
                                            w_data (0x00);
                            
                            }
w_cmd (0xAF);
                    }
                    
                    
                    
           
    void oprint (uint8_t w, struct insert *in){
      
                uint8_t t, n;
                for (t = 0; t < 2; t++){
                            w_cmd (0xB0 + in->page + t);
                            w_cmd (in->start & 0x0F);
                            w_cmd (((in->start >> 4) & 0x0F) | 0x10);
                            for (n = 0; n < 8; n++){
                                            switch (w){
                                              
                                              case '0':  
                                              w_data (buff_0[t][n]);
                                              break;
                                              case '1':  
                                              w_data (buff_1[t][n]);
                                              break;
                                              case '2':  
                                              w_data (buff_2[t][n]);
                                              break;
                                              case '3':  
                                              w_data (buff_3[t][n]);
                                              break;
                                              case '4':  
                                              w_data (buff_4[t][n]);
                                              break;
                                              case '5':  
                                              w_data (buff_5[t][n]);
                                              break;
                                              case '6':  
                                              w_data (buff_6[t][n]);
                                              break;
                                              case '7':  
                                              w_data (buff_7[t][n]);
                                              break;
                                              case '8':  
                                              w_data (buff_8[t][n]);
                                              break;
                                              case '9':  
                                              w_data (buff_9[t][n]);
                                              break;
                                              case 'a':  
                                              w_data (buff_a[t][n]);
                                              break;
                                              case 'b':  
                                              w_data (buff_b[t][n]);
                                              break;
                                              case 'c':  
                                              w_data (buff_c[t][n]);
                                              break;
                                              case 'd':  
                                              w_data (buff_d[t][n]);
                                              break;
                                              case 'e':  
                                              w_data (buff_e[t][n]);
                                              break;
                                              case 'f':  
                                              w_data (buff_f[t][n]);
                                              break;
                                              case 'g':  
                                              w_data (buff_g[t][n]);
                                              break;
                                              case 'h':  
                                              w_data (buff_h[t][n]);
                                              break;
                                              case 'i':  
                                              w_data (buff_i[t][n]);
                                              break;
                                              case 'j':  
                                              w_data (buff_j[t][n]);
                                              break;
                                              case 'k':  
                                              w_data (buff_k[t][n]);
                                              break;
                                              case 'l':  
                                              w_data (buff_l[t][n]);
                                              break;
                                              case 'm':  
                                              w_data (buff_m[t][n]);
                                              break;
                                              case 'n':  
                                              w_data (buff_n[t][n]);
                                              break;
                                              case 'o':  
                                              w_data (buff_o[t][n]);
                                              break;
                                              case 'p':  
                                              w_data (buff_p[t][n]);
                                              break;
                                              case 'q':  
                                              w_data (buff_q[t][n]);
                                              break;
                                              case 'r':  
                                              w_data (buff_r[t][n]);
                                              break;
                                              case 's':  
                                              w_data (buff_s[t][n]);
                                              break;
                                              case 't':  
                                              w_data (buff_t[t][n]);
                                              break;
                                              case 'u':  
                                              w_data (buff_u[t][n]);
                                              break;
                                              case 'v':  
                                              w_data (buff_v[t][n]);
                                              break;
                                              case 'w':  
                                              w_data (buff_w[t][n]);
                                              break;
                                              case 'x':  
                                              w_data (buff_x[t][n]);
                                              break;
                                              case 'y':  
                                              w_data (buff_y[t][n]);
                                              break;
                                              case 'z':  
                                              w_data (buff_z[t][n]);
                                              break;
                                              case ' ':  
                                              w_data (0x00);
                                              break;                                       


                                            }  //switch
                            }//for
                  }
                  in->start += 8;
                  if (in->start == 128){
                          in->start = 0;
                          in->page += 2;
                  }
                  if (in->page == 10 ){
                          *in = {0, 0};
                          clear_display ();
                  }
    
    }

void oled_printf(char text[]) {
int c;
for (c = 0; c < 16; c++)
oprint (text[c], &in);

}

                                          
