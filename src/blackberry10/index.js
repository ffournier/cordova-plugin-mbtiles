/*
* Copyright (c) 2013 BlackBerry Limited
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

var mbtilesplugin,
	resultObjs = {},
	_utils = require("../../lib/utils");

module.exports = {

	// Code can be declared and used outside the module.exports object,
	// but any functions to be called by MBTilesPlugin.js need to be declared
	// here in this object.

	// These methods call into JNEXT.MBTilesPlugin through the JNEXT plugin to mbtilesplugin_js.cpp
	open: function (success, fail, args, env) {
		var result = new PluginResult(args, env),
		data = JSON.parse(decodeURIComponent((args["input"]))),
		response = mbtilesplugin.getInstance().open(result.callbackId, data);
		result.ok(response, false);
	},

	get_metadata:function (success, fail, args, env) {
		var result = new PluginResult(args, env),
		response = mbtilesplugin.getInstance().get_metadata(result.callbackId, args);
		result.ok(response, false);
	},

	get_min_zoom: function (success, fail, args, env) {
		var result = new PluginResult(args, env),
		response = mbtilesplugin.getInstance().get_min_zoom(result.callbackId, args);
		result.ok(response, false);
	},

	get_max_zoom: function (success, fail, args, env) {
		var result = new PluginResult(args, env),
		response = mbtilesplugin.getInstance().get_max_zoom(result.callbackId, args);
		result.ok(response, false);
	},

	get_tile: function (success, fail, args, env) {
		var result = new PluginResult(args, env),
		data = JSON.parse(decodeURIComponent((args["input"]))),
		response = mbtilesplugin.getInstance().get_tile(result.callbackId, data);
		result.ok(response, false);
	},

	execute_statment: function (success, fail, args, env) {
		var result = new PluginResult(args, env), 
		data = JSON.parse(decodeURIComponent((args["input"]))),
		response = mbtilesplugin.getInstance().execute_statment(result.callbackId, data);
		result.ok(response, false);
	}
};

///////////////////////////////////////////////////////////////////
// JavaScript wrapper for JNEXT plugin for connection
///////////////////////////////////////////////////////////////////

JNEXT.MBTilesPlugin = function () {
	var self = this,
		hasInstance = false;

	self.getId = function () {
		return self.m_id;
	};

	self.init = function () {
		if (!JNEXT.require("libMBTilesPlugin")) {
			return false;
		}

		self.m_id = JNEXT.createObject("libMBTilesPlugin.MBTilesPluginJS");

		if (self.m_id === "") {
			return false;
		}

		JNEXT.registerEvents(self);
	};

	// ************************
	// Enter your methods here
	// ************************

	// calls into InvokeMethod(string command) in mbtilesplugin_js.cpp
	self.open = function (callbackId, input) {
		return JNEXT.invoke(self.m_id, "open " + callbackId + " " + JSON.stringify(input));
	}; // open

	self.get_metadata = function (callbackId, input) {
		return JNEXT.invoke(self.m_id, "get_metadata " + callbackId + " " + JSON.stringify(input));
	};

	self.get_min_zoom = function (callbackId, input) {
		return JNEXT.invoke(self.m_id, "get_min_zoom " + callbackId + " " + JSON.stringify(input));
	};	

	self.get_min_zoom = function (callbackId, input) {
		return JNEXT.invoke(self.m_id, "get_max_zoom " + callbackId + " " + JSON.stringify(input));
	};

	self.get_min_zoom = function (callbackId, input) {
		return JNEXT.invoke(self.m_id, "get_tile " + callbackId + " " + JSON.stringify(input));
	};

	self.get_min_zoom = function (callbackId, input) {
		return JNEXT.invoke(self.m_id, "execute_statment " + callbackId + " " + JSON.stringify(input));
	};

	// Fired by the Event framework (used by asynchronous callbacks)
	self.onEvent = function (strData) {
		var arData = strData.split(" "),
			callbackId = arData[0],
			result = resultObjs[callbackId],
			data = arData.slice(1, arData.length).join(" ");
		if (result) {
			result.callbackOk(data, true);
		}
	};

	// ************************
	// End of methods to edit
	// ************************
	self.m_id = "";

	self.getInstance = function () {
		if (!hasInstance) {
			hasInstance = true;
			self.init();
		}
		return self;
	};

};

mbtilesplugin = new JNEXT.MBTilesPlugin();
