#!/usr/bin/env python3
import json
import subprocess

#args = .split()
print("Content-type: text/html\n")
pr = subprocess.Popen("timedatectl list-timezones", shell=True, stdout=subprocess.PIPE)
res = pr.communicate()[0].decode("utf-8").replace('\n','\n\r')
a = res.split()
b = '{TZ : ['
for i in a:
	 b += ("\"" + i + "\", ")
b = b[:-2] + "] }"
print(b)
