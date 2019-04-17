int prevState;
unsigned long prevtime;
unsigned long offtime;
bool dash = false;
bool benchmarked = false;
int buttonState;
bool inLetter = false;
bool inWord = false;
bool inSentence = false;
unsigned long savedtime;
String letter;
bool checked = false;
//char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
//char alphabet[] = {'a'};
bool printed = false; bool printed2 = false; bool printed3 = false;

struct Morse {
  String raw; // dashes and dots
  char letter; // alphanumeric values
} alphabet[] = {
  {".-", 'a'},
  {"-...", 'b'},
  {"-.-.", 'c'},
  {"-..", 'd'},
  {".", 'e'},
  {"..-.", 'f'},
  {"--.", 'g'},
  {"....", 'h'},
  {"..", 'i'},
  {".---", 'j'},
  {"-.-", 'k'},
  {".-..", 'l'},
  {"--", 'm'},
  {"-.", 'n'},
  {"---", 'o'},
  {".--.", 'p'},
  {"--.-", 'q'},
  {".-.", 'r'},
  {"...", 's'},
  {"-", 't'},
  {"..-", 'u'},
  {"...-", 'v'},
  {".--", 'w'},
  {"-..-", 'x'},
  {"-.--", 'y'},
  {"--..", 'z'},
  {".----", '1'},
  {"..---", '2'},
  {"...--", '3'},
  {"....-", '4'},
  {".....", '5'},
  {"-....", '6'},
  {"--...", '7'},
  {"---..", '8'},
  {"----.", '9'},
  {"-----", '0'},
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // LED's
  pinMode(13, OUTPUT);
  // Buttons
  pinMode(3, INPUT);
  //pinMode(A1, INPUT);
}

// LOW = ON
// HIGH = OFF
void loop() {
  // put your main code here, to run repeatedly:
  // pinMode(13, LOW);
  // delay(10000);

  prevState = 1;
  benchmarked = false;
  while (!digitalRead(3)) {
    printed = false; printed2 = false; printed3 = false;



    if (!benchmarked) {
      prevtime = millis();
      benchmarked = true;
    }

    // Serial.print("hi");
    // dash = false;
    if ((millis() - prevtime) > 500 && !dash) {
      //Serial.print("dash\n");
      //Serial.print("-");
      //Serial.print("in letter dash\n");
      dash = true;
      break;
    }
    prevState = 0;
  }

  if (digitalRead(3) && prevState == 0) {
    offtime = millis();
    if (inLetter) {
      if (!dash) {
        letter.concat('.');
        Serial.print('.');
      }
      else {
        letter.concat('-');
        Serial.print('-');
      }
      dash = false;
    }
    if (inWord || inSentence) { // SENTENCE SHOULD HAVE ITS OWN THING
      // use map to print letter
      Serial.print("morse = ");
      Serial.print(letter);
      for (int i = 0; i < 36; i++) {
        if (alphabet[i].raw == letter) {
          Serial.print("\nletter = ");
          Serial.print(alphabet[i].letter);
          //Serial.print("\n");
          break;
        }
      }
      Serial.print("\n\n");
      letter = "";
    }
  }
  while (digitalRead(3) && prevState == 0) {

    if ((millis() - offtime) < 2000) {
      if (!printed) {
        //Serial.print("in letter\n");
        printed = true;
      }
      inLetter = true;
      inWord = false;
      inSentence = false;
    }
    savedtime = millis() - offtime;
    if (savedtime < 4000 && savedtime > 2000) {
      if (!printed2) {
        //Serial.print("in word\n");
        printed2 = true;
      }
      inLetter = false;
      inWord = true;
      inSentence = false;
    }
    savedtime = millis() - offtime;
    if (savedtime > 4000) {
      if (!printed3) {
        //Serial.print("in sentence\n");
        printed3 = true;
      }
      inLetter = false;
      inWord = false;
      inSentence = true;
    }
    checked = false;
    //prevState = 1; // does this matter?
    /*if((millis() - offtime) > 1500){
       Serial.print("out of letter. in word.");
       // process and print letter
      }
      else if (!dash) {
      //Serial.print("dot\n");
      //Serial.print(".");
      Serial.print("in letter dot\n");
      // add dot to letter string
      }
      dash = false;
      prevState = 1;*/
  }


} // end loop



