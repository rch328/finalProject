/* Madeline Phillips
 * 4/25/2019
 * Morse Code Translator
 * Description: This program accepts button press input from
 * an Arduino and analyzes both the length of the button presses
 * and the length between button presses to interpret morse code
 * input into strings, which are output to the Serial Monitor.
 */

// Global Variables & Descriptions
/* prevState is used to keep track of whether of not the button has been pressed 
 * yet. Is only relevant for the first press to keep the program from starting 
 * the spacing timer before it's necessary. */
int prevState; 
/* prevtime is used to track the time the button has been pressed down
 * to determine whether the press was a dot or a dash. */
unsigned long prevtime;
/* offtime and savedtime are used in conjunction used to track the time after the 
 * previous button press to figure out whether to start a new letter or a new word. */
unsigned long offtime;
unsigned long savedtime;
/* dash is set to true if button is held down long enough. Checked later when composing letter */
bool dash = false;
/* benchmarked is used to check if the initial time has been saved yet. 
 * The initial time is millis() the instant the button is first pressed. */
bool benchmarked = false;
/* inWord and inSentence are used to determine whether letter composition behavior.
 * They're set based on the space between button presses. */
bool inWord = false;
bool inSentence = false;
/* letter is the string to which the raw morse code is appended. */
String letter; // collects raw morse

/* I couldn't find a map/dictionary data structure that worked with Arduino,
 * so I made my own map: an array of structs. O(n) search is kinda gross, but
 * here we are. It contains the alphabet and integers 0-9. */
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
  {"-----", '0'}
};

void setup() {
  // this runs once
  // Serial.begin is used to print to Serial Monitor
  Serial.begin(9600);
  // Button
  pinMode(3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  prevState = 1; // button is up
  benchmarked = false; // time has never been saved
  while (!digitalRead(3)) {
    if (!benchmarked) {
      // if time hasn't been saved, save it
      prevtime = millis();
      benchmarked = true;
    }
    // if button has been held long enough to qualify for a dash, set the flag
    if ((millis() - prevtime) > 500) { 
      dash = true;
      break;
    }
    prevState = 0; // button has been pressed
  } // end while(!digitalRead(3))

  // button has been released
  if (digitalRead(3) && prevState == 0) {
    // save the time the instant the button is released to see how long it stays up
    offtime = millis();

    if (inWord) {
      // if the morse for the letter is complete, find the letter and print it out
      for (int i = 0; i < 36; i++) {
        if (alphabet[i].raw == letter) {
          Serial.print(alphabet[i].letter);
          Serial.print("\n");
          break;
        }
      }
      // clear letter
      letter = "";
    }
    // if between words, add a space
    if (inSentence) {
      Serial.print(" ");
    }
    // construct letter, one dot/dash at a time
    if (!dash) {
      letter.concat('.');
      Serial.print('.');
    }
    else {
      letter.concat('-');
      Serial.print('-');
    }
    dash = false; // reset dash flag
  } // end if

  // begin actually caring about how long the button has been up and setting flags accordingly
  while (digitalRead(3) && prevState == 0) {
    savedtime = millis() - offtime;
    // letter is complete. print and start new.
    if (savedtime < 4000 && savedtime > 2000) {
      inWord = true;
      inSentence = false;
    }
    savedtime = millis() - offtime;
    // word is complete. print a space.
    if (savedtime > 4000) {
      inWord = false;
      inSentence = true;
    }
  } // end while

} // end loop


