#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
MaxT = cursor.execute("SELECT Value FROM Parameters WHERE name = 'MaxT'").fetchone()
db.close()
res = json.dumps({'MaxT':MaxT[0]})
print("Content-type: application/json\n")
print(res)
