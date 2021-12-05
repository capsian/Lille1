#!/usr/bin/env python3
import sys
import random
import colorsys
from math import log, ceil

SCALE = 0.1
LEFT = 20
TOP = 70
RIGHT = 60
BOTTOM = 30

DETAILS = False

def hls_to_rgb(h,l,s):
    r, g, b = colorsys.hls_to_rgb(h, l, s)
    return "#{:02x}{:02x}{:02x}".format(int(255 * r), int(255 * g), int(255 * b))

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("USAGE: ./gantt.py [instance file] [scheduling file]")
        sys.exit(1)
    instance_filename = sys.argv[1]
    solution_filename = sys.argv[2]

    A = []
    SIZE = []
    T = []    
    with open(instance_filename, "r") as f:
        m = int(f.readline())
        n = int(f.readline())
        while True:
            line = f.readline()
            if not line:
                break
            a, size, t = line.split()
            A.append(int(a))
            SIZE.append(int(size))
            T.append(int(t))
    if len(A) != n:
        print("wrong number of tasks in instance (the header says {}, but there are {} in the body)".format(n, len(A)))
        sys.exit(1)

    D = []
    with open(solution_filename, "r") as f:
        i = 0
        while True:
            line = f.readline()
            if not line:
                break
            D.append(int(line))
            i += 1
    if i != n:
        print("wrong number of tasks in solution ({} in instance, {} in solution)".format(n, i))
    print("m={} machines and n={} tasks".format(m, n), file=sys.stderr)
    

    # validate and allocate machines
    R = {}
    events = [(D[i] + T[i], 'stop', i) for i in range(n)] + [(D[i], 'start', i) for i in range(n)]
    events.sort(key=lambda x: x[0])
    available = [True for j in range(m)]
    n_idle = m
    for (t, kind, i) in events:
        if kind == 'start':
            if D[i] < A[i]:
                print("Task {} starts at t={}, which is before its arrival date ({})".format(i, D[i], A[i]))
                sys.exit(1)
            if SIZE[i] > n_idle:
                print("Task {} scheduled at t={} and requires {} machines, but only {} are available".format(i, D[i], SIZE[i], idle))
                sys.exit(1)
            n_idle -= SIZE[i]
            R[i] = []
            for j in range(m):
                if len(R[i]) == SIZE[i]:
                    break
                if available[j]:
                    available[j] = False
                    R[i].append(j)
            assert len(R[i]) == SIZE[i]        
        if kind == 'stop':
            n_idle += SIZE[i]
            for j in R[i]:
                available[j] = True

    # render gantt diagram
    workspan = max([d + t for (d, t) in zip(D, T)])
    SCALE = 1000 / workspan
    gantt = []
    hue = []
    for i in range(n):
        hue.append(random.random())
        a = None
        b = None
        for j in R[i]:
            if b is None:
                a = j
                b = j+1
            else:
                if j == b:
                    b += 1
                else:
                    gantt.append((i, a, b, D[i], D[i] + T[i]))
                    a = j
                    b = j + 1
        if b is not None:
            gantt.append((i, a, b, D[i], D[i] + T[i]))
            

    print('<?xml version="1.0" standalone="no"?>')
    print('<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" ')
    print('     "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">')
    print('<svg xmlns="http://www.w3.org/2000/svg" width="{}" height="{}">'.format(SCALE * workspan + RIGHT + LEFT, 10*m + TOP + BOTTOM))

    # background
    print('<rect width="{w}" height="{h}" fill="white" />'.format(w=SCALE * workspan + RIGHT + LEFT, h=TOP + 10*m + TOP + BOTTOM))

    # machines number and horizontal blue lines
    for i in range(m):
        print('    <text x="{x}" y ="{y}" font-size="10" text-anchor="end" alignment-baseline="middle">{i}</text>'
                  .format(x=LEFT-2, y=TOP + 10*i + 8, i=i))
    if DETAILS:
        for i in range(m+1):
            print('    <line x1="{x}" y1="{y}" x2="{w}" y2="{y}" stroke="blue" stroke-width="0.5" />'
                     .format(x=LEFT, y=TOP + 10*i, w=LEFT + SCALE * workspan))

    # vetrical red lines and ticks
    if DETAILS:
        hticks = set()
        for i in range(n):
            hticks.add(D[i])
            hticks.add(D[i] + T[i])
        for t in sorted(hticks):
            print('    <line x1="{x}" y1="{y}" x2="{x}" y2="{h}" stroke="red" stroke-width="1" />'
                      .format(x=LEFT + SCALE*t, y=TOP - 10, h=TOP + 10 * m))
            print('    <text fill="red"  x="{x}" y="{y}" text-anchor="start" transform="rotate(-60 {x},{y})" alignment-baseline="middle">{t}</text>'
                      .format(x=LEFT + SCALE*t, y=TOP-13, t=t))

    for (i, a, b, d, f) in gantt:
            print('  <g>')
            print('    <rect x="{x}" y ="{y}" width="{w}" height="{h}" fill="{fill}" stroke="#000000" stroke-width="1" />'
                  .format(x=LEFT + SCALE * d, y=TOP + 10 * a, h=10 * (b - a), w=SCALE * (f - d), fill=hls_to_rgb(hue[i], 0.75, 0.75)))
            if SCALE * (f - d) > 5 * ceil(log(i+1, 10)):
                size = 10
                if SCALE * (f - d) > 10 * ceil(log(i+1, 10)):
                    size = 20
                print('    <text x="{x}" y ="{y}" font-size="{size}" text-anchor="middle" alignment-baseline="middle">{i}</text>'
                      .format(x=LEFT + SCALE * (d + f) / 2, y=TOP + 5 * (a + b) + 3, i=i, size=size))
            print('  </g>')
    print('</svg>')
    
    score = 0
    for i in range(n):
        score += D[i] - A[i]
    print("Score = {:,}".format(score), file=sys.stderr)
