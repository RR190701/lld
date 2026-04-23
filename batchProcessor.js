function createBatcher({ batchSize, timeout, onFlush }) {
    let batch = [];
    let timer = null;

    function flush() {
        const toSend = batch;
        batch = [];
        clearTimeout(timer);
        timer = null;
        onFlush(toSend);
    }

    function add(value) {
        batch.push(value);

        // start timer when first item arrives
        if (batch.length === 1) {
            timer = setTimeout(() => flush(), timeout);
        }

        // send immediately if batch is full
        if (batch.length === batchSize) {
            flush();
        }
    }

    return { add };
}

// --- test ---
const delay = (ms) => new Promise(res => setTimeout(res, ms));
const start = Date.now();
const log = (msg) => console.log(`${msg} at ${Date.now() - start}ms`);

const batcher = createBatcher({
    batchSize: 3,
    timeout: 2000,
    onFlush: (batch) => log(`sending: [${batch}]`)
});

// t=0s: fills batch immediately
batcher.add(1);
batcher.add(2);
batcher.add(3); // → sends [1,2,3] immediately

// t=0s: only 2 added, timeout fires at 2s
batcher.add(4);
batcher.add(5);

// t=3s: new batch, fills immediately
setTimeout(() => {
    batcher.add(6);
    batcher.add(7);
    batcher.add(8); // → sends [6,7,8] immediately
}, 3000);
