const int sensorPin = A0;
float sensorVoltage = 0;
float pressure_kPa = 0;
float zero_offset = 0;
float referencePressure = 0.66;  // Fine-tune offset based on your initial observation

// Smoothing parameters
const int numReadings = 20;
int readings[numReadings];
int readIndex = 0;
long total = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);  // Sensor stabilization delay

  // Auto calibration at startup (both nozzles open to atmosphere)
  long calibrationTotal = 0;
  for (int i = 0; i < 100; i++) {
    calibrationTotal += analogRead(sensorPin);
    delay(10);
  }
  float avg_adc = calibrationTotal / 100.0;
  zero_offset = avg_adc * (5.0 / 1023.0);

  Serial.print("Calibration complete. Zero offset (V): ");
  Serial.println(zero_offset);

  // Initialize smoothing buffer
  for (int i = 0; i < numReadings; i++) {
    readings[i] = analogRead(sensorPin);
    total += readings[i];
  }
}

void loop() {
  // Update moving average buffer
  total -= readings[readIndex];
  readings[readIndex] = analogRead(sensorPin);
  total += readings[readIndex];

  readIndex++;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  float avgSensorValue = total / (float)numReadings;
  sensorVoltage = avgSensorValue * (5.0 / 1023.0);

  // Apply calibration and fine offset
  pressure_kPa = (sensorVoltage - zero_offset) * (50.0 / (4.7 - 0.2)) + referencePressure;

  // Convert kPa to Pa
  float pressure_Pa = pressure_kPa * 1000.0;

  Serial.print("Pressure (Pa): ");
  Serial.println(pressure_Pa);
  delay(200);
}