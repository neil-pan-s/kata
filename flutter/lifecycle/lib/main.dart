import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      //应用名称  
      title: 'Flutter Demo', 
      theme: new ThemeData(
        //蓝色主题  
        primarySwatch: Colors.blue,
      ),
      //应用首页路由  
      home: Scaffold(
        appBar: AppBar(
          // Here we take the value from the MyHomePage object that was created by
          // the App.build method, and use it to set our appbar title.
          title: Text("Flutter Demo"),
        ),
        body: Center(
          // Center is a layout widget. It takes a single child and positions it
          // in the middle of the parent.
          child: Column(
            // Column is also layout widget. It takes a list of children and
            // arranges them vertically. By default, it sizes itself to fit its
            // children horizontally, and tries to be as tall as its parent.
            //
            // Invoke "debug painting" (press "p" in the console, choose the
            // "Toggle Debug Paint" action from the Flutter Inspector in Android
            // Studio, or the "Toggle Debug Paint" command in Visual Studio Code)
            // to see the wireframe for each widget.
            //
            // Column has various properties to control how it sizes itself and
            // how it positions its children. Here we use mainAxisAlignment to
            // center the children vertically; the main axis here is the vertical
            // axis because Columns are vertical (the cross axis would be
            // horizontal).
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[new CounterWidget()],
          ),
        ), // This trailing comma makes auto-formatting nicer for build methods.
      ),
    );
  }
}

class CounterWidget extends StatefulWidget {
  const CounterWidget({
    Key key,
    this.initValue: 0
  });

  final int initValue;

  @override
  _CounterWidgetState createState() => new _CounterWidgetState();
}

class _CounterWidgetState extends State<CounterWidget> {  
  int _counter;

  // 当Widget第一次插入到Widget树时会被调用，对于每一个State对象，Flutter framework只会调用一次该回调，
  // 所以，通常在该回调中做一些一次性的操作，如状态初始化、订阅子树的事件通知等。
  @override
  void initState() {
    super.initState();
    //初始化状态  
    _counter=widget.initValue;
    print("initState");
  }

  /*
   此回调主要是用于构建Widget子树的，会在如下场景被调用：
    在调用initState()之后。
    在调用didUpdateWidget()之后。
    在调用setState()之后。
    在调用didChangeDependencies()之后。
    在State对象从树中一个位置移除后（会调用deactivate）又重新插入到树的其它位置之后。
  */
  @override
  Widget build(BuildContext context) {
    print("build");
    return Center(
      child: FlatButton(
        child: Text('$_counter'),
        //点击后计数器自增  
        onPressed:()=>setState(()=> ++_counter) ,
      ),
    );
  }

  // 在widget重新构建时，Flutter framework会调用Widget.canUpdate来检测Widget树中同一位置的新旧节点，然后决定是否需要更新，如果Widget.canUpdate返回true则会调用此回调。
  // 正如之前所述，Widget.canUpdate会在新旧widget的key和runtimeType同时相等时会返回true，也就是说在在新旧widget的key和runtimeType同时相等时didUpdateWidget()就会被调用。
  @override
  void didUpdateWidget(CounterWidget oldWidget) {
    super.didUpdateWidget(oldWidget);
    print("didUpdateWidget");
  }

  // 当State对象从树中被移除时，会调用此回调
  @override
  void deactivate() {
    super.deactivate();
    print("deactive");
  }

  // 当State对象从树中被永久移除时调用；通常在此回调中释放资源。
  @override
  void dispose() {
    super.dispose();
    print("dispose");
  }

  // 此回调是专门为了开发调试而提供的，在热重载(hot reload)时会被调用，此回调在Release模式下永远不会被调用。
  @override
  void reassemble() {
    super.reassemble();
    print("reassemble");
  }

  // 当State对象的依赖发生变化时会被调用
  @override
  void didChangeDependencies() {
    super.didChangeDependencies();
    print("didChangeDependencies");
  }

}