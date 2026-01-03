const t0 = performance.now();

for(var i = 0 ; i < 10000 ; ++i){
    console.log(i)
}

const t1 = performance.now();
console.log(`\n Time taken by JS : ${(t1 - t0)} ms.`);
