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

#ifndef MBTILESPLUGINDATABASEIMPLNDK_HPP_
#define MBTILESPLUGINDATABASEIMPLNDK_HPP_

#include "mbtilespluginaction_ndk.hpp"
#include "sqlite3.h"

namespace webworks {

class MBTilesPluginDataBaseImplNDK : public MBTilesPluginActionNDK {

	private:
		sqlite3* database;

	public:
		explicit MBTilesPluginDataBaseImplNDK(MBTilesPluginJS *parent = NULL);
		virtual ~MBTilesPluginDataBaseImplNDK();


		Json::Value open(const std::string& callbackId, const std::string name);

		bool isOpen();

		Json::Value getMetaData(const std::string& callbackId);

		Json::Value getMinZoom(const std::string& callbackId);

		Json::Value getMaxZoom(const std::string& callbackId);

		int getMaxZoomValue();

		Json::Value getTile(const std::string& callbackId, int zoom_level, int column, int row);

		Json::Value getExecuteStatment(const std::string& callbackId, const std::string query, const QList<Json::Value> params);

		Json::Value getDirectoryWorking(const std::string& callbackId);

		bool bindValue(sqlite3_stmt* stmt, QList<Json::Value> params);

	protected:
		void close();

};

} // namespace webworks

#endif /* MBTILESPLUGINDATABASEIMPLNDK_HPP_ */
