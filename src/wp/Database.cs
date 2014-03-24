using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SQLite;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Sqlite3Statement = Sqlite.Statement;

namespace MBTilesPlugin
{
    class Database : SQLiteConnection
    {
        private Sqlite3Statement stmt = null;

        public Database(string path)
            : base(path)
        {
        }

        public JArray execute(String query, object[] param) {
            JArray array = new JArray();
            if (query != null && query.Length > 0)
            {
                stmt = SQLite3.Prepare2(this.Handle, query);
                if (stmt != null)
                {
                    if (param != null && param.Length > 0)
                    {
                        for (int i = 1; i <= param.Length; i++)
                        {
                            bindValue(param.GetValue(), i);
                        }
                    }

                    while (SQLite3.Step(stmt) == SQLite3.Result.Row)
                    {
                        int count = SQLite3.ColumnCount(stmt);
                        JObject obj = new JObject();
                        for (int i = 0; i < count; i++)
                        {
                            string name = SQLite3.ColumnName(stmt, i);
                            SQLite3.ColType colType = SQLite3.ColumnType(stmt, i);
                            switch (colType)
                            {
                                case SQLite3.ColType.Blob:
                                    byte[] bytes = SQLite3.ColumnByteArray(stmt, i);
                                    obj.Add(name, bytes);
                                    break;
                                case SQLite3.ColType.Integer:
                                    int intValue = SQLite3.ColumnInt(stmt, i);
                                    obj.Add(name, intValue);
                                    break;
                                case SQLite3.ColType.Float:
                                    double doubleValue = SQLite3.ColumnDouble(stmt, i);
                                    obj.Add(name, doubleValue);
                                    break;
                                case SQLite3.ColType.Text:
                                    string text = SQLite3.ColumnString(stmt, i);
                                    obj.Add(name, text);
                                    break;
                                case SQLite3.ColType.Null:
                                default:
                                    obj.Add(name, null);
                                    break;
                            }
                        }
                        array.Add(obj);
                    }

                }
                SQLite3.Finalize(stmt);
            }
            return array;
        }

        private bool bindValue(object value, int index) {
            if (value == null) {
				SQLite3.BindNull (stmt, index);
			} else {
				if (value is Int32) {
					SQLite3.BindInt (stmt, index, (int)value);
				} else if (value is String) {
					SQLite3.BindText (stmt, index, (string)value, -1, new IntPtr (-1));
				} else if (value is Byte || value is UInt16 || value is SByte || value is Int16) {
					SQLite3.BindInt (stmt, index, Convert.ToInt32 (value));
				} else if (value is Boolean) {
					SQLite3.BindInt (stmt, index, (bool)value ? 1 : 0);
				} else if (value is UInt32 || value is Int64) {
					SQLite3.BindInt64 (stmt, index, Convert.ToInt64 (value));
				} else if (value is Single || value is Double || value is Decimal) {
					SQLite3.BindDouble (stmt, index, Convert.ToDouble (value));
				} else if (value is DateTime) {
					SQLite3.BindText (stmt, index, ((DateTime)value).ToString ("yyyy-MM-dd HH:mm:ss"), -1, new IntPtr (-1));
#if !NETFX_CORE
				} else if (value.GetType().IsEnum) {
#else
				} else if (value.GetType().GetTypeInfo().IsEnum) {
#endif
					SQLite3.BindInt (stmt, index, Convert.ToInt32 (value));
                } else if (value is byte[]){
                    SQLite3.BindBlob(stmt, index, (byte[]) value, ((byte[]) value).Length, new IntPtr (-1));
                } else if (value is Guid) {
                    SQLite3.BindText(stmt, index, ((Guid)value).ToString(), 72, new IntPtr (-1));
                } else {
                    throw new NotSupportedException("Cannot store type: " + value.GetType());
                }
			}
            return true;
        }
    }
}
