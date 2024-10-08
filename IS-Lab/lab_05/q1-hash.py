def hash_function(input_string):
    # Initialize the hash value
    hash_value = 5381

    # Process each character in the input string
    for char in input_string:
        # Update the hash value according to the algorithm
        hash_value = (hash_value * 33) ^ ord(char)

        # Apply a 32-bit mask to ensure the hash value is within 32-bit range
        hash_value = hash_value & 0xFFFFFFFF

    return hash_value

# Example usage
string = "doner kabab nacho, alejandro garnacho"

print(f"Hash value (decimal): {hash_function(string)}")
print(f"Hash value (hex): {hash_function(string):08x}")
