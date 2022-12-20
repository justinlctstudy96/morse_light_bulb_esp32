#include <morse_logic.h>

std::vector<std::vector<int>> morse_code;
bool morse_state = false;
int time_diff = 0;
int code_time = 0;
int record_start_time = 0;
// for btn pressing check (avoid small electrical variation cause less then ms button pressing count)
int code_btn_digital_read_time = 0;
int state_btn_digital_read_time = 0;
int bulb_btn_digital_read_time = 0;
bool current_pressed_code = false;
bool current_pressed_state = false;
bool current_pressed_bulb = false;
bool last_pressed_code = false;
bool last_pressed_state = false;
bool last_pressed_bulb = false;
// morse state
bool last_morse_state = false;
int count = 0;

void morse_btns_check() { // checks for pressing of the buttons
    current_pressed_code = (digitalRead(PIN_BTN_MORSE) == 0);
    current_pressed_state = (digitalRead(PIN_BTN_MODE) == 0);
    current_pressed_bulb = (digitalRead(PIN_BTN_BULB) == 0);
    code_btn(current_pressed_code);
    state_btn(current_pressed_state);
    bulb_btn(current_pressed_bulb);
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
                last_pressed_code = pressed;
                morse_mqtt_pub(morse_state, String(pressed));
            }
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
            if (!morse_state) { // state 0 
                digitalWrite(PIN_LIGHT_BTN_STATE, LOW);
                time_diff = millis() - code_time;
                morse_code.push_back({current_pressed_code, time_diff});
                if (morse_code.size() > 0 ) { // if there is morse code recorded
                    for (std::vector<int> temp : morse_code) Serial.print((String)temp[0] + ": " + (String)temp[1] + ", ");
                    Serial.println();
                    morse_mqtt_pub(!morse_state, vector_to_string(morse_code));
                    morse_code.clear();
                }
            } else { // state 1
                digitalWrite(PIN_LIGHT_BTN_STATE, HIGH);
                code_time = millis();
                record_start_time = millis();
            }
        } 
    } else {
        if (millis() - state_btn_digital_read_time > 200) {
            last_pressed_state = false;
        }
    }
}

void bulb_btn(bool pressed) {
    if (pressed) {
        if (!last_pressed_bulb) {
            bulb_btn_digital_read_time = millis();
            last_pressed_bulb = true;
            digitalWrite(PIN_LIGHT_BULB, !digitalRead(PIN_LIGHT_BULB));
        }
    } else {
        if (millis() - bulb_btn_digital_read_time > 100) {
            last_pressed_bulb = false;
        }
    }
}

void state_one_record_timeout_check() {
    if  (morse_state) {
        if ( millis() - record_start_time > MORSE_RECORD_TIMEOUT) {
            if (morse_code.size() > 0 ) { // if there is morse code recorded
                for (std::vector<int> temp : morse_code) Serial.print((String)temp[0] + ": " + (String)temp[1] + ", ");
                Serial.println();
                morse_mqtt_pub(morse_state, vector_to_string(morse_code));
                morse_code.clear();
            }
            morse_state = false;
            digitalWrite(PIN_LIGHT_BTN_STATE, LOW);
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

std::vector<std::vector<int>> string_to_vector(String str) {
    int bracket_lv = 0;
    std::vector<std::vector<int>> res;
    std::vector<int> vector;
    String temp;
    for (char c : str) {
        if (c == '[') {
            bracket_lv++;
            continue;
        }
        if (bracket_lv==2) {
            if (c == ',' || c == ']') {
                vector.push_back(temp.toInt());
                temp = "";
                if (c == ']') {
                    bracket_lv--;
                    if (vector.size() > 0) {
                        res.push_back(vector);
                        vector.clear();
                    }
                }
                continue;
            }
            temp += c;
        }
    }
    return res;
}

void mqtt_morse_msg_render(String msg) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, msg);
    JsonObject obj = doc.as<JsonObject>();
    if (!obj["state"]) { // state 0
        digitalWrite(PIN_LIGHT_BULB, obj["content"] ? !digitalRead(PIN_LIGHT_BULB) : digitalRead(PIN_LIGHT_BULB));;
    } else { // state 1
        std::vector<std::vector<int>> morse = string_to_vector(obj["content"]);
        int original_digital = digitalRead(PIN_LIGHT_BULB);
        for (std::vector<int> code : morse ) {
            int code_start_time = millis();
            digitalWrite(PIN_LIGHT_BULB, code[0] ? !original_digital : original_digital);
            while (millis() - code_start_time < code[1]);
        }
        digitalWrite(PIN_LIGHT_BULB, original_digital); // confirm the light bulb return to its initial digital stage
    }
}