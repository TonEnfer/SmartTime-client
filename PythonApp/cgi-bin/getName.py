#!/usr/bin/env python3

import json
import sqlite3
db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
print("Content-type: text/html\n")
cursor.execute("SELECT Value FROM Parameters WHERE name = 'name'")
name = cursor.fetchone()

res = json.dumps({'name':name[0]})
print(res)
