package com.makina.offline.mbtiles;

import org.json.JSONException;
import org.json.JSONObject;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.SyncStateContract.Columns;
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
	
	@Override
	public void open(String path)
	{
		this.db = SQLiteDatabase.openDatabase(path, null, SQLiteDatabase.NO_LOCALIZED_COLLATORS | SQLiteDatabase.OPEN_READONLY);
		
		Log.d(getClass().getName(), "openDatabase : " + this.db.getPath());
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
			this.db = null;
		}
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
	
	@Override
	public JSONObject getExecuteStatment(String query, String... params) {
		JSONObject result = new JSONObject();
		if (query != null && query.length() > 0) {
			Cursor cursor = db.rawQuery(query, params);
			if (cursor != null) {
				while (cursor.moveToNext()) {
					for (String name : cursor.getColumnNames()) {
						if (name != null ) {
							int columnIndex = cursor.getColumnIndex(name);
							if (columnIndex >= 0) {
								int type = cursor.getType(columnIndex);
								Object value ;
								switch (type) {
								case Cursor.FIELD_TYPE_BLOB:
									value = cursor.getBlob(columnIndex);
									break;
								case Cursor.FIELD_TYPE_FLOAT:
									value = cursor.getDouble(columnIndex);
									break;
								case Cursor.FIELD_TYPE_INTEGER:
									value = cursor.getInt(columnIndex);
									break;
								case Cursor.FIELD_TYPE_STRING:
									value = cursor.getString(columnIndex);
									break;
								case Cursor.FIELD_TYPE_NULL:
								default:
									value = null;
									break;
								}
								try {
									result.put(name, value);
								} catch (JSONException e) {
									Log.w(getClass().getName(), e.getMessage());
								}
							}
						}
					}
				}
			}
		}
		return result;
	}
}
