from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import binascii

BLOCK_SIZE = 16

def aes_192_encrypt(msg, key):
    cipher = AES.new(key, AES.MODE_ECB)
    padded_msg = pad(msg.encode('utf-8'), BLOCK_SIZE)
    ciphertext = cipher.encrypt(padded_msg)
    return ciphertext

def aes_192_decrypt(ciphertext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    padded_plaintext = cipher.decrypt(ciphertext)
    plaintext = unpad(padded_plaintext, BLOCK_SIZE).decode('utf-8')
    return plaintext

key_hex = "FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210" 
key = binascii.unhexlify(key_hex)
message = "Top Secret Data"

ciphertext = aes_192_encrypt(message, key)
print(f'Ciphertext (hex): {ciphertext.hex()}')

plaintext = aes_192_decrypt(ciphertext, key)
print(f'Plaintext: {plaintext}')
