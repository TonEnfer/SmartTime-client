#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
print("Content-type: text/html\n")
cursor.execute("SELECT Value FROM Parameters WHERE name = 'TimerTime'")
status = int(cursor.fetchone()[0])
res = json.dumps({'Time':status})
print(res)
