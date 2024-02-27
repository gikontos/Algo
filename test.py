import subprocess

flag = 0

for i in range(1, 23):
    try:
        # Run the highway.exe program with input file
        process = subprocess.Popen(
            ["./Series3/visit.exe"],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )

        with open(f"visit/input{i}.txt", "r") as input_file:
            program_output, stderr = process.communicate(input=input_file.read())

        expected_output = open(f"visit/output{i}.txt", "r").read()

        if process.returncode != 0 or program_output != expected_output:
            flag = 1
            print(f"Input {i}:")
            print(f"Expected {expected_output.strip()}")
            print(f"But got {program_output.strip()}")
            print("-------")

    except Exception as e:
        flag = 1
        print(f"Error while processing input {i}: {str(e)}")
        print("-------")

if flag == 0:
    print("Everything is good")
else:
    print("There were issues")
