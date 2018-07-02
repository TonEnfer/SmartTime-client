#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
MinH = cursor.execute("select value from Temperature where date = (select max(date) from Temperature) LIMIT 1").fetchone()
db.close()
res = json.dumps({'temperature':MinH[0]})
print("Content-type: application/json\n")
print(res)
