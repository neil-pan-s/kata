import 'package:flutter/material.dart';

import 'package:hello_world/shopping-list/shopping-list.dart';
import 'package:hello_world/shopping-list/shopping-list-item.dart';

void main() {
  runApp(new MaterialApp(
    title: 'Shopping App',
    home: new ShoppingList(
      products: <Product>[
        new Product(name: 'Eggs'),
        new Product(name: 'Flour'),
        new Product(name: 'Chocolate chips'),
      ],
    ),
  ));
}