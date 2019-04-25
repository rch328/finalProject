int buzzer_pin = 3;

struct MusicStruct {
  int c = 262;
  int d = 294;
  int e = 330;
  int f = 349;
  int g = 392;
  int a = 440;
  int b = 494;
  int c2 = 523;
  int d2 = 587;
  int e2 = 659;
  int f2 = 370;

} Music;

struct LengthStruct {
  float eighth = .5;
  float quarter = 0.25;
  float three_quarter = 0.75;
  float half = .5;
  float one = 1.0;
  float two = 2.0;
  float two_half = 2.5;
  float three = 3;
  float four = 4;
} Length;


int tempo = 400;

void setup() {

  pinMode(buzzer_pin, OUTPUT);
}

void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}

void loop() {
  //1
  setTone(buzzer_pin, Music.a, tempo * Length.one);
  setTone(buzzer_pin, Music.a, tempo * Length.one);
  setTone(buzzer_pin, Music.a, tempo * Length.one);
  setTone(buzzer_pin, Music.a, tempo * Length.one);

  setTone(buzzer_pin, Music.b, tempo * Length.one);
  setTone(buzzer_pin, Music.b, tempo * Length.one);

  setTone(buzzer_pin, Music.a, tempo * Length.half);
  setTone(buzzer_pin, Music.f2, tempo * Length.half);

  setTone(buzzer_pin, Music.d, tempo * Length.one);
  setTone(buzzer_pin, Music.d, tempo * Length.one);

  setTone(buzzer_pin, Music.d, tempo * Length.half);
  setTone(buzzer_pin, Music.d, tempo * Length.half);

  setTone(buzzer_pin, Music.e, tempo * Length.half);
  setTone(buzzer_pin, Music.d, tempo * Length.half);
  setTone(buzzer_pin, Music.e, tempo * Length.one);

  setTone(buzzer_pin, Music.f2, tempo * Length.four);

  setTone(buzzer_pin, Music.a, tempo * Length.one);
  setTone(buzzer_pin, Music.a, tempo * Length.one);
  setTone(buzzer_pin, Music.a, tempo * Length.one);
  setTone(buzzer_pin, Music.a, tempo * Length.one);


  setTone(buzzer_pin, Music.b, tempo * Length.one);
  setTone(buzzer_pin, Music.b, tempo * Length.one);

  setTone(buzzer_pin, Music.a, tempo * Length.half);
  setTone(buzzer_pin, Music.f2, tempo * Length.half);

  setTone(buzzer_pin, Music.d, tempo * Length.one);
  setTone(buzzer_pin, Music.d, tempo * Length.one);
  setTone(buzzer_pin, Music.d, tempo * Length.one);

  setTone(buzzer_pin, Music.f2, tempo * Length.eighth);
  setTone(buzzer_pin, Music.f2, tempo * Length.eighth);
  setTone(buzzer_pin, Music.f2, tempo * Length.eighth);
  setTone(buzzer_pin, Music.e, tempo * Length.eighth);

  setTone(buzzer_pin, Music.d, tempo * Length.four);



  //19


}
