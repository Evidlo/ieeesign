//Evan Widloski - 2014-01-26
//Purdue IEEE Sign Code

//time between each loop
int timer = 150;
//Register input pins
int REG1=5;
int REG2=6;
int REG3=7;
int REG4=8;
int REG5=9;
int REG6=10;
int REG7=11;
int REG8=12;
//An array representing all 64 leds on the board
boolean leds[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int leds_size=64;
//Clock pin for all registers
int CLK=13;

//Prints the entire array 'leds' to the display
void printLEDS(boolean leds[]){
  for(int pos=7; pos >= 0; pos--){     //Writes a boolean to each register and clocks them
    digitalWrite(REG8,leds[pos]);
    digitalWrite(REG7,leds[pos+8]);
    digitalWrite(REG6,leds[pos+16]);
    digitalWrite(REG5,leds[pos+24]);    
    digitalWrite(REG4,leds[pos+32]);
    digitalWrite(REG3,leds[pos+40]);
    digitalWrite(REG2,leds[pos+48]);
    digitalWrite(REG1,leds[pos+56]);
    digitalWrite(CLK,LOW); 
    digitalWrite(CLK,HIGH);
  }
}

//Wipes anything on the display
void clearDisplay(){
  for(int i = 0; i < leds_size; i++) {
    leds[i] = 0;
  } 
  printLEDS(leds);
}

//Animates a ball bouncing around the screen for a given number of iterations
void bounce(int cycles){
  for(int i=1;i<64;i++){
    leds[i]=0;
  }
  int x=0;
  int y=0;
  int last_x=0;
  int last_y=0;
  int x_dir=1;
  int y_dir=1;
  for(int cycles=0;cycles<80;cycles++){
    leds[(4*last_y)+last_x]=0;
    leds[(4*last_y)+last_x+32]=0;
    leds[(4*y)+x]=1;
    leds[(4*y)+x+32]=1;
    last_y=y;
    last_x=x;
    y+=y_dir;
    x+=x_dir;
    if(y>=(sizeof(leds)/8)-1 || y<=0){
      y_dir*=-1;
  
    }
    if(x>=3 || x<=0){
      x_dir*=-1;
    }
    printLEDS(leds);
    delay(timer);  
  }
}

//Animates propeller thingamobobs for a given number of cycles
void spin(int cycles){
  for(int cycles=0;cycles<5;cycles++){
    leds={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    printLEDS(leds);
    delay(timer);
    leds={0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0};
    printLEDS(leds);
    delay(timer);
    leds={0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0};
    printLEDS(leds);
    delay(timer);
    leds={0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0};
    printLEDS(leds);
    delay(timer);
    leds={0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0};
    printLEDS(leds);
    delay(timer);
    leds={0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0};
    printLEDS(leds);
    delay(timer);
  }
}

//Takes an array of given size (height, must be 4 wide) and shifts it into the leds[] array line by line
void printSymbol(boolean symbol[],int symbol_size){
  for(int symbol_row=0;symbol_row<symbol_size/4;symbol_row++ ){
    //Shift down all lines by one
    for(int i=leds_size-1;i>=4;i--){
      leds[i]=leds[i-4];
    }
    
    //Read top row from input into bottom row of leds
    for(int i=0;i<4;i++){
      leds[i]=symbol[symbol_row*4+i];
    }
    
//    DEBUG
//    for(int i=0;i<4;i++){
//      Serial.print(leds[i]);
//    }
//    Serial.println();
    
    printLEDS(leds);
    delay(timer);
  }

}

//Initialize all output pins
void setup(){
  pinMode(REG1,OUTPUT);
  pinMode(REG2,OUTPUT);
  pinMode(REG3,OUTPUT);
  pinMode(REG4,OUTPUT);
  pinMode(REG5,OUTPUT);
  pinMode(REG6,OUTPUT);
  pinMode(REG7,OUTPUT);
  pinMode(REG8,OUTPUT);
  pinMode(CLK,OUTPUT);
  Serial.begin(9600);
  
}

//Various symbols (letters) for printing out messages
boolean P[20]={1,1,1,1,
               1,0,0,1,
               1,1,1,1,
               1,0,0,0,
               1,0,0,0};
boolean U[20]={1,0,0,1,
               1,0,0,1,
               1,0,0,1,
               1,0,0,1,
               0,1,1,0};
boolean R[20]={1,1,1,1,
               1,0,0,1,
               1,1,1,1,
               1,0,1,0,
               1,0,0,1};
boolean D[20]={1,1,1,0,
               1,0,0,1,
               1,0,0,1,
               1,0,0,1,
               1,1,1,0};
boolean I[20]={1,1,1,1,
               0,1,1,0,
               0,1,1,0,
               0,1,1,0,
               1,1,1,1};
boolean E[20]={1,1,1,1,
               1,0,0,0,
               1,1,1,0,
               1,0,0,0,
               1,1,1,1};
boolean L[20]={1,0,0,0,
               1,0,0,0,
               1,0,0,0,
               1,0,0,0,
               1,1,1,1};
boolean J[20]={1,1,1,1,
               0,0,0,1,
               0,0,0,1,
               1,0,0,1,
               0,1,1,0};
boolean O[20]={1,1,1,1,
               1,0,0,1,
               1,0,0,1,
               1,0,0,1,
               1,1,1,1};
boolean H[20]={1,0,0,1,
               1,0,0,1,
               1,1,1,1,
               1,0,0,1,
               1,0,0,1};
boolean N[20]={1,1,0,1,
               1,1,0,1,
               1,0,1,1,
               1,0,1,1,
               1,0,0,1};
boolean S[20]={1,1,1,1,
               1,0,0,0,
               1,1,1,1,
               0,0,0,1,
               1,1,1,1};
boolean X[20]={1,0,0,1,
               0,1,1,0,
               0,1,1,0,
               1,0,0,1,
               1,0,0,1};
boolean B[20]={1,1,1,1,
               1,0,0,1,
               1,1,1,0,
               1,0,0,1,
               1,1,1,1};
boolean EXCLAIM[20]={
               0,1,1,0,
               0,1,1,0,
               0,1,1,0,
               0,0,0,0,
               0,1,1,0};
boolean PERIOD[20]={
               0,0,0,0,
               0,1,1,0,
               0,1,1,0,
               0,0,0,0,
               0,0,0,0};
boolean G[20]={1,1,1,1,
               1,0,0,0,
               1,0,1,1,
               1,0,0,1,
               1,1,1,1};
boolean space[8]={0,0,0,0,0,0,0,0};


void loop(){
  spin(4);
  clearDisplay();
  for(int i=0;i<8;i++){
    printSymbol(space,8);
  }

  printSymbol(P,20);
  printSymbol(space,8);
  printSymbol(U,20);
  printSymbol(space,8);
  printSymbol(R,20);
  printSymbol(space,8);
  printSymbol(D,20);
  printSymbol(space,8);
  printSymbol(U,20);
  printSymbol(space,8);
  printSymbol(E,20);
  printSymbol(space,8);
  printSymbol(space,8);
  printSymbol(I,20);
  printSymbol(space,8);
  printSymbol(E,20);
  printSymbol(space,8);
  printSymbol(E,20);
  printSymbol(space,8);
  printSymbol(E,20);
  printSymbol(space,8);
  printSymbol(space,8);
  printSymbol(space,8);
  printSymbol(B,20);
  printSymbol(space,8);
  printSymbol(O,20);
  printSymbol(space,8);
  printSymbol(I,20);
  printSymbol(space,8);
  printSymbol(L,20);
  printSymbol(space,8);
  printSymbol(E,20);
  printSymbol(space,8);
  printSymbol(R,20);
  printSymbol(space,8);
  printSymbol(space,8);
  printSymbol(U,20);
  printSymbol(space,8);
  printSymbol(P,20);
  printSymbol(space,8);
  printSymbol(EXCLAIM,20);
  printSymbol(space,8);
  printSymbol(space,8);
  printSymbol(P,20);
  printSymbol(space,8);
  printSymbol(I,20);
  printSymbol(space,8);
  printSymbol(E,20);
  printSymbol(space,8);
  printSymbol(E,20);
  printSymbol(space,8);
  printSymbol(E,20);
  printSymbol(PERIOD,20);
  printSymbol(O,20);
  printSymbol(space,8);
  printSymbol(R,20);
  printSymbol(space,8);
  printSymbol(G,20);
  printSymbol(space,8);
  printSymbol(space,8);
  printSymbol(space,8);
  printSymbol(space,8);
  for(int i=0;i<8;i++){
    printSymbol(space,8);
  }
  
  bounce(60);
  clearDisplay();
  for(int i=0;i<8;i++){
    printSymbol(space,sizeof(space));
  }


    //while(Serial.available() == 0){}
    //Serial.read();

  }


