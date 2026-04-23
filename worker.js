// Implement `mapAsyncLimit` — same as mapLimit but 
// using Promises instead of callbacks.

async function mapAsyncLimit(array, asyncMapFn, limit) {
    let completed = 0;
    let index = 0;
    const result = [];
    
    return new Promise((resolve) => {
        
        function call() {
            
            if(index >= array.length){
              resolve(result);
              return;
            }
            
            let completed = 0;
        const chunck = array.slice(index, limit + index);
        index = index + limit;
        
        for(let i = 0; i < chunck.length; i++){
            asyncMapFn(chunck[i]).then((value) => { 
                completed++;
                result.push(value);
                if(completed == chunck.length){
                    call();
                }
                
            })
            
        }
            
        }
        call();
        
    });
    
    
}

// example:
const results = await mapAsyncLimit(
    [1, 2, 3, 4, 5],
    async (id) => "User" + id,
    2  // limit
);
console.log(results); // ["User1", "User2", "User3", "User4", "User5"]








// --------------------------------------- 2 --------------------------------------------------



// Implement `mapAsync` that maps an array with an async 
// function and returns a Promise with all results.
// No concurrency limit this time — run all at once.

async function mapAsync(array, asyncMapFn) { 
    
    
// map() fires ALL calls immediately, no awaiting between them
// Promise.all then waits for all of them together
const result = [];
let completed = 0;

return new Promise((resolve) => {
    for(let i = 0; i < array.length; i++){
        // this would run all the call one by one and wait for it to complete
        // await asyncMapFn(array[i]).then((value) => result.push(value));
      asyncMapFn(array[i]).then((value) =>{
          completed++;
          result.push(value)
          if(completed == array.length){
              resolve(result);
          }
      });
    }
    
})
    
    
}

// example:
const results = await mapAsync(
    [1, 2, 3],
    async (id) => "User" + id
);
console.log(results); // ["User1", "User2", "User3"]



// ------------------------------------------- 3 -------------------------------------------------

// Implement a `promisePool` that runs async tasks 
// with a concurrency limit but doesn't wait for 
// full chunks — starts next task as soon as 
// ANY slot frees up.

async function promisePool(functions, limit) {
    
    let completed = 0;
    let globalIndex = 0;
    const result = [];
    
    return new Promise(resolve){
        runFunc(){
            
            if(globalIndex == functions.length)
            return;
        
        let index = globalIndex++;
        
        functions[index]().then((value) => {
            result.push(value);
            completed++;
            
        if(completed == fucntions.length){
            resolve(result);
        }
        else{
            runFunc();
        }
        })
        
        
    }
    
    //run limit size workers
    for(let i = 0; i < Math.min(limit, functions.length); i++){
        runFunc();
    }
        
    }
    

}

// example:
// limit = 2
// tasks: [t1(3s), t2(1s), t3(2s), t4(1s)]

// time 0s:   t1 starts, t2 starts
// time 1s:   t2 done → t3 starts immediately (don't wait for t1!)
// time 3s:   t1 done → t4 starts
// time 4s:   t3 done
// time 4s:   t4 done → all done!
