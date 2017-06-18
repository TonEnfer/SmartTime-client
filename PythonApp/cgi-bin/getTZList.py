#!/usr/bin/env python3

import json
import sqlite3
import os
print("Content-type: text/html\n")
#print(os.getcwd());
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

tznames = [str(i)[2:-3] for i in cursor.execute("SELECT name FROM TimeZone")]
# = cursor.fetchone()
#print(tzname)
res = '{"tz" : ['
for tz in tznames:
	res += ("\"" + tz + "\", ")
res = res[:-2] + "] }"
#res = json.dumps({'TZ':tzname})

print(res)

#db.close()
