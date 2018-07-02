#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
MaxH = form.getfirst("MaxH", '')

res = "error"
if(MaxH != ''):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'MaxH'".format(MaxH)
	cursor.execute(query);
	res = MaxH
	db.commit()
db.close()
res = json.dumps({"result":res})
print("Content-type: application/json\n")
print(res)
