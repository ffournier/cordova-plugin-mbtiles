var MBTilesPlugin = function()
{
};

MBTilesPlugin.prototype.open = function(params, onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "open", [params]);
};

MBTilesPlugin.prototype.getMetadata = function(onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_metadata", []);
};

MBTilesPlugin.prototype.getMinZoom = function(onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_min_zoom", []);
};

MBTilesPlugin.prototype.getMaxZoom = function(onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_max_zoom", []);
};

MBTilesPlugin.prototype.getTile = function(params, onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "get_tile", [params]);
};

MBTilesPlugin.prototype.getTile = function(params, onSuccess, onError)
{
	return cordova.exec(onSuccess, onError, "MBTilesPlugin", "execute_statment", [params]);
};
	
module.exports = MBTilesPlugin;
