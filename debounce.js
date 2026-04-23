function debounce(fn, delay) {
    let timer = null;

    return function(...args) {
        clearTimeout(timer);  // clear previous timer
        timer = setTimeout(() => {
            fn(...args);      // call with latest args
        }, delay);
    }
}
