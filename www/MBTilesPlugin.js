/*
Declaration of the variable MBTilesPlugin to have acces to the plugin
*/
var MBTilesPlugin = function()
{
};

/*
function open
open the given database sqlite
params : {name : 'name of database', type : 'file' or 'db'}
return : success or error callback
*/
MBTilesPlugin.prototype.open = function(params, onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "open", [params]);
};

/*
function getMetadata
get the metadata of the database opened
return : success or error callback
*/
MBTilesPlugin.prototype.getMetadata = function(onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_metadata", []);
};

/*
function getMinZoom
get the min zoom of the database opened
return : success or error callback
*/
MBTilesPlugin.prototype.getMinZoom = function(onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_min_zoom", []);
};

/*
function getMaxZoom
get the max zoom of the database opened
return : success or error callback
*/
MBTilesPlugin.prototype.getMaxZoom = function(onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_max_zoom", []);
};

/*
function getTile
get tile in base 64 of the database opened with params
params : {z:'z', x:'x', y:'y'} // coord
return : success or error callback
*/
MBTilesPlugin.prototype.getTile = function(params, onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_tile", [params]);
};

/*
function executeStatment
execute query in the database opened
params : {query:'query', params:['param', 'param', 'param']} 
return : success or error callback
*/
MBTilesPlugin.prototype.executeStatment = function(params, onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "execute_statment", [params]);
};

/*
function getDirectoryWorking
get the directory path of working
params : {type:'type'} // db or file
return : success or error callback
*/
MBTilesPlugin.prototype.getDirectoryWorking = function(params, onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_directory_working", [params]);
};
	
module.exports = MBTilesPlugin;
