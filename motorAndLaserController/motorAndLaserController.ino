const int stepsPerRevolution = 2048;  
const int maxSteps = 1024;// this represents doing a full 180
bool laserOn = false;
int horizontalCount = 0;//these count variables represent how many steps we've gone in a particular direction(can be negative), both will be limited by maxSteps
int verticalCount = 0;

//control pins
int laserPin = 12;
int hIN1 = 32;
int hIN2 = 33;
int hIN3 = 14;
int hIN4 = 13;

int vIN1 = 1;
int vIN2 = 3;
int vIN3 = 2;
int vIN4 = 15;

// ULN2003 Motor 
void setup() {
  // put your setup code here, to run once:
   pinMode(laserPin, OUTPUT);//our laser pin
  //horizontal
  pinMode(hIN1, OUTPUT);
  pinMode(hIN2, OUTPUT);
  pinMode(hIN3, OUTPUT);
  pinMode(hIN4, OUTPUT);
  //vertical
  pinMode(vIN1, OUTPUT);
  pinMode(vIN2, OUTPUT);
  pinMode(vIN3, OUTPUT);
  pinMode(vIN4, OUTPUT);
  //note: some pins are for boot straping, so while flashing code, make sure to have them disconnected
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //laser test code(currently just a LED)
  activateOrDeactivateLaser();
  delay(1000);
  activateOrDeactivateLaser();

  //test code for horizontal stepper
  
  delay(1000);
  for(int i = 0; i < 64; i++){//this represents a full 180 turn
    left();
  }
  delay(1000);
  for(int i = 0; i < 64; i++){
    right();
  }
  activateOrDeactivateLaser();
  delay(1000);

  //test code for vertical stepper
  delay(1000);
  for(int i = 0; i < 64; i++){//this represents a full 180 turn
    down();
  }
  delay(1000);
  for(int i = 0; i < 64; i++){
    up();
  }
  activateOrDeactivateLaser();
  delay(1000);
  

}

void left(){
  if(horizontalCount > maxSteps * -1){
    digitalWrite(hIN1, HIGH); digitalWrite(hIN2, LOW); digitalWrite(hIN3, LOW); digitalWrite(hIN4, HIGH);
    delay(5);
    digitalWrite(hIN1, HIGH); digitalWrite(hIN2, HIGH); digitalWrite(hIN3, LOW); digitalWrite(hIN4, LOW);
    delay(5);
    digitalWrite(hIN1, LOW); digitalWrite(hIN2, HIGH); digitalWrite(hIN3, HIGH); digitalWrite(hIN4, LOW);
    delay(5); 
    digitalWrite(hIN1, LOW); digitalWrite(hIN2, LOW); digitalWrite(hIN3, HIGH); digitalWrite(hIN4, HIGH);
    delay(5);
    horizontalCount -= 1;
  }
}

void right(){
  if(horizontalCount < maxSteps){
    digitalWrite(hIN1, LOW); digitalWrite(hIN2, LOW); digitalWrite(hIN3, HIGH); digitalWrite(hIN4, HIGH);
    delay(5);
    digitalWrite(hIN1, LOW); digitalWrite(hIN2, HIGH); digitalWrite(hIN3, HIGH); digitalWrite(hIN4, LOW);
    delay(5);
    digitalWrite(hIN1, HIGH); digitalWrite(hIN2, HIGH); digitalWrite(hIN3, LOW); digitalWrite(hIN4, LOW);
    delay(5);
    digitalWrite(hIN1, HIGH); digitalWrite(hIN2, LOW); digitalWrite(hIN3, LOW); digitalWrite(hIN4, HIGH);
    delay(5);
    horizontalCount += 1;
  }
}

void down(){
  if(horizontalCount > maxSteps * -1){
    digitalWrite(vIN1, HIGH); digitalWrite(vIN2, LOW); digitalWrite(vIN3, LOW); digitalWrite(vIN4, HIGH);
    delay(5);
    digitalWrite(vIN1, HIGH); digitalWrite(vIN2, HIGH); digitalWrite(vIN3, LOW); digitalWrite(vIN4, LOW);
    delay(5);
    digitalWrite(vIN1, LOW); digitalWrite(vIN2, HIGH); digitalWrite(vIN3, HIGH); digitalWrite(vIN4, LOW);
    delay(5); 
    digitalWrite(vIN1, LOW); digitalWrite(vIN2, LOW); digitalWrite(vIN3, HIGH); digitalWrite(vIN4, HIGH);
    delay(5);
    verticalCount -= 1;
  }
}

void up(){
  if(horizontalCount < maxSteps){
    digitalWrite(vIN1, LOW); digitalWrite(vIN2, LOW); digitalWrite(vIN3, HIGH); digitalWrite(vIN4, HIGH);
    delay(5);
    digitalWrite(vIN1, LOW); digitalWrite(vIN2, HIGH); digitalWrite(vIN3, HIGH); digitalWrite(vIN4, LOW);
    delay(5);
    digitalWrite(vIN1, HIGH); digitalWrite(vIN2, HIGH); digitalWrite(vIN3, LOW); digitalWrite(vIN4, LOW);
    delay(5);
    digitalWrite(vIN1, HIGH); digitalWrite(vIN2, LOW); digitalWrite(vIN3, LOW); digitalWrite(vIN4, HIGH);
    delay(5);
    verticalCount += 1;
  }
}

void activateOrDeactivateLaser(){
  if(laserOn){
    digitalWrite(laserPin, LOW);
    laserOn = false;
  }
  else{
    digitalWrite(laserPin, HIGH);
    laserOn = true;
  }
}


