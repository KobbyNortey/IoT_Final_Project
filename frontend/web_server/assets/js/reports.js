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
    .catch(err => console.error('Error fetching nodes:', err));

document.getElementById('report-form').addEventListener('submit', (event) => {
    event.preventDefault();
    const nodeId = document.getElementById('report-node-id').value;

    fetch(`/api/report?node=${nodeId}`)
        .then(response => response.json())
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
        .catch(err => console.error('Error fetching report:', err));
});
