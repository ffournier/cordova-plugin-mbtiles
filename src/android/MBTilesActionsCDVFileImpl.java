package com.makina.offline.mbtiles;

import android.content.Context;

/**
 * {@link IMBTilesActions} SQLite implementation.
 * 
 * @author <a href="mailto:sebastien.grimault@makina-corpus.com">S. Grimault</a>
 */
public class MBTilesActionsCDVFileImpl extends MBTilesActionsGenDatabaseImpl
{
	
	public MBTilesActionsCDVFileImpl(Context context, String url) {
		super(context);
		if (url != null && url.length() > 0) {
	 		if (FileUtils.checkExternalStorageState()) {
				mDirectory = "cdvfile://localhost/persistent/tiles/";
			}
		} else {
			mDirectory = url;
		}
	}
}
