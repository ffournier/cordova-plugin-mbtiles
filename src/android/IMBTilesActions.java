package com.makina.offline.mbtiles;

import org.json.JSONObject;

/**
 * Describe all MBTiles available actions
 * 
 * @author <a href="mailto:sebastien.grimault@makina-corpus.com">S. Grimault</a>
 */
public interface IMBTilesActions
{
	static final String KEY_NAME = "name";
	static final String KEY_VERSION = "version";
	static final String KEY_FORMAT = "format";
	static final String KEY_MIN_ZOOM = "min_zoom";
	static final String KEY_MAX_ZOOM = "max_zoom";
	static final String KEY_TILE_DATA = "tile_data";
	
	/**
	 * Tries to open MBTiles resource
	 * @param path absolute path to the given resource
	 */
	void open(String path);
	
	/**
	 * Returns <code>true</code> if the given MBTiles resource is still opened and used.
	 * @return <code>true</code> if the given MBTiles resource is still opened and used.
	 */
	boolean isOpen();
	
	/**
	 * Tries to close and freeing up MBTiles resource
	 */
	void close();
	
	/**
	 * Gets all metadata for the given MBTiles resource as <code>JSONObject</code>.
	 * <p>
	 * Five keys are <strong>required</strong> :
	 * </p>
	 * <ul>
	 * <li>name : the plain-english name of the tileset</li>
	 * <li>type : overlay or baselayer</li>
	 * <li>version : the version of the tileset, as a plain number</li>
	 * <li>description : a description of the layer as plain text</li>
	 * <li>format : the image file format of the tile data (png as default format or jpg) 
	 * </ul>
	 * @return the metadata as <code>JSONObject</code>
	 */
	JSONObject getMetadata();
	
	/**
	 * Gets the minimal zoom level as <code>JSONObject</code>.
	 * <p>
	 * One key is <strong>required</strong> :
	 * <p>
	 * <ul>
	 * <li>min_zoom : minimal zoom of the tileset</li>
	 * </ul>
	 * @return the minimal zoom level as <code>JSONObject</code>
	 */
	JSONObject getMinZoom();
	
	/**
	 * Gets the maximum zoom level as <code>JSONObject</code>.
	 * <p>
	 * One key is <strong>required</strong> :
	 * <p>
	 * <ul>
	 * <li>max_zoom : maximum zoom of the tileset</li>
	 * </ul>
	 * @return the maximum zoom level as <code>JSONObject</code>
	 */
	JSONObject getMaxZoom();
	
	/**
	 * Retrieves the tile as <code>JSONObject</code> into a Base64 representation according to given parameters.
	 * <p>
	 * One key is <strong>required</strong> :
	 * <p>
	 * <ul>
	 * <li>tile_data : the tile data into a Base64 representation</li>
	 * </ul>
	 * @param zoomLevel the current zoom level
	 * @param column column index
	 * @param row row index
	 * @return the tile as <code>JSONObject</code>
	 */
	JSONObject getTile(int zoomLevel, int column, int row);
}
