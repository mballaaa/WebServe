import sys

def count_lines_from_input():
    line_count = 0
    # Read input line by line
    for line in sys.stdin:
        line_count += 1
    return line_count

if __name__ == "__main__":
    # Call the function to count lines from input
    lines = count_lines_from_input()
    print("Number of lines:", lines)
