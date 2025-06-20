#ifndef OTA_CICD_H
#define OTA_CICD_H

#include <Arduino.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <HttpsOTAUpdate.h>
#include <esp_https_ota.h>
#include <esp_http_client.h>
#include <mqtt_client.h>

#ifndef APP_VERSION
# define APP_VERSION "dev"
#endif

struct ReleaseMessage {
  String repository;
  String url;
  String version;
};

class OtaCicd
{
public:
    static bool init(String certPem);
    static bool init(String certPem, String releaseTopic, String versionTopic, esp_mqtt_client_config_t mqttConfig);
    static void start(String message);
    static String getVersion();
    static esp_mqtt_client_handle_t mqttClient;
    static String getCurrentVersion();
    static bool _confirmUpdate();
    static void sendVersionAndMac();
    static String _versionTopic;

private:
    static String _certPem;
    static String _releaseTopic;
    static Preferences _preferences;
    static bool _setVersion(String version);
    static ReleaseMessage _parseMessage(String message);
    static void _onMqttData(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
};

#endif