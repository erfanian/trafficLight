trafficLight
============

Arduino code and a utility to control a homemade traffic light.

For build instructions see [my website.](http://www.ericerfanian.com/create-your-own-traffic-signal-status-lamp-with-adafruit-flora-neopixels-and-python)

The lamp is programmed to blink until it receives instructions over the serial connection.

The lamp will time out and blink again if it doesn't hear anything over serial for a half hour.

### Dependencies
Ubuntu:
```
sudo apt-get install python-serial
```

Arch:
```
sudo pacman -S python-pyserial
```

### Usage

To try the web_checker.py wrapper for the util:
```
python web_checker.py
```

The lamp should turn green if https://www.google.com returns 200 OK


To use the utility, try the help:
```
python trafficlight_util.py --help

usage: trafficlight_util.py [-h] --interface INTERFACE [--on] [--off]
                            [--reset] [--red] [--yellow] [--green] [--up_down]
                            [--fade]

A traffic light utility.

optional arguments:
  -h, --help            show this help message and exit
  --interface INTERFACE
                        The device interface, e.g. /dev/ttyACM0
  --on                  Turn on all the lights.
  --off                 Turn off all the lights.
  --reset               Reset the light to the initial state.
  --red                 Turn on the red light.
  --yellow              Turn on the yellow light.
  --green               Turn on the green light.
  --up_down             Cycle the lights up and down.
  --fade                Fade the lights up and down.
```