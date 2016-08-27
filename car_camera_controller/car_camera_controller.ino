const int ctrl1 = 2;
const int ctrl2 = 2;
const int frontCameraPin = 1;
const int rearCameraPin = 0;
const int delayLoop = 50;
const int delayFrontCam = 160;

void setup() {
  pinMode(ctrl1, INPUT);
//  pinMode(ctrl2, INPUT);
  pinMode(frontCameraPin, OUTPUT);
  pinMode(rearCameraPin, OUTPUT);
}

bool frontCam = false;
bool rearCam = false;
int frontCamDuration = 0;

void loop() {
//  DigiKeyboard.sendKeyStroke(0);
//  DigiKeyboard.println("Run");

  int reverseState = digitalRead(ctrl1);

  if (reverseState == HIGH && !rearCam) {
//    DigiKeyboard.println("ReversePushed");
    digitalWrite(frontCameraPin, LOW);
    delay(100);
    rearCam = true;
    digitalWrite(rearCameraPin, HIGH);
  } else if (reverseState == LOW && rearCam) {
//    DigiKeyboard.println("ReverseRemoved");
    rearCam = false;
    digitalWrite(rearCameraPin, LOW);
    delay(100);
    frontCam = true;
    digitalWrite(frontCameraPin, HIGH);
//    DigiKeyboard.println("FrontCamTurnedOn");
  } else if (frontCam) {
    if (frontCamDuration >= delayFrontCam) {
//      DigiKeyboard.println("FrontCamTurnedOff");
      frontCam = false;
      digitalWrite(frontCameraPin, LOW);
      frontCamDuration = 0;
    } else {
      frontCamDuration++;
    }
  }

  delay(delayLoop);
//  DigiKeyboard.delay(50);
}
