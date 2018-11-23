#!/usr/bin/env python3
# This test validates that all source files have _correct_ copyright notices.

import subprocess
import argparse
import sys
import re

subprocess.getoutput("ls")

# This is pretty general, it will match any line with the word "Copyright" and 4 numbers

COPYRIGHT_EXISTS_PATTERN=r'Copyright .* \d\{4\}'

COPYRIGHT_SINGLE_YEAR_PATTERN=r'\(\d\{4\}\)'
COPYRIGHT_RANGE_PATTERN=r'\(\d\{4\} - \d\{4\}\)'
COPYRIGHT_LITERAL_PATTERN=r'Copyright (c)'

parser = argparse.ArgumentParser()
parser.add_argument('input', type=argparse.FileType('r+'),
                    help='Input file. \'-\' for stdin.')
parser.add_argument('-o', type=argparse.FileType('w'),
                    metavar='output',
                    help='Output file. Defaults to stdout.',
                    default=sys.stdout)

args = parser.parse_args()

def has_copyright_header(candidate_filepath):
    with open(args.input.readlines(), "r+") as f:
        matches = re.findall(COPYRIGHT_EXISTS_PATTERN, f)
        for match in matches:
            print("file has a copyright notice")
            print(match)
        else:
            print("file doesn't have a copyright notice")
