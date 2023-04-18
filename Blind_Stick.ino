#define SIGNAL_PIN A5
int botBuzzer = 11;
int topBuzzer = 2;
const int botTrigPin = 12;
const int botEchoPin = 13;
const int topTrigPin = 3;
const int topEchoPin = 4;
int botLedpin = 10;
int topLedpin = 5;
long duration;
int distance;
int waterValue = 0;
const int buttonPin = 8;
int buttonState = 0;
int botflag=0;

void setup() {
  pinMode(botBuzzer, OUTPUT);
  pinMode(topBuzzer, OUTPUT);

  pinMode(botTrigPin, OUTPUT);
  pinMode(botEchoPin, INPUT);

  pinMode(topTrigPin, OUTPUT);
  pinMode(topEchoPin, INPUT);

  pinMode(botLedpin, OUTPUT);
  pinMode(topLedpin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  botflag=1;
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW)
  {
    delay(10000);
  }
  waterValue = analogRead(SIGNAL_PIN);
  Serial.print("Sensor value: ");
  Serial.println(waterValue);
  if (waterValue > 400)
  {
    tone(botBuzzer, 500);
    delay(2500);
    noTone(botBuzzer);
    delay(500);
  }
  int d=calculateDistance(topTrigPin,topEchoPin);
  topTrigger(d);
  Serial.print("Top Distance(cm): ");
  Serial.println(d);
  d=calculateDistance(botTrigPin,botEchoPin);
  if(botflag)
  {
    botTrigger(d);
  }
  Serial.print("Bot Distance(cm): ");
  Serial.println(d);
}

int calculateDistance(int trigPin,int echoPin)
{
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;
  return distance;
}

void topTrigger(int d)
{
  botflag=0;
  if (d > 105)
  {
    botflag=1;
    nonoise(topBuzzer);
  } else if (d <= 105 && d > 70)
  {
    lowNoise();
  } else if (d <= 70 && d > 40)
  {
    midNoise();
  } else {
    highNoise();
  }
}
void botTrigger(int d)
{
  if (d > 94)
  {
    nonoise(botBuzzer);
  } else {
    notify();
  }
}
void highNoise()
{
  tone(topBuzzer, 100);
  highBlink();
  delay(600);
  noTone(topBuzzer);
  delay(50);
}

void midNoise()
{
  tone(topBuzzer, 68);
  lowBlink();
  delay(200);
  noTone(topBuzzer);
  delay(200);
}

void lowNoise()
{
  tone(topBuzzer, 500);
  delay(100);
  noTone(topBuzzer);
  delay(500);
}
void nonoise(int buzzer)
{
  noTone(buzzer);
}
void lowBlink()
{
  digitalWrite(topLedpin, HIGH);
  delay(1300);
  digitalWrite(topLedpin, LOW);
}
void highBlink()
{
  digitalWrite(topLedpin, HIGH);
  delay(700);
  digitalWrite(topLedpin, LOW);
  digitalWrite(botLedpin, HIGH);
  delay(700);
  digitalWrite(botLedpin, LOW);
}
void notify()
{
  tone(botBuzzer, 500);
  delay(1000);
  noTone(botBuzzer);
  delay(500);
}
