#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
print("Content-type: text/html\n")
cursor.execute("SELECT Value FROM Parameters WHERE name = 'TZ'")
tzname = cursor.fetchone()

res = json.dumps({'TZ':tzname[0]})
print(res)
