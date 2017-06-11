#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

form = cgi.FieldStorage()
status = form.getfirst("Status", '')

res = "error"
if(status == 'Enable'):
	status = 1
	query = "UPDATE Parameters SET value = {} WHERE name = 'TimerEn'".format(status)
	cursor.execute(query);
	db.commit()
	db.close()
	res = 'ok'
elif(status == 'Disable'):
	status = 0
	query = "UPDATE Parameters SET value = {} WHERE name = 'TimerEn'".format(status)
	cursor.execute(query);
	db.commit()
	db.close()
	res = 'ok'

res = json.dumps({"RESULT":res})
print("Content-type: text/html\n")
print(res)
