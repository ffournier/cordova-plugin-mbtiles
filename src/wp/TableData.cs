using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// the namespace of MBTilesPlugin </summary>
namespace MBTilesPlugin
{
    public class metadata
    {
        public string name { get; set; }

        public string value { get; set; }

    }

    public class tiles
    {
        public int zoom_level { get; set; }

        public int tile_column { get; set; }

        public int tile_row { get; set; }

        public byte[] tile_data { get; set; }

    }

}
