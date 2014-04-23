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

#ifndef MBTILESPLUGINGENDATABASEIMPLNDK_HPP_
#define MBTILESPLUGINGENDATABASEIMPLNDK_HPP_

#include "mbtilesplugingenimpl_ndk.hpp"
#include "sqlite3.h"

namespace webworks {

class MBTilesPluginGenDataBaseImplNDK : public MBTilesPluginGenImplNDK {

	private:
		sqlite3* database;

	public:
		explicit MBTilesPluginGenDataBaseImplNDK(MBTilesPluginJS *parent = NULL);
		virtual ~MBTilesPluginGenDataBaseImplNDK();


		Json::Value open(const std::string& callbackId, const std::string name);

		bool isOpen();

		Json::Value getMetaData(const std::string& callbackId);

		Json::Value getMinZoom(const std::string& callbackId);

		Json::Value getMaxZoom(const std::string& callbackId);

		int getMaxZoomValue();

		Json::Value getTile(const std::string& callbackId, int zoom_level, int column, int row);

		Json::Value getExecuteStatement(const std::string& callbackId, const std::string query, const QList<Json::Value> params);

		Json::Value getDirectoryWorking(const std::string& callbackId);

		bool bindValue(sqlite3_stmt* stmt, QList<Json::Value> params);

	protected:
		void close();

};

} // namespace webworks

#endif /* MBTILESPLUGINGENDATABASEIMPLNDK_HPP_ */
