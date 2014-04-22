package com.makina.offline.mbtiles;

import android.content.Context;
import android.os.Environment;

/**
 * {@link IMBTilesActions} SQLite implementation.
 * 
 * @author <a href="mailto:sebastien.grimault@makina-corpus.com">S. Grimault</a>
 */
public class MBTilesActionsDatabaseImpl extends MBTilesActionsGenDatabaseImpl
{
	
	public MBTilesActionsDatabaseImpl(Context context) {
		super(context);
		if (FileUtils.checkExternalStorageState()) {
			mDirectory = Environment.getExternalStorageDirectory().getAbsolutePath() + "/Android/data/" +
							mContext.getPackageName() + "/databases/";
		}
	}
	
}
