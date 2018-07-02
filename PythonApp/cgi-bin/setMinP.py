#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
MinP = form.getfirst("MinP", '')

res = "error"
if(MinP != ''):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'MinP'".format(MinP)
	cursor.execute(query);
	res = MinP
	db.commit()
db.close()
res = json.dumps({"result":res})
print("Content-type: application/json\n")
print(res)
