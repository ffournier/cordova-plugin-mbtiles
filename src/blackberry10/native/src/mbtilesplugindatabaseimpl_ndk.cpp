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

#include <json/reader.h>
#include <json/writer.h>
#include <QFile>
#include <QVariant>
#include <QByteArray>
#include <bps/removablemedia.h>
#include "mbtilesplugindatabaseimpl_ndk.hpp"
#include "mbtilespluginutils_ndk.hpp"
#include "mbtilespluginaction_ndk.hpp"
#include "mbtilesplugin_js.hpp"

namespace webworks {

	MBTilesPluginDataBaseImplNDK::MBTilesPluginDataBaseImplNDK(MBTilesPluginJS *parent)
	: MBTilesPluginActionNDK(parent)
	{
		database = NULL;
	}

	MBTilesPluginDataBaseImplNDK::~MBTilesPluginDataBaseImplNDK()
	{
		close();
	}

	// The extension methods are defined here
	Json::Value MBTilesPluginDataBaseImplNDK::open(const std::string& callbackId, const std::string name)
	{
		//
		close();
		Json::FastWriter writer;
		Json::Value root;

		// test if the sdcard is present
		if (detectSDCard()) {
			QString installName = getInstallName();
			QString result = QString::fromStdString("/accounts/1000/removable/sdcard/");
			result += installName;
			result += "/";
			result += QString::fromStdString(name);
			QFile* path = new QFile(result);
			if (path != NULL && path->exists() == true)
			{
				if (sqlite3_open_v2(path->fileName().toStdString().c_str(), &database, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK )
				{
					close();
					root[PLUGIN_ERROR] = "Cannot open database";
				} else {
					root[PLUGIN_RESULT] = "OK";
				}
			} else {
				root[PLUGIN_ERROR] = "Database doesn't exist";
			}

			if (path != NULL) {
				delete path;
			}
		} else {
			root[PLUGIN_ERROR] = "No SdCard";
		}
		return root;
	}

	void MBTilesPluginDataBaseImplNDK::close()
	{
		if (database != NULL) {
			sqlite3_close(database);
			delete database;
		}
		database = NULL;
	}

	bool MBTilesPluginDataBaseImplNDK::isOpen()
	{
		return database != NULL;
	}

	Json::Value MBTilesPluginDataBaseImplNDK::getMetaData(const std::string& callbackId)
	{
		// test if the database is open
		Json::FastWriter writer;
		Json::Value root;
		if (isOpen() == true)
		{
			std::string query = "SELECT * FROM metadata";
			sqlite3_stmt* stmt;
			// execute query
			int ret = sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, NULL);
			if (ret == SQLITE_OK) {
				// treat answer
				while (sqlite3_step(stmt) == SQLITE_ROW)
				{
					std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,0)));
					std::string type = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt,1)));
					root[name] = type;
				}
			} else {
				root[PLUGIN_ERROR] = "Error SQL Statment";
			}
			sqlite3_finalize(stmt);
		} else {
			root[PLUGIN_ERROR] = "Database not open";
		}
		return root;

	}


	Json::Value MBTilesPluginDataBaseImplNDK::getMinZoom(const std::string& callbackId)
	{
		Json::FastWriter writer;
		Json::Value root;


		 // test if the db is open
		if(isOpen() == true) {
			// run query max zoom
			std::string query = "SELECT MIN(zoom_level) AS min_zoom_level FROM tiles";
			sqlite3_stmt* stmt;
			int ret = sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, NULL);
			if( ret == SQLITE_OK) {
				// treat the answer
				if(sqlite3_step(stmt) == SQLITE_ROW) {
					int min = sqlite3_column_int(stmt, 0);
					// TODO
					root[KEY_MIN_ZOOM] = min;
				} else {
					root[PLUGIN_ERROR] = "Query not Execute";
				}
				sqlite3_finalize(stmt);
			} else {
				root[PLUGIN_ERROR] = "Min not Found";
			}
		} else {
			root[PLUGIN_ERROR] = "Database not Open";
		}
		return root;
	}


	int MBTilesPluginDataBaseImplNDK::getMaxZoomValue()
	{
		int max = -1;
		 // test if the db is open
		if(isOpen() == true) {
			// run query max zoom
			std::string query = "SELECT MAX(zoom_level) AS max_zoom_level FROM tiles";
			sqlite3_stmt* stmt;
			int ret = sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, NULL);
			if( ret == SQLITE_OK) {
				// treat the answer
				if(sqlite3_step(stmt) == SQLITE_ROW) {
					max = sqlite3_column_int(stmt, 0);
				}

				sqlite3_finalize(stmt);
			}
		}
		return max;
	}


	Json::Value MBTilesPluginDataBaseImplNDK::getMaxZoom(const std::string& callbackId)
	{
		Json::FastWriter writer;
		Json::Value root;
		int max = getMaxZoomValue();
		if (max != -1) {
			// ok
			root[KEY_MAX_ZOOM] = max;
		} else {
			root[PLUGIN_ERROR] = "Max not Found";
		}
		return root;

	}


	Json::Value MBTilesPluginDataBaseImplNDK::getTile(const std::string& callbackId, int zoom_level, int column, int row)
	{
		Json::FastWriter writer;
		Json::Value root;
		int currentLevelZoom = zoom_level;
		// test if db is open
		if (isOpen()) {
			// get max zoom
			int maxZoom =  getMaxZoomValue();
			if (maxZoom > -1) {
			   // if the currentlevelzoom is higher than the max zoom, reinit it.
			   if (currentLevelZoom > maxZoom) {
					currentLevelZoom = maxZoom;
			   }
			}
			// run query of tiles.
			std::string query = "SELECT tile_data FROM tiles WHERE zoom_level = ?1 AND tile_column = ?2 AND tile_row = ?3";
			sqlite3_stmt* stmt;
			int ret = sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, NULL);
			if( ret == SQLITE_OK) {
			// bind value
				sqlite3_bind_int(stmt, 1, currentLevelZoom);
				sqlite3_bind_int(stmt, 2, column);
				sqlite3_bind_int(stmt, 3, row);
				// treat answer
				if(sqlite3_step(stmt) == SQLITE_ROW) {
					int lenght_bytes = sqlite3_column_bytes(stmt, 0);
					QByteArray* data = new QByteArray(((const char*)sqlite3_column_blob(stmt, 0)), lenght_bytes);
					root[KEY_TILE_DATA] = data->toBase64().data();
					root["zoom_level"] = currentLevelZoom;
					root["column"] = column;
					root["row"] = row;
					delete data;
				} else {
					root[PLUGIN_ERROR] = "Tiles not found " + query + "--";
					root["zoom_level"] = currentLevelZoom;
					root["column"] = column;
					root["row"] = row;
				}
				sqlite3_finalize(stmt);
			} else {
				root[PLUGIN_ERROR] = "Query not execute";
			}
		}  else {
			root[PLUGIN_ERROR] = "Database not open";
		}
		return root;
	}


	Json::Value MBTilesPluginDataBaseImplNDK::getExecuteStatment(const std::string& callbackId, const std::string query, const QList<Json::Value> params)
	{
		Json::FastWriter writer;
		Json::Value root;
		// test if the database is open
		if (isOpen() == true) {
			// run given query
			std::string sql_stmt = query;
			sqlite3_stmt* stmt;
			int ret = sqlite3_prepare_v2(database, sql_stmt.c_str(), -1, &stmt, NULL);
			if( ret == SQLITE_OK) {

				// bind value
				bool result = bindValue(stmt,params);
				if (result == true) {
					Json::Value array;
					// treat answer
					while (sqlite3_step(stmt) == SQLITE_ROW) {

						int count = sqlite3_column_count(stmt);
						Json::Value objectJson;

						for (int i = 0; i < count ; i++) {
							QVariant* object = NULL;
							// get type of column
							int type = sqlite3_column_type(stmt, i);
							// get name of column
							QString name = QString::fromStdString(sqlite3_column_name(stmt, i));
							switch(type) {
								case SQLITE_INTEGER:
									object = new QVariant(sqlite3_column_int(stmt, i));
									break;
								case SQLITE_FLOAT:
									object = new QVariant(sqlite3_column_double(stmt, i));
									break;
								case SQLITE_TEXT:
									object = new QVariant(QString::fromStdString(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)))));
									break;
								case SQLITE_BLOB:
									{
										int lenght_bytes = sqlite3_column_bytes(stmt, 0);
										QByteArray* data = new QByteArray(((const char*)sqlite3_column_blob(stmt, 0)), lenght_bytes);
										object = new QVariant(data->toBase64());
										delete data;
									}
									break;
								case SQLITE_NULL:
								default:
									QString temp = NULL;
									object = new QVariant(temp);
									break;
							}
							// add to object
							if (object != NULL) {
								QString value = object->toString();
								objectJson[name.toStdString()] = value.toStdString();
								delete object;
							} else {
								objectJson[name.toStdString()] = "NULL";
							}
						}
						// add to array
						array.append(objectJson);
					}
					root[KEY_EXECUTE_STATMENT] = array;

				} else {
					root[PLUGIN_ERROR] = "Bind Value error";
				}
			} else {
				root[PLUGIN_ERROR] = "Query not execute";
			}
			sqlite3_finalize(stmt);
		} else {
			root[PLUGIN_ERROR] = "Database not Open";
		}
		return root;
	}


	Json::Value MBTilesPluginDataBaseImplNDK::getDirectoryWorking(const std::string& callbackId)
	{
		Json::Value root;
		if (detectSDCard()) {
			QString name = getInstallName();
			QString result = QString::fromStdString("/accounts/1000/removable/sdcard/");
			result += name;
			root[KEY_DIRECTORY_WORKING] = result.toStdString();
		} else{
			root[PLUGIN_ERROR] = "No SdCard";
		}
		return root;
	}

	bool MBTilesPluginDataBaseImplNDK::bindValue(sqlite3_stmt* stmt, QList<Json::Value> params) {

		for (int i = 1; i <= params.size(); i++) {
			Json::Value object = params[i-1];
			// test type of object
			if (object.isNull()) {
				sqlite3_bind_null(stmt, i);
			} else if (object.isInt()) {
				sqlite3_bind_int(stmt, i, object.asInt());
			} else if (object.isDouble()) {
				sqlite3_bind_double(stmt, i, object.asDouble());
			} else if (object.isUInt()) {
				sqlite3_bind_int(stmt, i, object.asUInt());
			} else if (object.asBool()) {
				sqlite3_bind_int(stmt, i, object.asBool());
			} else {
				sqlite3_bind_text(stmt, i, object.asString().c_str(), -1, SQLITE_TRANSIENT);
			}
		}
	    return true;
	}
}
