My solutions of tasks in [Advent of Code](http://adventofcode.com), a set of
programming exercises suitable for beginners (at least the first week or two),
learning new languages or remembering those you've forgot.

### 2016

I first implemented solutions in Python to find the correct answer and sometimes already to prototype the C-style solutions. Next I implemented the solution in C. Both serve mostly as preparation for the solution on Arduino.

### 2016 - Arduino

I challenged myself to solve the AoC on Arduino.

I used a 7-segment LED display with 8-digits, except for tasks that output text, where I used a two-line LCD display. Both are connected to the usual pins. A speaker for sound effects is connected to pin 2.

For most tasks, the input is fed via USB using different speeds that depend on how fast the Arduino can handle it, given the amount of processing it does on the fly. See `Serial.begin(speed)`.

I added `.` at the end of most inputs since this is the only way to tell Arduino that the input is finished.

I posted videos of Arduino solving tasks to [YouTube channel](https://www.youtube.com/playlist?list=PLm-JYoU3uw-aIWvjuzHk2KOQSjLQT6Ac-).

### 2015

I started in several languages but didn't have time to proceed like this, so
most solutions are in Python. Some are interesting, though.
See [Spherical horses in bash](https://github.com/janezd/advent-of-code/blob/master/2015/03%20Spherical%20horses/solution.sh) or some [nice solutions of Some Assembly Required](https://github.com/janezd/advent-of-code/tree/master/2015/07%20Some%20Assembly%20Required),
for example.

Tasks include some NP-complete problems and other problems. No smart solutions
here, just pure brute force with minor optimizations. It is amazing how short
these solutions can be in Python, and how they still run fast enough.
