// Implement a function `promisify` that takes a 
// callback-based function and returns a Promise-based version.


function promisify(fn) {
    //whatever args we are getting from calling this function here it will id value
    //in the calllback function you basically call the fucntion and resolve the promise with its result
    return function (...args){
             return new Promise((resolve) => {
                 fn(...args, (res) => {
                     resolve(res);
                 });
        
    });
        
    }
    }

// example:
function getNameById(id, callback) {
    setTimeout(() => callback("User" + id), 200);
}


//
const getNameByIdPromise = promisify(getNameById);

// now you can use it like:
// await getNameByIdPromise(1); must return promise
// but const getNameByIdPromise = promisify(getNameById); then it mean
const name = await getNameByIdPromise(1);
console.log(name); // "User1"
