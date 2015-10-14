static int pins[] = {10,9,8,11}; //up, right, down, left
static int tones[] = {247, 523, 988, 1397};
int tonePin = 12, upDownPin = 0, leftRightPin = 1;

void setup(){
  for (int i = 0; i < 4; i++){
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }
  delay(2000);
  for (int i = 0; i < 4; i++){
    digitalWrite(pins[i], LOW);
  }  
  delay(1000);
}

void flash(){
  for (int n = 0; n < 4; n++){
    for (int i = 0; i < 4; i++){
      digitalWrite(pins[i], HIGH);
    }
    tone(tonePin, tones[0], 500);
    delay(500);
    for (int i = 0; i < 4; i++){
      digitalWrite(pins[i], LOW);
    }  
    delay(500);
  }
}

void loop(){
  randomSeed(analogRead(5));
  int upDown = 512, leftRight = 512;    //set joystick variables to neutral position
  int next = 0;
  int moves[20];    //stores all moves so far
  int roundNum = 0;
  boolean lost = false;    //reset for new game
  while(!lost){
    next = random(0,4);
    moves[roundNum] = next;
    roundNum++;
    for (int i = 0; i < roundNum; i++){    //play moves
      digitalWrite(pins[moves[i]], HIGH);
      tone(tonePin, tones[moves[i]], 500);
      delay(500); 
      digitalWrite(pins[moves[i]], LOW);
      delay(200);
    }
    delay(800);
    for (int i = 0; i < roundNum; i++){    //user plays round
      while(true){    //wait for input
        upDown = analogRead(upDownPin);
        leftRight = analogRead(leftRightPin);       
        //evaluate input
        if(upDown > 600){    //User inputs up
          digitalWrite(pins[0], HIGH);
          tone(tonePin, tones[0], 300);
          delay(300);
          digitalWrite(pins[0], LOW);
          if(moves[i] != 0){
            lost = true;
          }
          break;
        }
        else if(leftRight > 600){    //User inputs right
          digitalWrite(pins[1], HIGH);
          tone(tonePin, tones[1], 300);
          delay(300);
          digitalWrite(pins[1], LOW);
          if(moves[i] != 1){
            lost = true;
          }         
          break;
        }
        else if(upDown < 400){      //user inputs down
          digitalWrite(pins[2], HIGH);
          tone(tonePin, tones[2], 300);
          delay(300);
          digitalWrite(pins[2], LOW);
          if(moves[i] != 2){
            lost = true;
          }         
          break;
        }
        else if(leftRight < 400){    //user inputs left
          digitalWrite(pins[3], HIGH);
          tone(tonePin, tones[3], 300);
          delay(300);
          digitalWrite(pins[3], LOW);
          if(moves[i] != 3){
            lost = true;
          }       
          break;
        }
      }
      delay(1000);
    }
  }
  flash();
  delay(5000);    //delay between games
}
