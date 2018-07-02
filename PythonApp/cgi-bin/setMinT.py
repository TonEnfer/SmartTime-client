#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
MinT = form.getfirst("MinT", '')

res = "error"
if(MinT != ''):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'MinT'".format(MinT)
	cursor.execute(query);
	res = MinT
	db.commit()
db.close()
res = json.dumps({"result":res})
print("Content-type: application/json\n")
print(res)
