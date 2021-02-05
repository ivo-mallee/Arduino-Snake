
#include <Wire.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)


#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
byte HeadX = 64;
byte HeadY = 32;
byte XSegment[210] = {1};
byte YSegment[210] = {1};
byte FoodX;
byte FoodY;
byte SegmentsFree =0;
const int AX = A0;
const int AY = A3;
const int AButton = 8;
const int BButton = 9;
byte FoodAmount = 10;
int Move =1;
bool gameState = true;
void setup() {

 display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)


  Serial.begin(9600);
 pinMode(AButton,INPUT_PULLUP);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.display(); 
  PopulateWorld(10);
}

void loop() {

delay(10);
display.clearDisplay();
UpdateSegment();
MoveSnake();
DrawFood();
DrawSnek();
CheckCollision(); 
}







void DrawSnek() 
{
  display.drawPixel(HeadX,HeadY,WHITE);
  for (int i =0; i<= SegmentsFree;i++) 
  {
    display.drawPixel(XSegment[i],YSegment[i],WHITE);
    
  }
  
  
  
  display.display();
}

void DrawFood() 
{
  display.drawCircle(FoodX,FoodY,2,WHITE);
}








int GetDir() 
{
  while (true){
  if (analogRead(AX) < 172) {return 1; break;} //left
  if (analogRead(AX) > 570) {return 2; break;} //right
  if (analogRead(AY) < 150) {return 3; break;} //down
  if (analogRead(AY) > 550) {return 4; break;} //up
  return 6;
  
  break;
  }
}


void CheckCollision() 
{
  if (HeadX <= FoodX+2 && HeadX >= FoodX-2 && HeadY <= FoodY+2 && HeadY >= FoodY-2) {PopulateWorld(1); if(SegmentsFree <= 200) {SegmentsFree+=5; }  Serial.println("HIT");}
    
    
    for (int i =1; i<= SegmentsFree;i++) 
  {
    if (XSegment[i] == HeadX && YSegment[i] == HeadY) {gameState = false;}
    
  }
  
}







void MoveSnake() 
{

if (gameState == false) {HeadX = 255; HeadY=255;}
  switch (GetDir()) 
  {
    case 1:
    HeadX--;
    break;
    case 2:
    HeadX++;
    break;    
    case 4:
    HeadY--;
    break;    
    case 3:
    HeadY++;
    break;    
   default:
    NoMove();
    break;
  }
 
 if (GetDir() != 6){
 Move = GetDir();  
 }
  
  
  
  
  
  
  
  
  
  
  
  
    
}    
    
    
    
    
void NoMove(){
  switch (Move) 
  {
    case 1:
    HeadX--;
    break;
    case 2:
    HeadX++;
    break;    
    case 4:
    HeadY--;
    break;    
    case 3:
    HeadY++;
    break;    
   default:
   HeadX++;
    break;
  }
}  
  
void UpdateSegment() 
{

  for (int i =SegmentsFree ; i> 0;i--)  
  {
    
     YSegment[i] = YSegment[i-1];
     XSegment[i] = XSegment[i-1];
  }
  XSegment[0] = HeadX;
  YSegment[0] = HeadY;
  
}  
  
  
void PopulateWorld(int amount) 
{
  FoodX = random(1,128);
  FoodY = random(1,64);
  
}  
  
void moveleft() 
{ 
  if (HeadX-1 != XSegment[0] && HeadY-1 != YSegment[0]) {HeadX--;} else {Serial.println("ERROR");}
  
}
  
  
  
  
  
  
    



  

    
    
    
    
    
    
    
    
    
    
    
    
    
  
  
