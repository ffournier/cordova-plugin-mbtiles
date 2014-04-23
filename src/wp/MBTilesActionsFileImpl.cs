using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.IsolatedStorage;
using WPCordovaClassLib.Cordova.JSON;
using MBTilesPlugin;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

/// <summary>
/// the namespace of MBTilesPlugin </summary>
namespace MBTilesPlugin
{
    /// <summary>
    /// class MBTilesActionsFileImpl</summary>
    class MBTilesActionsFileImpl : MBTilesActionsGenImpl
    {
        
        private string mapDirectory = null;

        public MBTilesActionsFileImpl()
            : base()
        {
            directory = Path.Combine(Windows.Storage.ApplicationData.Current.LocalFolder.Path, "maps//");
        }

        public override void open(string name)
	    {
            close();
            try
            {
                using (IsolatedStorageFile isoFile = IsolatedStorageFile.GetUserStoreForApplication())
                {
			        /// test if directory exist
                    string path = getDirectory(); 
                    if (isoFile.DirectoryExists(path))
                    {
                        mapDirectory = path;
                    }
                }
            } 
            catch(Exception) {
                // Add log
            }
        }

        public override bool isOpen()
	    {
		    return (this.mapDirectory != null);
	    }

	    public override void close()
	    {
		  this.mapDirectory = null;
	    }

        /// <summary>
        /// get metadata in JObject format</summary>
  	/// <returns>
	/// the JObject repsenting the metadata</returns>
        private JObject getMetadataObject()
        {
            JObject obj = new JObject(); 
            string filePath = mapDirectory + "\\metadata.json";
            string text = readText(filePath);
	        if (text != null) {
		       
		        metadata[] list = JsonHelper.Deserialize<metadata[]>(text);
			    
			    foreach (metadata data in list)
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
            try
            {
                List<int> zoomLevels = getZoomLevels();

                if (zoomLevels.Count > 0)
                {
                    result = new minzoom_output(zoomLevels.ElementAt(0));
                }
            }
            catch (Exception)
            {
                // Add log
            }

            return result;
		}

        public override maxzoom_output getMaxZoom()
	    {
            maxzoom_output result = null;
            try
            {
                List<int> zoomLevels = getZoomLevels();

                if (zoomLevels.Count > 0)
                {
                    result = new maxzoom_output(zoomLevels.ElementAt(zoomLevels.Count - 1));
                }
            }
            catch (Exception)
            {
                // Add log
            }
            return result;
		}

        public override tiles_output getTile(int zoomLevel, int column, int row)
	    {
            tiles_output result = null;
            int currentZoomLevel = zoomLevel;
            try
		    {
			    maxzoom_output max = getMaxZoom();
                if (max != null)
                {
                    int maxZoom = max.value;

                    if (zoomLevel > maxZoom)
                    {
                        currentZoomLevel = maxZoom;
                    }
                }
                
		    }
		    catch (Exception)
		    {
			}

            try
		    {
                JObject metadata = getMetadataObject();
                if (metadata != null)
                {
                    string name = (string)metadata.GetValue(ConstantMbTilePlugin.KEY_NAME);
                    string version = (string)metadata.GetValue(ConstantMbTilePlugin.KEY_VERSION);
                    string format = (string)metadata.GetValue(ConstantMbTilePlugin.KEY_FORMAT);
		            if (name != null && version != null && format != null)
                    {
			            /// get path of tiles
			            string tileFile = this.mapDirectory + "\\" + version + "\\" + name + "\\" +
			                                    currentZoomLevel.ToString() + "\\" + column.ToString() + "\\" + row.ToString() + "." + format;
			            /// encode raw
			            string raw = readText(tileFile);
			            if (raw != null) {
                            string data = ConstantMbTilePlugin.Base64Encode(raw);
				            result = new tiles_output(data);
			            }
		            }
                }
            }
            catch(Exception)
            {

            }

            return result;

		}


        /// <summary>
        /// read raw of given file</summary>
  	/// <returns>
	/// return the raw of file in string</returns>
	/// <param name="filePath"> the path of file</param>
        private string readText(string filePath) 
        {
            string text = null;
            try
            {
                using (IsolatedStorageFile isoFile = IsolatedStorageFile.GetUserStoreForApplication())
                {
                    if (isoFile.FileExists(filePath))
                    {
                        // read text
                        using (IsolatedStorageFileStream reader = isoFile.OpenFile(filePath, FileMode.Open, FileAccess.Read))
                        {
                            var buffer = new byte[(int)reader.Length];

                            reader.Seek(0, SeekOrigin.Begin);
                            reader.Read(buffer, 0, buffer.Length);

                            Encoding encoding = Encoding.GetEncoding("UTF-8");
                            text = encoding.GetString(buffer, 0, buffer.Length);
                        }
                    }
                }
            } 
            catch(Exception)
            {

            }
            return text;
        }

        /// <summary>
        /// get all zoom level</summary>
  	    /// <returns>
	    /// return a list of zoom level present</returns>
	    private List<int> getZoomLevels()
        {
            JObject metadata = getMetadataObject();
            List<int> zoomLevels = new List<int>();
            if (metadata != null)
            {
                try
                {
                    string name = (string)metadata.GetValue(ConstantMbTilePlugin.KEY_NAME);
                    string version = (string)metadata.GetValue(ConstantMbTilePlugin.KEY_VERSION);
                    if (name != null && version != null)
                    {

                        string dirPath = this.mapDirectory + "\\" + version + "\\" + name;
                        using (IsolatedStorageFile isoFile = IsolatedStorageFile.GetUserStoreForApplication())
                        {
                            // create the file if not exists
                            if (isoFile.DirectoryExists(dirPath))
                            {
                                foreach (string filePath in isoFile.GetFileNames(dirPath))
                                {
                                    zoomLevels.Add(int.Parse(filePath));
                                }
                            }
                        }
                    }
                }
                catch (Exception)
                {
                    // Add log
                }
			   
            }   
		    return zoomLevels;
        }

        public override string executeStatement(String query, List<object> param)
        {
            string result = "";
            // not implemented
            return result;
        }

        public override directory_working_output getDirectoryWorking()
	    {
		    return new directory_working_output(getDirectory());
	    }

    }
}
