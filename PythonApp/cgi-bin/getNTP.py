#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
ntp = cursor.execute("SELECT Value FROM Parameters WHERE name = 'NTP'").fetchone()
db.close()
res = json.dumps({'ntp':ntp[0]})
print("Content-type: application/json\n")
print(res)
