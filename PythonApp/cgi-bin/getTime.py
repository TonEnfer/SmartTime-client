#!/usr/bin/env python3

import json
import sqlite3
import datetime

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
tz = cursor.execute('select value from Parameters where name = "TZ"').fetchall()[0][0]
offset = int(cursor.execute('select offset from TimeZone where name = "{}"'.format(tz)).fetchall()[0][0])
db.close()
h = abs(offset/100)
m = abs(offset%100)
sign = 1 if (offset>0) else -1

fmt = "%H:%M"
dt = datetime.datetime.utcnow()
time = (dt + sign*(datetime.timedelta(hours=h,minutes=m))).time()
time = time.strftime(fmt)
print("Content-type: application/json\n")
res = json.dumps({'time':time})
print(res)

