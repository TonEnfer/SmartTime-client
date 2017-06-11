#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
print("Content-type: text/html\n")
cursor.execute("SELECT Value FROM Parameters WHERE name = 'TimerEn'")
status = int(cursor.fetchone()[0])
if(status):
	status = 'Enable'
else:
	status = 'Disable'
res = json.dumps({'Timer':status})
print(res)
