#pragma once

#include <ArduinoJson.h>
#include "SolarDataRecord.h"
#include "StatefulService.h"

// #include <LightMqttSettingsService.h>

// #include <HttpEndpoint.h>
// #include <MqttPubSub.h>
// #include <WebSocketTxRx.h>

// #define LIGHT_SETTINGS_ENDPOINT_PATH "/rest/lightState"
// #define LIGHT_SETTINGS_SOCKET_PATH "/ws/lightState"
// #define LIGHT_SETTINGS_MQTT_PATH "/ws/lightState"

class SolarChargerState {
 public:
  SolarChargerRecord solarData;

  //   static void read(SolarChargerState& settings, JsonObject& root) {
  //     root["led_on"] = settings.ledOn;
  //  }

  //   static StateUpdateResult update(JsonObject& root, SolarChargerState& lightState) {
  //     boolean newState = root["led_on"] | DEFAULT_LED_STATE;
  //     if (lightState.ledOn != newState) {
  //       lightState.ledOn = newState;
  //       return StateUpdateResult::CHANGED;
  //     }
  //     return StateUpdateResult::UNCHANGED;
  //   }

  //   static void haRead(SolarChargerState& settings, JsonObject& root) {
  //     root["state"] = settings.ledOn ? ON_STATE : OFF_STATE;
  //   }

  //   static StateUpdateResult haUpdate(JsonObject& root, SolarChargerState& lightState) {
  //     String state = root["state"];
  //     // parse new led state
  //     boolean newState = false;
  //     if (state.equals(ON_STATE)) {
  //       newState = true;
  //     } else if (!state.equals(OFF_STATE)) {
  //       return StateUpdateResult::ERROR;
  //     }
  //     // change the new state, if required
  //     if (lightState.ledOn != newState) {
  //       lightState.ledOn = newState;
  //       return StateUpdateResult::CHANGED;
  //     }
  //     return StateUpdateResult::UNCHANGED;
  //   }
};

class SolarChargerStateService : public StatefulService<SolarChargerState> {
  //  public:
  //   SolarChargerStateService(AsyncWebServer* server,
  //                     SecurityManager* securityManager,
  //                     AsyncMqttClient* mqttClient,
  //                     LightMqttSettingsService* lightMqttSettingsService);
  //   void begin();

  //  private:
  //   HttpEndpoint<SolarChargerState> _httpEndpoint;
  //   MqttPubSub<SolarChargerState> _mqttPubSub;
  //   WebSocketTxRx<SolarChargerState> _webSocket;
  //   AsyncMqttClient* _mqttClient;
  //   LightMqttSettingsService* _lightMqttSettingsService;

  //   void registerConfig();
  //   void onConfigUpdated();
};
