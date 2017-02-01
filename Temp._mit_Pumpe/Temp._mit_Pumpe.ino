

#include <DHT.h>


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000001, B10000000,
  B00000011, B11000000,
  B00000111, B11100000,
  B00001111, B11110000,
  B00011111, B11111000,
  B00111111, B11111100,
  B01111111, B11111110,
  B11111111, B11111111,
  B01111111, B11111110,
  B00111111, B11111100,
  B00011111, B11111000,
  B00001111, B11110000,
  B00000111, B11100000,
  B00000011, B11000000,
  B00000001, B10000000,
  B00000000, B00000000};

#define SSD1306_LCDHEIGHT 64

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define DHTPIN D3 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

unsigned long Time  =0;
unsigned long Time2 =0;
unsigned long Time3 =0;
unsigned long Time4 =0;
int temp=analogRead(A0);
int water=digitalRead(D7);
int h;
int t;
int wend = 0;
int wenden = 1;
int tmin = 413;
int tmax = 400;
int hmin = 50;
int tsoll = 38;

void setup() {
 pinMode(D0, INPUT);  //Schwimmerschalter
                      //D1+2 durch Display belegt
                      //D3 DHT
 pinMode(D4, OUTPUT); //Pumpe
 pinMode(D5, OUTPUT); //Nebler
 pinMode(D6, OUTPUT); //Heizfolie
 pinMode(D7, OUTPUT); //Wender
 pinMode(D8, OUTPUT); //Wender
 pinMode(10, INPUT);  //Modusschalter
 Serial.begin(9600);
 digitalWrite(D7, LOW);
 digitalWrite(D8, LOW);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
 display.display();
 
}
//Wert 37,8Grad Celsius~407 
//Wert 38 Grad Celsius~405
//1Grad entsprechen 9,8 Einheiten

  void drop(int x, int y){  
  display.drawLine(x+6,y-2,x,y+6, WHITE); //(x,y,x,y)
  display.drawLine(x,y+6,x,y+9, WHITE); //(x,y,x,y)
  display.drawLine(x,y+9,x+3,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+3,y+12,x+9,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+9,y+12,x+12,y+9, WHITE); //(x,y,x,y)
  display.drawLine(x+12,y+9,x+12,y+6, WHITE); //(x,y,x,y)
  display.drawLine(x+12,y+6,x+6,y-2, WHITE); //(x,y,x,y)
  display.display();
  }
  void filldrop( int x, int y){
  display.drawLine(x,y+6,x,y+9, WHITE); //(x,y,x,y)
  display.drawLine(x+1,y+5,x+1,y+10, WHITE); //(x,y,x,y)
  display.drawLine(x+2,y+3,x+2,y+11, WHITE); //(x,y,x,y)
  display.drawLine(x+3,y+2,x+3,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+4,y+1,x+4,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+5,y-1,x+5,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+6,y-2,x+6,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+7,y-1,x+7,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+8,y+1,x+8,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+9,y+2,x+9,y+12, WHITE); //(x,y,x,y)
  display.drawLine(x+10,y+3,x+10,y+11, WHITE); //(x,y,x,y)
  display.drawLine(x+11,y+5,x+11,y+10, WHITE); //(x,y,x,y)
  display.drawLine(x+12,y+6,x+12,y+9, WHITE); //(x,y,x,y)
  display.display();
  }

void pump (){
    if (water==0){
      digitalWrite(D2, HIGH);
    }
    else{
     digitalWrite(D2, LOW);
    }
  }

void nebler() {
  if (h<hmin){
    digitalWrite(D5, HIGH);
  }
  else{
    digitalWrite(D5, LOW);
  }
}


void heizfolie (){
 if (temp >= tmin){
   digitalWrite(D1, LOW);
 }
 if (temp <= tmax){
   digitalWrite(D1, HIGH);
 }
}

void wender(){
  if (millis()-Time3>28800000){
    if(wend%4<2){
     digitalWrite(D7, HIGH);
     if(millis()-Time4>1500){
      digitalWrite(D7, LOW);
      Time4=millis();
      wend++;
     }
    }
    if(wend%4>=2){
     digitalWrite(D8, HIGH);
     if(millis()-Time4>1500){
      digitalWrite(D8, LOW);
      Time4=millis();
      wend++;
     }
    }
    Time3=millis();
  }
}

void Display() {

   int x=57;
   int y=42;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);           //Cursor: (x;y)
  display.println("Soll:");
  display.print("F:   ");
  display.print(hmin);
  display.println("%");
  display.print("T:   ");
  display.print(t);
  display.println("C");
  display.print("min: ");
  display.println(tmin);
  display.print("max: ");
  display.println(tmax);
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(64,0);           //Cursor: (x;y)
  display.print("Ist:");
  display.setCursor(64,8);
  display.print("F:     ");
  display.print(h);
  display.print("%");
  display.setCursor(64,16);
  display.print("Temp:  ");
  display.print(t);
  display.print("C");
  display.setCursor(64,24);
  display.print("analog:");
  display.print(temp);
  display.display();
  if (temp >= tmin){
    display.fillRect(0,42,42,20, WHITE); //(x,y,b,h)
    display.display();
  }
  if (temp <= tmax){
    display.drawRect(0,42,50,20, WHITE); //(x,y,b,h)
    display.display();
  }
  if(h<hmin){
    filldrop(94,40);
    filldrop(110,45);
    display.display();
  }
  else{
    drop(94,40);
    drop(110,45);
    display.display();
  }
  if(wenden==0){
    display.drawRect(x,y,25,16, WHITE);
    display.drawTriangle(x+24,y-5,x+24,y+21,x+35,y+8, WHITE);    //x,y,x,y,x,y
    display.display();
  }
  if(wenden==1){
  display.fillRect(x,y,25,16, WHITE);
  display.fillTriangle(x+24,y-5,x+24,y+21,x+35,y+8, WHITE);    //x,y,x,y,x,y
  display.display();
  }
  Serial.print("Temperatur:   ");
  Serial.print(t);
  Serial.println("*C");
  Serial.print("Luftfeuchte:   ");
  Serial.print(h);
  Serial.println("%");
}

void loop() {

  temp=analogRead(A0);
  water=digitalRead(D7);
  int modus = digitalRead(9);

  if(modus==1&&wenden>0){
    tmin = 420;
    tmax = 410;
    tsoll=37;
    hmin = 80;
    wenden = 0;
  }

  if(modus==1&&wenden==0){
    tmin = 413;
    tmax = 400;
    tsoll=38;
    hmin = 50;
    wenden = 1;
  }

      
  if(millis()-Time<10000){
    h=dht.readHumidity();
    t=dht.readTemperature();
    nebler();
    Display();
    Time = millis();
  }
  if(wenden==1){
    wender();
  }
  pump();
  heizfolie();
}
