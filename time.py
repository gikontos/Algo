import time

# Define the number of operations
num_operations = 10_000_000

# Start time
start_time = time.time()

# Perform operations (e.g., simple additions) repeatedly
for _ in range(num_operations):
    result = 1 + 1  # Perform a simple operation (change this as per the type of operations you want to measure)

# End time
end_time = time.time()

# Calculate elapsed time
elapsed_time = end_time - start_time

# Calculate operations per second
operations_per_second = num_operations / elapsed_time

print(f"Operations per second: {operations_per_second}")