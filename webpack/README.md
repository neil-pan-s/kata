
# Webpack

## install 
  npm install -g webpack

## init package.json
  npm init -y
  
# loader

## 加载样式
  npm install style-loader css-loader

## 加载图片
  npm install file-loader

## 加载数据

webpack可以加载的有用资源还有数据，如 JSON 文件，CSV、TSV 和 XML。类似于 NodeJS，JSON 支持实际上是内置的，也就是说 import Data from './data.json' 默认将正常运行。要导入 CSV、TSV 和 XML，你可以使用 csv-loader 和 xml-loader。让我们处理这三类文件：

  npm install csv-loader xml-loader

import 这四种类型的数据(JSON, CSV, TSV, XML)中的任何一种，所导入的 Data 变量将包含可直接使用的已解析 JSON.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<note>
  <to>Mary</to>
  <from>John</from>
  <heading>Reminder</heading>
  <body>Call Cindy on Tuesday</body>
</note>
```  
import xml as json:

```json
{
    "note": {
        "to": ["Mary"],
        "from": ["John"],
        "heading": ["Reminder"],
        "body": ["Call Cindy on Tuesday"]
    }
}
```

## webpack-dev-server

webpack-dev-server 为你提供了一个服务器和实时重载（live reloading） 功能。

首先从 npm 安装 webpack-dev-server：
  npm install --save-dev webpack-dev-server

安装完成之后，你应该可以使用 webpack-dev-server 了，方式如下：
  webpack-dev-server --open


## 生产环境构建 

  webpack -p  

(也可以运行 webpack --optimize-minimize --define process.env.NODE_ENV="production")
它会执行如下步骤：
使用 UglifyJsPlugin 进行 JS 文件压缩
运行LoaderOptionsPlugin，查看其文档
设置 NodeJS 环境变量，触发某些 package 包，以不同的方式进行编译。

## Tree shaking
Tree shaking 是一个术语，通常用来描述移除 JavaScript 上下文中无用代码这个过程，或者更准确的说是按需引用代码，它依赖于 ES2015 模块系统中 import/export 的静态结构特性。这个术语和概念实际上是兴起于 ES2015 模块打包工具 rollup。

webpack 2 原生支持 ES6 模块 (别名 harmony modules) ，并能检测出未使用的模块输出。

## 使用Babel 
  npm install --save-dev babel-plugin-transform-async-to-generator babel-plugin-transform-regenerator babel-plugin-transform-runtime babel-plugin-syntax-async-functions

## 使用 async/await
  npm install --save-dev babel-plugin-transform-async-to-generator babel-plugin-transform-regenerator babel-plugin-transform-runtime babel-plugin-syntax-async-functions