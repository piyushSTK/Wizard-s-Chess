/********************************************************************
 *ChessRobotControl.ino Robot Control File                                   *
 *Witten by Nicholas Maselli                                        *
 and modified for personal use for project in Wizards Chess   
 this code has x y plotter with servo control 90 degree rotation*
 ********************************************************************/
/*log  the z has been handleled 
 * others need to be done
 * 1 april i think the code is done lookout  10 5v 11 gnd
 for mechanical problems 
 z precisemove thik karna hai
 
 
 
 */


 
#include <Stepper.h>
#include <Servo.h> 
#include <Wire.h>


int XSwitch = 1;
int YSwitch = 1;
Servo myservo;
const int stepc=2366;
const int steph=1183;
const int stepsPerLimit = 1;
const int stepsPerRevolution = 200;
const int stepsPerTile = 65*stepsPerRevolution;
#define x1 28
#define x2 26
#define x3 24
#define x4 22
#define y1 29
#define y2 27
#define y3 25
#define y4 23
#define sw1 2
#define sw2 3
#define sw3 4
#define act 5
int Xpul = 6;
int Xdir = 7;
int Ypul = 8;
int Ydir = 9;
int Zpul = 10;
int Zdir = 11;
int nocaptured=0;

const int Xinit=8;
const int Yinit=9;


/*Precise Position variables*/
int XPrecisePosition = 0;
int YPrecisePosition = 0;


int XCoordinates[8];
int YCoordinates[8];


int XCaptureCoordinates[16];
int YCaptureCoordinates[16];

/*Player Color*/
bool color = 0;

/*Capture variables*/
byte captures = 0;
bool holding = 0;

/*Detection Variables*/
byte board_length = 8;
byte board_total = 64;

byte numberOfChanges = 0;
byte changes[4];
byte changeType[4];
byte moveArray[4];

byte squares[64];
byte check_squares[64];



//Stepper XStepper(stepsPerRevolution, Xdir, Xpul); 
//Stepper YStepper(stepsPerRevolution, Ydir, Ypul);
//Stepper ZStepper(stepsPerRevolution, Zdir, Zpul);
/////////////////////////////////motor control functions/////////////////////////

/////////////////////////////////movexf
void movexf(int steps){
  int x=0;
  int cstep=0;
  while(x<steps)
  {
  switch(cstep)
  {
   case 0:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, LOW);
     digitalWrite(x4, HIGH);
   break; 
   case 1:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, HIGH);
     digitalWrite(x4, HIGH);
   break; 
   case 2:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, HIGH);
     digitalWrite(x4, LOW);
   break; 
   case 3:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, HIGH);
     digitalWrite(x3, HIGH);
     digitalWrite(x4, LOW);
   break; 
   case 4:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, HIGH);
     digitalWrite(x3, LOW);
     digitalWrite(x4, LOW);
   break; 
   case 5:
     digitalWrite(x1, HIGH); 
     digitalWrite(x2, HIGH);
     digitalWrite(x3, LOW);
     digitalWrite(x4, LOW);
   break; 
     case 6:
     digitalWrite(x1, HIGH); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, LOW);
     digitalWrite(x4, LOW);
   break; 
   case 7:
     digitalWrite(x1, HIGH); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, LOW);
     digitalWrite(x4, HIGH);
   break; 
   default:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, LOW);
     digitalWrite(x4, LOW);
   break; 
  }
   x++;
   cstep=cstep+1;
   if(cstep==8)
     {cstep=0;}
    delayMicroseconds(1500); 
   }
   XPrecisePosition+=steps;
}
//////////////////////////////////////////movexbackwards
void movexb(int steps){
  int x=0;
  int cstep=8;
  while(x<steps)
  {
  switch(cstep)
  {
   case 0:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, LOW);
     digitalWrite(x4, HIGH);
   break; 
   case 1:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, HIGH);
     digitalWrite(x4, HIGH);
   break; 
   case 2:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, HIGH);
     digitalWrite(x4, LOW);
   break; 
   case 3:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, HIGH);
     digitalWrite(x3, HIGH);
     digitalWrite(x4, LOW);
   break; 
   case 4:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, HIGH);
     digitalWrite(x3, LOW);
     digitalWrite(x4, LOW);
   break; 
   case 5:
     digitalWrite(x1, HIGH); 
     digitalWrite(x2, HIGH);
     digitalWrite(x3, LOW);
     digitalWrite(x4, LOW);
   break; 
     case 6:
     digitalWrite(x1, HIGH); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, LOW);
     digitalWrite(x4, LOW);
   break; 
   case 7:
     digitalWrite(x1, HIGH); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, LOW);
     digitalWrite(x4, HIGH);
   break; 
   default:
     digitalWrite(x1, LOW); 
     digitalWrite(x2, LOW);
     digitalWrite(x3, LOW);
     digitalWrite(x4, LOW);
   break; 
  }
   x++;
   cstep=cstep-1;
   if(cstep==0)
     {cstep=8;}
    delayMicroseconds(1500); 
   }
   XPrecisePosition-=steps;
}

///////////////////////////////////////moveyforward////////////////////////
void moveyf(int steps){
  int x=0;
  int cstep=0;
  while(x<steps)
  {
  switch(cstep)
  {
   case 0:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, LOW);
     digitalWrite(y4, HIGH);
   break; 
   case 1:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, HIGH);
     digitalWrite(y4, HIGH);
   break; 
   case 2:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, HIGH);
     digitalWrite(y4, LOW);
   break; 
   case 3:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, HIGH);
     digitalWrite(y3, HIGH);
     digitalWrite(y4, LOW);
   break; 
   case 4:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, HIGH);
     digitalWrite(y3, LOW);
     digitalWrite(y4, LOW);
   break; 
   case 5:
     digitalWrite(y1, HIGH); 
     digitalWrite(y2, HIGH);
     digitalWrite(y3, LOW);
     digitalWrite(y4, LOW);
   break; 
     case 6:
     digitalWrite(y1, HIGH); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, LOW);
     digitalWrite(y4, LOW);
   break; 
   case 7:
     digitalWrite(y1, HIGH); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, LOW);
     digitalWrite(y4, HIGH);
   break; 
   default:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, LOW);
     digitalWrite(y4, LOW);
   break;
  }
   x++;
   cstep=cstep+1;
   if(cstep==8)
     {cstep=0;}
    delayMicroseconds(1500); 
   }
   YPrecisePosition+=steps;

}
//////////////////////////////////////////moveybackwards
void moveyb(int steps){
  int x=0;
  int cstep=8;
  while(x<steps)
  {
  switch(cstep)
  {
   case 0:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, LOW);
     digitalWrite(y4, HIGH);
   break; 
   case 1:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, HIGH);
     digitalWrite(y4, HIGH);
   break; 
   case 2:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, HIGH);
     digitalWrite(y4, LOW);
   break; 
   case 3:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, HIGH);
     digitalWrite(y3, HIGH);
     digitalWrite(y4, LOW);
   break; 
   case 4:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, HIGH);
     digitalWrite(y3, LOW);
     digitalWrite(y4, LOW);
   break; 
   case 5:
     digitalWrite(y1, HIGH); 
     digitalWrite(y2, HIGH);
     digitalWrite(y3, LOW);
     digitalWrite(y4, LOW);
   break; 
     case 6:
     digitalWrite(y1, HIGH); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, LOW);
     digitalWrite(y4, LOW);
   break; 
   case 7:
     digitalWrite(y1, HIGH); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, LOW);
     digitalWrite(y4, HIGH);
   break; 
   default:
     digitalWrite(y1, LOW); 
     digitalWrite(y2, LOW);
     digitalWrite(y3, LOW);
     digitalWrite(y4, LOW);
   break; 
  }
   x++;
   cstep=cstep-1;
   if(cstep==0)
     {cstep=8;}
    delayMicroseconds(1500); 
   }
   YPrecisePosition-=steps;

}


void halfmovef()

{
  int i=0;
  
    movexf(steph);
  
  XPrecisePosition+=steph;
  i=0;
  
  
    moveyf(steph);
  
  YPrecisePosition+=steph;
}
void halfmoveb()

{
  int i=0;
  
  
    movexb(steph);
  
  XPrecisePosition-=steph;
  i=0;
  
  
    moveyb(steph);
  
  YPrecisePosition-=steph;
}

////////////////////////////////////////////////////////////////////////////////////////
void playerBlack();
void playerWhite();
void PlayerInput();
void ComputerInput();
void home();
void XHome();
void YHome();
void calibrateCoordinates();
void XPreciseMove(int newPosition);
void YPreciseMove(int newPosition);
void ZPreciseMove(int newPosition);
bool getPlayerColor();
String serialInput();
void turn(String command);
void preciseMove(int file, int rank);
void preciseCapture();
void setSquares() ;
void detectChanges();
void calculateMove();
void resetChanges();
void printSquares();
void XPreciseInput();
void YPreciseInput();
void correctCheckSquares();

/////////////////////////////////////////////////////////////////////////////////////////////



void setup() {
  
//  1400 max speed for x and y, 1200 for z
//  XStepper.setSpeed(1400); 
//  YStepper.setSpeed(1400); 
//  ZStepper.setSpeed(1200);
  calibrateCoordinates();
  
  //pinMode(7,OUTPUT);
  
  myservo.attach(7);
  Serial.begin(9600); 
  Serial1.begin(9600);
  //Initialize moves
  for (int i=0; i < 4; i++) {
    changes[i] = 64;
    changeType[i] = 2;
    moveArray[i] = 64;
  }  
  
  //Initialize squares
  for (int i=0; i < board_total; i++) {
    squares[i] = 1;
  }
  
  /////////
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  pinMode(Xinit,OUTPUT);            //these 2 for the the limit switches
  pinMode(Yinit,OUTPUT);
  
  //Set the detection y pins
//  pinMode(py0, OUTPUT);
//  pinMode(py1, OUTPUT);
//  pinMode(py2, OUTPUT);
//  pinMode(py3, OUTPUT); 
//  pinMode(py4, OUTPUT);
//  pinMode(py5, OUTPUT);
//  pinMode(py6, OUTPUT);
//  pinMode(py7, OUTPUT);
//  //set the detection x pins
//  pinMode(px0, INPUT);
//  pinMode(px1, INPUT);
//  pinMode(px2, INPUT);
//  pinMode(px3, INPUT); 
//  pinMode(px4, INPUT);
//  pinMode(px5, INPUT);
//  pinMode(px6, INPUT);
//  pinMode(px7, INPUT);

  

  //motor control pins
  pinMode(x1, OUTPUT);  
  pinMode(x2, OUTPUT); 
  pinMode(x3, OUTPUT); 
  pinMode(x4, OUTPUT); 
  pinMode(y1, OUTPUT);  
  pinMode(y2, OUTPUT); 
  pinMode(y3, OUTPUT); 
  pinMode(y4, OUTPUT);
  //switches of user interface initilisation
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);

  //hit switches
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  delay(700);
  digitalWrite(13,LOW);
  delay(700);
  digitalWrite(13,HIGH);
  delay(700);
  digitalWrite(13,LOW);
  delay(700);
  digitalWrite(13,HIGH);
  delay(700);
  digitalWrite(13,LOW);
  delay(700);
  color=getPlayerColor(); 
  digitalWrite(13,HIGH);
  
  //ZPreciseMove(1);
  //ZPreciseMove(-1);
  home();
  ////setSquares();                                               //////might change these functions for initial state
  for(int i=0;i<16;i++)
  {
    squares[i]=0;
  }
  for(int i=48;i<64;i++){
    squares[i]=0;
  }
  
  
  correctCheckSquares(); 

  if (color == 0) {
    playerWhite();
  }

  if (color == 1) {
    playerBlack();
  }
}

void playerWhite() {
  while(true) {
     /*Player Input*/
    PlayerInput();
    
    /*Computer Input*/
    ComputerInput();  
  }
}

void playerBlack() {
  while(true) {
    /*Computer Input*/
    ComputerInput();
    
    /*Player Input*/
    PlayerInput();
  }
}



void loop() {
}

/*Takes in player input by moving pieces on the board and
  relays this information to python through serial port*/
void PlayerInput() {
  //setSquares();                                       ///loookout for this
  resetChanges();
  
  while(digitalRead(sw1) == 0) {    
    Serial.print("Number of changes:");
    Serial.println(numberOfChanges);

    printSquares();
    if(digitalRead(sw2)==1){
      setSquares();
      Serial1.println("setsq ke bahar") ;
    }   
    
    detectChanges();

    //Allows player to reset board if computer makes an error
//    if (digitalRead(sw2) == 1) {
//      numberOfChanges = 0;
//    }

    //Allows player to home robot if arm makes a mechanical error
    if (digitalRead(sw3) == 1) {
      home();
    }
    
    delay(1000);
  }
  
  Serial.print("Final number of changes:");
  Serial.println(numberOfChanges);

  calculateMove();
  if (numberOfChanges == 2) {
    Serial.print("x");
    Serial.write(moveArray[0]);
    Serial.write(moveArray[1]);
  }

  if (numberOfChanges == 3) {
    Serial.print("y");
    Serial.write(moveArray[0]);
    Serial.write(moveArray[2]);
  }

  if (numberOfChanges == 4) {
    Serial.print("z");
    Serial.write(moveArray[0]);
    Serial.write(moveArray[1]);
 }

   resetChanges();
  delay(1000);
}

void ComputerInput() {
  String input = serialInput();
  turn(input);
  delay(1000);
}

/*******************************************/
/*****   X, Y, and Z home functions    *****/
/*******************************************/
void home() {
  ZHome();
   digitalWrite(13,LOW);
  delay(700);
  digitalWrite(13,HIGH);
  YHome();
   digitalWrite(13,LOW);
  delay(700);
  digitalWrite(13,HIGH);
  XHome(); 
}

void XHome() {
  //XSwitch = mcp2.digitalRead(15);
  digitalWrite(Xinit,HIGH);
  XSwitch = digitalRead(16);
  while(XSwitch != 1) {
    movexb(70);
    //XSwitch = mcp2.digitalRead(15);
    XSwitch = digitalRead(16);
    //Serial.println(XSwitch);  
  }
  digitalWrite(Xinit,LOW);
  XPrecisePosition = 0;
  Serial.println("X Limit Switch Hit");
  delay(500);
}

void YHome() {
  digitalWrite(Yinit,HIGH);
  YSwitch = digitalRead(15); 
  while(YSwitch != 1) {             
    moveyb(70);
    YSwitch = digitalRead(15);    
  }
  digitalWrite(Yinit,LOW);
  YPrecisePosition = 0;
  Serial.println("Y Limit Switch Hit"); 
}

void ZHome()
{
//  if (holding == 1) {
//    ZPreciseMove(-1);
//    holding = 0;
//  }
//  else {
//   //ServoMove(90);
//   ZPreciseMove(1);
//
//   holding = 1;    
//  }
  myservo.write(0);
  holding=0;
}

/**********************************************/
/***** X, Y, and Z precise move functions *****/
/**********************************************/

/*Manual coordinate calibration*/

void calibrateCoordinates() {

  XCoordinates[0]=0;
  XCoordinates[1]=2366;
  XCoordinates[2]=4732;
  XCoordinates[3]=7098;
  XCoordinates[4]=9464;
  XCoordinates[5]=11830;
  XCoordinates[6]=14196;
  XCoordinates[7]=16562;

  YCoordinates[0]=0;
  YCoordinates[1]=2366;
  YCoordinates[2]=4732;
  YCoordinates[3]=7098;
  YCoordinates[4]=9464;
  YCoordinates[5]=11830;
  YCoordinates[6]=14196;
  YCoordinates[7]=16562;

  XCaptureCoordinates[0]=18928;
  XCaptureCoordinates[1]=21294;

 
  YCaptureCoordinates[0]=0;
  YCaptureCoordinates[1]=2366;
  YCaptureCoordinates[2]=4732;
  YCaptureCoordinates[3]=7098;
  YCaptureCoordinates[4]=9464;
  YCaptureCoordinates[5]=11830;
  YCaptureCoordinates[6]=14196;
  YCaptureCoordinates[7]=16562;


}

void XPreciseMove(int newPosition) {
  int revolutions = newPosition - XPrecisePosition;
  Serial.print("X Move new precise position: ");
  Serial.println(newPosition);

  //Using loops because arduino can't handle large numbers
  if (revolutions < 0) {
  
        movexb(-revolutions);
    
    delay(500);
  }
  else if (revolutions > 0) {
    
        movexf(revolutions);
        
      delay(500);
    }
  XPrecisePosition = newPosition;
}

void YPreciseMove(int newPosition) {
  int revolutions = newPosition - YPrecisePosition;
  Serial.print("Y Move new precise position: ");
  Serial.println(newPosition);

  //Using loops because arduino can't handle large numbers
  if (revolutions < 0) {
    
        moveyb(-revolutions);
    
    delay(500);
  }
  else if (revolutions > 0) {
    
        moveyf(revolutions);
      
      delay(500);   
    } 
  YPrecisePosition = newPosition;
}

void ZPreciseMove(int newPosition){
  int pos;
  if(newPosition==1)
  {
//    for(pos=0;pos<=90;pos++)
    {

      myservo.write(90);
      delay(40);
      holding=1;
    }
  }
  else if(newPosition==-1)
  {
//    for(pos=90;pos<=0;pos--)
    {

      myservo.write(0);
      delay(40);
      holding=0;
    }
  }

    
}
//
//void ServoMove(int state) {
//  delay(500);
//  gripservo.write(state);
//  delay(500);
//}

/*******************************/
/***** Get player function *****/
/*******************************/
bool getPlayerColor() {
  String str = "";

  //Must wait for serial input to become available
  if (!Serial.available()) {
    Serial.print("R");
  }
  while(!Serial.available()) { //Initial while loop to catch buffered data
  }
  
  while (Serial.available()) { //Ensures data is only read when it is available                         ///////the communication dealis going here
    delay(30);
    if (Serial.available() > 0) {
      char input = Serial.read(); //Obtain 1 byte from input move
      str += input;
    }
    else {
      break;
    }
  }

  if (str == "white") {
    return(0);
  }
  else if (str == "black") {
    return(1);
  }
  else {
    Serial.println("Error, white or black not chosen");
    Serial.println(str);
    return(0);  
  }
  
}

/**************************************************/
/***** Player turn and serial input functions *****/
/**************************************************/

/*Function for parsing the serial input from Python*/
String serialInput() {
  String str = "";

  //Must wait for serial input to become available
  if (!Serial.available()) {
    Serial.println("Waiting for move");
  }
  while(!Serial.available()) { //Initial while loop to catch buffered data
  }
  
  while (Serial.available()) { //Ensures data is only read when it is available    
    delay(30);
    if (Serial.available() > 0) {
      char input = Serial.read(); //Obtain 1 byte from input move
      str += input;
    }
    else {
      break;
    }
  }
  return(str);
}
String serial1Input() {
  String str = "";

  //Must wait for serial input to become available
  if (!Serial1.available()) {
    Serial1.println("Waiting for move");
  }
  while(!Serial1.available()) { //Initial while loop to catch buffered data
  }
  
  while (Serial1.available()) { //Ensures data is only read when it is available    
    delay(30);
    if (Serial1.available() > 0) {
      char input = Serial1.read(); //Obtain 1 byte from input move
      str += input;
    }
    else {
      break;
    }
  }
  Serial1.println(str);
  return(str);
}

/*Function processes robot's move from the serial input string*/
void turn(String command) {
  Serial.println("In turn");
  int length = command.length();
  Serial1.println(command);
  int inputs = 0;
  int file = 1;
  int rank = 1;
  if(length==4){
    preciseMove(int(command[0])-48,int(command[1])-48);
    preciseMove(int(command[2])-48,int(command[3])-48);
  }
  else if(length==7){
    preciseMove(int(command[0])-48,int(command[1])-48);
    preciseCapture();
    preciseMove(int(command[3])-48,int(command[4])-48);
    preciseMove(int(command[5])-48,int(command[6])-48);
    
  }
//  for (int i = 0; i < length; i++) {
//    if (command[i] != 't') {
//      if (inputs == 0) {
//        file = command[i]-48; //-48 because string is converting to ascii characters
//        inputs = inputs + 1;
//      }
//      else {
//        rank = command[i]-48; //-48 because string is converting to ascii characters
//        inputs = 0;        
//      }
//    }
//    else if (command[i] == 't') {
//      preciseCapture();
//      continue;
//    }
//
//    /*Make move*/
//    if (inputs == 0) {
//      preciseMove(file, rank);
//    }
//  }  
}

/**************************/
/***** Move functions *****/
/**************************/
void preciseMove(int file, int rank) {
  
  /*Convert file and rank to proper revolutions using the arrays
    and then precise move them*/
  int XNewPosition = XCoordinates[file-1];
  int YNewPosition = YCoordinates[rank-1];
  //int ZNewPosition = ZCoordinates[file-1][rank-1];
  
  YPreciseMove(YNewPosition);
  XPreciseMove(XNewPosition);
  halfmovef();
  /*Test Code*/
 
  
  if (holding == 1) {
    ZPreciseMove(-1);
    holding = 0;
  }
  else {
   //ServoMove(90);
   ZPreciseMove(1);

   holding = 1;    
  }
  halfmoveb();  
}

/*Move to capture currently held piece*/
void preciseCapture() {
  int XNewPosition;
  int YNewPosition;
  /*Convert file and rank to proper revolutions using the arrays
    and then precise move them */
  captures = captures + 1;
  if(captures<=8)
  {
    XNewPosition = XCaptureCoordinates[1];
  }
  else
  {
    XNewPosition = XCaptureCoordinates[0];
  }  


  
  if(captures<=8)
  {
    YNewPosition = YCaptureCoordinates[captures];
  }
  else
  {
    YNewPosition = YCaptureCoordinates[captures-8];
  }

  captures+=1;

  //YFirst to avoid hitting wood
  YPreciseMove(YNewPosition);
  XPreciseMove(XNewPosition);  
   halfmovef();
  
  //ServoMove(90);
  ZPreciseMove(-1);

  holding = 0;
  halfmoveb();
}

/*******************************/
/***** Detection functions *****/
/*******************************/

/*Sets the squares for the array representing the chessboard*/
void setSquares() {  
  String str=serial1Input();
  delay(60);
  
  //Serial1.println("here in set squares");
  delay(30);
  //Serial1.println(str);
  //int p=5;
  int file=1;
  int rank=1;
  int i;
  Serial1.println(str);
//  for(i=0;i<5;i++)
//  {
//    if(i==0){
//      file=int(str[i])-65;
//    }
//    else if(i==1){
//      rank=int(str[i])-48;
//      squares[8*file+rank]=1;
//    }
//    else if(i=3)
//    {
//      file=int(str[i])-65;
//    }
//    else if(i==4){
//      rank=int(str[i])-48;
//      squares[8*file+rank]=0;
//    }
//    Serial1.println("lol");
//    
//  }
squares[(int(str[0])-65)+8*(int(str[1])-49)]=1;
squares[(int(str[3])-65)+8*(int(str[4])-49)]=0;
  delay(30);
  Serial1.println("hogaya");
//  for (int j = 0; j < 8; j++) {
//    for (int i = 0; i < 8; i++) {
//      Serial1.print(squares[(7-j)*8 + i]);
//    }
//    Serial1.println("");
//  }
  
  
}
  
  
  
  
  


/*Detects changes in the squares (board representation) array*/
void detectChanges() {
  bool movedPiece = false;
  for (int i=0; i < board_total; i++) {
    if (check_squares[i] != squares[i]) {
      changes[numberOfChanges] = i;
      changeType[numberOfChanges] = squares[i];
      numberOfChanges += 1;
      movedPiece = true;  
    }
  }

  if (movedPiece == true) {
    correctCheckSquares();
  }
}

/*Calculates the move given the changes in the array*/
void calculateMove() {
  int movingPiece = 64;
  int landingSquare = 64;
  
  if (numberOfChanges == 2) {
    for (int i = 0; i < numberOfChanges; i++) {
      if (changeType[i] == 1) {
        movingPiece = changes[i]; 
      }
      else if (changeType[i] == 0) {
        landingSquare = changes[i];
      }
    }
    moveArray[0] = movingPiece;
    moveArray[1] = landingSquare;
  }

  if (numberOfChanges == 3) {
    int movedPieces[2];
    movedPieces[0] = 64;
    movedPieces[1] = 64;
    int moveIndex = 0;
    for (int i = 0; i < numberOfChanges; i++) {
      if (changeType[i] == 1) {
        movedPieces[moveIndex] = changes[i];
        moveIndex += 1; 
      }
      else if (changeType[i] == 0) {
        landingSquare = changes[i];
      }
    }

    //Find the landing square (capture square) make that moveArray[1]
    if (movedPieces[0] == landingSquare) {
      moveArray[0] = movedPieces[1];
      moveArray[1] = movedPieces[0];
      moveArray[2] = landingSquare;
    }
    else if (movedPieces[1] == landingSquare) {
      moveArray[0] = movedPieces[0];
      moveArray[1] = movedPieces[1];
      moveArray[2] = landingSquare;  
    }
    else if ((landingSquare-8 == movedPieces[0]) || (landingSquare+8 == movedPieces[0])) { // En Passant Testing
      moveArray[0] = movedPieces[1];
      moveArray[1] = movedPieces[0];
      moveArray[2] = landingSquare; 
    }
    else if ((landingSquare-8 == movedPieces[1]) || (landingSquare+8 == movedPieces[1])) { // En Passant Testing
      moveArray[0] = movedPieces[0];
      moveArray[1] = movedPieces[1];
      moveArray[2] = landingSquare; 
    }
  }

  if (numberOfChanges == 4) {
    int movedPieces[2];
    movedPieces[0] = 64;
    movedPieces[1] = 64;
    int moveIndex = 0;
    
    int landedSquares[2];
    landedSquares[0] = 64;
    landedSquares[1] = 64;
    int landIndex = 0;

    int movingPiece = 64;
    int landingSquare = 64;
    for (int i = 0; i < numberOfChanges; i++) {
      if (changeType[i] == 1) {
        movedPieces[moveIndex] = changes[i];
        moveIndex += 1;
        
        /*if statement to determine if white king or black king*/
        if (color == 0) {
          if (changes[i] == 4) {
             movingPiece = 4;
          }
        }
        else if (color == 1) {
          if (changes[i] == 3) {
             movingPiece = 3;
          }  
        }
      }
      else if (changeType[i] == 0) {
        landedSquares[landIndex] = changes[i];
        landIndex += 1;

         /*if statement to determine if white king or black king*/
        if (color == 0) {
          if (changes[i] == 2 || changes[i] == 6) {
             landingSquare = changes[i];
          }
        }
        else if (color == 1) {
          if (changes[i] == 1 || changes[i] == 5) {
             landingSquare = changes[i];
          }
        }
      }
    }
    moveArray[0] = movingPiece;
    moveArray[1] = landingSquare;
  }
}

/*Reset function resets all detection arrays*/
void resetChanges() {
  correctCheckSquares();
  for (int i = 0; i < 4; i++) {
    changes[i] = 64;
    changeType[i] = 2;
    moveArray[i] = 64;
  }
  numberOfChanges = 0;
}

/*Sets the check array equal to the board representation array*/
void correctCheckSquares() {
  for (int i=0; i < board_total; i++) {
    check_squares[i] = squares[i];
  }
}

/***************************/
/***** Print functions *****/
/***************************/
void printSquares() {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      Serial.print(squares[(7-j)*8 + i]);
    }
    Serial.println("");
  }
  Serial.println("");
}

/****************************************************/
/***** X, Y, and Z precise input test functions *****/
/****************************************************/

void XPreciseInput() {
  Serial.print("X Precise Position: ");
  Serial.println(XPrecisePosition);
  Serial.print("Input new precise position: ");
  while(true) {
    
    int newPosition = Serial.parseInt();
    if (newPosition > 0) {
      XPreciseMove(newPosition);      
      Serial.print("X Precise Position: ");
      Serial.println(XPrecisePosition);
      Serial.print("Input new precise position: ");
    }
  }
}

void YPreciseInput() {
  Serial.print("Y Precise Position: ");
  Serial.println(YPrecisePosition);
  Serial.print("Input new precise position: ");
  while(true) {
    
    int newPosition = Serial.parseInt();
    if (newPosition > 0) {
      YPreciseMove(newPosition);
      
      Serial.print("Y Precise Position: ");
      Serial.println(YPrecisePosition);
      Serial.print("Input new precise position: ");
    }
  }
}
