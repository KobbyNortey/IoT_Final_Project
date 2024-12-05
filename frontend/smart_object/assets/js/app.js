// Fetch sensor readings every 5 seconds
setInterval(() => {
    fetch('/api/sensor-readings')
        .then(response => response.json())
        .then(data => {
            document.getElementById('temp').textContent = data.temperature;
            document.getElementById('humidity').textContent = data.humidity;
            document.getElementById('light').textContent = data.light;
        })
        .catch(err => console.error('Error fetching sensor readings:', err));
}, 5000);

// Fetch last 15 LDR readings
fetch('/api/ldr-readings')
    .then(response => response.json())
    .then(data => {
        const ldrList = document.getElementById('ldr-list');
        ldrList.innerHTML = '';
        data.forEach((reading) => {
            const listItem = document.createElement('li');
            listItem.textContent = `${reading.timestamp}: ${reading.value} lux`;
            ldrList.appendChild(listItem);
        });
    })
    .catch(err => console.error('Error fetching LDR readings:', err));

// Fan controls
document.getElementById('start-fan').addEventListener('click', () => {
    fetch('/api/fan/start', { method: 'POST' })
        .then(response => {
            if (response.ok) alert('Fan started manually.');
        })
        .catch(err => console.error('Error starting fan:', err));
});

document.getElementById('stop-fan').addEventListener('click', () => {
    fetch('/api/fan/stop', { method: 'POST' })
        .then(response => {
            if (response.ok) alert('Fan stopped manually.');
        })
        .catch(err => console.error('Error stopping fan:', err));
});
