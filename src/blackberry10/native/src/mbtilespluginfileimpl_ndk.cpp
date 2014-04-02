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

#include <string>
#include <json/reader.h>
#include <json/writer.h>
#include "mbtilespluginfileimpl_ndk.hpp"
#include "mbtilespluginaction_ndk.hpp"
#include "mbtilesplugin_js.hpp"

namespace webworks {

	MBTilesPluginFileImplNDK::MBTilesPluginFileImplNDK(MBTilesPluginJS *parent)
	: MBTilesPluginActionNDK(parent)
	{
	}

	MBTilesPluginFileImplNDK::~MBTilesPluginFileImplNDK()
	{
	}

	// The extension methods are defined here
	Json::Value MBTilesPluginFileImplNDK::open(const std::string& callbackId, const std::string name)
	{
	}

	void MBTilesPluginFileImplNDK::close()
	{
	}

	bool MBTilesPluginFileImplNDK::isOpen()
	{
		return false;
	}

	Json::Value MBTilesPluginFileImplNDK::getMetaData(const std::string& callbackId)
	{

	}


	Json::Value MBTilesPluginFileImplNDK::getMinZoom(const std::string& callbackId)
	{

	}


	Json::Value MBTilesPluginFileImplNDK::getMaxZoom(const std::string& callbackId)
	{

	}


	Json::Value MBTilesPluginFileImplNDK::getTile(const std::string& callbackId, int zoom_level, int column, int row)
	{

	}


	Json::Value MBTilesPluginFileImplNDK::getExecuteStatment(const std::string& callbackId, const std::string query, const QList<Json::Value> params)
	{

	}

}
