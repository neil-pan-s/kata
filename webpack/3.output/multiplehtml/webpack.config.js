var path = require('path');

module.exports = {
    entry: {
        entry1: './src/entry1.js',
        entry2: './src/entry2.js'
    },
    output: {
        filename: '[name].js',
        path: path.resolve(__dirname, 'dist')
    },
    module: {
        rules: [{
            test: /\.css$/,
            use: [
                'style-loader',
                'css-loader'
            ]
        }]
    }
};