import difflib
import pexpect


def print_diff(s1, s2):
    for line in difflib.unified_diff(s1.splitlines(), s2.splitlines(), lineterm=""):
        color = (
            "\033[92m"
            if line.startswith("+")
            else "\033[91m"
            if line.startswith("-")
            else "\033[0m"
        )
        print(f"{color}{line}\033[0m")


def run_useHeap(input_data):
    child = pexpect.spawn("./bin/useHeap.exe")
    output = ""

    for line in input_data:
        child.expect(".*:")
        output += child.before.decode() + child.after.decode()
        child.sendline(line)

    child.expect(pexpect.EOF)
    output += child.before.decode()

    return "$ ./useHeap.exe\n" + output.strip()


with open("test/ece365_useHeap_SR.txt", "r") as f:
    expected_output = f.read()


# test case 1: ece365_useHeap_SR.txt
input_data = [
    "100",  # capacity
    "1",  # option: Insert a new itema
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
print_diff(expected_output, result)
