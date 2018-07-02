#!/usr/bin/env python3

import json
import sqlite3
from datetime import datetime
from pytz import timezone

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()
tz = cursor.execute('select value from Parameters where name = "TZ"').fetchall()[0][0]
db.close()
tz = timezone(tz)
fmt = "%H:%M"
dt = datetime.now(tz)
time = dt.astimezone(tz)
time = time.strftime(fmt)
print("Content-type: application/json\n")
res = json.dumps({'time':time})
print(res)

