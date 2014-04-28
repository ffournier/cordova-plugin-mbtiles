/*
* Copyright 2013 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef MBTILESPLUGINUTILSNDK_HPP_
#define MBTILESPLUGINUTILSNDK_HPP_

#include <string>

#define ACTION_INIT "init"
#define ACTION_OPEN "open"
#define ACTION_GETMETADATA "get_metadata"
#define ACTION_GETMINZOOM "get_min_zoom"
#define ACTION_GETMAXZOOM "get_max_zoom"
#define ACTION_GETTILE "get_tile"
#define ACTION_EXECUTESTATEMENT "execute_statement"
#define ACTION_GETDIRECTORYWORKING "get_directory_working"
#define ACTION_IS_SDCARD "is_sdcard"

#define KEY_TYPE "type"
#define KEY_TYPEPATH "typepath"
#define KEY_NAME "name"
#define KEY_URL "url"
#define KEY_Z "z"
#define KEY_Y "y"
#define KEY_X "x"
#define KEY_VERSION "version"
#define KEY_FORMAT "format"
#define KEY_MIN_ZOOM "min_zoom"
#define KEY_MAX_ZOOM "max_zoom"
#define KEY_TILE_DATA "tile_data"
#define KEY_QUERY "query"
#define KEY_PARAMS "params"
#define KEY_EXECUTE_STATEMENT "result_execute"
#define KEY_DIRECTORY_WORKING "directory_working"


#define TYPE_DB "db"
#define TYPE_FILE "file"
#define TYPE_UNDEFINED "type undefined"

#define TYPE_PATH_CDVFILE "cdvfile"
#define TYPE_PATH_FULL "fullPath"
#define TYPE_PATH_UNDEFINED "type undefined"


#define PLUGIN_NAME "MBTilePluginJS"
#define PLUGIN_RESULT "result"
#define PLUGIN_OK "ok"
#define PLUGIN_ERROR "error"
#define PLUGIN_NOT_OPEN "not open"
#define PLUGIN_PARSE_ERROR "Cannot parse JSON object"
#define PLUGIN_NO_ACTION "Action not found"
#define PLUGIN_SDCARD "SDCard Present"
#define PLUGIN_NO_SDCARD "SDCard Not Present"

namespace webworks {

class MBTilesPluginUtilsNDK {

	public:
		static bool fileExists(const std::string file);
};

} // namespace webworks

#endif /* MBTILESPLUGINUTILSNDK_HPP_ */
