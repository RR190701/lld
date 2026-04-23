function createRateLimiter(fn, limit, interval) {
    let calls = 0;
    const queue = [];

    setInterval(() => {
        calls = 0;
        while(queue.length > 0 && calls < limit) {
            const { args, resolve } = queue.shift();
            calls++;
            resolve(fn(...args));
        }
    }, interval);

    return function(...args) {
        return new Promise((resolve) => {
            if(calls < limit) {
                calls++;
                resolve(fn(...args));
            } else {
                queue.push({ args, resolve });
            }
        });
    }
}
