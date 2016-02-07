#define WAIT_TIME (30 * 60 * 1000)
#define THRESHOLD 50

unsigned long switched_on_time = millis();

int photon_led = D7;
int photoresistor = A0;
int power = A5;

bool is_geyser_on = false;
int ldr_value;

void setup() {
    pinMode(photon_led, OUTPUT);
    pinMode(photoresistor, INPUT);
    pinMode(power, OUTPUT);

    Spark.variable("ldr", &ldr_value, INT);
    Spark.function("led", ledToggle);

    digitalWrite(photon_led, LOW);
    digitalWrite(power, HIGH);
}

void loop() {
    ldr_value = analogRead(photoresistor);

    // Geyser is on
    if (ldr_value > THRESHOLD) {
        if (!is_geyser_on) {
            is_geyser_on = true;
            switched_on_time = millis();
        }

        else if (millis() - switched_on_time >= WAIT_TIME) {
            Spark.publish("geyserStatus", "on", 60, PRIVATE);
            switched_on_time = millis();
        }
    }

    else {
        is_geyser_on = false;
        switched_on_time = millis();
    }
}

int ledToggle(String command) {
    if (command == "on") {
        digitalWrite(photon_led, HIGH);
        return 1;
    }

    if (command == "off") {
        digitalWrite(photon_led, LOW);
        return 0;
    }

    return -1;
}
