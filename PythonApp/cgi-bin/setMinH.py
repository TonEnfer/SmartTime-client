#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
MinH = form.getfirst("MinH", '')

res = "error"
if(MinH != ''):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'MinH'".format(MinH)
	cursor.execute(query);
	res = MinH
	db.commit()
db.close()
res = json.dumps({"result":res})
print("Content-type: application/json\n")
print(res)
