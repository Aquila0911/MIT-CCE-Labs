from Crypto.Util import number
import random

def generate_keypair(bits=512):
    """Generates a public/private key pair for Paillier encryption"""
    p = number.getPrime(bits)
    q = number.getPrime(bits)
    n = p * q
    g = n + 1  # g = n + 1 is often used in practical implementations
    lambda_n = (p - 1) * (q - 1)  # λ(n) = (p - 1)(q - 1)
    mu = number.inverse(lambda_n, n)  # Modular inverse of λ(n) modulo n
    return (n, g), (lambda_n, mu)

def encrypt(public_key, message):
    """Encrypts a message using the Paillier encryption scheme"""
    n, g = public_key
    r = random.randint(1, n - 1)  # Random value for encryption
    ciphertext = (pow(g, message, n * n) * pow(r, n, n * n)) % (n * n)
    return ciphertext

def decrypt(private_key, public_key, ciphertext):
    """Decrypts a ciphertext using the Paillier encryption scheme"""
    n, _ = public_key
    lambda_n, mu = private_key
    u = pow(ciphertext, lambda_n, n * n)
    l = (u - 1) // n
    message = (l * mu) % n
    return message

def string_to_int(s):
    """Convert a string to an integer by encoding it to bytes and interpreting the bytes as an integer."""
    return int.from_bytes(s.encode(), 'big')

def int_to_string(i):
    """Convert an integer to a string by interpreting the integer as bytes and decoding the bytes."""
    return i.to_bytes((i.bit_length() + 7) // 8, 'big').decode('utf-8')

def main():
    # Generate key pair
    public_key, private_key = generate_keypair(bits=512)

    # Take string inputs and convert to integers
    str_a = input("Enter string a: ")
    str_b = input("Enter string b: ")
    a = string_to_int(str_a)
    b = string_to_int(str_b)

    # Encrypt the integers
    ciphertext_a = encrypt(public_key, a)
    ciphertext_b = encrypt(public_key, b)

    # Decrypt the ciphertexts
    decrypted_a = decrypt(private_key, public_key, ciphertext_a)
    decrypted_b = decrypt(private_key, public_key, ciphertext_b)

    # Convert the decrypted integers back to strings
    decrypted_str_a = int_to_string(decrypted_a)
    decrypted_str_b = int_to_string(decrypted_b)

    # Print results
    print(f"Original string a: {str_a}")
    print(f"Encrypted a: {ciphertext_a}")
    print(f"Decrypted a: {decrypted_str_a}")

    print(f"Original string b: {str_b}")
    print(f"Encrypted b: {ciphertext_b}")
    print(f"Decrypted b: {decrypted_str_b}")

if __name__ == "__main__":
    main()

# input_string = "string"
# byte_string = input_string.encode('utf-8')
# print(byte_string)
