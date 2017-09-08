#!/usr/bin/env python3

import sqlite3
import datetime
import subprocess
from subprocess import *

def getTime():
	db = sqlite3.connect("../DB/db.sqlite")
	cursor = db.cursor()
	tz = cursor.execute('select value from Parameters where name = "TZ"').fetchall()[0][0]
	offset = int(cursor.execute('select offset from TimeZone where name = "{}"'.format(tz)).fetchall()[0][0])
	db.close()

	h = abs(offset/100)
	m = abs(offset%100)
	sign = 1 if (offset>0) else -1

	fmt = "%H:%M:%S"
	dt = datetime.datetime.utcnow()
	time = (dt + sign*(datetime.timedelta(hours=h,minutes=m))).time()
	time = time.strftime(fmt)
	return time  

def main():
	proc = Popen(["../NativeApp/DisplayData/DisplayData","0","{}".format(getTime())], stdout=PIPE);
	#safeprint(proc.communicate()[0].decode('cp1251'))
	
if __name__ == "__main__":
    # execute only if run as a script
    main()