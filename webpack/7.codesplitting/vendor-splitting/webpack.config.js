var webpack = require('webpack');
var path = require('path');

//隐式公共 vendor chunk + Manifest 公共代码
module.exports = function() {
    return {
        entry: {
            main: './src/index.js' //Notice that we do not have an explicit vendor entry here
        },
        output: {
			filename: '[name].js',
            //filename: '[name].[chunkhash].js',
            path: path.resolve(__dirname, 'dist')
        },
        plugins: [
            new webpack.optimize.CommonsChunkPlugin({
                name: 'vendor',
                minChunks: function (module) {
                   // this assumes your vendor imports exist in the node_modules directory
                   return module.context && module.context.indexOf('node_modules') !== -1;
                }
            }),
            //CommonChunksPlugin will now extract all the common modules from vendor and main bundles
            new webpack.optimize.CommonsChunkPlugin({
                name: 'manifest' //But since there are no more common modules between them we end up with just the runtime code included in the manifest file
            })
        ]
    };
}