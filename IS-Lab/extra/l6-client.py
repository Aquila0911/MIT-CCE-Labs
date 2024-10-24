import socket
import hashlib
from ecdsa import SigningKey, NIST256p, BadSignatureError
import hashlib
import pickle

# Generate Schnorr Keys
private_key = SigningKey.generate(curve=NIST256p)  # Private key
public_key = private_key.verifying_key  # Public key


# Schnorr Sign
def schnorr_sign(message, private_key):
    message_hash = hashlib.sha256(message.encode()).digest()
    signature = private_key.sign(message_hash, hashfunc=hashlib.sha256)
    return signature


# Schnorr Verify
def schnorr_verify(message, signature, public_key):
    try:
        message_hash = hashlib.sha256(message.encode()).digest()
        return public_key.verify(signature, message_hash, hashfunc=hashlib.sha256)
    except BadSignatureError:
        return False

def start_client(server_host='127.0.0.1', server_port=65432):
    """Start the client and send data to the server."""
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_host, server_port))

    try:
        # Define the data to send
        message = input("Enter message: ")
        signature = schnorr_sign(message, private_key)

        # Serialize the private key, public key, and signature
        data_to_send = {
            'private_key': private_key.to_string().hex(),
            'public_key': public_key.to_string().hex(),
            'signature': signature.hex(),
            'message': message
        }
        serialized_data = pickle.dumps(data_to_send)

        # Send serialized data to the server
        client_socket.sendall(serialized_data)

        received_data = client_socket.recv(4096).decode()
        print(f"Received Message: {received_data}")
        
    finally:
        client_socket.close()

if __name__ == "__main__":
    start_client()
