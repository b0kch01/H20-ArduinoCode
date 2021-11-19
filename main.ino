  #include <DFRobot_VL6180X.h>
  #include <SoftwareSerial.h>
  
  SoftwareSerial BTserial(10, 11); // RX | TX
  
  int sensorPin = A0;
  int sensorValue = 0;
  
  DFRobot_VL6180X VL6180X;
  
  void setup() {
    Serial.begin(9600);
    while (!(VL6180X.begin())) {
      Serial.println("[Initiation Failed]: Please check that the IIC device is properly connected (retrying in 1s)");
      delay(1000);
    }
  }
  
  /* Gets poll measurement of ambient light data */
  float getLux() {
    return VL6180X.alsPoLLMeasurement();
  }
  
  /* Returns range of the sensor */
  uint8_t getDistance() {
    return VL6180X.rangePollMeasurement();
  }
  
  /* Returns the error type (if present) */
  uint8_t getReadStatus() {
    return VL6180X.getRangeResult();
  }
  
  void loop() {
    /* Sensor read speed */
    delay(500);
  
    uint8_t distance = getDistance();
    uint8_t readStatus = getReadStatus();
  
    switch (readStatus) {
      case VL6180X_NO_ERR:
        Serial.println(distance);
        break;
      case VL6180X_EARLY_CONV_ERR:
        Serial.println("[RANGE ERR]: ECE check failed");
        break;
      case VL6180X_MAX_CONV_ERR:
        Serial.println("[RANGE ERR]: System did not converge before the specified max");
        break;
      case VL6180X_IGNORE_ERR:
        Serial.println("[RANGE ERR]: Ignore threshold check failed");
        break;
      case VL6180X_MAX_S_N_ERR:
        Serial.println("[RANGE ERR]: Measurement invalidated");
        break;
      case VL6180X_RAW_Range_UNDERFLOW_ERR:
        Serial.println("[RANGE ERR]: RESULT_RANGE_RAW < 0");
        break;
      case VL6180X_RAW_Range_OVERFLOW_ERR:
        Serial.println("[RESULT_RANGE_RAW]: is out of range");
        break;
      case VL6180X_Range_UNDERFLOW_ERR:
        Serial.println("[RANGE ERR]: RESULT__RANGE_VAL < 0");
        break;
      case VL6180X_Range_OVERFLOW_ERR:
        Serial.println("[RANGE ERR]: RESULT__RANGE_VAL is out of range");
        break;
      default:
        Serial.println("[RANGE ERR]: Systerm err");
        break;
    }
  }
