#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>

#define SCAN_TIME 5
#define BUZZER_PIN 5
#define LED_RED_PIN 23
#define LED_GREEN_PIN 22

#define BUZZER_FREQUENCY 1200
#define BUZZER_DURATION 1000
#define MAX_ALARM_CYCLES 5

#define RSSI_THRESHOLD -80

BLEScan* pBLEScan;

const char* pivotTagMAC = "ff:ff:11:94:ae:5f";

const char* requiredTags[] = {
    "ff:ff:11:94:ae:59",
    "a4:c1:38:de:ad:be"
};

const int numRequiredTags = 2;

int alarmCycleCount = 0;

int averageRSSI(const char* mac, BLEScanResults* results)
{
    int sumRSSI = 0;
    int count = 0;

    for (int i = 0; i < results->getCount(); i++)
    {
        BLEAdvertisedDevice device = results->getDevice(i);

        if (strcmp(device.getAddress().toString().c_str(), mac) == 0)
        {
            sumRSSI += device.getRSSI();
            count++;
        }
    }

    return (count > 0) ? (sumRSSI / count) : -999;
}

bool isTagNearby(const char* mac, BLEScanResults* results)
{
    int avgRSSI = averageRSSI(mac, results);

    if (avgRSSI == -999)
        return false;

    Serial.printf("%s -> Avg RSSI: %d dBm\n", mac, avgRSSI);

    return (avgRSSI > RSSI_THRESHOLD);
}

void setup()
{
    Serial.begin(115200);

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);

    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);

    BLEDevice::init("");

    pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(50);
    pBLEScan->setWindow(49);
}

void loop()
{
    Serial.println("Scanning for BLE devices...");

    BLEScanResults* foundDevices =
        pBLEScan->start(SCAN_TIME, false);

    bool pivotNearby =
        isTagNearby(pivotTagMAC, foundDevices);

    if (pivotNearby)
    {
        alarmCycleCount = 0;

        digitalWrite(LED_GREEN_PIN, HIGH);
        digitalWrite(LED_RED_PIN, LOW);

        Serial.println("Pivot nearby");
    }
    else
    {
        digitalWrite(LED_GREEN_PIN, LOW);

        bool requiredItemPresent = false;

        for (int i = 0; i < numRequiredTags; i++)
        {
            if (isTagNearby(requiredTags[i], foundDevices))
            {
                requiredItemPresent = true;
                break;
            }
        }

        if (requiredItemPresent &&
            alarmCycleCount < MAX_ALARM_CYCLES)
        {
            Serial.printf(
                "Pivot missing! Alarm %d/%d\n",
                alarmCycleCount + 1,
                MAX_ALARM_CYCLES
            );

            digitalWrite(LED_RED_PIN, HIGH);

            tone(
                BUZZER_PIN,
                BUZZER_FREQUENCY,
                BUZZER_DURATION
            );

            alarmCycleCount++;
        }
        else if (requiredItemPresent)
        {
            Serial.println("Alarm limit reached");

            digitalWrite(LED_RED_PIN, LOW);
        }
        else
        {
            Serial.println("All items taken");

            digitalWrite(LED_RED_PIN, LOW);

            alarmCycleCount = 0;
        }
    }

    Serial.println("-------------------------");

    delay(100);
}