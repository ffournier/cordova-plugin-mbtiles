using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SQLite;
using MBTilesPlugin;
using WPCordovaClassLib.Cordova.JSON;

namespace MBTilesPlugin
{

    class MBTilesActionsDatabaseImpl : IMBTilesActions
    {

        private string dbPath = null;
	
	    public void open(string path)
	    {
		    try
            {
                SQLiteConnection db = new SQLiteConnection(path);
                dbPath = path;
            }
            catch (SQLiteException)
            {
                dbPath = null;
            }
	    }

	    public bool isOpen()
	    {
            return (this.dbPath != null);
	    }

	    public void close()
	    {
		    if (isOpen())
		    {
			    this.dbPath = null;
		    }
	    }

        public string getMetadata()
	    {

            string result = "{";
            using (SQLiteConnection db = new SQLiteConnection(dbPath))
            {
                List<metadata> list = db.Query<metadata>("SELECT * FROM metadata");

                if (list != null)
                {
                    foreach(metadata data in list)
                    {
                        result += data.name + " : \"" + data.value + "\"";
                    }
                }
            }
            result += "}";
            return result;
		}

        public minzoom_output getMinZoom()
	    {
            minzoom_output result = null;
            using (SQLiteConnection db = new SQLiteConnection(dbPath))
            {
                tiles zoom_min = db.Query<tiles>("SELECT * FROM tiles ORDER BY zoom_level ASC LIMIT 1").FirstOrDefault();
                if (zoom_min != null)
                {
                   result = new minzoom_output(zoom_min.zoom_level);
                }
               
            }
            return result;
		}

        public maxzoom_output getMaxZoom()
	    {
            maxzoom_output result = null;
            using (SQLiteConnection db = new SQLiteConnection(dbPath))
            {
                tiles zoom_max = db.Query<tiles>("SELECT * FROM tiles ORDER BY zoom_level DESC LIMIT 1").FirstOrDefault();
                if (zoom_max != null)
                {
                    result = new maxzoom_output(zoom_max.zoom_level); 
                }

            }
            return result;
		}

        public tiles_output getTile(int zoomLevel, int column, int row)
	    {
            tiles_output result = null;

            int currentZoomLevel = zoomLevel;
            try
		    {
                maxzoom_output value = getMaxZoom();
                // name, type
                int maxZoom = value.value;

			    if (zoomLevel > maxZoom)
			    {
				    currentZoomLevel = maxZoom;
			    }
		    }
		    catch (Exception)
		    {
			}

            using (SQLiteConnection db = new SQLiteConnection(dbPath))
            {

                tiles til = db.Query<tiles>("SELECT * FROM tiles WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?", currentZoomLevel, column, row).FirstOrDefault();

                // try to load the last zoom level if zoomLevel is too high
                if (til != null)
                {
                    string data = ConstantMbTilePlugin.Base64EncodeByte(til.tile_data);
                    result = new tiles_output(data);
                }

            }
            return result;
		}

    }
}
