import websocket
import json

# WebSocket URL (replace with your actual Node-RED server IP)
NODE_RED_WS_URL = "ws://172.24.114.190:1880/ws/ecg/1"  # Change patient ID as needed

# Callback when WebSocket connection is opened
def on_open(ws):
    print(f"✅ Connected to {NODE_RED_WS_URL}")

# Callback when a message is received
def on_message(ws, message):
    try:
        data = json.loads(message)  # Parse JSON message
        print(f"📡 Received ECG Data: {data}")
    except Exception as e:
        print(f"❌ Error parsing message: {e}")

# Callback when WebSocket connection is closed
def on_close(ws, close_status_code, close_msg):
    print("⚠️ WebSocket Connection Closed")

# Callback when WebSocket error occurs
def on_error(ws, error):
    print(f"❌ WebSocket Error: {error}")

# Create WebSocket client
ws = websocket.WebSocketApp(
    NODE_RED_WS_URL,
    on_open=on_open,
    on_message=on_message,
    on_close=on_close,
    on_error=on_error
)

# Run WebSocket client
ws.run_forever()
