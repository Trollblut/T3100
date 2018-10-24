#include <TFT.h> // Hardware-specific library
#include <SPI.h>

//#define CS   10
//#define DC   9
//#define RESET  8

#define SCLK 52
#define MOSI 51
#define CS   10
#define DC   9
#define RESET 8 
#define ButtonRunter 3
#define ButtonHoch 4

int Menu1[2][4];
char* Menu1B[2];

int CheckedIndex = 0;

int ButtonValue = 2;

//TFT myScreen = TFT(CS, DC, MOSI, SCLK, RESET);
TFT myScreen = TFT(CS, DC, RESET);

void initializeMenu1()
{
    char* autoOption = "Automatische Erkennung";
    char* icWahlOption = "IC-Auswahl";
    Menu1B[0] = autoOption;
    Menu1B[1] = icWahlOption;
    
    Menu1[0][0] = 10;
    Menu1[0][1] = 10;
    Menu1[0][2] = 1;
    
    Menu1[1][0] = 10;
    Menu1[1][1] = 30;
    Menu1[1][2] = 0;
}

void setup() {
  Serial.begin(9600);
  myScreen.begin();
  myScreen.background(0,0,0);  // clear the screen with black
  myScreen.stroke(255, 255, 255);
  myScreen.setTextSize(1.2);
  
  initializeMenu1();
  delay(200); 
  
}



void loop() {

  for(int i = 0; i < (sizeof(Menu1B)/sizeof(char*)); i++) 
  {
    if(Menu1[i][2] == 1)
    {
      Serial.print("Haaalooooo ich werde Blaaaaau");
      Serial.println(i);
      myScreen.stroke(255, 20, 20);
      myScreen.text(Menu1B[i],int(Menu1[i][0]),int(Menu1[i][1]));
    }else
    {
      Serial.print("Ich muss weiß");
      Serial.println(i);
      myScreen.stroke(255, 255, 255);
      myScreen.text(Menu1B[i],int(Menu1[i][0]),int(Menu1[i][1]));
    }
  }

  

 int Runter = digitalRead(ButtonRunter);
 int Hoch = digitalRead(ButtonHoch);

if(ButtonValue ==1 && Runter == 0 && Hoch == 0)
  {
    delay(800);
    ButtonValue = 0;
  }

 Serial.print("Button Value");
 Serial.println(ButtonValue);
 Serial.print("runter");
 Serial.println(Runter);

 if(Runter == 1 && ButtonValue != Runter)
 {
  Serial.println("Changing!");
  ButtonValue = 1;
        
  if(CheckedIndex==(sizeof(Menu1B)/sizeof(char*)-1))
  {
    Menu1[CheckedIndex][2] = 0;
    Menu1[0][2] = 1;

    CheckedIndex = 0;
  }
  else
  {
    Serial.print("Setze meinen Nachfolger auf Checked");
    Serial.println(CheckedIndex);
    Menu1[CheckedIndex][2] = 0;
    Menu1[CheckedIndex+1][2] = 1;

    CheckedIndex++;
  }

 }



 if(Hoch == 1 && ButtonValue != Hoch)
 {
  Serial.println("Changing!");
  ButtonValue = 1;
        
  if(CheckedIndex==0)
  {
    Menu1[CheckedIndex][2] = 0;
    Menu1[sizeof(Menu1B)/sizeof(char*)-1][2] = 1;

    CheckedIndex = sizeof(Menu1B)/sizeof(char*)-1;
  }
  else
  {
    Serial.print("Setze meinen Vorgänger auf Checked");
    Serial.println(CheckedIndex);
    Menu1[CheckedIndex][2] = 0;
    Menu1[CheckedIndex-1][2] = 1;

    CheckedIndex--;
  }

 }

//  if(Menu1[0][2] == 1)
//  {
//  myScreen.stroke(255, 255, 255);
//  }
//  else
//  {
//  myScreen.stroke(255, 20, 20);
//  }
//  myScreen.text(Menu1B[0],int(Menu1[0][0]),int(Menu1[0][1]));
//  if(Menu1[1][2] == 1)
//  {
//  myScreen.stroke(255, 255, 255);
//  }
//  else
//  {
//  myScreen.stroke(255, 20, 20);
//  }
//  myScreen.text(Menu1B[1],Menu1[1][0],Menu1[1][1]);
  delay(1000); 
}
