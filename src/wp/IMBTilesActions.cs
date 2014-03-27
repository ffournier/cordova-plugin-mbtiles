using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

/// <summary>
/// the namespace of MBTilesPlugin </summary>
namespace MBTilesPlugin
{
    /// <summary>
    /// class ConstantMbTilePlugin</summary>
    public static class ConstantMbTilePlugin {

	/// static key
        public static string KEY_NAME = "name";
        public static string KEY_VERSION = "version";
        public static string KEY_FORMAT = "format";
        public static string KEY_MIN_ZOOM = "min_zoom";
        public static string KEY_MAX_ZOOM = "max_zoom";
        public static string KEY_TILE_DATA = "tile_data";
        public static string KEY_QUERY = "query";
        public static string KEY_PARAMS = "params";
        public static string KEY_EXECUTE_STATMENT = "result_execute";
        
	/// <summary>
	/// encode a string to a string encoding in base64 </summary>
	/// <returns>
	/// return a string encoding in base64 </returns> 
	/// <param name="plainText"> the text to encode</param>
	public static string Base64Encode(string plainText)
        {
            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(plainText);
            return System.Convert.ToBase64String(plainTextBytes);
        }

        /// <summary>
	/// encode a byte[] to a string encoding in base64 </summary>
	/// <returns>
	/// return a string encoding in base64 </returns> 
	/// <param name="plainTextBytes"> the bytes to encode</param>
	public static string Base64EncodeByte(byte[] plainTextBytes)
        {
            return System.Convert.ToBase64String(plainTextBytes);
        }
    }

    /// <summary>
    /// interface IMBTilesActions</summary>
    interface IMBTilesActions
    {
    
            /// <summary>
	    /// open file</summary>
	    /// <param name="path"> the path to open</param>
	    void open(string path);
	
	    /// <summary>
	    /// if the given MBTiles resource is still opened and used.</summary>
	    /// <returns>
	    /// if the given MBTiles resource is still opened and used. </returns> 
	    bool isOpen();
	
	    /// <summary>
	    /// Tries to close and freeing up MBTiles resource</summary>
	    void close();
	
	    /// <summary>
	    /// Gets all metadata for the given MBTiles resource as JSONObject.
	    /// Five keys are required :
            /// name : the plain-english name of the tileset
            /// type : overlay or baselayer
            /// version : the version of the tileset, as a plain number
            /// description : a description of the layer as plain text
            /// format : the image file format of the tile data (png as default format or jpg) </summary>
	    /// <returns>
	    /// the metadata as string in JSonFormat</returns>
	    string getMetadata();
	
	    /// <summary>
	    /// Gets the minimal zoom level as JSONObject.
	    /// One Key is required :
            /// min_zoom : minimal zoom of the tileset</summary>
            /// <returns>
	    /// the minimal zoom level as minzoom_output</returns>
	    minzoom_output getMinZoom();
	
	    /// <summary>
	    /// Gets the maximum zoom level as JSONObject.
	    /// One Key is required :
            /// max_zoom : maximum zoom of the tileset</summary>
            /// <returns>
	    /// the maximum zoom level as maxzoom_output</returns>
	    maxzoom_output getMaxZoom();
	
	    /// <summary>
	    /// Retrieves the tile as JSONObject into a Base64 representation according to given parameters.
	    /// One key is required :
            /// tile_data : the tile data into a Base64 representation </summary>
            /// <returns>
	    /// the tile as tiles_output</returns>
  	    /// <param name="zoomLevel"> the current zoom level</param>
	    /// <param name="column"> column index</param>
	    /// <param name="row"> row index</param>
	    tiles_output getTile(int zoomLevel, int column, int row);

            /// <summary>
	    /// Execute query according to given parameters.</summary>
            /// <returns>
	    /// the tile as string in format JSon</returns>
  	    /// <param name="query"> the query to execute</param>
	    /// <param name="param"> the parameters needed to execute query</param>
	    string executeStatment(String query, List<object> param);
    }
}
