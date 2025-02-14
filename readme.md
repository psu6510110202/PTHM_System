## Installation

### 1. Install All Services with Docker
Navigate to the `docker` folder and run:

```sh
docker-compose up -d
```

# Node-RED Setup Guide

## Prerequisites
- Node-RED installed and running.
- PostgreSQL service available.
- MQTT Broker service available.

## Installation & Configuration

### 1. Open Node-RED
Start Node-RED and open your browser to:


```
http://localhost:1880
```

### 2. Install Required Nodes
1. Open the **menu (☰)** in the top-right corner.
2. Select **Manage Palette**.
3. Go to the **Install** tab.
4. Search for and install:

```
node-red-contrib-re-postgres
```

### 3. Import Flow Configuration
1. Open the **menu (☰)** and select **Import**.
2. Click **Select a file to import**.
3. Navigate to and select:
   
```
/node_red/flows.json
```

4. Click **Import** to load the flow.

### 4. Configure MQTT Broker
1. Locate the **MQTT node** in the imported flow.
2. Open its settings and update the **MQTT host** to match your broker’s IP address (If you run all service in docker , Go to Inspect -> Network).

### 5. Configure PostgreSQL Connection
1. Locate the **PostgreSQL node** in the imported flow.
2. Open its settings and update the **PostgreSQL host** to match your database server’s IP address.

### 6. Deploy the Flow
Click the **Deploy** button in the top-right corner to apply changes.

---

Your Node-RED setup is now ready! 🚀
