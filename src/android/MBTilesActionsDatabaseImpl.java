package com.makina.offline.mbtiles;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.database.Cursor;
import android.database.CursorWindow;
import android.database.sqlite.SQLiteCursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.util.Base64;
import android.util.Log;

/**
 * {@link IMBTilesActions} SQLite implementation.
 * 
 * @author <a href="mailto:sebastien.grimault@makina-corpus.com">S. Grimault</a>
 */
public class MBTilesActionsDatabaseImpl implements IMBTilesActions
{
	private SQLiteDatabase db = null;
	
	// declaration of static variable
	protected static final int FIELD_TYPE_BLOB = 4;
    protected static final int FIELD_TYPE_FLOAT = 2;
    protected static final int FIELD_TYPE_INTEGER = 1;
    protected static final int FIELD_TYPE_NULL = 0;
    protected static final int FIELD_TYPE_STRING = 3;

	
	@Override
	public void open(String path)
	{
		close();
		try {
			this.db = SQLiteDatabase.openDatabase(path, null, SQLiteDatabase.NO_LOCALIZED_COLLATORS | SQLiteDatabase.OPEN_READONLY);
			Log.d(getClass().getName(), "openDatabase : " + this.db.getPath());
		} catch (SQLiteException e) {
			Log.e(getClass().getName(), "SQLiteException : " + e.getMessage());
			this.db = null;

		}
	}

	@Override
	public boolean isOpen()
	{
		return (this.db != null) && this.db.isOpen();
	}

	@Override
	public void close()
	{
		if (isOpen())
		{
			Log.d(getClass().getName(), "close '" + db.getPath() + "'");
			this.db.close();
		}
		this.db = null;
	}

	@Override
	public JSONObject getMetadata()
	{
		Cursor cursor = db.query("metadata",
				new String[]{"name", "value"},
				null, null, null, null, null);
		
		JSONObject metadata = new JSONObject();
		
		if (cursor.moveToFirst())
		{
			while (!cursor.isAfterLast())
			{
				try
				{
					metadata.put(cursor.getString(cursor.getColumnIndex("name")), cursor.getString(cursor.getColumnIndex("value")));
				}
				catch (JSONException je)
				{
					Log.e(getClass().getName(), je.getMessage(), je);
				}
				
				cursor.moveToNext();
			}
		}
		
		cursor.close();
		
		return metadata;
	}

	@Override
	public JSONObject getMinZoom()
	{
		Cursor cursor = db.rawQuery("SELECT MIN(zoom_level) AS min_zoom FROM tiles", null);
		
		JSONObject minZoom = new JSONObject();
		
		// we should have only one result
		if (cursor.moveToFirst())
		{
			try
			{
				minZoom.put(KEY_MIN_ZOOM, cursor.getInt(cursor.getColumnIndex("min_zoom")));
			}
			catch (JSONException je)
			{
				Log.e(getClass().getName(), je.getMessage(), je);
			}
		}
		
		cursor.close();
		
		return minZoom;
	}

	@Override
	public JSONObject getMaxZoom()
	{
		Cursor cursor = db.rawQuery("SELECT MAX(zoom_level) AS max_zoom FROM tiles", null);
		
		JSONObject maxZoom = new JSONObject();
		
		// we should have only one result
		if (cursor.moveToFirst())
		{
			try
			{
				maxZoom.put(KEY_MAX_ZOOM, cursor.getInt(cursor.getColumnIndex("max_zoom")));
			}
			catch (JSONException je)
			{
				Log.e(getClass().getName(), je.getMessage(), je);
			}
		}
		
		cursor.close();
		
		return maxZoom;
	}

	@Override
	public JSONObject getTile(int zoomLevel, int column, int row)
	{
		Log.d(getClass().getName(), "getTile [" + zoomLevel + ", " + column + ", " + row + "]");
		
		int currentZoomLevel = zoomLevel;
		
		// try to load the last zoom level if zoomLevel is too high
		try
		{
			int maxZoom = getMaxZoom().getInt(KEY_MAX_ZOOM);

			if (zoomLevel > maxZoom)
			{
				currentZoomLevel = maxZoom;
			}
		}
		catch (JSONException je)
		{
			Log.e(getClass().getName(), je.getMessage(), je);
		}
		
		Cursor cursor = db.query("tiles",
				new String[]{"tile_data"},
				"zoom_level = ? AND tile_column = ? AND tile_row = ?",
				new String[]{String.valueOf(currentZoomLevel), String.valueOf(column), String.valueOf(row)},
				null, null, null);
		
		JSONObject tileData = new JSONObject();
		
		// we should have only one result
		if (cursor.moveToFirst())
		{
			try
			{
				tileData.put(KEY_TILE_DATA, Base64.encodeToString(cursor.getBlob(cursor.getColumnIndex("tile_data")), Base64.DEFAULT));
			}
			catch (JSONException je)
			{
				Log.e(getClass().getName(), je.getMessage(), je);
			}
		}
		
		cursor.close();
		
		return tileData;
	}
	
	/**
	 * get type of data in column
	 * @param cursor, the selected cursor
	 * @param index, the column to treat
	 * @return the type of data 
	 */
	private int getType(Cursor cursor, int index) {
		int type = FIELD_TYPE_NULL;
		if (cursor != null) {
			int currentapiVersion = android.os.Build.VERSION.SDK_INT;
			if (currentapiVersion >= android.os.Build.VERSION_CODES.HONEYCOMB){
			    type = cursor.getType(index);
			} else {
				SQLiteCursor sqLiteCursor = (SQLiteCursor) cursor;
		        CursorWindow cursorWindow = sqLiteCursor.getWindow();
		        int pos = cursor.getPosition();
		        if (cursorWindow.isNull(pos, index)) {
		            type = FIELD_TYPE_NULL;
		        } else if (cursorWindow.isLong(pos, index)) {
		            type = FIELD_TYPE_INTEGER;
		        } else if (cursorWindow.isFloat(pos, index)) {
		            type = FIELD_TYPE_FLOAT;
		        } else if (cursorWindow.isString(pos, index)) {
		            type = FIELD_TYPE_STRING;
		        } else if (cursorWindow.isBlob(pos, index)) {
		            type = FIELD_TYPE_BLOB;
		        }
			}
		}
		return type;
	}
	
	@Override
	public JSONObject executeStatment(String query, String... params) {
		JSONObject result = new JSONObject();
		JSONArray rows = new JSONArray();
		if (query != null && query.length() > 0) {
			// run the query
			Cursor cursor = db.rawQuery(query, params);
			if (cursor != null) {
				// loop the row
				while (cursor.moveToNext()) {
					JSONObject row = new JSONObject();
					// loop the column
					for (String name : cursor.getColumnNames()) {
						if (name != null ) {
							int columnIndex = cursor.getColumnIndex(name);
							if (columnIndex >= 0) {
								// get type of data in column
								int type = getType(cursor, columnIndex);
								Object value ;
								// treat the data
								switch (type) {
								case FIELD_TYPE_BLOB:
									value = Base64.encodeToString(cursor.getBlob(columnIndex),Base64.DEFAULT);
									break;
								case FIELD_TYPE_FLOAT:
									value = cursor.getDouble(columnIndex);
									break;
								case FIELD_TYPE_INTEGER:
									value = cursor.getInt(columnIndex);
									break;
								case FIELD_TYPE_STRING:
									value = cursor.getString(columnIndex);
									break;
								case FIELD_TYPE_NULL:
								default:
									value = null;
									break;
								}
								// put in JSONObject
								try {
									row.put(name, value);
								} catch (JSONException e) {
									Log.w(getClass().getName(), e.getMessage());
								}
							}
						}
					}
					// put in JSONArray
					rows.put(row);
				}
				cursor.close();
			}
		}
		// put all rows in JSONObject
		try {
			result.put(KEY_EXECUTE_STATMENT, rows);
		} catch (JSONException e) {
			Log.w(getClass().getName(), e.getMessage());
		}
		return result;
	}

	/**
	 * return the directory of working
	 * @param path : the pah of working
	 * @return <code>JSONObject</code>
	 */
	@Override
	public JSONObject getDirectoryWorking(String path) {
		JSONObject directoryWorking = new JSONObject();
		try {
			directoryWorking.put(KEY_DIRECTORY_WORKING, path);
		} catch (JSONException e) {
			Log.w(getClass().getName(), e.getMessage());
		}
		return directoryWorking;
	}
}
