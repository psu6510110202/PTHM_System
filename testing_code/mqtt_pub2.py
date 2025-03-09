import paho.mqtt.client as mqtt
import json

# MQTT Broker Configuration
BROKER = "localhost"  # Change this to your MQTT broker IP
TOPIC = "sensor/device/000005"
client = mqtt.Client()
client.connect(BROKER, 1883, 60)


payload = json.dumps({"body_temp": 38.6, "heart_rate": 150, 
                          "blood_oxy": 91.98, "room_temp": 40, 
                          "room_humidity": 65, "patient_id": "000004" })  # Round for better readability
client.publish(TOPIC, payload)
print(f"Published: {payload}")