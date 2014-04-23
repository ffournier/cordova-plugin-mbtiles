using System;
using System.Text;
using MBTilesPlugin;
using System.Collections.Generic;


/// <summary>
/// the namespace of MBTilesPlugin </summary>
namespace MBTilesPlugin
{

    /// <summary>
    /// class MBTilesActionsDatabaseImpl</summary>
    abstract class MBTilesActionsGenImpl : IMBTilesActions
    {

        protected string directory = null;

        public MBTilesActionsGenImpl()
            : base()
        {
            directory = null;
        }
	
	    protected string getDirectory()
	    {
            return directory;
	    }

        public abstract void open(string name);

        public abstract bool isOpen();

        public abstract void close();

        public abstract string getMetadata();

        public abstract minzoom_output getMinZoom();

        public abstract maxzoom_output getMaxZoom();

        public abstract tiles_output getTile(int zoomLevel, int column, int row);

        public abstract string executeStatement(String query, List<object> param);

        public abstract directory_working_output getDirectoryWorking();
    }
}
