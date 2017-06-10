#!/usr/bin/env python3

import os
import os.path
import sys 
import json

print("Content-type: text/html\n")
f = open('/etc/timezone',"r")
tzname =  f.read().replace('\n','')
Area,City = tzname.split('/')
res = json.dumps({'Area':Area,'City':City})
print(res)