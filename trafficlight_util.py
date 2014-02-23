#!/usr/bin/python2.7

"""A small utility to control the traffic light from the command line."""

import argparse
import serial

parser = argparse.ArgumentParser(description='A traffic light utility.')
parser.add_argument('--interface', dest='interface', required=True,
                    help='The device interface, e.g. /dev/ttyACM0')
parser.add_argument('--on', action='store_true', dest='on',
                    help='Turn on all the lights.')
parser.add_argument('--off', action='store_true', dest='off',
                     help='Turn off all the lights.')
parser.add_argument('--reset', action='store_true', dest='reset',
                    help='Reset the light to the initial state.')
parser.add_argument('--red', action='store_true', dest='red',
                    help='Turn on the red light.')
parser.add_argument('--yellow', action='store_true', dest='yellow',
                    help='Turn on the yellow light.')
parser.add_argument('--green', action='store_true', dest='green',
                    help='Turn on the green light.')
parser.add_argument('--up_down', action='store_true', dest='up_down',
                    help='Cycle the lights up and down.')
parser.add_argument('--fade', action='store_true', dest='fade',
                    help='Fade the lights up and down.')

class TrafficCommandsToSerial():
  def __init__(self, args):
    """The internal init method:

    Args:
      args (ArgumentParser) - A set of runtime arguments.
    """
    self._traffic_args = [0, 0, 0, 0, 0, 0, 0]
    self._send_string = ""

    if args.on:
      self._traffic_args[0] = 1

    if args.off:
      self._traffic_args[1] = 1

    if args.red:
      self._traffic_args[2] = 1

    if args.yellow:
      self._traffic_args[3] = 1

    if args.green:
      self._traffic_args[4] = 1

    if args.up_down:
      self._traffic_args[5] = 1

    if args.fade:
      self._traffic_args[6] = 1

    for arg in self._traffic_args:
      self._send_string += str(arg)

  def GetSerialString(self):
    """A method to return the internal serial string."""
    return self._send_string

if __name__ == '__main__':
  args = parser.parse_args()
  command = TrafficCommandsToSerial(args)
  try:
    conn = serial.Serial(args.interface, 9600)
    conn.write(command.GetSerialString())
  except serial.serialutil.SerialException:
    print("Could not connect to the light.")
