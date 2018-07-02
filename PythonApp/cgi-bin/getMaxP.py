#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
MaxP = cursor.execute("SELECT Value FROM Parameters WHERE name = 'MaxP'").fetchone()
db.close()
res = json.dumps({'MaxP':MaxP[0]})
print("Content-type: application/json\n")
print(res)
