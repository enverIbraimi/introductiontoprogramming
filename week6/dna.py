import csv
import sys

def main():
    # 1. Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # 2. Read database file into a list of dictionaries
    database = []
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        for row in reader:
            database.append(row)

    # 3. Read DNA sequence file into a string
    with open(sys.argv[2]) as f:
        sequence = f.read()

    # 4. Find longest match of each STR
    # Get the list of STRs from the database header (skipping 'name')
    strs = list(database[0].keys())[1:]
    
    results = {}
    for str_name in strs:
        results[str_name] = longest_match(sequence, str_name)

    # 5. Check database for matching profiles
    for person in database:
        match = True
        for str_name in strs:
            if int(person[str_name]) != results[str_name]:
                match = False
                break
        
        if match:
            print(person["name"])
            return

    print("No match")

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    sub_len = len(subsequence)
    seq_len = len(sequence)

    for i in range(seq_len):
        count = 0
        while True:
            start = i + count * sub_len
            end = start + sub_len
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break
        longest_run = max(longest_run, count)

    return longest_run

if __name__ == "__main__":
    main()