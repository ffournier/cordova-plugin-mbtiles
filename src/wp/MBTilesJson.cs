using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

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
    public class metadata_output
    {
        [DataMember(Name = "center")]
        public string center { get; set; }

        [DataMember(Name = "format")]
        public string format { get; set; }

        [DataMember(Name = "minzoom")]
        public string minzoom { get; set; }

        [DataMember(Name = "bounds")]
        public string bounds { get; set; }

        [DataMember(Name = "maxzoom")]
        public string maxzoom { get; set; }

        [DataMember(Name = "template")]
        public string template { get; set; }

        [DataMember(Name = "name")]
        public string name { get; set; }

        [DataMember(Name = "version")]
        public string version { get; set; }

        public metadata_output()
        {
            center = null;
            format = null;
            bounds = null;
            maxzoom = null;
            minzoom = null;
            template = null;
            name = null;
            version = null;
        }

        public void setValue(metadata data)
        {
            if (data != null)
            {
                if (data.name != null && data.name.Equals("center"))
                {
                    center = data.value;
                }
                else if (data.name != null && data.name.Equals("bounds"))
                {
                    bounds = data.value;
                }
                else if (data.name != null && data.name.Equals("maxzoom"))
                {
                    maxzoom = data.value;
                }
                else if (data.name != null && data.name.Equals("minzoom"))
                {
                    minzoom = data.value;
                }
                else if (data.name != null && data.name.Equals("format"))
                {
                    format = data.value;
                }
                else if (data.name != null && data.name.Equals("template"))
                {
                    template = data.value;
                }
                else if (data.name != null && data.name.Equals("name"))
                {
                    name = data.value;
                }
                else if (data.name != null && data.name.Equals("version"))
                {
                    version = data.value;
                }
            }
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
    public class EntryOpen
    {
        [DataMember(Name = "name")]
        public string name { get; set; }

        [DataMember(Name = "type")]
        public string type { get; set; }
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
}
