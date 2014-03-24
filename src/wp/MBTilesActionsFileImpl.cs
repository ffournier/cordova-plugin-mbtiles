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


namespace MBTilesPlugin
{
    class MBTilesActionsFileImpl : IMBTilesActions
    {
        
        private string mapDirectory = null;
            
	    public void open(string path)
	    {
            mapDirectory = null;
            if (path != null)
            {
                try
                {
                    using (IsolatedStorageFile isoFile = IsolatedStorageFile.GetUserStoreForApplication())
                    {
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
	    }

	    public bool isOpen()
	    {
		    return (this.mapDirectory != null);
	    }

	    public void close()
	    {
		    if (isOpen())
		    {
			    this.mapDirectory = null;
		    }
	    }

        private JObject getMetadataObject()
        {
            string filePath = mapDirectory + "\\metadata.json";
            string text = readText(filePath);
            metadata[] list = JsonHelper.Deserialize<metadata[]>(text);

            JObject obj = new JObject();
            foreach (metadata data in list)
            {
                obj.Add(data.name, data.value);
            }
           
            return obj;
        }

        public string getMetadata()
	    {
            JObject obj = getMetadataObject();
            return obj.ToString(); ;
		}

        public minzoom_output getMinZoom()
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

	    public maxzoom_output getMaxZoom()
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

	    public tiles_output getTile(int zoomLevel, int column, int row)
	    {
            tiles_output result = null;
            int currentZoomLevel = zoomLevel;
            try
		    {
			    maxzoom_output max = getMaxZoom();
                // name, type
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

                    string tileFile = this.mapDirectory + "\\" + version + "\\" + name + "\\" +
                                            currentZoomLevel.ToString() + "\\" + column.ToString() + "\\" + row.ToString() + "." + format;

                    string data = ConstantMbTilePlugin.Base64Encode(readText(tileFile));
                    result = new tiles_output(data);
                }
            }
            catch(Exception)
            {

            }

            return result;

		}


        private string readText(string filePath) {
            string text = "";
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

        public string executeStatment(String query, List<object> param)
        {
            string result = "";
            // not implemented
            return result;
        }

    }
}
