import sys, os
import subprocess
from markdownify import markdownify
from bs4 import BeautifulSoup

template = """#include "../template.hpp"

int main() {

}
"""

day = int(sys.argv[1])
fifth = (day-1) // 5
folder = f"{fifth*5+1:02}-{(fifth+1)*5:02}"
cookie = open("session").read()

os.makedirs(folder, exist_ok=True)
os.system(f"curl --cookie \"session={cookie}\" https://adventofcode.com/2022/day/{day}/input > {folder}/{day:02}.in")
open(f"{folder}/{day:02}.md", "w").write(
    markdownify(
        str(BeautifulSoup(
            str(subprocess.check_output(
                ["curl", "--cookie", f"\"session={cookie}\"", f"https://adventofcode.com/2022/day/{day}"]
            ))
        , "html.parser").find("article", attrs={"class": "day-desc"})).encode("utf-8").decode("unicode-escape")
    )
)
open(f"{folder}/{day:02}-1.cpp", "w").write(template)
open(f"{folder}/{day:02}-2.cpp", "w").write(template)