var onDeviceReady = function() {
	
	var localFileName = 'tiles-ign.mbtiles';
    	var remoteFile = 'http://cg44.makina-corpus.net/tmp/POSOW-19.04.2012.mbtiles';
	
    
	resizeMap();

	$(window).resize(function() {
		console.log("resize");

		resizeMap();
	});

	console.log("verifyingMap");
	verifyingMap(localFileName, remoteFile);
	//buildMap();

};

function initMapPage() {
	console.log("initMapPage");
	document.addEventListener("deviceready", onDeviceReady, true);
}

function resizeMap() {
	console.log("resizeMap");

	var mapHeight = $(window).height();
	var mapWidth = $(window).width();
	$("#map").height(mapHeight);
	$("#map").width(mapWidth);
}

function buildMap() {
	console.log("buildMap");


	var name = "tiles-ign.mbtiles";
	var type = "db";
	console.log("before MBTilesPlugin ");
	var mbTilesPlugin = new MBTilesPlugin();
	console.log("after MBTilesPlugin ");
	
	var query ="SELECT * FROM metadata WHERE rowid = ?1";
	var params = new Array();
	params[0] = "1";

	mbTilesPlugin.init({type: type}, function(rinit) {

		mbTilesPlugin.getDirectoryWorking(function(r) {
				console.log("getDirectoryWorking : " + r.directory_working);
			}, function(e) {
				console.log("getDirectoryWorking error: " + JSON.stringify(e));
			});

		mbTilesPlugin.open({name: name},
				function(r) {
					console.log("open : " + r);

					mbTilesPlugin.executeStatement({query: query, params: params},
								function(result)
								{
									console.log("executeStatement : " + JSON.stringify(result));
								},
								function(error)
								{
									console.log("executeStatement Error " + JSON.stringify(error));
								});

					mbTilesPlugin.getMinZoom(function(result) {
					console.log("getMinZoom --" + result + "--");

						mbTilesPlugin.getMetadata(function(result) {
							console.log("getMetadata");

							var metadatacenter = result.center;

							var res = metadatacenter.split(",");

							var map = new L.Map("map", {
								center : [res[1],res[0]],//tozeur

								zoom : res[2],
								attributionControl: false

						});
						console.log("MBTilesPlugin");
						var layer = new L.TileLayer.MBTilesPlugin(mbTilesPlugin,{
							tms:true,
							zoom: result.min_zoom,
							maxZoom : result.max_zoom,
							zoomOffset:0
						}, function(temp) {
							console.log("TileLayer initalized");
							console.log(temp);
							map.addLayer(temp);
							console.log("TileLayer initalized2");
						});
						console.log("MAP CENTER POINT " + JSON.stringify(map.latLngToLayerPoint(new L.LatLng(38.89611,-77.035446))));
					});
				}, function(e) {
					console.log("err : " + JSON.stringify(e));
				});
				}, function(e) {
					console.log("open failed : " + JSON.stringify(e));


				});
	}, function(e) {
		console.log("init failed : " + JSON.stringify(e));


	});
}

function toggle_visibility(id) {
	var e = document.getElementById(id);
	if (e.style.display == 'block') {
		console.log("change in non");
		e.style.display = 'none';	
	} else {
		console.log("change in block");
		e.style.display = 'block';
	}
}

function changevalue(newval) {
	console.log(newval);
	document.getElementById('progBar').value = newval * 100;
}

function verifyingMap(localFileName, remoteFile){
	
	var fs;				// file system object
	var ft;				// TileTransfer object
	var type = "db";
	
	window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, function (fileSystem) {
		console.log('file system retrieved.');
		fs = fileSystem;

		var mbTilesPlugin = new MBTilesPlugin();
		mbTilesPlugin.isSDCard(function(rsd) {
				console.log("sdcard present");
			}, function(esd) {
				console.log("sdcard not present");
			}
		);

		console.log("after MBTilesPlugin ");
		mbTilesPlugin.init({type: type}, function(rinit) {
			mbTilesPlugin.getDirectoryWorking(function(r) {
				console.log("getDirectoryWorking Verify : " + r.directory_working);
				var absoluteLocalFileName = r.directory_working + localFileName;

				console.log(absoluteLocalFileName);
				// check to see if files already exists
				var file = fs.root.getFile(absoluteLocalFileName, null, function (fileEntry) {
					// file exists
					console.log('exists, or not...');
					console.log(fileEntry);

					buildMap();
				}, function () {
					// file does not exist
					console.log('does not exist');


					console.log('downloading sqlite file...');
					ft = new FileTransfer();
					var loadingStatus;
					ft.onprogress = function(progressEvent) {
					    if (progressEvent.lengthComputable) {
					      loadingStatus = progressEvent.loaded / progressEvent.total;
					      //console.log(progressEvent.loaded / progressEvent.total);
					      changevalue(loadingStatus);
					    } else {
					      //loadingStatus.increment();
					      console.log("+1");
					    }

					};
					toggle_visibility('progBar');
					
					console.log('platform : ' + cordova.platformId);
					if (cordova.platformId === "blackberry10") {
						console.log('pass platformId BB10');
						// need to add file:// for the plugin blackberry, so bad :/
						absoluteLocalFileName = "file://" + absoluteLocalFileName;
					    
						new DirManager().create_r( r.directory_working, Log('create sucessfully'));
					} else if (cordova.platformId === "ios") {
						absoluteLocalFileName = "cdvfile://localhost/persistent/" + absoluteLocalFileName;
					} else if (cordova.platformId === "windowsphone") {
						console.log('pass platformId WP8');
						new DirManager().create_r( r.directory_working, Log('create sucessfully'));
					}
					ft.download(remoteFile, absoluteLocalFileName, function (entry) {
						toggle_visibility('progBar');
						console.log('download complete: ' + entry.fullPath);
						buildMap();

					}, function (error) {
						console.log('error with download', error);
						toggle_visibility('progBar');
						navigator.notification.confirm(
							'You are the winner!',  // message
							onConfirm(button),              // callback to invoke with index of button pressed
							'Game Over',            // title
							'Retry,Cancel'          // buttonLabels
						    );
					});
				});

			}, function(edir) {
				console.log('error with dir', edir);
			});
		}, function(einit) {
			console.log('error with init', einit);
		});
	});
	
	function onConfirm(button){
		
		console.log('You selected button ' + buttonIndex);

	}
	

	function logButton(){
		
		console.log('You selected button');

	}
	
	
	
}
