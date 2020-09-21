///////////////////////////////////////////////////////////////////////////////////////////////////
// Components
byte const DIGITAL_COMPONENT_LED = 1;
byte const DIGITAL_COMPONENT_BUTTON = 1;
byte const DIGITAL_COMPONENT_SWITCH = 2;

int const DIGITAL_OUTPUT_COUNT = 2;
byte const DIGITAL_OUTPUT_PIN_IDS[DIGITAL_OUTPUT_COUNT] = { 9, 8 };
byte const DIGITAL_OUTPUT_COMPONENT_TYPES[DIGITAL_OUTPUT_COUNT] = { DIGITAL_COMPONENT_LED, DIGITAL_COMPONENT_LED };

int const DIGITAL_INPUT_COUNT = 2;
byte const DIGITAL_INPUT_PIN_IDS[DIGITAL_INPUT_COUNT] = { 52, 53 };
byte const DIGITAL_INPUT_COMPONENT_TYPES[DIGITAL_INPUT_COUNT] = { DIGITAL_COMPONENT_BUTTON, DIGITAL_COMPONENT_SWITCH };

int g_lastDigitalInputStates[DIGITAL_INPUT_COUNT];
unsigned long g_lastDigitalInputDebounceTimes[DIGITAL_INPUT_COUNT];

byte const OUTPUT_DATA_SIZE = DIGITAL_OUTPUT_COUNT;
byte g_outputData[OUTPUT_DATA_SIZE];

byte const INPUT_DATA_SIZE = DIGITAL_INPUT_COUNT;
byte g_inputData[INPUT_DATA_SIZE];

unsigned long const DEBOUNCE_DELAY = 50; // ms


///////////////////////////////////////////////////////////////////////////////////////////////////
// Serial
byte const BYTECODE_INVALID = 0
byte const BYTECODE_HANDSHAKE = 1;
byte const BYTECODE_ACKNOWLEDGE = 2;
byte const BYTECODE_UPDATE_INPUT_DATA = 3;
byte const BYTECODE_UPDATE_OUTPUT_DATA = 4;


///////////////////////////////////////////////////////////////////////////////////////////////////
// Arduino execution functions
void setup()
{
  SetupComponents();
  SetupSerial();
}

void loop()
{
  UpdateInputComponents();
  UpdateSerial();
  UpdateOutputComponents();
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Components updates
void SetupComponents()
{
  for (int digitalOutputIndex = 0; digitalOutputIndex < DIGITAL_OUTPUT_COUNT; ++digitalOutputIndex)
  {
    pinMode(DIGITAL_OUTPUT_PIN_IDS[digitalOutputIndex], OUTPUT);
  }
  
  for (int digitalInputIndex = 0; digitalInputIndex < DIGITAL_INPUT_COUNT; ++digitalInputIndex)
  {
    pinMode(DIGITAL_INPUT_PIN_IDS[digitalInputIndex], INPUT);
    g_lastDigitalInputStates[digitalInputIndex] = LOW;
    g_lastDigitalInputDebounceTimes[digitalInputIndex] = 0;
  }
}

void UpdateInputComponents()
{
  // Update components
  int currentDigitalInputStates[DIGITAL_INPUT_COUNT];
  for (int digitalInputIndex = 0; digitalInputIndex < DIGITAL_INPUT_COUNT; ++digitalInputIndex)
  {
    currentDigitalInputStates[digitalInputIndex] = digitalRead(DIGITAL_INPUT_PIN_IDS[digitalInputIndex]);
  }
  
  for (int digitalInputIndex = 0; digitalInputIndex < DIGITAL_INPUT_COUNT; ++digitalInputIndex)
  {
    if (g_lastDigitalInputStates[digitalInputIndex] != currentDigitalInputStates[digitalInputIndex])
    {
      unsigned long const timeMillis = millis();
      if (timeMillis - g_lastDigitalInputDebounceTimes[digitalInputIndex] > DEBOUNCE_DELAY)
      {
        g_lastDigitalInputDebounceTimes[digitalInputIndex] = timeMillis;
        g_lastDigitalInputStates[digitalInputIndex] = currentDigitalInputStates[digitalInputIndex];
        
        g_inputData[digitalInputIndex] = g_lastDigitalInputStates[digitalInputIndex] == HIGH ? 255 : 0;
      }
    }
  }
}

void UpdateOutputComponents()
{
  // Update status lights
  for (int digitalOutputIndex = 0; digitalOutputIndex < DIGITAL_OUTPUT_COUNT; ++digitalOutputIndex)
  {
      int const state = g_outputData[digitalOutputIndex] > 0 ? HIGH : LOW;
      digitalWrite(DIGITAL_OUTPUT_PIN_IDS[digitalOutputIndex], state);
  }
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Serial updates
void SetupSerial()
{
  // Serial
  Serial.begin(9600);
  HandleSerial_Handshake();
}

void UpdateSerial()
{
  if (Serial.available())
  {
    int const bytecode = Serial.peek();
    switch(bytecode)
    {
      case BYTECODE_UPDATE_INPUT_DATA:
        HandleSerial_UpdateInputs();
        break;
        
      case BYTECODE_UPDATE_OUTPUT_DATA:
        HandleSerial_UpdateOutputs();
        break;
    }
  }
}

void HandleSerial_Handshake()
{
  unsigned int const HANDSHAKE_BYTE_SIZE = 4 + INPUT_DATA_SIZE + OUTPUT_DATA_SIZE;
  unsigned int currentBytePos = 0;
  
  byte bytesToSend[HANDSHAKE_BYTE_SIZE];
  bytesToSend[currentBytePos++] = BYTECODE_HANDSHAKE;
  bytesToSend[currentBytePos++] = INPUT_DATA_SIZE;
  for (int dataIndex = 0; dataIndex < INPUT_DATA_SIZE; ++dataIndex)
  {
    bytesToSend[currentBytePos++] = DIGITAL_INPUT_COMPONENT_TYPES[dataIndex];
  }
  bytesToSend[currentBytePos++] = OUTPUT_DATA_SIZE;
  for (int dataIndex = 0; dataIndex < OUTPUT_DATA_SIZE; ++dataIndex)
  {
    bytesToSend[currentBytePos++] = DIGITAL_OUTPUT_COMPONENT_TYPES[dataIndex];
  }
  
  Serial.flush();
  Serial.write(bytesToSend, HANDSHAKE_BYTE_SIZE);
}

void HandleSerial_Acknowledge()
{
  Serial.flush();
  Serial.write(BYTECODE_ACKNOWLEDGE);
}

void HandleSerial_UpdateOutputs()
{
  int const bytecode = Serial.read();
  int const dataSize = min(Serial.read(), OUTPUT_DATA_SIZE);
  for (int dataIndex = 0; dataIndex < dataSize; ++dataIndex)
  {
    int const byteRead = Serial.read();
    if (byteRead >= 0)
    {
      g_outputData[dataIndex] = byteRead;
    }
  }

  HandleSerial_Acknowledge();
}
