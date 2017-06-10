#!/usr/bin/env python3

import os
import os.path
import sys 
import json


def main(argv):
	tzname = os.environ.get('TZ')
	print("Content-type: text/html")
	res = "none"
	if tzname:
		res = json.dumps({'TZ':tzname})
		print(res)
	elif os.path.exists('/etc/timezone'):
		f = open('/etc/timezone',"r")
		tzname =  f.read()
		res = json.dumps({'TZ':tzname})
		print(res)
	else:
		print("res)
		sys.exit(1)
	#res = "1"#json.dumps(({'TZ':"none"})
	


if __name__ == '__main__':
	main(sys.argv)