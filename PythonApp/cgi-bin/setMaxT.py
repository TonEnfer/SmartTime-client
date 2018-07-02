#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
MaxT = form.getfirst("MaxT", '')

res = "error"
if(MaxT != ''):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'MaxT'".format(MaxT)
	cursor.execute(query);
	res = MaxT
	db.commit()
db.close()
res = json.dumps({"result":res})
print("Content-type: application/json\n")
print(res)
