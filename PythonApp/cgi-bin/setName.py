#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
name = form.getfirst("Name", '')

res = "error"
if(name != ''):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'name'".format(name)
	cursor.execute(query);
	#res = TZ
db.commit()
db.close()
res = json.dumps({"RESULT":name})
print("Content-type: text/html\n")
print(res)
