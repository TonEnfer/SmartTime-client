#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
status = form.getfirst("status", '')

res = "error"
if(status == 'on'):
	status = 1
	query = "UPDATE Parameters SET value = {} WHERE name = 'showDate'".format(status)
	cursor.execute(query);
	db.commit()
	db.close()
	res = 'on'
elif(status == 'off'):
	status = 0
	query = "UPDATE Parameters SET value = {} WHERE name = 'showDate'".format(status)
	cursor.execute(query);
	db.commit()
	db.close()
	res = 'off'

res = json.dumps({"status":res})
print("Content-type: text/html\n")
print(res)
