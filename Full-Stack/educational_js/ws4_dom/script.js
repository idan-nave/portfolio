document.addEventListener('DOMContentLoaded', () => {
    const taskInput = document.getElementById('task-input');
    const addTaskBtn = document.getElementById('add-task-btn');
    const taskList = document.getElementById('task-list');
    const clearCompletedBtn = document.getElementById('clear-completed-btn');

    // Add Task
    addTaskBtn.addEventListener('click', () => {
        const taskText = taskInput.value.trim();
        if (taskText) {
            createTask(taskText);
            taskInput.value = '';
        }
    });

    // Clear Completed Tasks
    clearCompletedBtn.addEventListener('click', () => {
        const completedTasks = document.querySelectorAll('.completed');
        completedTasks.forEach(task => {
            task.classList.add('removing');
            setTimeout(() => task.remove(), 500); // Pin throw animation before removal
        });
    });

    // Create Task Element
    function createTask(taskText) {
        const li = document.createElement('li');
        li.innerHTML = `
            <img src="pin.png" class="pin" alt="Pin">
            <span>${taskText}</span>
            <div>
                <input type="checkbox" class="complete-checkbox">
                <button class="delete-btn">Delete</button>
            </div>
        `;

        // Add delete functionality
        li.querySelector('.delete-btn').addEventListener('click', () => {
            li.classList.add('removing');
            setTimeout(() => li.remove(), 500); // Pin throw animation before removal
        });

        // Add complete functionality
        li.querySelector('.complete-checkbox').addEventListener('change', (e) => {
            li.classList.toggle('completed', e.target.checked);
        });

        taskList.appendChild(li);
    }
});
