

/**
 * @param {(...args) => void} func
 * @returns {(...args) => Promise<any}
 */
// function promisify(func) {
//     // Return a new function that accepts the original arguments
//     return function(...args) {
//         // This new function returns a Promise
//         return new Promise((resolve, reject) => {
//             // Call the original function with all args + our custom callback
//             func(...args, (error, data) => {
//                 if (error) {
//                     reject(error);   // callback got an error → reject
//                 } else {
//                     resolve(data);   // callback got data → resolve
//                 }
//             });
//         });
//     }
// }

function promisify(func) {
    return function(...args) {
        return new Promise((resolve, reject) => {
            // 'this' here refers to whatever object calls promisedFunc
            func.call(this, ...args, (error, data) => {
                if (error) {
                    reject(error);
                } else {
                    resolve(data);
                }
            });
        });
    }
}
