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
#include "../public/tokenizer.h"
#include "mbtilesplugin_js.hpp"
#include "mbtilesplugindatabaseimpl_ndk.hpp"
#include "mbtilespluginfileimpl_ndk.hpp"
#include "mbtilespluginutils_ndk.hpp"
#include <QList>

using namespace std;

/**
 * Default constructor.
 */
MBTilesPluginJS::MBTilesPluginJS(const std::string& id) :
		m_id(id) {
	m_pLogger = new webworks::Logger("MBTilesPluginJS", this);
	m_pMBTilesPluginController = NULL;
}

/**
 * MBTilesPlugin destructor.
 */
MBTilesPluginJS::~MBTilesPluginJS() {
	if (m_pMBTilesPluginController != NULL)
		delete m_pMBTilesPluginController;
	if (m_pLogger)
			delete m_pLogger;
}

webworks::Logger* MBTilesPluginJS::getLog() {
	return m_pLogger;
}

/**
 * This method returns the list of objects implemented by this native
 * extension.
 */
char* onGetObjList() {
	static char name[] = "MBTilesPluginJS";
	return name;
}

/**
 * This method is used by JNext to instantiate the MBTilesPlugin object when
 * an object is created on the JavaScript server side.
 */
JSExt* onCreateObject(const string& className, const string& id) {
	if (className == "MBTilesPluginJS") {
		return new MBTilesPluginJS(id);
	}

	return NULL;
}

/**
 * Method used by JNext to determine if the object can be deleted.
 */
bool MBTilesPluginJS::CanDelete() {
	return true;
}

/**
 * It will be called from JNext JavaScript side with passed string.
 * This method implements the interface for the JavaScript to native binding
 * for invoking native code. This method is triggered when JNext.invoke is
 * called on the JavaScript side with this native objects id.
 */
string MBTilesPluginJS::InvokeMethod(const string& command) {
	// format must be: "command callbackId params"
	size_t commandIndex = command.find_first_of(" ");
	std::string strCommand = command.substr(0, commandIndex);
	size_t callbackIndex = command.find_first_of(" ", commandIndex + 1);
	std::string callbackId = command.substr(commandIndex + 1, callbackIndex - commandIndex - 1);
	std::string arg = command.substr(callbackIndex + 1, command.length());

	Json::FastWriter writer;
	Json::Reader reader;
	Json::Value root;
	Json::Value result;

	std::string log = "Debug::Action : " + strCommand;
	getLog()->debug(log.c_str());
	// based on the command given, run the appropriate method in template_ndk.cpp
	if (strCommand.compare(ACTION_OPEN) == 0) {
		log = "Debug::Action : Open";
		getLog()->debug(log.c_str());
		bool parse = arg != strCommand;
		if (parse) {
			parse = reader.parse(arg, root);
		}
		if (!parse) {
			result[PLUGIN_RESULT] = PLUGIN_PARSE_ERROR;
		} else {
			std::string type = root[KEY_TYPE].asString();
			std::string name = root[KEY_NAME].asString();
			if (type.compare(TYPE_DB) == 0) {
				m_pMBTilesPluginController = new webworks::MBTilesPluginDataBaseImplNDK(this);
				result = m_pMBTilesPluginController->open(callbackId, name);
			} else if (type.compare(TYPE_FILE) == 0) {
				m_pMBTilesPluginController = new webworks::MBTilesPluginFileImplNDK(this);
				result = m_pMBTilesPluginController->open(callbackId, name);
			} else {
				result[PLUGIN_RESULT] = TYPE_UNDEFINED;
			}
		}
	} else if (strCommand.compare(ACTION_GETMETADATA) == 0) {
		if (m_pMBTilesPluginController != NULL && m_pMBTilesPluginController->isOpen()) {
			result = m_pMBTilesPluginController->getMetaData(callbackId);
		} else {
			result[PLUGIN_RESULT] = PLUGIN_NOT_OPEN;
		}
	} else if (strCommand.compare(ACTION_GETMINZOOM) == 0) {
		if (m_pMBTilesPluginController != NULL && m_pMBTilesPluginController->isOpen()) {
			result = m_pMBTilesPluginController->getMinZoom(callbackId);
		} else {
			result[PLUGIN_RESULT] = PLUGIN_NOT_OPEN;
		}
	} else if (strCommand.compare(ACTION_GETMAXZOOM) == 0) {
		if (m_pMBTilesPluginController != NULL && m_pMBTilesPluginController->isOpen()) {
			result = m_pMBTilesPluginController->getMaxZoom(callbackId);
		} else {
			result[PLUGIN_RESULT] = PLUGIN_NOT_OPEN;
		}
	} else if (strCommand.compare(ACTION_GETTILE) == 0) {
		bool parse = arg != strCommand;
		if (parse) {
			parse = reader.parse(arg, root);
		}
		if (!parse) {
			result[PLUGIN_RESULT] = PLUGIN_PARSE_ERROR;
		} else {
			if (m_pMBTilesPluginController != NULL && m_pMBTilesPluginController->isOpen()) {
				int z = root[KEY_Z].asInt();
				int x = root[KEY_X].asInt();
				int y = root[KEY_Y].asInt();
				result = m_pMBTilesPluginController->getTile(callbackId, z, x, y);
			} else {
				result[PLUGIN_RESULT] = PLUGIN_NOT_OPEN;
			}
		}
	} else if (strCommand.compare(ACTION_EXECUTESTATMENT) == 0) {
		std::string query = "";
		QList<Json::Value> params;
		bool parse = arg != strCommand;
		if (parse) {
			parse = reader.parse(arg, root);
			if (parse) {
				query = root[KEY_QUERY].asString();
				std::string temp= root[KEY_PARAMS].asString();
				Json::Value params_value;
				parse = reader.parse(temp, params_value);
				if (parse && params_value.isArray()) {
					for (int i = 0; i < params_value.size(); i++) {
						params.push_back(params_value);
					}
				}
			}
		}
		if (!parse) {
			result[PLUGIN_RESULT] = PLUGIN_PARSE_ERROR;
		} else {
			if (m_pMBTilesPluginController != NULL && m_pMBTilesPluginController->isOpen()) {
				result = m_pMBTilesPluginController->getExecuteStatment(callbackId, query, params);
			} else {
				result[PLUGIN_RESULT] = PLUGIN_NOT_OPEN;
			}
		}
	} else if (strCommand.compare(ACTION_GETDIRECTORYWORKING) == 0) {
		bool parse = arg != strCommand;
		if (parse) {
			parse = reader.parse(arg, root);
		}
		if (!parse) {
			result[PLUGIN_RESULT] = PLUGIN_PARSE_ERROR;
		} else {
			webworks::MBTilesPluginActionNDK * action = NULL;
			std::string type = root[KEY_TYPE].asString();
			if (type.compare(TYPE_DB) == 0) {
				action = new webworks::MBTilesPluginDataBaseImplNDK(this);
				result = action->getDirectoryWorking(callbackId);
			} else if (type.compare(TYPE_FILE) == 0) {
				action = new webworks::MBTilesPluginFileImplNDK(this);
				result = action->getDirectoryWorking(callbackId);
			} else {
				result[PLUGIN_RESULT] = TYPE_UNDEFINED;
			}
			if (action != NULL) {
				delete action;
			}
		}
	} else {
		result[PLUGIN_ERROR] = PLUGIN_NOT_ACTION;
	}
	//strCommand.append(";");
	//strCommand.append(command);
	//return resutString;
	return writer.write(result);
}

// Notifies JavaScript of an event
void MBTilesPluginJS::NotifyEvent(const std::string& event) {
	std::string eventString = m_id + " ";
	eventString.append(event);
	SendPluginEvent(eventString.c_str(), m_pContext);
}
