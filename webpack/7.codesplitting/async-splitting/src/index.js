//method 1
async function asyncComponent() {
    const _ = await
    import ('lodash');

    var element = document.createElement('div');

    // Lodash, now imported by this script
    element.innerHTML = _.join(['Hello', 'AsyncComponent'], ' ');
    element.classList.add('hello');
    return element;
}

asyncComponent().then(element => document.body.appendChild(element));

//method 2
function component() {

    //在使用 import() 时，该路径必须包含路径信息或完整的静态路径
    import ('lodash').then(function(_) {
        var element = document.createElement('div');

        // Lodash, now imported by this script
        element.innerHTML = _.join(['Hello', 'Component'], ' ');
        element.classList.add('hello');

        document.body.appendChild(element);

    }).catch(function(err) {
        console.log('Failed to load lodash', err);
    });
}

component();