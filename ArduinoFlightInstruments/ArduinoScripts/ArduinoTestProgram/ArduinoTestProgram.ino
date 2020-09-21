
int const LOCAL_LED_PIN_ID = 8;
int const REMOTE_LED_PIN_ID = 9;

bool g_isLocalLedOn = false;
bool g_isRemoteLedOn = false;

unsigned long const LED_TOGGLE_DELAY_MS = 1000;
unsigned long g_lastLedToggleTime = 0;


void setup()
{
  pinMode(LOCAL_LED_PIN_ID, OUTPUT);
  pinMode(REMOTE_LED_PIN_ID, OUTPUT);
  
  Serial.begin(9600);
  
  g_lastLedToggleTime = millis();
}

void loop()
{
  if (millis() - g_lastLedToggleTime >= LED_TOGGLE_DELAY_MS)
  {
    g_isLocalLedOn = !g_isLocalLedOn;
    Serial.write(g_isLocalLedOn ? "l_led on\n" : "l_led off\n");
    g_lastLedToggleTime = millis();
  }

  if (Serial.available())
  {
    String const dataStr = Serial.readStringUntil('\n');
    int const cmdSpcIdx = dataStr.indexOf(' ');
    bool const hasFoundSpc = cmdSpcIdx >= 0;
    
    String const cmd = hasFoundSpc ? dataStr.substring(0, cmdSpcIdx) : dataStr;
    String const args = hasFoundSpc ? dataStr.substring(cmdSpcIdx + 1, dataStr.length()) : "";
    
    if (cmd.equals("r_led"))
    {
      if (args.equals("on"))
      {
        g_isRemoteLedOn = true;
      }
      else if (args.equals("off"))
      {
        g_isRemoteLedOn = false;
      }
    }
  }
  
  digitalWrite(LOCAL_LED_PIN_ID, g_isLocalLedOn ? HIGH : LOW);
  digitalWrite(REMOTE_LED_PIN_ID, g_isRemoteLedOn ? HIGH : LOW);
}
