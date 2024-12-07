document.getElementById('config-form').addEventListener('submit', (event) => {
    event.preventDefault();

    const formData = {
        id: document.getElementById('object-id').value,
        protocol: document.getElementById('protocol').value,
        fanMode: document.getElementById('fan-mode').value,
        triggerTemp: document.getElementById('trigger-temp').value
    };

    fetch('/api/config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(formData)
    })
        .then(response => {
            if (response.ok) alert('Configuration saved successfully.');
        })
        .catch(err => console.error('Error saving configuration:', err));
});
