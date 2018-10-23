/*
#define P1 A8
#define P2 A9
#define P3 A10
#define P4 A11
#define P5 A12
#define P6 A13
#define P7 A14
#define P8 A15
#define P9 A0
#define P10 A1
#define P11 A2
#define P12 A3
#define P13 A4
#define P14 A5
#define P15 A6 
#define P16 A7 
*/

#define P1 3
#define P2 5
#define P3 6
#define P4 9
#define P5 10
#define P6 11
#define P7 13
#define P8 -1
#define P9 -1
#define P10 A5
#define P11 A4
#define P12 A3
#define P13 A2
#define P14 A1
#define P15 A0 
#define P16 -1 

int Read(int port) {
  pinMode(port, INPUT);
  delay(200);
  return digitalRead(port);
}
/*
unsigned int xorshift(unsigned int xs) {
  xs ^= xs << 7;
  xs ^= xs >> 9;
  xs ^= xs << 8;
  return xs;
}
struct TestResult {
  int Passes;
  int Tests;
};
struct SocketSignals {
  unsigned int Signals = 0;
  bool AP1() { return 0 != (Signals & (1 << 0));};
  bool AP2() { return 0 != (Signals & (1 << 1));};
  bool AP3() { return 0 != (Signals & (1 << 2));};
  bool AP4() { return 0 != (Signals & (1 << 3));};
  bool AP5() { return 0 != (Signals & (1 << 4));};
  bool AP6() { return 0 != (Signals & (1 << 5));};
  bool AP7() { return 0 != (Signals & (1 << 6));};
  bool AP8() { return 0 != (Signals & (1 << 7));};
  bool AP9() { return 0 != (Signals & (1 << 8));};
  bool AP10() { return 0 != (Signals & (1 << 9));};
  bool AP11() { return 0 != (Signals & (1 << 10));};
  bool AP12() { return 0 != (Signals & (1 << 11));};
  bool AP13() { return 0 != (Signals & (1 << 12));};
  bool AP14() { return 0 != (Signals & (1 << 13));};
  bool AP15() { return 0 != (Signals & (1 << 14));};
  bool AP16() { return 0 != (Signals & (1 << 15));};

  void Apply() {
     analogWrite(P1, 0 != (Signals & (1 << 0)) ? 255 : 0);
     analogWrite(P2, 0 != (Signals & (1 << 1)) ? 255 : 0);
     analogWrite(P3, 0 != (Signals & (1 << 2)) ? 255 : 0);
     analogWrite(P4, 0 != (Signals & (1 << 3)) ? 255 : 0);
     analogWrite(P5, 0 != (Signals & (1 << 4)) ? 255 : 0);
     analogWrite(P6, 0 != (Signals & (1 << 5)) ? 255 : 0);
     analogWrite(P7, 0 != (Signals & (1 << 6)) ? 255 : 0);
//     analogWrite(P8, 0 != (Signals & (1 << 7)) ? 255 : 0);
//     analogWrite(P9, 0 != (Signals & (1 << 8)) ? 255 : 0);
     analogWrite(P10, 0 != (Signals & (1 << 9)) ? 255 : 0);
     analogWrite(P11, 0 != (Signals & (1 << 10)) ? 255 : 0);
     analogWrite(P12, 0 != (Signals & (1 << 11)) ? 255 : 0);
     analogWrite(P13, 0 != (Signals & (1 << 12)) ? 255 : 0);
     analogWrite(P14, 0 != (Signals & (1 << 13)) ? 255 : 0);
     analogWrite(P15, 0 != (Signals & (1 << 14)) ? 255 : 0);
//     analogWrite(P16, 0 != (Signals & (1 << 15)) ? 255 : 0);
delay(1000);
  }
};
/*
class IC {
  public:
    virtual int V();
    virtual int G();
    virtual int InputCount();
    virtual int Input(int number);
    virtual int OutputCount();
    virtual TestResult Score(SocketSignals in, SocketSignals out);
    virtual SocketSignals Test();
};

class IC_14_Pin {
    int V() { return P16; };
    int G() { return P7; };
};
class IC_14_Pin_Unary {
  
};
*/
void setup() {
  // put your setup code here, to run once:
  
  
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Hallo");
  
}

void loop() {
  Serial.println("GO!");
  /*unsigned int j = 1;
  for (int i = 0; i < 10;i++) {
    Serial.println(i);
    Serial.println((int)j);
    j = xorshift(j);
  }*/

  analogWrite(P7,0);
  //analogWrite(P16,255);
  analogWrite(P3, 0);
  analogWrite(P6,85);
  analogWrite(P10,130);
  analogWrite(P13,255);
  analogWrite(P1,0);
  analogWrite(P2,0);
  analogWrite(P4,0);
  analogWrite(P5,255);
  analogWrite(P11,255);
  analogWrite(P12,0);
  analogWrite(P14,255);
  analogWrite(P15,255);
  delay(300);
    Serial.println(String("P3: ") + Read(P3));
    Serial.println(String("P6: ") + Read(P6));
    Serial.println(String("P10: ") + Read(P10));
    Serial.println(String("P13: ") + Read(P13));
  
  delay(1000);/*/
  // put your main code here, to run repeatedly:
   SocketSignals ss;
   ss.Signals = 33811;
   Serial.println("Start Loop");
   for (int i = 0; i < 100; i++) {
    //ss.Signals = xorshift(ss.Signals);
    String s1 = "Signal: ";
    Serial.println(s1 + ss.Signals);

    Serial.println(String("P1: ") + ss.AP1());
    Serial.println(String("P2: ") + ss.AP2());
    Serial.println(String("P3: ") + ss.AP3());
    Serial.println(String("P4: ") + ss.AP4());
    Serial.println(String("P5: ") + ss.AP5());
    Serial.println(String("P6: ") + ss.AP6());
    Serial.println(String("P7: ") + ss.AP7());
    Serial.println(String("P10: ") + ss.AP10());
    Serial.println(String("P11: ") + ss.AP11());
    Serial.println(String("P12: ") + ss.AP12());
    Serial.println(String("P13: ") + ss.AP13());
    Serial.println(String("P14: ") + ss.AP14());
    Serial.println(String("P15: ") + ss.AP15());
    Serial.println(String("P16: ") + ss.AP16());
    
    Serial.println(String("P1: ") + Read(P1));
    ss.Apply();
    Serial.println(String("P2: ") + Read(P2));
    ss.Apply();
    Serial.println(String("P3: ") + Read(P3));
    ss.Apply();
    Serial.println(String("P4: ") + Read(P4));
    ss.Apply();
    Serial.println(String("P5: ") + Read(P5));
    ss.Apply();
    Serial.println(String("P6: ") + Read(P6));
    ss.Apply();
    Serial.println(String("P7: ") + Read(P7));
    ss.Apply();
    Serial.println(String("P10: ") + Read(P10));
    ss.Apply();
    Serial.println(String("P11: ") + Read(P11));
    ss.Apply();
    Serial.println(String("P12: ") + Read(P12));
    ss.Apply();
    Serial.println(String("P13: ") + Read(P13));
    ss.Apply();
    Serial.println(String("P14: ") + Read(P14));
    ss.Apply();
    Serial.println(String("P15: ") + Read(P15));
    ss.Apply();
    
    delay(10000);
   }
   /* SS.Apply();
     Serial.println();
   delay(200);
   Serial.println(sizeof(int));
   Serial.print(String(i) + " " + digitalRead(P14) + " " + analogRead(P14) + "\n");
   delay(200);
   }*/
  
}
