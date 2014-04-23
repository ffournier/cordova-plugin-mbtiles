using System;
using System.Text;
using System.IO;
using MBTilesPlugin;


/// <summary>
/// the namespace of MBTilesPlugin </summary>
namespace MBTilesPlugin
{

    /// <summary>
    /// class MBTilesActionsDatabaseImpl</summary>
    class MBTilesActionsDatabaseImpl : MBTilesActionsGenDatabaseImpl
    {

        public MBTilesActionsDatabaseImpl()
            : base()
        {
            directory = Path.Combine(Windows.Storage.ApplicationData.Current.LocalFolder.Path, "tiles//");
        }
    }
}
