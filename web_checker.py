#!/bin/python2.7

"""A simple python script to get the status of a website, and then change the
status of the traffic light."""

import subprocess
import urllib

url = urllib.urlopen('https://www.google.com/')
status = url.getcode()
interface = '/dev/ttyACM0'

if status == 200:
  subprocess.call('python2.7 trafficlight_util.py --interface %s --green'
                  % interface, shell=True)
else:
  subprocess.call('python2.7 trafficlight_util.py --interface %s --red'
                  % interface, shell=True)

