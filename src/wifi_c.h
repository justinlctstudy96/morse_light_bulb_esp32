#ifndef __WIFI_C_H__
#define __WIFI_C_H__

#include <Arduino.h>
#include <WiFi.h>
#include <config.h>

void wifi_init();
bool wifi_stat();
void wifi_connect_check();

#endif