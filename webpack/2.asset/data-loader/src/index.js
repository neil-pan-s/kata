import Data from './data.xml';

function component() {
    var element = document.createElement('div');

    element.innerHTML = 'Hello Webpack';

    console.log(JSON.stringify(Data));

    return element;
}

document.body.appendChild(component());