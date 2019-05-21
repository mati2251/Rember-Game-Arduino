#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza

int button[3], led[3], tab[50];

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  for(int i=0; i<50; i++){
    tab[i]=random(3);
    Serial.println(tab[i]);
  }
  button[0]=12;
  button[1]=11;
  button[2]=13;
  led[0]=8;
  led[1]=9;
  led[2]=10;
  for(int i=0; i<3; i++){
    pinMode(button[i], INPUT_PULLUP);
    pinMode(led[i], OUTPUT);
  }
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Wybierz Tryb"); //Wyświetlenie tekstu
  delay(500);
  lcd.clear();
  lcd.print("Rember - Zolta");
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("Hero - Niebieska"); //Wyświetlenie tekstu
}

void loop() {
  if(digitalRead(button[0])==LOW){
    lcd.clear();
    lcd.print("Hero Mode");
    heroMode();
  }
  if(digitalRead(button[1])==LOW){
    lcd.clear();
    lcd.print("Rember");
    remberMode();
  }
}

void remberMode(){
  bool b=false;
  for(int i=0; i<50; i++){
    for(int y=0; y<i; y++){
      digitalWrite(led[tab[y]], HIGH);
      delay(500);
      digitalWrite(led[tab[y]], LOW);
    }
    delay(500);
    for(int y=0; y<i; y++){
      while(true){
        if(digitalRead(button[0])==LOW||digitalRead(button[1])==LOW||digitalRead(button[2])==LOW){
          for(int c=0; c<3; c++){
            if(digitalRead(button[c])==LOW){
              digitalWrite(led[c], HIGH);
              delay(500);
              digitalWrite(led[c], LOW);
              if (c!=tab[y]){
                lose();
                b=true;
                break;
              }
            }
          }
          break;
        }
      }
      if(b==true){
        break;
      }
    }
    delay(1000);
    if(b==true){
        break;
    }
    win();
  }
}

void heroMode(){
  int pause = 300;
  bool b=false;
  String road = "";
  for(int i=0; i<50; i++){
    String buf;
    if(tab[i]==0){
      buf="NIE";
    }
    else if(tab[i]==1){
      buf="ZOL";
    }
    else if(tab[i]==2){
      buf="ZIE";
    }
    lcd.clear();
    for(int y=0; y<13; y++){
      lcd.setCursor(0,0);
      lcd.print(buf + road + buf);
      road=road + " ";
      delay(pause);
    }
    lcd.setCursor(0,1);
    lcd.print("Teraz");
    lcd.setCursor(0,0);
    delay(300);
    for(int c=0; c<4; c++){
      if(digitalRead(button[c])==LOW){
      digitalWrite(led[c], HIGH);
      delay(500);
      digitalWrite(led[c], LOW);
      if(tab[i]!=c||c==3){
       lose();
       b=true;
       break;
      } 
    pause-=15;
    road="";
    break;
    }
  }
  if(b==true){
     break;
  }
}
  if(b==true){
     win();
  }
}

void lose(){
  for(int i=0; i<3; i++){
    for(int c=0; c<3; c++){
      digitalWrite(led[c], HIGH);
      delay(200);
      digitalWrite(led[c], LOW);
      delay(200);
    }
  }
  lcd.clear();
  lcd.print("Przegrales");
  lcd.setCursor(0, 1);
  lcd.print("Wybierz tryb");
}

void win(){
 for(int c=0; c<3; c++){
    digitalWrite(led[c], HIGH);
  }
  delay(500);
  for(int c=0; c<3; c++){
    digitalWrite(led[c], LOW);
  }
  lcd.clear();
  lcd.print("Dobrze");
  delay(2000);
  lcd.clear();
}
