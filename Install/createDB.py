#!/usr/bin/env python3

import sqlite3
import subprocess

db = sqlite3.connect("../DB/db.sqlite")
cursor = db.cursor()

cursor.execute('''CREATE TABLE Parameters
						(name text, value text)''')
cursor.execute('''CREATE TABLE Temperature
						(date integer, value real)''')
cursor.execute('''CREATE TABLE Humidity
						(date integer, value real)''')
cursor.execute('''CREATE TABLE Pressure
						(date integer, value real)''')
cursor.execute('''CREATE TABLE TimeZone
						(name text)''')
cursor.execute('''INSERT INTO Parameters VALUES 
					('name','SmartTimer'),
					('TZ', 'Asia/Yekaterinburg'),
					('TimerEn','0'),
					('TimerTime','0'),
					('MaxT', '35'),
					('MinT', '16'),
					('MaxH', '80'),
					('MinH', '30'),
					('MaxP', '740'),
					('MinP', '720')''')
pr = subprocess.Popen("timedatectl list-timezones", shell=True, stdout=subprocess.PIPE)
res = pr.communicate()[0].decode("utf-8").replace('\n','\n\r')
a = res.split()
for tz in a:
	cursor.execute("INSERT INTO TimeZone VALUES ('{}')".format(tz))

db.commit()
db.close()