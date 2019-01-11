var path = require('path');
var ExtractTextPlugin = require('extract-text-webpack-plugin');

//css 内容独立打包为 common.css
module.exports = {
    entry: './src/index.js',
    output: {
        filename: 'bundle.js',
        path: path.resolve(__dirname, 'dist')
    },
    module: {
        rules: [{
            test: /\.css$/,
            // use: [
            //     'style-loader',
            //     'css-loader'
            // ]
            use: ExtractTextPlugin.extract({
                use: 'css-loader'
            })
        }]
    },
    plugins: [
        new ExtractTextPlugin('common.css'),
    ]
};