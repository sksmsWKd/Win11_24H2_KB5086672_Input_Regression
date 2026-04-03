#include <windows.h>
#include <iostream>

// Global Counters for Comparison
int g_physCount = 0; // Physical State (GetAsyncKeyState)
int g_hookCount = 0; // OS Message Event (WH_KEYBOARD_LL)

HHOOK hHook = NULL;

// Low-level Keyboard Hook Callback
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            KBDLLHOOKSTRUCT* pKey = (KBDLLHOOKSTRUCT*)lParam;
            // Target: Left Control or 'A' key
            if (pKey->vkCode == VK_LCONTROL || pKey->vkCode == 'A') {
                g_hookCount++;
            }
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {
    std::cout << "====================================================\n";
    std::cout << " Windows 11 Input Regression Diagnostic Tool\n";
    std::cout << " Target Build: 26100.8117 / KB5086672\n";
    std::cout << " Exit: Press ESC\n";
    std::cout << "====================================================\n\n";

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;

        // Poll Physical State
        if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) || (GetAsyncKeyState('A') & 0x8000)) {
            g_physCount++;
        }

        // Process Message Pump for Hook
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        printf("\r[Physical State]: %d | [OS Message Hook]: %d", g_physCount, g_hookCount);
        Sleep(10);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}