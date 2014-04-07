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

#ifndef MBTILESPLUGINACTIONNDK_HPP_
#define MBTILESPLUGINACTIONNDK_HPP_

#include <string>
#include <pthread.h>
#include <json/reader.h>
#include <json/writer.h>
#include <QList>

class MBTilesPluginJS;

namespace webworks {

class MBTilesPluginActionNDK {
	public:
		explicit MBTilesPluginActionNDK(MBTilesPluginJS *parent = NULL);
		virtual ~MBTilesPluginActionNDK();

		// The extension methods are defined here
		virtual Json::Value open(const std::string& callbackId, const std::string name) = 0;

		virtual void close() = 0;

		virtual bool isOpen() = 0;

		virtual Json::Value getMetaData(const std::string& callbackId) = 0;

		virtual Json::Value getMinZoom(const std::string& callbackId) = 0;

		virtual Json::Value getMaxZoom(const std::string& callbackId) = 0;

		virtual Json::Value getTile(const std::string& callbackId, int zoom_level, int column, int row) = 0;

		virtual Json::Value getExecuteStatment(const std::string& callbackId, const std::string query, const QList<Json::Value> params) = 0;

		virtual Json::Value getDirectoryWorking(const std::string& callbackId) = 0;

	protected:
		MBTilesPluginJS *m_pParent;
};

} // namespace webworks

#endif /* MBTILESPLUGINNDK_H_ */
