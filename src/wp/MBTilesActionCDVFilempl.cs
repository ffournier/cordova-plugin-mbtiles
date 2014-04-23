using System;
using System.Text;
using MBTilesPlugin;
using FileEntry = WPCordovaClassLib.Cordova.Commands.File.FileEntry;


/// <summary>
/// the namespace of MBTilesPlugin </summary>
namespace MBTilesPlugin
{

    /// <summary>
    /// class MBTilesActionsCDVFileImpl</summary>
    class MBTilesActionsCDVFileImpl : MBTilesActionsGenDatabaseImpl
    {

        public MBTilesActionsCDVFileImpl(string url)
            : base()
        {
            if (url == null)
            {
                url = "cdvfile://localhost/persistent/tiles";
            }
            FileEntry entry = new FileEntry(url);
            directory = entry.FullPath;
        }
    }
}
