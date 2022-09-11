#include <Streaming.h>  // https://github.com/janelia-arduino/Streaming
#include <DS3232RTC.h>  // https://github.com/JChristensen/DS3232RTC

DS3232RTC myRTC;

String Serial_cmd;

const char *weekStr[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

void setup() {
  Serial.begin(115200);
  Serial.println("DS3231_Setup");
  myRTC.begin();
  Serial.println("Tset run.Time and alarm are set.");
  RTCtest();
}

void loop() {
  if(Serial.available()){
    Serial_cmd = Serial.readString();
    if(Serial_cmd = "test") {
      RTCtest();
    } else if(Serial_cmd = "read") {
      RTCtimeread();
    } else if(Serial_cmd = "settime") {
      RTCtimeset();
    } else {
      Serial.println("none");
    }
  }
}

void RTCtimeread() {
  Serial.print(year());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(day());
  Serial.print(" ");
//  Serial.print(weekSty[weekday()-1]);
  Serial.print(" ");
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.println(second());
  delay(1000);
}

void RTCtest() {
  setTime(5,00,9,9,9,2099);
  myRTC.set(now);
  setSyncProvider(myRTC.get);
  if(timeStatus() != timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
  RTCtimeread();
  
}

void RTCtimeset() {
  Serial.println("Set time in RTC");
  Serial.println("year");
  uint16_t inputyear = DelaySerialread();
  Serial.println("month");
  uint8_t inputmonth = DelaySerialread();
  Serial.println("day");
  uint8_t inputday = DelaySerialread();
  Serial.println("hour");
  uint8_t inputhour = DelaySerialread();
  Serial.println("minute");
  uint8_t inputminute = DelaySerialread();
  Serial.println("second");
  uint8_t inputsecond = DelaySerialread();
  Serial.println("Input Confirmation");
  Serial.println(inputyear + inputmonth + inputday + inputhour + inputminute + inputsecond);
  if(Serial.available()) {
    setTime(inputhour,inputminute,inputsecond,inputday,inputmonth,inputyear)
    myRTC.set(now());
    RTCtimeread();
  }
}

void DelaySerialread() {
  while(Serial.available() == 0) {
  }
  uint16_t result = Serial.read;
  return result;
}
