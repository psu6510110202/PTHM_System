import paho.mqtt.client as mqtt

# MQTT Broker Details
MQTT_BROKER = "localhost"  # Use your public IP or domain
MQTT_PORT = 1883  # Default MQTT port
MQTT_TOPIC = "ecg/patient/000001"  # Change this to match your topic

# Callback function when connected to MQTT broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("✅ Connected to MQTT Broker!")
        client.subscribe(MQTT_TOPIC)  # Subscribe to the topic
        print(f"📡 Subscribed to topic: {MQTT_TOPIC}")
    else:
        print(f"⚠️ Connection failed with code {rc}")

# Callback function when a message is received
def on_message(client, userdata, msg):
    print(f"📥 Received message: {msg.topic} -> {msg.payload.decode()}")

# Create MQTT client
client = mqtt.Client()

# Assign callback functions
client.on_connect = on_connect
client.on_message = on_message

# Connect to MQTT broker
try:
    print(f"🔗 Connecting to MQTT Broker at {MQTT_BROKER}:{MQTT_PORT}...")
    client.connect(MQTT_BROKER, MQTT_PORT, 60)  # 60s keepalive
    client.loop_forever()  # Keep the connection running
except Exception as e:
    print(f"❌ Failed to connect: {e}")
