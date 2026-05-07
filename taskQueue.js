class AsyncTaskQueue {
    constructor(concurrency) {
        // Initialize the queue with the specified concurrency limit
        this.limit = concurrency
        this.taskQueue = [];
        this.tasks = 0;
    }
    work(){
        if(this.taskQueue.length === 0){
            return;
        }
        
       while(this.tasks < this.limit && this.taskQueue.length > 0){
        const task = this.taskQueue.shift();
        this.tasks++;
        task().then((res) => {
            console.log(res);
            this.tasks--;
            
        })
        .catch((error) =>{
            console.log(error);
            this.tasks--;
        })
        .finally(() => {
            if(this.taskQueue.length > 0){
                this.work();
            }
        });
            
        }

        
        
    }
    
    queue(task) {
        // Add an async task to the queue
        this.taskQueue.push(task);
        if(this.tasks === 0){
            this.work();
        }
    }
}

const queue = new AsyncTaskQueue(2); // Allow up to 2 tasks to run concurrently
// Example async tasks
const task1 = () => new Promise((resolve) => setTimeout(() => resolve("Task 1 done"), 1000));
const task2 = () => new Promise((resolve, reject) => setTimeout(() => reject("Task 2 failed"), 500));
const task3 = () => new Promise((resolve) => setTimeout(() => resolve("Task 3 done"), 200));
// Queue tasks
queue.queue(task1); // Starts immediately
queue.queue(task2); // Starts immediately (concurrency = 2)
queue.queue(task3);
