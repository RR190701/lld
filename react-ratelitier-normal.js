import { useState, useRef } from "react";

const LIMIT = 3;
const MIN_DURATION = 3000;
const MAX_DURATION = 5000;

let taskIdCounter = 0;
///as long as we are not passing these re -redenring fucntions in a child props it doesn't matter other wise Ihave to use useCallback

export default function App() {
  const [tasks, setTasks] = useState([]);
  const runningCount = useRef(0);
  const queue = useRef([]);

  function startTask(id, duration) {
    runningCount.current++;
    const start = performance.now();

    function tick(now) {
      const progress = Math.min((now - start) / duration, 1);

      setTasks(prev =>
        prev.map(t => t.id === id ? { ...t, progress, status: progress < 1 ? "running" : "done" } : t)
      );

      if (progress < 1) {
        requestAnimationFrame(tick);
      } else {
        runningCount.current--;
        flush();
      }
    }

    requestAnimationFrame(tick);
  }

  function flush() {
    while (runningCount.current < LIMIT && queue.current.length > 0) {
      const { id, duration } = queue.current.shift();
      startTask(id, duration);
    }
  }

  function addTask() {
    const id = ++taskIdCounter;
    const duration = MIN_DURATION + Math.random() * (MAX_DURATION - MIN_DURATION);

    queue.current.push({ id, duration });
    setTasks(prev => [...prev, { id, duration, progress: 0, status: "queued" }]);
    flush();
  }

  return (
    <div style={{ padding: "1.5rem", maxWidth: 600 }}>
      <button onClick={addTask}>+ Add progress bar</button>
      <div style={{ display: "flex", flexDirection: "column", gap: 12, marginTop: 16 }}>
        {tasks.map(task => (
          <ProgressBar key={task.id} task={task} />
        ))}
      </div>
    </div>
  );
}
