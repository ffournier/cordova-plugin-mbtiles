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

#ifndef MBTILESPLUGINGENIMPLNDK_HPP_
#define MBTILESPLUGINGENIMPLNDK_HPP_

#include "mbtilespluginaction_ndk.hpp"
#include "mbtilesplugin_js.hpp"
#include <bb/PackageInfo>
#include <bb/device/SdCardInfo>
#include <bb/device/SdCardState>

namespace webworks {

class MBTilesPluginGenImplNDK : public MBTilesPluginActionNDK {

	protected:
	QString directory;

	public:
		explicit MBTilesPluginGenImplNDK(MBTilesPluginJS *parent = NULL);
		virtual ~MBTilesPluginGenImplNDK();

	protected:

		QString getDirectory();

	public:
		static bool detectSDCard();
		static QString getInstallName();

};

} // namespace webworks

#endif /* MBTILESPLUGINGENIMPLNDK_HPP_ */
