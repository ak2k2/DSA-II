import difflib
import subprocess
import sys

import pexpect


def print_diff(s1: str, s2: str):
    # diff with colors
    for line in difflib.unified_diff(s1.splitlines(), s2.splitlines(), lineterm=""):
        if line.startswith("+"):
            print("\033[92m" + line + "\033[0m")
        elif line.startswith("-"):
            print("\033[91m" + line + "\033[0m")
        else:
            print(line)


def run_useHeap(input_data):
    # Start the child process
    child = pexpect.spawn("./useHeap.exe")

    # String to capture the output
    program_output = ""

    # Interact with the process
    for line in input_data:
        child.expect(
            ".*:"
        )  # This regex should be adjusted based on the expected prompts of your program
        program_output += (
            child.before.decode() + child.after.decode()
        )  # Capture the output
        child.sendline(line)

    # The child should terminate after all inputs are sent and it's done processing
    child.expect(pexpect.EOF)
    program_output += (
        child.before.decode()
    )  # Capture any remaining output after the last input

    return (
        program_output.strip()
    )  # Return the captured output, stripping any leading/trailing whitespace


with open("ece365_useHeap_SR.txt", "r") as f:
    expected_output = f.read()

# test case 1: ece365_useHeap_SR.txt
input_data = [
    "500",  # capacity
    "1",  # option: Insert a new item
    "string one",  # string to insert
    "35",  # associated integer key
    "1",  # option: Insert a new item
    "string two",  # string to insert
    "55",  # associated integer key
    "1",  # option: Insert a new item
    "string three",  # string to insert
    "45",  # associated integer key
    "1",  # option: Insert a new item
    "string four",  # string to insert
    "5",  # associated integer key
    "1",  # option: Insert a new item
    "string two",  # string to insert (duplicate)
    "10",  # associated integer key
    "1",  # option: Insert a new item
    "string five",  # string to insert
    "80",  # associated integer key
    "1",  # option: Insert a new item
    "string six",  # string to insert
    "20",  # associated integer key
    "1",  # option: Insert a new item
    "string seven",  # string to insert
    "70",  # associated integer key
    "4",  # option: Perform a deleteMin
    "3",  # option: Delete a specified item
    "string four",  # string to delete
    "4",  # option: Perform a deleteMin
    "2",  # option: Set the key of a specified item
    "string one",  # string whose key to change
    "50",  # new key
    "3",  # option: Delete a specified item
    "string two",  # string to delete
    "4",  # option: Perform a deleteMin
    "4",  # option: Perform a deleteMin
    "2",  # option: Set the key of a specified item
    "string five",  # string whose key to change
    "60",  # new key
    "4",  # option: Perform a deleteMin
    "4",  # option: Perform a deleteMin
    "4",  # option: Perform a deleteMin
    "5",  # option: Quit
]


result = run_useHeap(input_data)

# print(result)

print_diff(expected_output, result)
