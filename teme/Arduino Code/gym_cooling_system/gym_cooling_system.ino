#include <NewPing.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Pins
#define RELAY_PIN A0
#define TRIG_PIN 10
#define ECHO_PIN 9

// Max distance to detect an object
#define MAX_SENSOR_DIST 10

// Delays
#define SERIAL_INIT_DELAY 50
#define MOTION_READ_DELAY 100

// Max fan session uptime
#define SESSION_TIMEOUT 15000
// Session begin time
int session_begin_time;
// Current fan session uptime
int session_uptime;
// Total session time
int session_total_time;
// Session time left;
int session_time_left;

// Max no object found cnt during uptime
#define SLEEP_TIMEOUT 50
// Current no object found cnt during uptime
int sleep_cnt =  0;

// True = uptime; False = downtime
bool is_running;

// Motion sensor variable
NewPing motion_sensor (TRIG_PIN, ECHO_PIN, MAX_SENSOR_DIST);
// Distance to detected object
float dist;

// LCD display variable
LiquidCrystal_I2C disp(0x27, 16, 2);
 
void setup() {
  // Init digital pin A5 as output
  pinMode(RELAY_PIN, OUTPUT);

  // Init display
  disp.init();
  // Turn backlight on
  disp.backlight();
 
  // Establish connection to serial
  Serial.begin(9600);
  delay(SERIAL_INIT_DELAY);

  // Begin as downtime
  is_running = false;
}

// Routine for beginning new session
void begin_session() {
  // Reset session clock
  session_begin_time = millis();
  
  // Reset sleep cnt
  sleep_cnt = 0;

   // Turn on fan
  digitalWrite(RELAY_PIN, LOW); 

  // Set as uptime
  is_running = true;
}

void clear_clock() {
  session_begin_time = 0;
  session_uptime = 0;
  session_total_time = 0;
  session_time_left = 0;
}

// Routine for ending current session
void end_session() {
  // Clear clock
  clear_clock();
  
  // Turn off fan
  digitalWrite(RELAY_PIN, HIGH);

  // Set as downtime
  is_running = false;
}

// Condition to begin new session
bool can_begin() {
  return dist;
}

// Condition to stop current session
bool can_end() {
  int session_total_time;

  // Get total session time
  session_total_time = session_uptime - session_begin_time;
  
  // End if no more activity found for too long
  return (sleep_cnt >= SLEEP_TIMEOUT 
          // Or session timed out
          || session_total_time >= SESSION_TIMEOUT);
}

void update_clock() {
  // Update uptime
  session_uptime = millis();
  
  // Get total session time
  session_total_time = session_uptime - session_begin_time;

  // Get session time left
  session_time_left = SESSION_TIMEOUT - session_total_time;
}

void update_activity() {
  // If no object found
  if(!dist) {
    // Inc sleep cnt
    sleep_cnt++;
  }
  // Object still there
  else {
    // Reset sleep cnt
    sleep_cnt = 0;
  }
}

void display_running_status() {
  disp.print("Session: ");

  if (is_running) {
    disp.print("ON");
  } else {
    disp.print("OFF");
  }
  
}

float get_display_time() {
  float display_time = (float) session_time_left / 1000;

  if (display_time < 0.0) {
    display_time = 0;
  }
  
  return display_time;
}

void display_time_status() { 
  disp.print("Time left: ");
  disp.print(get_display_time());
}

void display_status() {
  // Clear LCD
  disp.clear();
  
  // Set cursor on top row
  disp.setCursor(0, 0);
  // Display session running status
  display_running_status();

  // Set cursor on bottom row
  disp.setCursor(0, 1);
  // Display session time status
  display_time_status();
}

void loop() {
  // Read distance
  dist = motion_sensor.ping_cm();
  
  // If no session running
  if (!is_running) {
    // If can begin session
    if(can_begin()){
      // Begin session
      begin_session();
    }
  } 
  // If session currently running
  else {
    // Update session times
    update_clock();

    // Update activity params
    update_activity();
    
    // If can end session
    if(can_end()) {
      // End session
      end_session();
    }
  }

  // Display session status on LCD
  display_status();
  
  // Delay between sensor readings
  delay(MOTION_READ_DELAY);
}
