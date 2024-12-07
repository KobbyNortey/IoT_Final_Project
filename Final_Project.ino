#include <WiFi.h>
#include <WebServer.h>
#include <pgmspace.h>


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>Smart Object Dashboard</title>
    <link rel="stylesheet" href="/assets/css/styles.css">
</head>
<body>
    <header>
        <h1>Smart Object Dashboard</h1>
        <nav>
            <ul>
                <li><a href="/index.html">Smart Object Dashboard</a></li>
                <li><a href="/config.html">Configuration</a></li>
                <li><a href="/historical_data.html">Historical Data</a></li>
                <li><a href="/node_management.html">Node Management</a></li>
                <li><a href="/reports.html">Reports</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <section id="sensor-readings">
            <h2>Current Sensor Readings</h2>
            <div id="readings">
                <p>Temperature: <span id="temp">Loading...</span> °C</p>
                <p>Humidity: <span id="humidity">Loading...</span> %</p>
                <p>Light Intensity: <span id="light">Loading...</span> lux</p>
            </div>
        </section>
        <section id="fan-controls">
            <h2>Fan Controls</h2>
            <button id="start-fan">Start Fan</button>
            <button id="stop-fan">Stop Fan</button>
        </section>
        <section id="ldr-data">
            <h2>Last 15 LDR Readings</h2>
            <ul id="ldr-list">Loading...</ul>
        </section>
    </main>
    <script src="/assets/js/app.js"></script>
</body>
</html>
)rawliteral";

const char config_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>Smart Object Configuration</title>
    <link rel="stylesheet" href="/assets/css/styles.css">
</head>
<body>
    <header>
        <h1>Smart Object Configuration</h1>
        <nav>
            <ul>
                <li><a href="/index.html">Smart Object Dashboard</a></li>
                <li><a href="/config.html">Configuration</a></li>
                <li><a href="/historical_data.html">Historical Data</a></li>
                <li><a href="/node_management.html">Node Management</a></li>
                <li><a href="/reports.html">Reports</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <form id="config-form">
            <label for="object-id">Smart Object ID/Name:</label>
            <input type="text" id="object-id" name="object-id" required>

            <label for="protocol">Data Protocol:</label>
            <select id="protocol" name="protocol">
                <option value="http">HTTP</option>
                <option value="mqtt">MQTT</option>
            </select>

            <label for="fan-mode">Fan Mode:</label>
            <select id="fan-mode" name="fan-mode">
                <option value="manual">Manual</option>
                <option value="auto">Automatic</option>
            </select>

            <label for="trigger-temp">Fan Trigger Temperature (°C):</label>
            <input type="number" id="trigger-temp" name="trigger-temp" required>

            <button type="submit">Save Configuration</button>
        </form>
    </main>
    <script src="/assets/js/config.js"></script>
</body>
</html>
)rawliteral";

const char historical_data_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>Historical Data</title>
    <link rel="stylesheet" href="/assets/css/styles.css">
</head>
<body>
    <header>
        <h1>Historical Data</h1>
        <nav>
            <ul>
                <li><a href="/index.html">Smart Object Dashboard</a></li>
                <li><a href="/config.html">Configuration</a></li>
                <li><a href="/historical_data.html">Historical Data</a></li>
                <li><a href="/node_management.html">Node Management</a></li>
                <li><a href="/reports.html">Reports</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <canvas id="data-chart"></canvas>
    </main>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <script src="/assets/js/historical_data.js"></script>
</body>
</html>
)rawliteral";

const char node_management_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>Node Management</title>
    <link rel="stylesheet" href="/assets/css/styles.css">
</head>
<body>
    <header>
        <h1>Node Management</h1>
        <nav>
            <ul>
                <li><a href="/index.html">Smart Object Dashboard</a></li>
                <li><a href="/config.html">Configuration</a></li>
                <li><a href="/historical_data.html">Historical Data</a></li>
                <li><a href="/node_management.html">Node Management</a></li>
                <li><a href="/reports.html">Reports</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <form id="node-form">
            <label for="node-id">Smart Node ID:</label>
            <input type="text" id="node-id" name="node-id" required>

            <label for="node-name">Descriptive Name:</label>
            <input type="text" id="node-name" name="node-name" required>

            <label for="node-location">Location:</label>
            <input type="text" id="node-location" name="node-location" required>

            <button type="submit">Add Node</button>
        </form>

        <section id="node-list-section">
            <h2>Registered Smart Nodes</h2>
            <ul id="node-list">Loading...</ul>
        </section>
    </main>
    <script src="/assets/js/node_management.js"></script>
</body>
</html>
)rawliteral";

const char reports_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>Reports</title>
    <link rel="stylesheet" href="/assets/css/styles.css">
</head>
<body>
    <header>
        <h1>Reports</h1>
        <nav>
            <ul>
                <li><a href="/index.html">Smart Object Dashboard</a></li>
                <li><a href="/config.html">Configuration</a></li>
                <li><a href="/historical_data.html">Historical Data</a></li>
                <li><a href="/node_management.html">Node Management</a></li>
                <li><a href="/reports.html">Reports</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <form id="report-form">
            <label for="report-node-id">Select Smart Node:</label>
            <select id="report-node-id"></select>
            <button type="submit">View Report</button>
        </form>
        <section id="report-results"></section>
    </main>
    <script src="/assets/js/reports.js"></script>
</body>
</html>
)rawliteral";

////////////////////////////////////////
// CSS
////////////////////////////////////////

const char styles_css[] PROGMEM = R"rawliteral(
* {
    margin:0; padding:0; box-sizing:border-box;
}
body {
    font-family:Arial,sans-serif; background:#f9f9f9; color:#333; line-height:1.6;
    margin:0;
}
header {
    background:#0056b3; color:#fff; text-align:center; padding:1rem 0; margin-bottom:1rem;
}
header h1 {
    font-size:1.8rem; text-transform:uppercase; letter-spacing:2px;
}
nav {
    background:#004080; margin-top:1rem; border-radius:4px; overflow:hidden;
}
nav ul {
    list-style:none; display:flex; flex-wrap:wrap; margin:0; padding:0;
}
nav li { margin:0; }
nav a {
    display:block; padding:0.8rem 1.2rem; color:#fff; text-decoration:none; transition:background-color 0.3s ease;
}
nav a:hover {
    background:#003060;
}
main {
    width:90%; max-width:1200px; margin:0 auto; display:flex; flex-direction:column; gap:2rem;
}
section {
    background:#fff; padding:1.5rem; border-radius:8px; box-shadow:0 2px 5px rgba(0,0,0,0.1);
}
section h2 {
    margin-bottom:1rem; font-size:1.5rem; color:#0056b3;
}
#fan-controls button,
form button {
    padding:0.8rem 1.5rem; margin-right:1rem; font-size:1rem; color:#fff; background:#007bff; border:none; border-radius:4px; cursor:pointer; transition:background-color 0.3s ease;
}
#fan-controls button:hover,
form button:hover {
    background:#0056b3;
}
#ldr-list li,
#node-list li {
    background:#f1f1f1; padding:0.5rem; border:1px solid #ddd; border-radius:4px; margin-bottom:0.5rem;
}
form {
    display:flex; flex-direction:column; gap:1rem;
}
form label {
    font-weight:bold; margin-bottom:0.3rem;
}
form input, form select {
    padding:0.8rem; font-size:1rem; border:1px solid #ddd; border-radius:4px;
}
canvas {
    max-width:100%; height:auto; margin-top:1rem;
}
@media (max-width:768px) {
    main { gap:1.5rem; }
    section h2 { font-size:1.3rem; }
    #fan-controls button { width:100%; margin-bottom:1rem; }
}
)rawliteral";

////////////////////////////////////////
// JavaScript
////////////////////////////////////////

// app.js (for index.html)
const char app_js[] PROGMEM = R"rawliteral(
setInterval(() => {
  fetch('/api/sensor-readings')
  .then(response => response.json())
  .then(data => {
    document.getElementById('temp').textContent = data.temperature;
    document.getElementById('humidity').textContent = data.humidity;
    document.getElementById('light').textContent = data.light;
  })
  .catch(err => console.error('Error:', err));
}, 5000);

fetch('/api/ldr-readings')
.then(response => response.json())
.then(data => {
  const ldrList = document.getElementById('ldr-list');
  ldrList.innerHTML = '';
  data.forEach(reading => {
    const li = document.createElement('li');
    li.textContent = `${reading.timestamp}: ${reading.value} lux`;
    ldrList.appendChild(li);
  });
})
.catch(err => console.error('Error:', err));

document.getElementById('start-fan').addEventListener('click', () => {
  fetch('/api/fan/start', {method:'POST'})
  .then(() => alert('Fan started manually.'))
  .catch(err => console.error('Error:', err));
});

document.getElementById('stop-fan').addEventListener('click', () => {
  fetch('/api/fan/stop', {method:'POST'})
  .then(() => alert('Fan stopped manually.'))
  .catch(err => console.error('Error:', err));
});
)rawliteral";

// config.js
const char config_js[] PROGMEM = R"rawliteral(
document.getElementById('config-form').addEventListener('submit', (e) => {
  e.preventDefault();
  const formData = {
    id: document.getElementById('object-id').value,
    protocol: document.getElementById('protocol').value,
    fanMode: document.getElementById('fan-mode').value,
    triggerTemp: document.getElementById('trigger-temp').value
  };
  fetch('/api/config', {
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body:JSON.stringify(formData)
  })
  .then(() => alert('Configuration saved successfully.'))
  .catch(err => console.error('Error:', err));
});
)rawliteral";

// historical_data.js
const char historical_data_js[] PROGMEM = R"rawliteral(
fetch('/api/historical-data')
.then(res => res.json())
.then(data => {
  const ctx = document.getElementById('data-chart').getContext('2d');
  new Chart(ctx, {
    type:'line',
    data:{
      labels: data.timestamps,
      datasets:[
        {label:'Temperature', data:data.temperatures},
        {label:'Humidity', data:data.humidities},
        {label:'Light', data:data.lights}
      ]
    }
  });
})
.catch(err => console.error('Error:', err));
)rawliteral";

// node_management.js
const char node_management_js[] PROGMEM = R"rawliteral(
// Fetch existing nodes
fetch('/api/nodes')
.then(res => res.json())
.then(nodes => {
  const nodeList = document.getElementById('node-list');
  nodeList.innerHTML = '';
  nodes.forEach(node => {
    const li = document.createElement('li');
    li.textContent = `${node.id} - ${node.name} (${node.location})`;
    nodeList.appendChild(li);
  });
})
.catch(err => console.error('Error:', err));

document.getElementById('node-form').addEventListener('submit', (event) => {
  event.preventDefault();
  const formData = {
    id: document.getElementById('node-id').value,
    name: document.getElementById('node-name').value,
    location: document.getElementById('node-location').value
  };
  fetch('/api/nodes', {
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body:JSON.stringify(formData)
  })
  .then(() => {
    alert('Node added successfully.');
    location.reload();
  })
  .catch(err => console.error('Error:', err));
});
)rawliteral";

// reports.js
const char reports_js[] PROGMEM = R"rawliteral(
// Populate node dropdown
fetch('/api/nodes')
.then(response => response.json())
.then(nodes => {
  const select = document.getElementById('report-node-id');
  nodes.forEach(node => {
    const option = document.createElement('option');
    option.value = node.id;
    option.textContent = `${node.name} (${node.location})`;
    select.appendChild(option);
  });
})
.catch(err => console.error('Error:', err));

document.getElementById('report-form').addEventListener('submit', (event) => {
  event.preventDefault();
  const nodeId = document.getElementById('report-node-id').value;
  fetch(`/api/report?node=${nodeId}`)
  .then(res => res.json())
  .then(reportData => {
    const reportResults = document.getElementById('report-results');
    reportResults.innerHTML = `
      <h2>Report for Node: ${reportData.nodeName}</h2>
      <p><strong>Location:</strong> ${reportData.location}</p>
      <p><strong>Average Temperature:</strong> ${reportData.avgTemp} °C</p>
      <p><strong>Average Humidity:</strong> ${reportData.avgHumidity} %</p>
      <p><strong>Average Light:</strong> ${reportData.avgLight} lux</p>
    `;
  })
  .catch(err => console.error('Error:', err));
});
)rawliteral";

////////////////////////////////////////
// Web Server Setup
////////////////////////////////////////
WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // HTML routes
  server.on("/", HTTP_GET, [](){
    server.send_P(200, "text/html", index_html);
  });
  server.on("/index.html", HTTP_GET, [](){
    server.send_P(200, "text/html", index_html);
  });

  server.on("/config.html", HTTP_GET, [](){
    server.send_P(200, "text/html", config_html);
  });

  server.on("/historical_data.html", HTTP_GET, [](){
    server.send_P(200, "text/html", historical_data_html);
  });

  server.on("/node_management.html", HTTP_GET, [](){
    server.send_P(200, "text/html", node_management_html);
  });

  server.on("/reports.html", HTTP_GET, [](){
    server.send_P(200, "text/html", reports_html);
  });

  // CSS
  server.on("/assets/css/styles.css", HTTP_GET, [](){
    server.send_P(200, "text/css", styles_css);
  });

  // JS
  server.on("/assets/js/app.js", HTTP_GET, [](){
    server.send_P(200, "application/javascript", app_js);
  });

  server.on("/assets/js/config.js", HTTP_GET, [](){
    server.send_P(200, "application/javascript", config_js);
  });

  server.on("/assets/js/historical_data.js", HTTP_GET, [](){
    server.send_P(200, "application/javascript", historical_data_js);
  });

  server.on("/assets/js/node_management.js", HTTP_GET, [](){
    server.send_P(200, "application/javascript", node_management_js);
  });

  server.on("/assets/js/reports.js", HTTP_GET, [](){
    server.send_P(200, "application/javascript", reports_js);
  });

  // API Endpoints (Placeholders)
  server.on("/api/sensor-readings", HTTP_GET, [](){
    // Return sample JSON data
    server.send(200, "application/json", R"({"temperature":25,"humidity":60,"light":300})");
  });

  server.on("/api/ldr-readings", HTTP_GET, [](){
    // Return sample array of LDR readings
    server.send(200, "application/json", R"([{"timestamp":"10:00","value":300},{"timestamp":"10:01","value":310}])");
  });

  server.on("/api/fan/start", HTTP_POST, [](){
    // Implement actual fan start logic
    server.send(200, "text/plain", "Fan started");
  });

  server.on("/api/fan/stop", HTTP_POST, [](){
    // Implement actual fan stop logic
    server.send(200, "text/plain", "Fan stopped");
  });

  server.on("/api/config", HTTP_POST, [](){
    // Here you'd parse the JSON and save config
    // For demo, just respond success
    server.send(200, "text/plain", "Configuration saved");
  });

  server.on("/api/historical-data", HTTP_GET, [](){
    // Return sample data for chart
    server.send(200, "application/json", R"({
      "timestamps":["10:00","10:05","10:10"],
      "temperatures":[25,26,27],
      "humidities":[60,62,63],
      "lights":[300,320,330]
    })");
  });

  server.on("/api/nodes", HTTP_GET, [](){
    // Return sample nodes
    server.send(200, "application/json", R"([
      {"id":"node1","name":"Living Room","location":"Indoors"},
      {"id":"node2","name":"Garden","location":"Outdoors"}
    ])");
  });

  server.on("/api/nodes", HTTP_POST, [](){
    // Add node logic
    // Just respond success for demo
    server.send(200, "text/plain", "Node added");
  });

  server.on("/api/report", HTTP_GET, [](){
    // Return sample report data
    // In a real scenario, you'd filter by the node query param
    server.send(200, "application/json", R"({
      "nodeName":"Living Room",
      "location":"Indoors",
      "avgTemp":26,
      "avgHumidity":61,
      "avgLight":315
    })");
  });

  // Not found
  server.onNotFound([](){
    server.send(404, "text/plain", "Not Found");
  });

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
