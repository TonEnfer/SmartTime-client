#!/usr/bin/env python3

import cgi
import json
import sqlite3

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()


form = cgi.FieldStorage()
time = form.getfirst("Time", '')
def isint(s):
    try:
        int(s)
        return True
    except ValueError:
        return False
res = "error"
if(time != '' and isint(time) and int(time) >= 0):
	query = "UPDATE Parameters SET value = '{}' WHERE name = 'TimerTime'".format(time)
	cursor.execute(query);
	db.commit()
	db.close()
	res = 'ok'

res = json.dumps({"RESULT":res})
print("Content-type: text/html\n")
print(res)
