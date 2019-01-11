import Library from './library';
import './style.css';

function component() {
    var element = document.createElement('div');

    element.innerHTML = 'Hello Webpack';
    element.classList.add('hello');

    return element;
}

document.body.appendChild(component());

if (module.hot) {
    module.hot.accept('./library', function() {
        console.log('Accepting the updated library module!');
        Library.log();
    })
}