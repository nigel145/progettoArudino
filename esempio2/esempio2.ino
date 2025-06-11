
String ipToGet="10.9.9.0";
String utenteToGet="admin";
String passwordToGet="password";

String comando0="255,0,0,0";
String comando2="255,0,0,2";
String comando4="255,0,0,4";

int red=0;
int green=2;
int blue=4;
int guasto=22;
int guastoHardwere=39;
int mosfet1=25;
int mosfet2=26;

const int tempoLed=3000;

void setup() {
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(guasto, OUTPUT);
  pinMode(guastoHardwere, INPUT);
  pinMode(mosfet1, OUTPUT);
  pinMode(mosfet2, OUTPUT);
}

void loop() {
  statoGuastoHardwere();
  if(controllo()==true){
    menu();
  }else{
    Serial.println("Errore, riprova");
  }
}

void statoGuastoHardwere(){
  int stato=digitalRead(guastoHardwere);
  if(stato==HIGH){
    Serial.println("guasto hardwere");
  }else{
    Serial.println("nessun guasto hardwere");
  }
}

int tempo100=100;

void accendeMosfet(){
  unsigned long myTime;
  myTime = millis();
  digitalWrite(mosfet1, HIGH);
  while(millis()-myTime<tempo100){
  }
  digitalWrite(mosfet2, HIGH);
}

void spegneUscita(){
  digitalWrite(mosfet1, LOW);
  digitalWrite(mosfet2, LOW);
}

boolean controllo(){
  String ip,utente,password;
  Serial.println("inserire ip da trovare: ");
  while(Serial.available()==0){
  }
  ip = Serial.readString();
  Serial.println("inserire utente da trovare: ");
  while(Serial.available()==0){
  }
  utente = Serial.readString();
  Serial.println("inserire password da trovare: ");
  while(Serial.available()==0){
  }
  password = Serial.readString();
  if(ipToGet==ip && utenteToGet==utente && passwordToGet==password){
    return true;
  }else{
    return false;
  }
}

int stato=LOW;

void attivaLed()
{
  unsigned long myTime;
  unsigned long previousMillis=0;
  long cont=500;
  myTime = millis();
  do{
  if(millis()-previousMillis>=cont){
    previousMillis=millis();
    if(stato==LOW){
      stato=HIGH;
      ledOn();
    }else{
      stato=LOW;
      ledOff();
    }
  }
  }while(millis()-myTime<=3000);
  ledOff();
}

void ledOn(){
  digitalWrite(red,HIGH);
  digitalWrite(green,HIGH);
  digitalWrite(blue,HIGH);
}

void ledOff(){
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
  digitalWrite(blue,LOW);
}

boolean controlloValore(String comando){
  String valore;
  Serial.println("inserire il valore: ");
  while(Serial.available()==0){
  }
  valore = Serial.readString();
  if(valore==comando){
    return true;
  }else{
    return false;
  }
}

void menu(){
  int scelta;
  do{
    Serial.println("1-spegne l'uscita");
    Serial.println("2-lampeggia il led");
    Serial.println("3-accende l'uscita");
    Serial.println("4-uscire dal progrmmma");
    Serial.println("scegliere dal menu': ");
    while(Serial.available()==0){
    }
    scelta = Serial.parseInt();
    switch(scelta){
      case 1:
      {
        if(controlloValore(comando0)==true){
          spegneUscita();
        }else{
           Serial.println("Errore, valore non valido");
        }
        break;
      }
      case 2:
      {
        if(controlloValore(comando2)==true){
          attivaLed();
        }else{
           Serial.println("Errore, valore non valido");
        }
        break;
      }
      case 3:
      {
        if(controlloValore(comando4)==true){
          accendeMosfet();
        }else{
           Serial.println("Errore, valore non valido");
        }
        break;
      }
      case 4:
      {
        Serial.println("Arrivederci!!");
        break;
      }
      default:
        Serial.println("Errore!!!");
        break;
    }
  }while(scelta!=4); 
}
