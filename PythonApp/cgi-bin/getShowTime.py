#!/usr/bin/env python3
import sys
import codecs
sys.stdout = codecs.getwriter("utf-8")(sys.stdout.detach())

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

cursor.execute("SELECT Value FROM Parameters WHERE name = 'showTime'")
status = int(cursor.fetchone()[0])
if(status):
	status = 'on'
else:
	status = 'off'
print("Content-type: application/json\n")
res = json.dumps({'timer':status})
print(res)
