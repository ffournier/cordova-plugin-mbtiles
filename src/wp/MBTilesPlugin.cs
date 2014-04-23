/*
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.IO.IsolatedStorage;
using System.Net;
using System.Runtime.Serialization;
using System.Windows;
using System.Security;
using System.Diagnostics;
using MBTilesPlugin;

/// <summary>
/// the namespace of WPCordovaClassLib.Cordova.Commands </summary>
namespace WPCordovaClassLib.Cordova.Commands
{
    public class MBTilesPlugin : BaseCommand
    {
        private IMBTilesActions mbTilesActions = null;

        public static string ACTION_OPEN_TYPE_DB = "db";
	    public static string ACTION_OPEN_TYPE_FILE = "file";
        public static string ACTION_OPEN_TYPE_CDV = "cdvfile";

        public void init(string options)
        {
            string callbackId;
            options = options.Replace("{}", ""); /// empty objects screw up the Deserializer
            try
            {
                /// name, type
                string[] args = JSON.JsonHelper.Deserialize<string[]>(options);
                /// to test maybe is not a string but a JSONObject
                EntryInit entryInit = JSON.JsonHelper.Deserialize<EntryInit>(args[0]);
                string type = entryInit.type;
                string url = entryInit.url;
                callbackId = args[1];

                if (type != null && type.Equals(ACTION_OPEN_TYPE_DB))
                {
                    //string dbPath = Path.Combine(Windows.Storage.ApplicationData.Current.LocalFolder.Path, name);
                    mbTilesActions = new MBTilesActionsDatabaseImpl();
                }
                else if (type != null && type.Equals(ACTION_OPEN_TYPE_FILE))
                {
                    //string dirPath = Path.Combine(Windows.Storage.ApplicationData.Current.LocalFolder.Path, "maps//" + name);
                    mbTilesActions = new MBTilesActionsFileImpl();
                }
                else if (type != null && type.Equals(ACTION_OPEN_TYPE_CDV))
                {
                    mbTilesActions = new MBTilesActionsCDVFileImpl(url);
                }

                if (mbTilesActions != null)
                {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.OK), callbackId);
                }
                else
                {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.IO_EXCEPTION), callbackId);
                }

            }
            catch (Exception)
            {
                DispatchCommandResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
            }

        }

        public void open(string options)
        {
            string callbackId;
            options = options.Replace("{}", ""); /// empty objects screw up the Deserializer
            try
            {
                /// name, type
                string[] args = JSON.JsonHelper.Deserialize<string[]>(options);
                /// to test maybe is not a string but a JSONObject
                EntryOpen entryOpen = JSON.JsonHelper.Deserialize<EntryOpen>(args[0]);
                string name = entryOpen.name;
                callbackId = args[1];

                if (mbTilesActions != null)
                {
                    mbTilesActions.open(name);
                    if (mbTilesActions.isOpen()) {
                        DispatchCommandResult(new PluginResult(PluginResult.Status.OK), callbackId);
                    }
                    else
                    {
                        DispatchCommandResult(new PluginResult(PluginResult.Status.ERROR), callbackId);
                    }
                }
                else
                {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.ERROR), callbackId);
                }

            }
            catch (Exception)
            {
                DispatchCommandResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
            }

        }

        public void get_metadata(string options)
        {
            /// no options
            string callbackId;
            options = options.Replace("{}", ""); /// empty objects screw up the Deserializer
            try
            {
                string[] args = JSON.JsonHelper.Deserialize<string[]>(options);
                callbackId = args[0];

                if (mbTilesActions != null && mbTilesActions.isOpen())
                {
                    string metadata = mbTilesActions.getMetadata();
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
                    pluginResult.Message = metadata;
                    DispatchCommandResult(pluginResult, callbackId);
                }
                else
                {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.IO_EXCEPTION), callbackId);
                }
            }
            catch (Exception)
            {
                DispatchCommandResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
            }
        }

        public void get_min_zoom(string options)
        {
            /// no options
            string callbackId;
            options = options.Replace("{}", ""); /// empty objects screw up the Deserializer
            try
            {
                string[] args = JSON.JsonHelper.Deserialize<string[]>(options);
                callbackId = args[0];

                if (mbTilesActions != null && mbTilesActions.isOpen())
                {
                    minzoom_output minzoom = mbTilesActions.getMinZoom();
                    DispatchCommandResult(new PluginResult(PluginResult.Status.OK, minzoom), callbackId);
                }
                else
                {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.IO_EXCEPTION), callbackId);
                }

            }
            catch (Exception e)
            {
                DispatchCommandResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
            }
        }

        public void get_max_zoom(string options)
        {
            /// no options

            string callbackId;
            options = options.Replace("{}", ""); /// empty objects screw up the Deserializer
            try
            {
                string[] args = JSON.JsonHelper.Deserialize<string[]>(options);
                callbackId = args[0];

                if (mbTilesActions != null && mbTilesActions.isOpen())
                {
                    maxzoom_output maxzoom = mbTilesActions.getMaxZoom();
                    DispatchCommandResult(new PluginResult(PluginResult.Status.OK, maxzoom), callbackId);
                }
                else
                {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.IO_EXCEPTION), callbackId);
                }
            }
            catch (Exception)
            {
                DispatchCommandResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
             }
        }

        public void get_tile(string options)
        {
            string callbackId;
            options = options.Replace("{}", ""); /// empty objects screw up the Deserializer
            try
            {
                /// z, x, y
                string[] args = JSON.JsonHelper.Deserialize<string[]>(options);
                /// to test maybe is not an integer but a JSONObject
                EntryTile entryTile = JSON.JsonHelper.Deserialize<EntryTile>(args[0]);
                int z = entryTile.z;
                int x = entryTile.x;
                int y = entryTile.y;
                callbackId = args[1];

                if (mbTilesActions != null && mbTilesActions.isOpen())
                {
                    tiles_output tile = mbTilesActions.getTile(z,x,y);
                    DispatchCommandResult(new PluginResult(PluginResult.Status.OK, tile), callbackId);
                }
                else
                {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.IO_EXCEPTION), callbackId);
                }

            }
            catch (Exception)
            {
                DispatchCommandResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
            }
        }

        public void execute_statement(string options)
        {
            string callbackId;
            options = options.Replace("{}", ""); /// empty objects screw up the Deserializer
            try
            {
                /// query params
                string[] args = JSON.JsonHelper.Deserialize<string[]>(options);
                /// to test maybe is not an integer but a JSONObject
                EntryExecuteStatement entryExecute = JSON.JsonHelper.Deserialize<EntryExecuteStatement>(args[0]);
                string query = entryExecute.query;
                /// to test not sure that's work
                List<object> param = entryExecute.param;
                callbackId = args[1];

                if (mbTilesActions != null && mbTilesActions.isOpen())
                {
                    string result = mbTilesActions.executeStatement(query, param);
                    PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
                    pluginResult.Message = result;
                    DispatchCommandResult(pluginResult, callbackId);
                }
                else
                {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.IO_EXCEPTION), callbackId);
                }

            }
            catch (Exception)
            {
                DispatchCommandResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
            }
        }

 	    public void get_directory_working(string options)
        {
            string callbackId;
            options = options.Replace("{}", ""); /// empty objects screw up the Deserializer
            try
            {
                string[] args = JSON.JsonHelper.Deserialize<string[]>(options);
                callbackId = args[0];
		
                if (mbTilesActions != null) {
                     directory_working_output dir = mbTilesActions.getDirectoryWorking();
                    DispatchCommandResult(new PluginResult(PluginResult.Status.OK, dir), callbackId);
                   
                } else {
                    DispatchCommandResult(new PluginResult(PluginResult.Status.ERROR), callbackId);
                }

            }
            catch (Exception)
            {
                DispatchCommandResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));
            }

        }

    }
	
}
