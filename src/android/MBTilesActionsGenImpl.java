package com.makina.offline.mbtiles;

import android.content.Context;

/**
 * {@link IMBTilesActions} SQLite implementation.
 * 
 * @author <a href="mailto:sebastien.grimault@makina-corpus.com">S. Grimault</a>
 */
public abstract class MBTilesActionsGenImpl implements IMBTilesActions
{
	protected String mDirectory;
	protected Context mContext;
	
	

	public MBTilesActionsGenImpl(Context context) {
		super();
		this.mContext = context;
		this.mDirectory = null;
	}

	/**
	 * return the Current Directory
	 * @return directory working 
	 */
	protected String getDirectory() {
		return mDirectory;
	}
	
}
