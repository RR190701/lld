
function createQueue(concurrency) {
    let running = 0;
    const waiting = [];

    function drain() {
        while(running < concurrency && waiting.length > 0) {
            const { task, resolve, reject } = waiting.shift();
            
            running++;
            task()
                .then(resolve)
                .catch(reject)
                .finally(() => {
                    running--;
                    drain();
                });
        }
    }

    function add(task) {
        return new Promise((resolve, reject) => {
            waiting.push({ task, resolve, reject });
            drain();
        });
    }

    return { add };
}


// helper
const delay = (ms, label) => new Promise(res => 
    setTimeout(() => res(label), ms)
);

const start = Date.now();
const log = (msg) => console.log(`${msg} at ${Date.now() - start}ms`);

// --- run it ---
const queue = createQueue(2);

queue.add(() => delay(3000, "t1")).then(v => log(`${v} done`));
queue.add(() => delay(1000, "t2")).then(v => log(`${v} done`));
queue.add(() => delay(2000, "t3")).then(v => log(`${v} done`));
queue.add(() => delay(1000, "t4")).then(v => log(`${v} done`));

// the TC will be O(n^2) because shift function have a hidden cost
// but with a real queue we can make  it to O(n)
