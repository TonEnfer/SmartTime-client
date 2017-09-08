#!/usr/bin/env python3

import sqlite3
import subprocess
import pytz
import datetime

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
						(name text, offset text)''')
cursor.execute('''INSERT INTO Parameters VALUES 
					('showTime','0'),
					('showDate','0'),
					('showPress','0'),
					('showTemp',0),
					('showHum','0'),
					('name','SmartTimer'),
					('TZ', 'Asia/Yekaterinburg'),
					('Time','0'),
					('TimerEn','0'),
					('TimerTime','0'),
					('MaxT', '35'),
					('MinT', '16'),
					('MaxH', '80'),
					('MinH', '30'),
					('MaxP', '740'),
					('MinP', '720'),
					('NTP', '0.europe.pool.ntp.org')''')
tzs = [(item, datetime.datetime.now(pytz.timezone(item)).strftime('%z')) for item in pytz.common_timezones]
for tz in tzs:
	cursor.execute("INSERT INTO TimeZone VALUES ('{name}','{offset}')".format(name = tz[0], offset = tz[1]))

db.commit()
db.close()