fetch('/api/historical-data')
    .then(response => response.json())
    .then(data => {
        const ctx = document.getElementById('data-chart').getContext('2d');
        new Chart(ctx, {
            type: 'line',
            data: {
                labels: data.timestamps,
                datasets: [
                    { label: 'Temperature', data: data.temperatures },
                    { label: 'Humidity', data: data.humidities },
                    { label: 'Light Intensity', data: data.lights }
                ]
            }
        });
    })
    .catch(err => console.error('Error fetching historical data:', err));
