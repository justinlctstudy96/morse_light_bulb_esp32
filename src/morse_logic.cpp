#include <morse_logic.h>

std::vector<std::vector<int>> morse_code;
bool morse_state = false;
int time_diff = 0;
int code_time = 0;
int code_btn_digital_read_time = 0;
int state_btn_digital_read_time = 0;
bool current_pressed_code = false;
bool current_pressed_state = false;
bool last_pressed_code = false;
bool last_pressed_state = false;
bool last_morse_state = false;
int count = 0;

void morse_btns_check() {
    current_pressed_code = (digitalRead(PIN_BUTTON_1) == 0);
    current_pressed_state = (digitalRead(PIN_BUTTON_2) == 0);
    code_btn(current_pressed_code);
    state_btn(current_pressed_state);
}

void code_btn(bool pressed) {
    if (millis() - code_btn_digital_read_time > 100) {
        if (morse_state) {
            if (pressed != last_pressed_code) {
                time_diff = millis() - code_time;
                morse_code.push_back({!pressed, time_diff});
                code_time = millis();
                last_pressed_code = pressed;
            }
        } else {
            if (pressed != last_pressed_code) {
                if (pressed) Serial.println("pressed in");
                if (!pressed) Serial.println("pressed out");
                last_pressed_code = pressed;
                morse_mqtt_pub(morse_state, String(pressed));
            }
            // mqtt_pub("natnat", "chi");
        }
        code_btn_digital_read_time = millis();
    }
}

void state_btn(bool pressed) {
    if (pressed) {
        if (!last_pressed_state) {
            state_btn_digital_read_time = millis();
            last_pressed_state = true;
            morse_state = !morse_state;
            Serial.println((String)"change morse state " + (String)count + ": " + (String)morse_state);
            count++;
            if (!morse_state) {
                time_diff = millis() - code_time;
                morse_code.push_back({current_pressed_code, time_diff});
                if (morse_code.size() > 0 ) {
                    for (std::vector<int> temp : morse_code) {
                        Serial.print((String)temp[0] + ": " + (String)temp[1] + ", ");
                    }
                    Serial.println();
                    morse_mqtt_pub(!morse_state, vector_to_string(morse_code));
                    morse_code.clear();
                }
            } else {
                code_time = millis();
            }
        } 
    } else {
        if (millis() - state_btn_digital_read_time > 200) {
            last_pressed_state = false;
        }
    }
}

void morse_mqtt_pub(bool state, String content) {
    DynamicJsonDocument pub_json(1024);
    pub_json["state"] = int(state);
    pub_json["content"] = content;
    String pub_json_string;
    serializeJson(pub_json, pub_json_string);
    mqtt_pub(pub_json_string, MQTT_PUB_TOPIC, false);
}

String vector_to_string(std::vector<std::vector<int>>& vectors) {
    String res = "[";
    // for (std::vector<int> vector : vectors) {
    for (int j = 0; j < vectors.size(); j++) {
        std::vector<int> vector = vectors[j];
        res += "[";
        for (int i = 0; i < vector.size(); i++) {
            res += String(vector[i]);
            if (i < vector.size() - 1) res += ",";
        }
        res += "]";
        if (j < vectors.size() - 1) res += ",";
    }
    return res + "]";
}
