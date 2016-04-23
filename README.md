# Water Heater Monitor

A program for the [Particle][] Photon that monitors the status of my water
heater and reminds me to switch it off in time.

If the heater continues to be on after a specified amount of time has elapsed,
it broadcasts an event that gets picked up by an [IFTTT][] recipe, which in
turn sends a push notification to my phone. It also blinks the Photon's onboard
LED in case I miss the notification for some reason.

Here is a picture of the first version of the device all wired up:

![Water Heater Monitor mounted on the switch](https://lh3.googleusercontent.com/-0sTzhfV3iEs/VxuszwkHb2I/AAAAAAAACGI/xpZ8f8aD4EkLCHnwqS6jJ6jh5lB6mYargCCo/s512/water-heater-monitor.jpg)

[Particle]: https://www.particle.io/
[IFTTT]: https://ifttt.com/
