#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
MinT = cursor.execute("SELECT Value FROM Parameters WHERE name = 'MinT'").fetchone()
db.close()
res = json.dumps({'MinT':MinT[0]})
print("Content-type: application/json\n")
print(res)
