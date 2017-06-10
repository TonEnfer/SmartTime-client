#!/usr/bin/env python3

import os
import os.path
import json

print("Content-type: text/html\n")
f = open('/etc/timezone',"r")
tzname =  f.read().replace('\n','')
res = json.dumps({'TZ':tzname})
print(res)
