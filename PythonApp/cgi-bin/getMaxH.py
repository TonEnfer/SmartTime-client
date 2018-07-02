#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
MaxH = cursor.execute("SELECT Value FROM Parameters WHERE name = 'MaxH'").fetchone()
db.close()
res = json.dumps({'MaxH':MaxH[0]})
print("Content-type: application/json\n")
print(res)
