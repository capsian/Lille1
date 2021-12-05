#!/usr/bin/python3

import os


print("EUID: " + str(os.geteuid()))
print("EGID: " + str(os.getegid()))

