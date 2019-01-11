
var car = {
	name : 'ford',
	set brand(v){
		this.name = v;
		console.log('set name() call ' + this.name);
	},
	get brand(){
		console.log('get name() call ' + this.name);
		return this.name;
	}
};

car.brand = 'bmw';
console.log(car.brand);

