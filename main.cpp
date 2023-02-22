#include <iostream>
#include <Windows.h>
#include <map>

using namespace std;

HHOOK hHook;
map<int, int> keyDownCounters;
map<int, int> keyUpCounters;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            keyDownCounters[p->vkCode]++;
            //cout << "Key Down: " << p->vkCode << " Count: " << keyDownCounters[p->vkCode] << endl;
        }
        else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            keyUpCounters[p->vkCode]++;
            cout << "Key Up: " << p->vkCode << " Count: " << keyUpCounters[p->vkCode] << endl;

            int total = 0;
            for (auto i = keyUpCounters.begin(); i != keyUpCounters.end(); ++i) {
                cout << i->first << " => " << i->second << endl;
                total += i->second;
            }
            cout << "total: " << total << endl;

            if (p->vkCode == 27) {
                keyUpCounters.clear();
                cout << "Cleared the KeyUpCounters." << endl;
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hHook == NULL) {
        cerr << "Failed to install hook" << endl;
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}
