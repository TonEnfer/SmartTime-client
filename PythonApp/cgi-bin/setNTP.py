#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
NTP = form.getfirst("ntp", '')

res = "error"
if(NTP != ''):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'NTP'".format(NTP)
	cursor.execute(query);
	res = NTP
	db.commit()
db.close()
res = json.dumps({"result":res})
print("Content-type: application/json\n")
print(res)
