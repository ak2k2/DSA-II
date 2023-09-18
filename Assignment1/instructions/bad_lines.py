# load in wordlist_small.txt and store each line as a pandas dataframe
import pandas as pd
import numpy as np

# load in wordlist_small.txt
with open("wordlist_small.txt") as f:
    lines = f.readlines()

# remove \n from each line
lines = [line.strip() for line in lines]


def badline(line) -> bool:
    allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-'"
    if lines.count(line) > 1:
        print("Duplicate Line")
        return True
    if len(line) > 20:
        return True
    for char in line:
        if char not in allowed_chars:
            return True
    return False


bad_lines = [line for line in lines if badline(line)]
print("\n")
print(bad_lines)
print("\n")
