#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
MinH = cursor.execute("SELECT Value FROM Parameters WHERE name = 'MinH'").fetchone()
db.close()
res = json.dumps({'MinH':MinH[0]})
print("Content-type: application/json\n")
print(res)
