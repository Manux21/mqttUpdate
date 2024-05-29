import paho.mqtt.client as mqtt
import os

broker_address = os.getenv("MQTT_BROKER_ADDRESS")
port = int(os.getenv("MQTT_PORT", 1883))
topic = "esp32/update"

client = mqtt.Client("GitHubActionsClient")
client.username_pw_set(os.getenv("MQTT_USERNAME"), os.getenv("MQTT_PASSWORD"))
client.connect(broker_address, port=port)

message = {
    "firmware_url": f"https://{os.getenv('S3_BUCKET')}.s3.amazonaws.com/firmware/firmware.bin",
    "version": os.getenv("FIRMWARE_VERSION", "1.0.0")  # Убедитесь, что обновляете версию при каждом изменении
}

client.publish(topic, str(message))
client.disconnect()