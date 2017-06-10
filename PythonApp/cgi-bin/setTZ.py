#!/usr/bin/env python3

import os
import os.path
import cgi
import json

form = cgi.FieldStorage()
TZ = form.getfirst("TZ", '')
res = "ERROR"
if(TZ != ''):
	f = open('/etc/timezone',"w")
	f = TZ
	res = "OK"

res = json.dumps({"RESULT":res})
print("Content-type: text/html\n")
print(res)
