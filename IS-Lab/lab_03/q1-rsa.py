from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import binascii

key = RSA.generate(2048)
n = key.n
e = key.e
d = key.d

public_key = key.publickey()
private_key = key

print("")
print("n: " + str(n))
print("")
print("e: " + str(e))
print("")
print("d: " + str(d))
print("")

message = "Asymmetric Encryption"

cipher_encrypt = PKCS1_OAEP.new(public_key)
ciphertext = cipher_encrypt.encrypt(message.encode())
print("Ciphertext (hex):", binascii.hexlify(ciphertext).decode())
print("")

cipher_decrypt = PKCS1_OAEP.new(private_key)
decrypted_message = cipher_decrypt.decrypt(ciphertext)
print("Decrypted message:", decrypted_message.decode())
print("")
