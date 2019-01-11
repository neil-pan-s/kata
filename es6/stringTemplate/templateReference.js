
let expression = "return " + "` hello ${name}`";
let say = new Function('name', expression);
console.log(say('fish'));

