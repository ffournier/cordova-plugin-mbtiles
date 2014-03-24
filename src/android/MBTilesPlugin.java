package com.makina.offline.mbtiles;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;

import android.os.Environment;
import android.util.Log;
/**
 * <code>MBTilesPlugin</code> Cordova plugin.
 * <p>
 * Manage MBTiles format as SQLite database or as filesystem.
 * 
 * @author <a href="mailto:sebastien.grimault@makina-corpus.com">S. Grimault</a>
 */
public class MBTilesPlugin extends CordovaPlugin
{
	public static final String ACTION_OPEN = "open";
	public static final String ACTION_OPEN_TYPE_DB = "db";
	public static final String ACTION_OPEN_TYPE_FILE = "file";
	public static final String ACTION_GET_METADATA = "get_metadata";
	public static final String ACTION_GET_MIN_ZOOM = "get_min_zoom";
	public static final String ACTION_GET_MAX_ZOOM = "get_max_zoom";
	public static final String ACTION_GET_TILE = "get_tile";
	public static final String ACTION_EXECUTE_STATMENT = "execute_statment";
	
	private IMBTilesActions mbTilesActions = null;
	
	/*
	 * (non-Javadoc)
	 * @see org.apache.cordova.api.Plugin#execute(java.lang.String, org.json.JSONArray, java.lang.String)
	 */
	@Override
	 public boolean execute(String action, JSONArray data, CallbackContext callbackContext) throws JSONException {
		Log.i(getClass().getName(), "execute Tiles");
		
		final JSONArray dataFinal = data;
		final String actionFinal = action;
		final CallbackContext callbackContextFinal = callbackContext;
		
		cordova.getThreadPool().execute(new Runnable() {
            public void run() {
		
	            PluginResult result = null;
				try
				{
					if (actionFinal.equals(ACTION_OPEN))
					{
						result = actionOpen(dataFinal);
					}
					
					if (actionFinal.equals(ACTION_GET_METADATA))
					{
						result = actionGetMetadata(dataFinal);
					}
					
					if (actionFinal.equals(ACTION_GET_MIN_ZOOM))
					{
						result = actionGetMinZoom(dataFinal);
					}
					
					if (actionFinal.equals(ACTION_GET_MAX_ZOOM))
					{
						result = actionGetMaxZoom(dataFinal);
					}
					
					if (actionFinal.equals(ACTION_GET_TILE))
					{
						Log.i(getClass().getName(), "get Tiles");
						result = actionGetTile(dataFinal);
					}
					
					if (actionFinal.equals(ACTION_EXECUTE_STATMENT))
					{
						Log.i(getClass().getName(), "execute statment");
						result = actionExecuteStatment(dataFinal);
					}
					
					if (result == null)
					{
						result = new PluginResult(PluginResult.Status.INVALID_ACTION);
					}
					
					callbackContextFinal.sendPluginResult(result);
				}
				catch (JSONException je)
				{
					callbackContextFinal.sendPluginResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
				}
			}
        });
		return true;
	}
	
	@Override
	public void onDestroy()
	{
		if ((mbTilesActions != null) && mbTilesActions.isOpen())
		{
			mbTilesActions.close();
		}
		
		super.onDestroy();
	}

	private PluginResult actionOpen(JSONArray data) throws JSONException
	{
		PluginResult result = null;
		
		String type = data.getJSONObject(0).getString("type");
		
		if (type.equals(ACTION_OPEN_TYPE_DB))
		{
			mbTilesActions = new MBTilesActionsDatabaseImpl();
			
			if (FileUtils.checkExternalStorageState())
			{
				mbTilesActions.open(Environment.getExternalStorageDirectory().getAbsolutePath() + "/Android/data/" + this.cordova.getActivity().getPackageName() + "/databases/" + data.getJSONObject(0).getString("name"));
			}
			
		}
		
		if (type.equals(ACTION_OPEN_TYPE_FILE))
		{
			mbTilesActions = new MBTilesActionsFileImpl();
			
			if (FileUtils.checkExternalStorageState())
			{
				mbTilesActions.open(Environment.getExternalStorageDirectory().getAbsolutePath() + "/Android/data/" + this.cordova.getActivity().getPackageName() + "/maps/" + data.getJSONObject(0).getString("name"));
			}
		}
		
		if ((mbTilesActions != null) && mbTilesActions.isOpen())
		{
			result = new PluginResult(PluginResult.Status.OK);
		}
		else
		{
			result = new PluginResult(PluginResult.Status.IO_EXCEPTION);
		}
		
		return result;
	}
	
	private PluginResult actionGetMetadata(JSONArray data) throws JSONException
	{
		PluginResult result = null;
		
		if ((mbTilesActions != null) && mbTilesActions.isOpen())
		{
			result = new PluginResult(PluginResult.Status.OK, mbTilesActions.getMetadata());
		}
		else
		{
			result = new PluginResult(PluginResult.Status.IO_EXCEPTION);
		}
		
		return result;
	}
	
	private PluginResult actionGetMinZoom(JSONArray data) throws JSONException
	{
		PluginResult result = null;
		
		if ((mbTilesActions != null) && mbTilesActions.isOpen())
		{
			result = new PluginResult(PluginResult.Status.OK, mbTilesActions.getMinZoom());
		}
		else
		{
			result = new PluginResult(PluginResult.Status.IO_EXCEPTION);
		}
		
		return result;
	}
	
	private PluginResult actionGetMaxZoom(JSONArray data) throws JSONException
	{
		PluginResult result = null;
		
		if ((mbTilesActions != null) && mbTilesActions.isOpen())
		{
			result = new PluginResult(PluginResult.Status.OK, mbTilesActions.getMaxZoom());
		}
		else
		{
			result = new PluginResult(PluginResult.Status.IO_EXCEPTION);
		}
		
		return result;
	}
	
	private PluginResult actionGetTile(JSONArray data) throws JSONException
	{
		PluginResult result = null;
		
		Log.i(getClass().getName(), "actionGetTile Tiles");
		if ((mbTilesActions != null) && mbTilesActions.isOpen())
		{
			Log.i(getClass().getName(), "isOpen Tiles");
			result = new PluginResult(PluginResult.Status.OK, mbTilesActions.getTile(data.getJSONObject(0).getInt("z"), data.getJSONObject(0).getInt("x"), data.getJSONObject(0).getInt("y")));
		}
		else
		{
			Log.i(getClass().getName(), "isOpen Error Tiles");
			result = new PluginResult(PluginResult.Status.IO_EXCEPTION);
		}
		
		return result;
	}
	
	private PluginResult actionExecuteStatment(JSONArray data) throws JSONException
	{
		PluginResult result = null;
		
		Log.i(getClass().getName(), "actionExecuteStatment");
		
		if ((mbTilesActions != null) && mbTilesActions.isOpen())
		{
			Log.i(getClass().getName(), "isOpen Execute Statment");
				
			String query= data.getJSONObject(0).getString("query");
			
			JSONArray jparams = (data.getJSONObject(0).length() < 3) ? null : data.getJSONObject(0).getJSONArray("params"));

			String[] params = null;

			if (jparams != null) {
				params = new String[jparams.length()];

				for (int j = 0; j < jparams.length(); j++) {
					if (jparams.isNull(j))
						params[j] = "";
					else
						params[j] = jparams.getString(j);
				}
			}
			
			result = new PluginResult(PluginResult.Status.OK,  mbTilesActions.getExecuteStatment(query, params);
		}
		else
		{
			Log.i(getClass().getName(), "isOpen Error Execute Statment");
			result = new PluginResult(PluginResult.Status.IO_EXCEPTION);
		}
		
		return result;
	}
}

