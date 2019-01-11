var webpack = require('webpack');
var path = require('path');

module.exports = function() {
    return {
        entry: {
            main: './src/index.js' //Notice that we do not have an explicit vendor entry here
        },
        output: {
            filename: '[name].js',
            path: path.resolve(__dirname, 'dist')
        },
        module: {
            rules: [{
                test: /\.js$/,
                exclude: /(node_modules)/,
                use: [{
                    loader: 'babel-loader',
                    options: {
                        presets: [
                            ['es2015', { modules: false }]
                        ],
                        plugins: [
                            'syntax-async-functions',
                            'syntax-dynamic-import',
                            'transform-async-to-generator',
                            'transform-regenerator',
                            'transform-runtime'
                        ]
                    }
                }]
            }]
        }
    };
}