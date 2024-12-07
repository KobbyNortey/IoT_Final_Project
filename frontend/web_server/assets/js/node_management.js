// Fetch existing nodes
fetch('/api/nodes')
    .then(response => response.json())
    .then(nodes => {
        const nodeList = document.getElementById('node-list');
        nodeList.innerHTML = '';
        nodes.forEach(node => {
            const li = document.createElement('li');
            li.textContent = `${node.id} - ${node.name} (${node.location})`;
            nodeList.appendChild(li);
        });
    })
    .catch(err => console.error('Error fetching nodes:', err));

document.getElementById('node-form').addEventListener('submit', (event) => {
    event.preventDefault();
    const formData = {
        id: document.getElementById('node-id').value,
        name: document.getElementById('node-name').value,
        location: document.getElementById('node-location').value
    };

    fetch('/api/nodes', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(formData)
    })
        .then(response => {
            if (response.ok) {
                alert('Node added successfully.');
                location.reload();
            }
        })
        .catch(err => console.error('Error adding node:', err));
});
