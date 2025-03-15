firstPromise = new Promise((resolve) => {
    resolve("First promise.")
});
secondPromise = new Promise((resolve) => {
    resolve("Second promise.")
});
console.log("First console.")
setTimeout(() => console.log("First setTimeout."), 10000);
setTimeout(() => console.log("Second setTimeout."));
firstPromise.then(response => console.log(response));
secondPromise.then(response => console.log(response));