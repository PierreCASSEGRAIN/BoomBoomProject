int ValeurCapteur1;                           //Valeur récupérée du capteur 1
int ValeurCapteur2;                           //Valeur récupérée du capteur 2
int EntreeCapteur1 = A4;                      //Entrée ANA PIN 4
int EntreeCapteur2 = A2;                      //Entrée ANA PIN 2
int EntreeBoutonValidation = 9;               //Entrée TOR PIN 9
int EntreeBoutonIncrementMode = 10;           //Entrée TOR PIN 10
int EtatBpMem = 1;                            //Etat précédent du bouton incrément pour détection front montant
int EtatBp = 0;                               //Etat actuel du bouton increment pour détection front montant
int EtatBpValidation = 0;                     //Etat précédent du bouton validation pour détection front montant
int EtatBpValidationMem = 1;                  //Etat actuel du bouton validation pour détection front montant
int Led1 = 5;                                 //Entrée TOR PIN 5
int Led2 = 6;                                 //Entrée TOR PIN 6
int Seuil = 50;                               //Seuil de ValeurCapteurX à partir duquel on considère une touche sur cible
int TempsOn = 1500;                           //Temps durant lequel les LED restent allumées (1.5s)
int TempsAntiReentrant = 0.1;                 //Timer empechant les reentrant (0.1s)
unsigned long TempsMancheModeDeJeu1 = 60000;  //Temps d'une manche du mode de jeu 1 (60s)
int TempsDeBaseRoundModeDeJeu1 = 10000;       //Temps d'un round du mode de jeu 1 (10s)
unsigned long TimerAllume1;                   //Temps à l'instant t où on allume la led 1
unsigned long TimerAntiReentrant1;            //Temps à l'instant t où on active l'anti réentrant pour la cible 1
unsigned long TimerAllume2;                   //Temps à l'instant t où on allume la led 2
unsigned long TimerAntiReentrant2;            //Temps à l'instant t où on active l'anti réentrant pour la cible 2
unsigned long TimerTotalJeu1;                 //Timer total mode de jeu 1
unsigned long TimerRoundJeu1;                 //Timer round mode de jeu 1
int Mode = 0;                                 //Compteur pour selection mode
int OK = 0;                                   //Validation du mode
int nbDeCapteurs = 2;                         
int nbDeRound = 20;                           //Nombre de round max possible dans la manche
int TableauCibleJeu1[20];                     //Tableau avec les valeurs des cibles de la manche (=nbderound)
unsigned long seed = 0;
byte EtatCibles;
int NumRound = 0;                             //Numéro du round actuel
bool RoundFini;
bool BlocageCible1=false;
bool BlocageCible2=false;
int Points;

void setup() {
  Serial.begin(9600);
  pinMode(Led1,OUTPUT);
  pinMode(Led2,OUTPUT);
  pinMode(EntreeBoutonValidation,INPUT_PULLUP);
  pinMode(EntreeBoutonIncrementMode,INPUT_PULLUP);
  }

void loop() {
  if (Mode==0) {
    selectionMode();
  }
  Serial.println(Mode);
  switch (Mode){
    case 1:
      PreparationModeDeJeu1();
      Jeu1();
  }

  Mode=0;
  
//  if (millis()>TimerAllume1+TempsOn) {
//    //Serial.println("Eteint1");
//    digitalWrite(Led1,LOW);
//  }
//
//  if (millis()>TimerAllume2+TempsOn) {
//    //Serial.println("Eteint2");
//    digitalWrite(Led2,LOW);
//  }
}

int selectionMode() {
  OK=0;
  Serial.println("Selection...");
  while (OK==0) 
  {
    EtatBp = digitalRead(EntreeBoutonIncrementMode);
    EtatBpValidation = digitalRead(EntreeBoutonValidation);
    if (EtatBp != EtatBpMem){
      EtatBpMem = EtatBp;
      if (EtatBp==1){
        Mode=Mode+1;
        if (Mode==6){
          Mode=1;
        }
        Serial.println("Mode = ");
        Serial.println(Mode);
      }
    }
    if (EtatBpValidation != EtatBpValidationMem){
      EtatBpValidationMem = EtatBpValidation;
      if (EtatBpValidation==1){
        OK=1;
      }
    }
  }
  return Mode;
}

void PreparationModeDeJeu1(){
  RefreshSeed();
  for (int i = 0; i < nbDeRound; i++){
    TableauCibleJeu1[i]=random(1,pow(2,nbDeCapteurs));
    Serial.print("TableauCibleJeu = ");
    Serial.println(TableauCibleJeu1[i]);
  }
}

void RefreshSeed(){
   for (int i=0; i<32; i++)
  {
    seed = seed | ((analogRead(A0) & 0x01) << i);
  }
  randomSeed(seed);
  Serial.print("Seed = ");
  Serial.println(seed);
}


int Jeu1(){
  Serial.println("Le jeu va commencer dans...");
  delay(1000);
  Serial.println("5...");
  delay(1000);
  Serial.println("4...");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("C'est parti !");
  TimerTotalJeu1=millis();
  Points=0;
  while (millis()<=TimerTotalJeu1+TempsMancheModeDeJeu1){
    TimerRoundJeu1=millis();
    EtatCibles = TableauCibleJeu1[NumRound];
    NumRound++;
    Serial.print("Round n°");
    Serial.println(NumRound);
    Serial.println(EtatCibles);
    RoundFini=false;
    BlocageCible1=false;
    BlocageCible2=false;
    if ((EtatCibles & 0b00000001)==1){
      digitalWrite(Led1,HIGH);
    }
    if ((EtatCibles & 0b00000010)==2){
      digitalWrite(Led2,HIGH);
    }
    while (!RoundFini){
      if (EtatCibles!=0){
        ValeurCapteur1=analogRead(EntreeCapteur1);
        ValeurCapteur2=analogRead(EntreeCapteur2);
        if (!BlocageCible1) {
          if (ValeurCapteur1 >= Seuil && (EtatCibles & 0b00000001)){
            BlocageCible1=1;
            EtatCibles ^= (1 << 0);
            digitalWrite(Led1,LOW);
            Points++;
          }
        }
       
        if (!BlocageCible2) {
          if (ValeurCapteur2 >= Seuil && (EtatCibles & 0b00000010)){
            BlocageCible2=1;
            EtatCibles ^= (1 << 1);
            digitalWrite(Led2,LOW);
            Points++;
          }
        }
      }
      else
      {
        RoundFini=true;
        delay(1500);
      }
      if(millis()>TimerRoundJeu1+TempsDeBaseRoundModeDeJeu1 || millis()>TimerTotalJeu1+TempsMancheModeDeJeu1){
        RoundFini=true;
        delay(1500);
      }
    }
  }
  Serial.println("Terminé !");
  Serial.print("Vous avez eu ");
  Serial.print(Points);
  Serial.println(" points");
}
