/**
 * Car Camera Controller software for Arduino Digispark device
 *
 * @author  Matus Marko
 * @email   matus@markoweb.eu
 * @gitlab  https://github.com/markoweb/car-cam
 * @version 3.0.1
 */

 
/* PIN CONFIGURATION */

// rear camera controll pin (output)
const int rearCameraPin = 3;

// front camera controll pin (output)
const int frontCameraPin = 4;

// pin for reverse gear (input)
const int ctrl1 = 1;

// pin for controll button (input)
const int ctrl2 = 2;


/* STATE CONFIGURATION */

// delay for front camera
const unsigned int TIMEOUT = 2500;

// current state
int state;

// current duration
unsigned int duration;

void setup() {
  pinMode(ctrl1, INPUT);
  pinMode(ctrl2, INPUT);
  pinMode(frontCameraPin, OUTPUT);
  pinMode(rearCameraPin, OUTPUT);

  setState(1);
}

void loop() {
  // check whether the reverse gear is set
  if (isReversingSet()) {
    if (state < 3) {
      setState(3);
    }
    else if (state = 4) {
      if (duration < TIMEOUT) {
        duration++;
      } else {
        setState(3);
      }
    }
  }
  // reverse gear is unset
  else {
    if (state == 1 || state == 2) {
      if (duration < TIMEOUT) {
        duration++;
      } else {
        setState(0);
      }
    }
    else if (state > 2) {
      setState(1);
    }
  }

  // check whether the button is pressed
  if (isButtonPressed()) {
    switch (state) {
      case 0:
        setState(1);
        break;
      case 1:
        setState(2);
        break;
      case 3:
        setState(4);
        break;
      case 4:
        setState(3);
        break;
      case 2:
      default:
        setState(0);
        break;
    }
    while (isButtonPressed()) {
      ;
    }
  }
  delay(5);
}

/** Change State */
void setState(int number) {
  state = number;
  switch (number) {
    case 1:
    case 4:
      rearCamOff();
      frontCamOn();
      duration = 0;
      break;
    case 3:
      frontCamOff();
      rearCamOn();
    case 2:
      duration = 0;
      break;
    case 0:
    default:
      frontCamOff();
      rearCamOff();
      break;
  }
}

/** Turn on front camera */
void frontCamOn() {
  digitalWrite(frontCameraPin, HIGH);
}

/** Turn off front camera */
void frontCamOff() {
  digitalWrite(frontCameraPin, LOW);
}

/** Turn on rear camera */
void rearCamOn() {
  digitalWrite(rearCameraPin, HIGH);
}

/** Turn off rear camera */
void rearCamOff() {
  digitalWrite(rearCameraPin, LOW);
}

/** Check whether the reverse gear is set */
bool isReversingSet() {
  return digitalRead(ctrl1) == HIGH;
}

/** Check whether the button is pressed */
bool isButtonPressed() {
  return digitalRead(ctrl2) == HIGH;
}

