import sys, os

day, part = map(int, sys.argv[1:3])
overwrite = True
if len(sys.argv) > 3:
    overwrite = False
fifth = (day-1) // 5
folder = f"{fifth*5+1:02}-{(fifth+1)*5:02}"

os.system(f"runcpp {folder}/{day:02}-{part}.cpp < {folder}/{day:02}.in")
if part == 1 and overwrite:
    open(f"{folder}/{day:02}-2.cpp", "w").write(open(f"{folder}/{day:02}-1.cpp", "r").read())