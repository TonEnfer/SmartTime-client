#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
TZ = form.getfirst("tz", '')

res = "error"
if(TZ != ''):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'TZ'".format(TZ)
	cursor.execute(query);
	#res = TZ
db.commit()
db.close()
res = json.dumps({"result":TZ})
print("Content-type: application/json\n")
print(res)
