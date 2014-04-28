Environnement
======================

Android
----------------------

### __Environnement__

Windows, Mac, Linux

### __IDE__

Eclipse, IntelliJ, NetBeans, etc ..


iOS
----------------------

### __Environnement__

Mac

### __IDE__ 

XCode


Windows Phone 8
----------------------

### __Environnement__

Windows Phone SDK 8.0 requires 64-bit Windows 8 Pro or higher.

#### __Emulator :__

##### _System requirements_

In the BIOS, the following features must be supported:

Hardware-assisted virtualization.

Second Level Address Translation (SLAT).

Hardware-based Data Execution Prevention (DEP).

4 GB or more of RAM.

64-bit version of Windows 8 Pro edition or higher.

##### _Network requirements_

DHCP.

Automatically configured DNS and gateway settings.

##### _Hyper-V requirements_

In the BIOS, the following features must be enabled:

Hardware-assisted virtualization.

Second Level Address Translation (SLAT).

Hardware-based Data Execution Prevention (DEP).

In Windows, Hyper-V must be enabled and running.

You have to be a member of the local Hyper-V Administrators group.

#### __System requirements :__

Your computer must meet the following requirements:

##### _BIOS_

In the BIOS, the following features must be supported:

Hardware-assisted virtualization.

Second Level Address Translation (SLAT).

Hardware-based Data Execution Prevention (DEP).

##### _RAM_

4 GB or more.

##### _Operating system_

Windows 8

64-bit

Pro edition or higher


Add in your vmx to enable Hyper-V

	hypervisor.cpuid.v0 = "FALSE"

	mce.enable = "TRUE"

since your system now access 

Activer ou désactiver des fonctionnalités Windows

Activer Hyper-V, Outils d'aministration Hyper-V et Plateforme Hyper-V

Si vous n'arriver pas à activerla plateforme il vous faudra :

Aller dans le centre de maintenance que vous trouverez dans le panneau de configuration est positionner au minimum (Ne jamais m'avertir).

Puis activer le LUAEnable de la regedit pour se faire aller dans la regedit :

	HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\system

et mettez la valeur à 0

Puis depuis une commande administrator

	bcdedit /set hypervisorlaunchtype Off --> pour pouvoir annuler le lancement de l'hypervisor au démarrage et ainsi le modifier depuis le panneau de configuration.


### __IDE__

Visual Studio 2013.


BlackBerry
----------------------

### __Environnement__

Linux Windows or Mac

### __IDE__ 

Momentics, based on eclipse

You just need to load the project and compile library for device (arm) and simulator (x86).

### _Emulator_

You need to install the VM to simulate a blackberry you can find this VM on the  [web site](https://developer.blackberry.com/).

To connect to the device and debug it, you need to create a token from the emulator.

You have like tools the controller inside the install of the emulator.

You can access to the emulator by the command telnet <ip_simulator> or ftp. (user: devuser, password:devuser).


How it works ? 
======================

This plugin can access to a database in sqlite or a file, to read mbtiles data. It create the link between webview and natif. This link depends of the OS where you will execute your program. just the interface in JavaScript must be the same to simplify the call of function. We will see by supported OS how it works and how call it.


Android
----------------------

You must create a class which extends CordovaPlugin, in this class override the function execute :

	public boolean execute(String action, JSONArray data, CallbackContext callbackContext) throws JSONException;

This function receive the call of javascript :

* __action__

 In this string we will find the name of function / action to execute

* __data__

 In this JSON we will find the parameters given by javascript
 
* __callbackContext__

 This class will can return the result to the Caller by a callback, the object returned is a PluginResult provides by the Cordova Library. 

	callbackContextFinal.sendPluginResult(new PluginResult(PluginResult.Status.JSON_EXCEPTION));

iOS
----------------------
You must create a class which extends CDVPlugin, in this class you can create all your function / action like this :

	- (void)open:(CDVInvokedUrlCommand*)command;

* __open__

 The name of the function / action

* __CDVInvokedUrlCommand__

 the command

command.arguments --> the parameters given by JavaScript

command.callbackId --> the callbackId to call.

To return the result to JavaScript :

	CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
	[self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];


Windows Phone 8
----------------------

You must create a class which extends BaseCommand and be inside the namespace WPCordovaClassLib.Cordova.Commands, in this class declare all your function / action like this:

	public void open(string options);

This function receive the call of javascript :

* __open__

 The name of the function / action

* __options__

 The parameters given by JavaScript
 

BlackBerry
----------------------

You must create a class which extends JSExt, in this class override the function execute :

	virtual std::string InvokeMethod(const std::string& command);

This function receive the call of javascript :

	size_t commandIndex = command.find_first_of(" ");
	std::string strCommand = command.substr(0, commandIndex);
	size_t callbackIndex = command.find_first_of(" ", commandIndex + 1);
	std::string callbackId = command.substr(commandIndex + 1, callbackIndex - commandIndex - 1);
	std::string arg = command.substr(callbackIndex + 1, command.length());

* __strCommand__

 the function / action to execute.
 
* __callbackId__

 this string can be used to return an async result.

* __arg__

	the paremeters given by JavaScript

Return the sync result to JavaScript by a return string of this funcion.


JavaScript
----------------------

### Android, iOS, Windows Phone 8

To call an function contained in your plugin, you must provide to the user an struct to call it easily.

_A Sample :_
	
cordova.exec(onSuccess, onError, "MBTilesPlugin", "open", [params]);

* __onSucess__

the function which receive a result of callback plugin --> function(result)

* __onError__

the function which receive an error of callback plugin --> function(error)

* __"MBTilesPlugin"__

the name of the plugin in file <plugin.xml>

* __"open"__

the action/function you call

* __[params]__

the parameters

### Blackberry

To call an function contained in your plugin, you must provide to the user an struct to call it easily.

_A Sample :_
	
	return cordova.exec(onSuccess, onError, "com.makina.offline.mbtiles", "open",  {input: input});

* __onSucess__

the function which receive a result of callback plugin --> function(result)

* __onError__

the function which receive an error of callback plugin --> function(error)

* __"com.makina.offline.mbtiles"__

the package name of the plugin 

* __"open"__

the action/function you call

* __{input: input}__

the parameters

Futhermore we need to create an another JavaScript file to plug the natif to the JavaScript, this file will be in src (index.js).

Initially declare all your function provides by your plugin like this :

	open: function (success, fail, args, env) {
		var result = new PluginResult(args, env),
		data = JSON.parse(decodeURIComponent(args.input)),
		response = <yourinstance>.getInstance().open(result.callbackId, data);
		result.ok(JSON.parse(response), false);
	},


Then declares a new struct JNEXT.yourplugin, in this struct load your library, this struc is your instance that you used before.

	JNEXT.MBTilesPlugin = function ()

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

To finish in this struct declare all your function must be used by your instance 

	// calls into InvokeMethod(string command) 
	self.open = function (callbackId, input) {
		return JNEXT.invoke(self.m_id, "open " + callbackId + " " + JSON.stringify(input));
	};


Feature 
======================

To use it :

	var mbTilesPlugin = new MBTilesPlugin();
	var type = "db";
	mbTilesPlugin.init({type: type}, function(result) {
		console.log("init : ");
	});





We will find in this plugin several features :

Glossary
----------------------

onSuccess --> function(result) {}

onError --> function(error) {}

init
----------------------

	_function(params, onSuccess, onError)_

### Description 

Open the database or save the workspace of file

### Parameters

__type__: 'file' or 'db'
__typepath__ : (optionnal) 'fullpath' or 'cdvfile'
__url__ : (optionnal) for path

To use the parameters typepath and url we need both !

For iOS the fullPath begin to the local directory of application


### Return

Nothing

open
----------------------

	_function(params, onSuccess, onError)_

### Description 

Open the database or save the workspace of file

### Parameters

__name__: name of database

### Return

Nothing

getMetadata
----------------------

	_function(onSuccess, onError)_

### Description 

Give the all metadata of the database or file

### Parameters

No Parameters

### Return

the metadata of the database or file

	{
		<name>: <value>,
		<name>: <value>,
		<name>: <value>,
		<name>: <value>,
		...,
		<name>: <value>
	}


getMinZoom
----------------------

	_function(onSuccess, onError)_

### Description 

Give the min zoom of the database or file

### Parameters

No Parameters

### Return

the min zoom in database or file

	{
		min_zoom: <value>
	}

getMaxZoom
----------------------

	_function(onSuccess, onError)_

### Description 

Give the max zoom of the database or file 

### Parameters

No Parameters

### Return

return the max zoom in the database or file

	{
		max_zoom: <value>
	}

getTile
----------------------

	_function(params, onSuccess, onError)_

### Description 

Give the data of tiles (z, x , y)

### Parameters

* __z__: zoom level

* __x__: colum

* __y__: row

### Return

The data of tiles in Base64.

	{
		tile_data: <value>
	}

executeStatement
----------------------

	_function(params, onSuccess, onError)_

### Description 

Can execute a query on database, and only database, this action is not implements for the type file

### Parameters

* __query__: the query to execute

* __params__: list of paremeters to bind ['param', 'param', 'param'] 

### Return

return the result of the query

	{
		result_execute: [
				{
					<name>: <value>,
					...,
					<name>: <value>
				},
				...,
				{
					<name>: <value>,
					...,
					<name>: <value>
				}
			]
			
		}
	}


getDirectoryWorking
----------------------

	_function(onSuccess, onError)_

### Description

Give the path of workspace of the database or file 

### Parameters

Nothing

### Return

the path of workspace of database/file

	{
		directory_working: <value>
	}

