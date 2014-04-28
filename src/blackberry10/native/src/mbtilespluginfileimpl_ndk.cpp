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

#include "mbtilespluginfileimpl_ndk.hpp"
#include "mbtilespluginutils_ndk.hpp"

namespace webworks {

	MBTilesPluginFileImplNDK::MBTilesPluginFileImplNDK(MBTilesPluginJS *parent, std::string typePath, std::string url)
	: MBTilesPluginGenImplNDK(parent)
	{
		directory = QString();

		if (!typePath.empty() && typePath.compare(TYPE_PATH_CDVFILE) == 0) {
			if (url.length() >0) {
				directory = QString::fromStdString(url);
			}
		} else if (typePath.empty() || typePath.compare(TYPE_PATH_FULL) == 0) {
			if (url.length() <=0 ) {
				if (detectSDCard()) {
					QString installName = getInstallName();
					directory = QString::fromStdString("/accounts/1000/removable/sdcard/");
					directory += installName;
					directory += QString::fromStdString("/maps/");
				}
			} else {
				directory = QString::fromStdString(url);
			}
		}
	}

	MBTilesPluginFileImplNDK::~MBTilesPluginFileImplNDK()
	{
		close();
	}

	// The extension methods are defined here
	Json::Value MBTilesPluginFileImplNDK::open(const std::string& callbackId, const std::string name)
	{
		Json::Value root;

		close();

		// test if the sdcard is present
		QString dir = getDirectory();
		if (dir != "") {
			QDir* path = new QDir(dir);
			if (path != NULL && path->exists() == true)
			{
				dirPath = path;
				root[PLUGIN_RESULT] = "File Open";
			} else {
				close();
				root[PLUGIN_ERROR] = "Cannot open file";
			}
		} else {
			root[PLUGIN_ERROR] = "No SdCard";
		}
		return root;
	}

	void MBTilesPluginFileImplNDK::close()
	{
		if (dirPath != NULL) {
			delete dirPath;
		}
		dirPath = NULL;
	}

	bool MBTilesPluginFileImplNDK::isOpen()
	{
		return dirPath != NULL;
	}

	Json::Value MBTilesPluginFileImplNDK::getMetaData(const std::string& callbackId)
	{
		return getMetaData();
	}


	Json::Value MBTilesPluginFileImplNDK::getMinZoom(const std::string& callbackId)
	{
		Json::Value root;

		QList<int> zoomLevels = getZoomLevels();

		if (!zoomLevels.isEmpty())
		{
			root[KEY_MIN_ZOOM] = zoomLevels[0];
		}

		return root;
	}


	Json::Value MBTilesPluginFileImplNDK::getMaxZoom(const std::string& callbackId)
	{
		return getMaxZoom();
	}

	Json::Value MBTilesPluginFileImplNDK::getMaxZoom()
	{
		Json::Value root;

		QList<int> zoomLevels = getZoomLevels();

		if (!zoomLevels.isEmpty())
		{
			root[KEY_MAX_ZOOM] = zoomLevels[zoomLevels.size() - 1];
		}

		return root;
	}

	Json::Value MBTilesPluginFileImplNDK::getTile(const std::string& callbackId, int zoom_level, int column, int row)
	{
		Json::Value root;
		Json::Value metadata = getMetaData();

		std::string name = metadata[KEY_NAME].asString();
		std::string version = metadata[KEY_VERSION].asString();
		std::string format = metadata[KEY_FORMAT].asString();
		Json::Value maxZoomValue = getMaxZoom();
		int maxZoom = maxZoomValue[KEY_MAX_ZOOM].asInt();
		int currentZoomLevel = zoom_level;
		if (zoom_level > maxZoom)
		{
			currentZoomLevel = maxZoom;
		}
		QString fileName = dirPath->absolutePath();
		fileName += QString::fromStdString("/" + version + "/" + name + "/");
		fileName += "/" ;
		fileName += QString::number(column);
		fileName += "/" ;
		fileName += QString::number(row);
		fileName += QString::fromStdString("." + format);
		QFile* tileFile = new QFile(fileName);

		// test if file exist
		if (tileFile != NULL && tileFile->exists())
		{
			if (tileFile->open(QIODevice::ReadOnly)) {
				// TODO maybe crash cause of memory
				QByteArray data = tileFile->readAll();
				root[KEY_TILE_DATA] = data.toBase64().data();
				tileFile->close();
			} else{
				root[PLUGIN_ERROR] = "Can't open the files";
			}
		} else {
			root[PLUGIN_ERROR] = "Tiles not exist";
		}

		if (tileFile != NULL) {
			delete tileFile;
		}

		return root;

	}


	Json::Value MBTilesPluginFileImplNDK::getExecuteStatement(const std::string& callbackId, const std::string query, const QList<Json::Value> params)
	{
		Json::Value root;
		root[PLUGIN_ERROR] = "Not Implemented";
		return root;
	}

	Json::Value MBTilesPluginFileImplNDK::getDirectoryWorking(const std::string& callbackId)
	{
		Json::Value root;

		QString dir = getDirectory();
		if (!dir.isNull()) {
			root[KEY_DIRECTORY_WORKING] = dir.toStdString();
		}else{
			root[PLUGIN_ERROR] = "No SdCard";
		}
		return root;
	}

	Json::Value MBTilesPluginFileImplNDK::getMetaData() {
		Json::Value root;
		QFile* fileMetadata = new QFile(dirPath->absolutePath() + "/" + "metadata.json");
		if (fileMetadata != NULL && fileMetadata->exists()) {
			if (fileMetadata->open(QIODevice::ReadOnly)) {
				QByteArray data = fileMetadata->readAll();
				if (!data.isEmpty() && !data.isNull()) {
					root = Json::Value(data.constData());
				}else{
					root[PLUGIN_ERROR] = "Error when reading file";
				}
				fileMetadata->close();
			} else {
				root[PLUGIN_ERROR] = "Can't open the files";
			}
		} else {
			root[PLUGIN_ERROR] = "File not present";
		}

		if (fileMetadata != NULL) {
			delete fileMetadata;
		}
		return root;
	}

	/**
	 * Tries to retrieve all available zoom levels for this MBTiles resource.
	 * @return a {@link List} of zoom levels as {@link Integer}
	 */
	QList<int> MBTilesPluginFileImplNDK::getZoomLevels()
	{
		Json::Value metadata = getMetaData();
		QList<int> zoomLevels;

		std::string name = metadata[KEY_NAME].asString();
		std::string version = metadata[KEY_VERSION].asString();

		QString dirZoom = QString::fromStdString(dirPath->absolutePath().toStdString() + "/" + version + "/" + name);
		QDir* contents = new QDir(dirZoom);
		if (contents != NULL && contents->exists()) {
			QFileInfoList info = contents->entryInfoList(QDir::Files, QDir::NoSort);
			if (!info.isEmpty()) {
				for (int i = 0 ; i < info.size() ; i++) {
					QString fileName = info[i].fileName();
					zoomLevels.append(fileName.toInt());
				}
				qSort(zoomLevels);
			}
		}
		if (contents != NULL) {
			delete contents;
		}
		return zoomLevels;
	}

}
