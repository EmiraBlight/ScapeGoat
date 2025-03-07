import os
import glob
import subprocess
import sys

def get_test_files(directory):
    """
    Returns a list of all files in the given directory that end with '.test'.
    """
    return glob.glob(os.path.join(directory, "*.test"))

def run_command_and_get_output(command):
    """
    Runs a command in the console and returns its output.

    Args:
        command: The command to run as a string.

    Returns:
        The output of the command as a string, or None if an error occurs.
    """
    try:
        process = subprocess.run(
            command,
            shell=True,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        return process.stdout.strip()
    except subprocess.CalledProcessError as e:
        return e.stderr

directory_path = EXE = sys.argv[2]
test_files = get_test_files(directory_path)
for index,file in enumerate(test_files):
    test_files[index] = file.replace('.test','')

results = {}
EXE = sys.argv[1]

for i in test_files:
    results.update({i:run_command_and_get_output(EXE + " < " + i+ ".test")})

    '''runs all of the tests with each input file'''
allPassed = True
for i in test_files:
    file = open(i+".output","r")
    Ni = i
    if i.find("/") >=0:
        Ni = i[i.rfind("/")+1:]
    expected = file.readline()
    #compares all input files and displays pass or fail
    if expected == results[i]:
        print(f"{Ni}.test passed \033[32m\u2713\033[0m")
    else:
        print(f"{Ni}.test failed "+ "\033[31m" + "x" + "\033[0m")
        print(f"Expected: {expected}, but got {results[i]}")
        allPassed = False
if allPassed:
    print("\033[32mALL TESTS PASSED \u2713\033[0m")