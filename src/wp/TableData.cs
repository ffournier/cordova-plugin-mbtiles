using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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

    public class sqlite_stat1
    {
        public string tbl { get; set; }

        public string idx { get; set; }

    }

   
}
