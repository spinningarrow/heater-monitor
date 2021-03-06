#define WAIT_TIME (30 * 60 * 1000)
#define THRESHOLD 50

unsigned long switched_on_time = millis();

int photon_led = D7;
int status_led = D0;
int photoresistor = A0;
int power = A5;

bool is_geyser_on = false;
bool is_wait_time_reached = false;
int ldr_value;

void setup() {
    pinMode(status_led, OUTPUT);
    pinMode(photon_led, OUTPUT);
    pinMode(photoresistor, INPUT);
    pinMode(power, OUTPUT);

    Spark.variable("ldr", &ldr_value, INT);
    Spark.function("led", ledToggle);

    digitalWrite(status_led, LOW);
    digitalWrite(photon_led, LOW);
    digitalWrite(power, HIGH);
}

void loop() {
    ldr_value = analogRead(photoresistor);

    // Geyser is on
    if (ldr_value > THRESHOLD) {
        digitalWrite(status_led, HIGH);

        if (!is_geyser_on) {
            is_geyser_on = true;
            switched_on_time = millis();
        }

        else if (millis() - switched_on_time >= WAIT_TIME) {
            is_wait_time_reached = true;
            Spark.publish("geyserStatus", "on", 60, PRIVATE);
            switched_on_time = millis();
        }

        if (is_wait_time_reached) {
            ledToggle("on");
            delay(500);

            ledToggle("off");
            delay(500);
        }
    }

    else {
        digitalWrite(status_led, LOW);

        is_geyser_on = false;
        switched_on_time = millis();

        is_wait_time_reached = false;
        ledToggle("off");
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
