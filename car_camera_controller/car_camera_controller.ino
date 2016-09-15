/**
 * Car Camera Controller software for Arduino Digispark device
 *
 * @author Matus Marko
 * @email  matus@markoweb.eu
 * @gitlab https://github.com/markoweb/car-cam
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

// mode
int mode = 0;

// front camera state
bool frontCamState = false;

// rear camera state
bool rearCamState = false;

// delay for front camera
const unsigned int frontCamDelay = 2500;

unsigned int frontCamDuration = 0;

void setup() {
  pinMode(ctrl1, INPUT);
  pinMode(ctrl2, INPUT);
  pinMode(frontCameraPin, OUTPUT);
  pinMode(rearCameraPin, OUTPUT);

  frontCamOn();
}

void loop() {
  // check whether the control button was pressed
  if (digitalRead(ctrl2) == HIGH) {
    changeMode();
  }

  // if mode was set to auto
  if (mode == 0) {

    // read the state of the reverse gear
    int reverseBtn = digitalRead(ctrl1);

    // reverse gear is on
    if (reverseBtn == HIGH) {
      // previous rear cam state is off
      if (!rearCamState) {
        frontCamOff();
        rearCamOn();
      }
    }
    // reverse gear is off
    else {
      // previous rear camera state is on
      if (rearCamState) {
        rearCamOff();
        frontCamOn();
        frontCamDuration = 0;
      }
      // previous rear camera state is off
      else {
        // previous front camera is on
        if (frontCamState) {
          // front camera is on within the duration time
          if (frontCamDuration <= frontCamDelay) {
            ++frontCamDuration;
          }
          // front camera duration is out of time
          else {
            frontCamOff();
          }
        }
      }
    }
  }
  delay(5);
}

/** Turn on front camera */
void frontCamOn() {
  frontCamState = true;
  digitalWrite(frontCameraPin, HIGH);
}

/** Turn off front camera */
void frontCamOff() {
  frontCamState = false;
  digitalWrite(frontCameraPin, LOW);
}

/** Turn on rear camera */
void rearCamOn() {
  rearCamState = true;
  digitalWrite(rearCameraPin, HIGH);
}

/** Turn off rear camera */
void rearCamOff() {
  rearCamState = false;
  digitalWrite(rearCameraPin, LOW);
}

/** Change operating mode */
void changeMode() {
  mode = ++mode % 4;

  switch (mode) {
    // auto mode
    case 0:
      break;
    // front camera on
    case 1:
      rearCamOff();
      frontCamOn();
      break;
    // rear camera on
    case 2:
      frontCamOff();
      rearCamOn();
      break;
    // both cameras off
    case 3:
      frontCamOff();
      rearCamOff();
      break;
  }
  while (true) {
    if (digitalRead(ctrl2) == LOW)
      break;
  }
}

