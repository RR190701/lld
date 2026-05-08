// Implement mapLimit, which is a utility function that produces a list of outputs by mapping each input through an asynchronous iteratee function. The provided limit dictates how many operations can occur at once.

// Inputs
// inputs: An array of inputs.
// limit: The maximum number of operations at any one time.
// iterateeFn: The async function that should be called with each input to generate the corresponding output. It will have two arguments:
//      input: The input being processed.
//      callback: A function that will be called when the input is finished processing. It will be provided one argument, the processed output.
// callback: A function that should be called with the array of outputs once all the inputs have been processed.

function getNameById(id, callback) {
  // simulating async request
  const randomRequestTime = Math.floor(Math.random() * 100) + 200;

  setTimeout(() => {
    callback("User" + id);
  }, randomRequestTime);
}

function mapLimit(inputs, limit, iterateeFn, callback) {
  // implement here
  
  const result = [];
  let index = 0;

  

  //some data
  function work(){
      
  if( index >= inputs.length){
      callback(result);
      return;
  }
  
  //make chunks
  
  const chunck = inputs.slice(index, index + limit);
  index = index + limit;
  let completed = 0;
  
  for(let i = 0; i < chunck.length ; i++){
      iterateeFn(chunck[i], (res) => {
          completed++;
          result.push(res);
          
          if(completed == chunck.length){
              work();
          }
      })
  }
  }
  
  
  work();

}
//example: 
mapLimit([1, 2, 3, 4, 5], 2, getNameById, (allResults) => {
  console.log("output", allResults); // ["User1", "User2", "User3", "User4", "User5"]
});



///////////REACT CODE EQUI



import { useState, useRef } from "react";

function getNameById(id, callback) {
  const delay = Math.floor(Math.random() * 100) + 200;
  setTimeout(() => callback("User" + id), delay);
}

function mapLimit(inputs, limit, iterateeFn, onChunkDone, callback) {
  const result = [];
  let index = 0;

  function work() {
    if (index >= inputs.length) { callback(result); return; }
    const chunk = inputs.slice(index, index + limit);
    index += limit;
    let completed = 0;

    for (let i = 0; i < chunk.length; i++) {
      iterateeFn(chunk[i], (res) => {
        completed++;
        result.push(res);
        onChunkDone(chunk[i], res);         // ← tells React to update this chip
        if (completed === chunk.length) work();
      });
    }
  }
  work();
}

export default function App() {
  const [inputsRaw, setInputsRaw] = useState("1, 2, 3, 4, 5");
  const [limit, setLimit] = useState(2);
  const [chips, setChips] = useState([]);
  const [output, setOutput] = useState(null);

  function updateChip(id, value) {
    setChips(prev =>
      prev.map(c => c.id === id ? { ...c, status: "done", value } : c)
    );
  }

  function runMap() {
    const inputs = inputsRaw.split(",").map(s => Number(s.trim())).filter(Boolean);
    const initial = inputs.map(id => ({ id, status: "queued", value: "" }));
    setChips(initial);
    setOutput(null);

    mapLimit(
      inputs,
      limit,
      (id, cb) => {
        setChips(prev => prev.map(c => c.id === id ? { ...c, status: "running" } : c));
        getNameById(id, cb);
      },
      updateChip,
      (results) => setOutput(results)
    );
  }

  const statusColor = { queued: "#633806", running: "#0C447C", done: "#27500A" };
  const statusBg   = { queued: "#FAEEDA", running: "#E6F1FB", done: "#EAF3DE" };

  return (
    <div style={{ padding: "1.5rem", maxWidth: 600, fontFamily: "sans-serif" }}>
      <div style={{ display: "flex", gap: 8, flexWrap: "wrap", marginBottom: 16 }}>
        <input
          value={inputsRaw}
          onChange={e => setInputsRaw(e.target.value)}
          style={{ flex: 1, padding: "6px 10px", borderRadius: 8, border: "1px solid #ccc" }}
        />
        <input
          type="number" value={limit} min={1}
          onChange={e => setLimit(Number(e.target.value))}
          style={{ width: 56, padding: "6px 8px", borderRadius: 8, border: "1px solid #ccc", textAlign: "center" }}
        />
        <button onClick={runMap}>Run</button>
        <button onClick={() => { setChips([]); setOutput(null); }}>Clear</button>
      </div>

      <div style={{ display: "grid", gridTemplateColumns: "repeat(auto-fill, minmax(100px, 1fr))", gap: 8, marginBottom: 16 }}>
        {chips.map(chip => (
          <div key={chip.id} style={{ border: "1px solid #eee", borderRadius: 8, padding: "10px 8px", textAlign: "center" }}>
            <div style={{ fontSize: 12, color: "gray" }}>Input: {chip.id}</div>
            <div style={{ fontSize: 14, fontWeight: 500, minHeight: 20 }}>{chip.value}</div>
            <span style={{
              fontSize: 11, padding: "2px 6px", borderRadius: 99, display: "inline-block",
              background: statusBg[chip.status], color: statusColor[chip.status]
            }}>
              {chip.status}
            </span>
          </div>
        ))}
      </div>

      {output && (
        <div style={{ padding: 12, borderRadius: 8, background: "#f5f5f5", fontSize: 14 }}>
          {JSON.stringify(output)}
        </div>
      )}
    </div>
  );
}
