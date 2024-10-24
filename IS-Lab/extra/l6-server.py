import socket
import hashlib
from ecdsa import SigningKey, NIST256p, BadSignatureError, VerifyingKey
import hashlib
import pickle
import signal
import sys
import select


# Schnorr Verify
def schnorr_verify(message, signature, public_key):
    try:
        message_hash = hashlib.sha256(message.encode()).digest()
        return public_key.verify(signature, message_hash, hashfunc=hashlib.sha256)
    except BadSignatureError:
        return False

def handle_client_connection(client_socket):
    """Handle incoming client connection."""
    try:
        # Receive serialized data from the client
        serialized_data = client_socket.recv(4096)
        data = pickle.loads(serialized_data)

        # Deserialize the private key, public key, and signature
        private_key = SigningKey.from_string(bytes.fromhex(data['private_key']), curve=NIST256p)
        public_key = VerifyingKey.from_string(bytes.fromhex(data['public_key']), curve=NIST256p)
        signature = bytes.fromhex(data['signature'])
        message = data['message']

        # Verify Sign
        is_valid = schnorr_verify(message, signature, public_key)
        print(f"Signature: {is_valid}")

        # Send data back to client after verifying
        if is_valid:
            print(f"Message from server: {message}")
            client_socket.send(message.encode())
        else:
            print("nope")
            client_socket.send(b"nope")
    finally:
        client_socket.close()

def start_server(host='127.0.0.1', port=65432):
    """Start the server."""
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)
    print(f"Server listening on {host}:{port}")

    def signal_handler(sig, frame):
        print("\nShutting down the server...")
        server_socket.close()
        sys.exit(0)

    # Register signal handler for graceful shutdown
    signal.signal(signal.SIGINT, signal_handler)

    while True:
        try:
            # Use select to handle non-blocking accept
            readable, _, _ = select.select([server_socket], [], [], 1)
            if server_socket in readable:
                client_socket, addr = server_socket.accept()
                print(f"Accepted connection from {addr}")
                handle_client_connection(client_socket)
        except Exception as e:
            print(f"Error: {e}")
            break

if __name__ == "__main__":
    start_server()
