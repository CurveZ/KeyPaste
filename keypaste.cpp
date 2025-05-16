/*
 * Author: CurveZ
 * Version: 1.0
 * Date: May 16, 2025
 * Description:
 * KeyPaste is a simple Windows application that simulates keyboard strokes
 * to paste the content of the clipboard. This is particularly useful in
 * environments where traditional paste commands do not work, such as
 * noVNC Console-Windows in Proxmox or other remote desktop environments.
 * 
 * Features:
 * - Simulates keyboard strokes to paste clipboard content.
 * - Supports an optional delay via command-line arguments.
 * - Handles up to 4,500 characters from the clipboard.
 */

#define UNICODE
#define _UNICODE

#include <windows.h>
#include <iostream>
#include <string>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::milliseconds

// Function to open the clipboard
bool openClipboard() {
    if (OpenClipboard(nullptr)) {
        return true;
    } else {
            MessageBox(
                nullptr,
                L"Failed to OpenClipboard.",
                L"Error",
                MB_OK | MB_ICONERROR | MB_TOPMOST
        );
        return false;
    }
}

// Function to close the clipboard
void closeClipboard() {
    CloseClipboard();
}

// Function to get text from the clipboard
std::wstring getClipboardText() {
    if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) {
        MessageBox(
            nullptr,
            L"Clipboard does not contain text.",
            L"Error",
            MB_OK | MB_ICONERROR | MB_TOPMOST
        );
        return L"";
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (hData == nullptr) {
        MessageBox(
            nullptr,
            L"Failed to get clipboard data.",
            L"Error",
            MB_OK | MB_ICONERROR | MB_TOPMOST
        );
        return L"";
    }

    wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
    if (pszText == nullptr) {
        MessageBox(
            nullptr,
            L"Failed to lock clipboard data.",
            L"Error",
            MB_OK | MB_ICONERROR | MB_TOPMOST
        );
        return L"";
    }

    std::wstring text(pszText);
    GlobalUnlock(hData);
    return text;
}

// Function to send text to the active window
void sendTextToWindow(const std::wstring& text) {
    for (size_t i = 0; i < text.size(); ++i) {
        wchar_t c = text[i];
        // Handle Windows line endings: skip '\r' if followed by '\n'
        if (c == L'\r' && i + 1 < text.size() && text[i + 1] == L'\n') {
            continue;
        }
        // If newline, send a real Enter key event
        if (c == L'\n' || c == L'\r') {
            INPUT input[2] = {};
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = VK_RETURN;
            input[0].ki.dwFlags = 0;

            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = VK_RETURN;
            input[1].ki.dwFlags = KEYEVENTF_KEYUP;

            SendInput(2, input, sizeof(INPUT));
        } else {
            INPUT input[2] = {};
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = 0;
            input[0].ki.wScan = c;
            input[0].ki.dwFlags = KEYEVENTF_UNICODE;

            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = 0;
            input[1].ki.wScan = c;
            input[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;

            SendInput(2, input, sizeof(INPUT));
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
}

int main(int argc, char* argv[]) {
    const int maxchar = 4500; // Allow up to 4,500 characters

    // Optional delay from command line
    if (argc > 1) {
        int delay = atoi(argv[1]);
        if (delay > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(delay));
        }
    }

    if (openClipboard()) {
        std::wstring clipboardText = getClipboardText();

        if (!clipboardText.empty() && clipboardText.length() < maxchar) {
            sendTextToWindow(clipboardText); // Send text directly to the active window
        } else {
            // Show a message box if the clipboard is empty or text exceeds the limit
            std::wstring message = clipboardText.empty()
                ? L"Clipboard is empty."
                : L"Text exceeds the maximum allowed length of 4,500 characters.";
            MessageBox(
                nullptr,
                message.c_str(),
                L"Error",
                MB_OK | MB_ICONERROR | MB_TOPMOST
            );
        }

        closeClipboard();
    } else {
        // Show a message box if the clipboard cannot be opened
        MessageBox(
            nullptr,
            L"Failed to open clipboard.",
            L"Error",
            MB_OK | MB_ICONERROR | MB_TOPMOST
        );
    }

    return 0;
}

