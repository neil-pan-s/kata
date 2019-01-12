package demo.org.ichanging.fragment;

import android.content.Intent;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by ChangingP on 2016/3/23.
 */
public class BookContent {

    public static class Book {
        public Integer id;
        public String title;
        public String desc;

        public Book(Integer id, String title, String desc) {
            this.id = id;
            this.title = title;
            this.desc = desc;
        }

        @Override
        public String toString() {
            return title;
        }
    }

    public static List<Book> Items = new ArrayList<Book>();
    public static Map<Integer,Book> Item_Map = new HashMap<Integer,Book>();

    static
    {
        addItem(new Book(1,"Harry Potter 1","J. K. Rowling"));
        addItem(new Book(2,"Harry Potter 2","J. K. Rowling"));
        addItem(new Book(3,"Harry Potter 3","J. K. Rowling"));
    }

    private static void addItem(Book book)
    {
        Items.add(book);
        Item_Map.put(book.id,book);
    }
}
