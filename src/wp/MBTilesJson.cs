using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

/// <summary>
/// the namespace of MBTilesPlugin </summary>
namespace MBTilesPlugin
{

    [DataContract]
    public class tiles_output
    {
        [DataMember(Name = "tile_data")]
        public string tile_data { get; set; }

        public tiles_output(string data)
        {
            tile_data = data;
        }

    }

    
    [DataContract]
    public class minzoom_output
    {
        [DataMember(Name = "min_zoom")]
        public int value { get; set; }

        public minzoom_output(int value)
        {
            this.value = value;
        }
    }

    [DataContract]
    public class maxzoom_output
    {

        [DataMember(Name = "max_zoom")]
        public int value { get; set; }

        public maxzoom_output(int value)
        {
            this.value = value;
        }
    }

    [DataContract]
    public class directory_working_output
    {
        [DataMember(Name = "directory_working")]
        public string directory_working { get; set; }

        public directory_working_output(string data)
        {
            directory_working = data;
        }

    }

    [DataContract]
    public class EntryInit
    {
        [DataMember(Name = "type")]
        public string type { get; set; }

        [DataMember(Name = "typepath")]
        public string typepath { get; set; }

        [DataMember(Name = "url")]
        public string url { get; set; }
    }

    [DataContract]
    public class EntryOpen
    {
        [DataMember(Name = "name")]
        public string name { get; set; }
    }

    [DataContract]
    public class EntryTile
    {
        [DataMember(Name = "z")]
        public int z { get; set; }

        [DataMember(Name = "x")]
        public int x { get; set; }

        [DataMember(Name = "y")]
        public int y { get; set; }
    }

    [DataContract]
    public class EntryExecuteStatement
    {
        [DataMember(Name = "query")]
        public string query { get; set; }

        [DataMember(Name = "params")]
        public List<object> param { get; set; }

    }
}
