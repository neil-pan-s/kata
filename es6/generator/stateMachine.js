var clock = function*() {
    while (true) {
        console.log('Tick!');
        yield;
        console.log('Tock!');
        yield;
    }
};

var ite = clock();
ite.next();
ite.next();
ite.next();
ite.next();
ite.next();