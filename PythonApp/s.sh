#!/bin/bash

while :; do sleep 1; flock -n /tmp/lock15 -c /var/www/smartTime/PythonApp/main.py & done