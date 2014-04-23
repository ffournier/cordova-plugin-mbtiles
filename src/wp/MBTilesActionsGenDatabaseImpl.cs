using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MBTilesPlugin;
using SQLite;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using WPCordovaClassLib.Cordova.JSON;

/// <summary>
/// the namespace of MBTilesPlugin </summary>
namespace MBTilesPlugin
{

    /// <summary>
    /// class MBTilesActionsDatabaseImpl</summary>
    class MBTilesActionsGenDatabaseImpl : MBTilesActionsGenImpl
    {

        private Database db = null;

        public MBTilesActionsGenDatabaseImpl()
            : base()
        {
        }

        public override void open(string name)
	    {
		    close();
            if (name != null) {
		        try
                {
                    string path = Path.Combine(getDirectory(), name);
                    db = new Database(path);
                }
                catch (SQLiteException)
                {
                    db = null;
                }
            }
	    }

        public override bool isOpen()
	    {
            return (this.db != null);
	    }

        public override void close()
	    {
		    if (isOpen())
		    {
                this.db.Close();
			    
		    }
		    this.db = null;
	    }

        /// <summary>
        /// get metadata in JObject format</summary>
  	    /// <returns>
	    /// the JObject repsenting the metadata</returns>
        public JObject getMetadataObject()
	    {
            JObject obj = new JObject();
            List<metadata> list = db.Query<metadata>("SELECT * FROM metadata");

            if (list != null)
            {
                foreach(metadata data in list)
                {
                    obj.Add(data.name, data.value);
                }
            }
            return obj;
	    }

        public override string getMetadata()
        {
            JObject obj = getMetadataObject();
            return obj.ToString(); ;
        }

        public override minzoom_output getMinZoom()
	    {
            minzoom_output result = null;
            tiles zoom_min = db.Query<tiles>("SELECT * FROM tiles ORDER BY zoom_level ASC LIMIT 1").FirstOrDefault();
            if (zoom_min != null)
            {
                result = new minzoom_output(zoom_min.zoom_level);
            }
            return result;
		}

        public override maxzoom_output getMaxZoom()
	    {
            maxzoom_output result = null;
            tiles zoom_max = db.Query<tiles>("SELECT * FROM tiles ORDER BY zoom_level DESC LIMIT 1").FirstOrDefault();
            if (zoom_max != null)
            {
                result = new maxzoom_output(zoom_max.zoom_level); 
            }
            return result;
		}

        public override tiles_output getTile(int zoomLevel, int column, int row)
	    {
            tiles_output result = null;

            int currentZoomLevel = zoomLevel;
            try
		    {
                maxzoom_output value = getMaxZoom();
                int maxZoom = value.value;

			    if (zoomLevel > maxZoom)
			    {
				    currentZoomLevel = maxZoom;
			    }
		    }
		    catch (Exception)
		    {
			}

            
            tiles til = db.Query<tiles>("SELECT * FROM tiles WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?", currentZoomLevel, column, row).FirstOrDefault();

            if (til != null)
            {
                string data = ConstantMbTilePlugin.Base64EncodeByte(til.tile_data);
                result = new tiles_output(data);
            }
            return result;
		}

        public override string executeStatement(String query, List<object> param)
        {
            string result = "";
            if (query != null && query.Length > 0)
            {
                JArray array = new JArray();
                if (param != null)
                {
                    array = db.execute(query, param.ToArray());
                }
                else
                {
                    array = db.execute(query, null);
                }
                JObject obj = new JObject();
                obj.Add(ConstantMbTilePlugin.KEY_EXECUTE_STATEMENT, array);
                result = obj.ToString();
            }
            return result;
        }

        public override directory_working_output getDirectoryWorking()
	    {
		    return new directory_working_output(getDirectory());
	    }
    }
}
