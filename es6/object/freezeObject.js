var constantize = (obj) => {
    Object.freeze(obj);
    Object.keys(obj).forEach(
        (key,value) => {
            if(typeof obj[key] === 'object'){
                constantize( obj[key] );
            }
        }
    );
};

var foo = {
    name : "changing",
    skill:{
        a : "html",
        b: "js",
        c: "css"
    },
    location: ["Shenzhen", "GuangDong", "China"]
};

constantize(foo);

//抛错
//foo.location.push("pax");
//不起作用 但不会抛错
foo.skill.b = "es6";

console.log(foo);