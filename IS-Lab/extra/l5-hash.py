import hashlib

def hash_string(input_string):
    """Hash the input string using MD5, SHA1, and SHA256."""
    
    md5_hash = hashlib.md5(input_string.encode()).hexdigest()    
    sha1_hash = hashlib.sha1(input_string.encode()).hexdigest()    
    sha256_hash = hashlib.sha256(input_string.encode()).hexdigest()
    
    return md5_hash, sha1_hash, sha256_hash

def main():
    # Take input from the user
    input_string = input("Enter a string to hash: ")
    
    # Compute hashes
    md5_hash, sha1_hash, sha256_hash = hash_string(input_string)
    
    # Print the results
    print(f"MD5: {md5_hash}")
    print(f"SHA1: {sha1_hash}")
    print(f"SHA256: {sha256_hash}")

if __name__ == "__main__":
    main()
