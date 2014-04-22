package com.makina.offline.mbtiles;

import org.apache.cordova.CordovaResourceApi;

import android.content.Context;
import android.net.Uri;

/**
 * {@link IMBTilesActions} SQLite implementation.
 * 
 * @author <a href="mailto:sebastien.grimault@makina-corpus.com">S. Grimault</a>
 */
public class MBTilesActionsCDVFileImpl extends MBTilesActionsGenDatabaseImpl
{
	
	public MBTilesActionsCDVFileImpl(Context context, String url, CordovaResourceApi resourceApi) {
		super(context);
		if (url != null && url.length() > 0) {
	 		if (FileUtils.checkExternalStorageState()) {
	 			url = "cdvfile://localhost/persistent/tiles/";
			}
		}
		
		if (url != null) {
			 Uri fileURL = resourceApi.remapUri(Uri.parse(url));
			 mDirectory = fileURL.getPath();
		}
	}
}
