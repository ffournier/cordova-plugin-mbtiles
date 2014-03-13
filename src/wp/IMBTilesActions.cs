using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

namespace MBTilesPlugin
{
    
    public static class ConstantMbTilePlugin {
        public static string KEY_NAME = "name";
        public static string KEY_VERSION = "version";
        public static string KEY_FORMAT = "format";
        public static string KEY_MIN_ZOOM = "min_zoom";
        public static string KEY_MAX_ZOOM = "max_zoom";
        public static string KEY_TILE_DATA = "tile_data";
        
        public static string Base64Encode(string plainText)
        {
            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(plainText);
            return System.Convert.ToBase64String(plainTextBytes);
        }

        public static string Base64EncodeByte(byte[] plainTextBytes)
        {
            return System.Convert.ToBase64String(plainTextBytes);
        }
    }

    interface IMBTilesActions
    {
    
        /**
	     * Tries to open MBTiles resource
	     * @param path absolute path to the given resource
	     */
	    void open(string path);
	
	    /**
	     * Returns <code>true</code> if the given MBTiles resource is still opened and used.
	     * @return <code>true</code> if the given MBTiles resource is still opened and used.
	     */
	    bool isOpen();
	
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
        metadata_output getMetadata();
	
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
        minzoom_output getMinZoom();
	
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
        maxzoom_output getMaxZoom();
	
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
        tiles_output getTile(int zoomLevel, int column, int row);

    }
}
