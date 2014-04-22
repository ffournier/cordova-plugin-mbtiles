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

#ifndef MBTILESPLUGINFILEIMPLNDK_HPP_
#define MBTILESPLUGINFILEIMPLNDK_HPP_

#include "mbtilespluginaction_ndk.hpp"
#include <QDir>
#include <QFile>

namespace webworks {

class MBTilesPluginFileImplNDK : public MBTilesPluginActionNDK {
	private:
		QDir* dirPath;

		QList<int> getZoomLevels();
		Json::Value getMetaData();
		Json::Value getMaxZoom();

	public:
		explicit MBTilesPluginFileImplNDK(MBTilesPluginJS *parent = NULL);
		virtual ~MBTilesPluginFileImplNDK();


		Json::Value open(const std::string& callbackId, const std::string name);

		bool isOpen();

		Json::Value getMetaData(const std::string& callbackId);

		Json::Value getMinZoom(const std::string& callbackId);

		Json::Value getMaxZoom(const std::string& callbackId);

		Json::Value getTile(const std::string& callbackId, int zoom_level, int column, int row);

		Json::Value getExecuteStatement(const std::string& callbackId, const std::string query, const QList<Json::Value> params);

		Json::Value getDirectoryWorking(const std::string& callbackId);

	protected:
		void close();
};

} // namespace webworks

#endif /* MBTILESPLUGINFILEIMPLNDK_HPP_ */
