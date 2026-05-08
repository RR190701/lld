import { useState, useRef, useCallback } from "react";

const LIMIT = 3;
const MIN_DURATION = 3000;
const MAX_DURATION = 5000;

let taskIdCounter = 0;

export default function App() {
  const [tasks, setTasks] = useState([]);
  const runningCount = useRef(0);
  const queue = useRef([]);

  const startTask = useCallback((id, duration) => {
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

    setTasks(prev =>
      prev.map(t => t.id === id ? { ...t, status: "running" } : t)
    );
    requestAnimationFrame(tick);
  }, []);

  const flush = useCallback(() => {
    while (runningCount.current < LIMIT && queue.current.length > 0) {
      const { id, duration } = queue.current.shift();
      startTask(id, duration);
    }
  }, [startTask]);

  const addTask = useCallback(() => {
    const id = ++taskIdCounter;
    const duration = MIN_DURATION + Math.random() * (MAX_DURATION - MIN_DURATION);
    const newTask = { id, duration, progress: 0, status: "queued" };

    queue.current.push({ id, duration });
    setTasks(prev => [...prev, newTask]);
    flush();
  }, [flush]);

  return (
    <div style={{ padding: "1.5rem", fontFamily: "sans-serif", maxWidth: 600 }}>
      <button onClick={addTask}>+ Add progress bar</button>

      <p style={{ fontSize: 13, color: "gray" }}>
        {runningCount.current} running · {queue.current.length} queued
      </p>

      <div style={{ display: "flex", flexDirection: "column", gap: 12, marginTop: 16 }}>
        {tasks.map(task => (
          <ProgressBar key={task.id} task={task} />
        ))}
      </div>
    </div>
  );
}

function ProgressBar({ task }) {
  const { id, progress, status } = task;

  const statusColor = { running: "blue", queued: "orange", done: "green" }[status];
  const fillColor = { running: "#378ADD", queued: "#D3D1C7", done: "#639922" }[status];

  return (
    <div style={{ border: "1px solid #eee", borderRadius: 8, padding: "10px 14px" }}>
      <div style={{ display: "flex", justifyContent: "space-between", marginBottom: 8 }}>
        <span style={{ fontWeight: 500 }}>Task #{id}</span>
        <span style={{ fontSize: 12, color: statusColor }}>{status}</span>
      </div>
      <div style={{ height: 8, background: "#f0f0f0", borderRadius: 99, overflow: "hidden" }}>
        <div style={{
          height: "100%",
          width: `${(progress * 100).toFixed(1)}%`,
          background: fillColor,
          borderRadius: 99,
          transition: "width 0.05s linear"
        }} />
      </div>
    </div>
  );
}
