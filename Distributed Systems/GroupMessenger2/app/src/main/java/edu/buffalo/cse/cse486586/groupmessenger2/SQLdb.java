package edu.buffalo.cse.cse486586.groupmessenger2;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by Ankesh N. Bhoi on 02/11/2018.
 * Credits:https://www.youtube.com/watch?v=cp2rL3sAFmI
 */

public class SQLdb extends SQLiteOpenHelper{

    public static final String db_name="kvalpair.db";
    public static final String tbl_name="kvalpair";


    public SQLdb(Context context) {
        super(context,db_name, null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        sqLiteDatabase.execSQL("create table "+tbl_name+" (`key` TEXT PRIMARY KEY,`value` TEXT)");
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {
        sqLiteDatabase.execSQL("DROP TABLE IF EXISTS kvalpairs.db");
        onCreate(sqLiteDatabase);
    }

    public void insert(ContentValues values){
        SQLiteDatabase db = this.getWritableDatabase();
        Object key = values.get("key");
        db.delete(tbl_name,"key="+"'"+key+"'",null);
        final long check = db.insert(tbl_name, null, values);
    }
    public Cursor query_response(String selection) {
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor res = db.rawQuery("select * from "+tbl_name+" WHERE `key`= "+"'"+selection+"'",null);
        //res.moveToFirst();
        int x=res.getCount();
        return res;
    }
}
