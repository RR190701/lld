// Implement a function `delay` that returns a Promise 
// which resolves after a given number of milliseconds.

const delay = (ms) => {
    return new Promise((resolve, reject) => {
        // rejecting, ig not handled it will throw unhandled promis rejection
        if(ms > 9000){
            return reject("Rashika broke the code");
        }
        setTimeout(() => {
            //resolve();
            //resolve(undefined);
            
            //resolving with a value will be retured to the function call in await
            resolve("Have a good day");
        }, ms);
    })
    }
//since we saw that we are calling delay with await so we have to return a promise
//now promise have two things (resolve and reject)
//when we call resolve you can catch it in then if called reject then catch it in error

// usage:]
//This doesn't block the code below it
//value from resolve and reject can be ignored like being done below
//then(() => console.log("3 second passed"))
delay(3000).then((value) => console.log("3 second passed", value ))
.catch(() => {
    console.log("call got failed");
})

// with async/await:
//But await the code below it and waits till the promis reolsoves
// await delay(1000); - can be used like this to ignore value
//const value = await delay(10000); only this will cause triggerUncaughtException

//option 1
const value = await delay(10000).catch(() => console.log("Nothing happened"))
//option 2
// async function main() {
//     try {
//         const value = await delay(10000);
//           console.log("1 second passed", value);
//     } catch(err) {
//         console.log("Error", err);
//     }
// }

// main();
