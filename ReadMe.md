## 🛠️ KeyPaste

KeyPaste is a simple Windows application that simulates keyboard strokes to paste the content of the clipboard. This project is particularly useful for environments like **noVNC Consoles in Proxmox**, where traditional paste commands do not work. KeyPaste allows users to quickly paste text from their clipboard into any application by simulating keyboard input.

## Features

- Simulates keyboard strokes to paste clipboard content.
- Easy to use and lightweight.
- Standalone executable that does not require installation.

## Typical Usage Example

A common way to use KeyPaste is to position your cursor in the target application where you want to paste, and then press a programmable button on your keyboard or mouse that is configured to run the KeyPaste program. KeyPaste will then automatically type out the current contents of your clipboard at the cursor location, simulating real keyboard input.

### More Usage

To use KeyPaste, simply run the application win delay from start menu or use the designated keyboard shortcut to paste the clipboard content into your desired application.

## Where KeyPaste is Useful

KeyPaste is particularly helpful in environments where traditional clipboard pasting (`Ctrl+V`) does not work, such as:

- **KVM Consoles**:
  - noVNC Consoles in Proxmox.
  - IPMI/KVM Over IP Consoles (e.g., Dell iDRAC, HP iLO, Supermicro IPMI).
- **Remote Desktop Environments**:
  - RDP sessions without clipboard redirection.
  - X2Go or VNC sessions without clipboard synchronization.
- **Virtual Machines**:
  - VirtualBox or VMware consoles without clipboard sharing enabled.
- **Command-Line Interfaces**:
  - Serial console interfaces (e.g., PuTTY, Tera Term).
  - Linux TTYs (`Ctrl+Alt+F1`).
- **Web-Based Management Interfaces**:
  - Web-based SSH clients (e.g., Cockpit, Guacamole).
  - Admin panels for routers, switches, or other network devices.
- **Legacy Applications**:
  - Old Windows or DOS applications that lack modern clipboard support.
- **Security-Restricted Environments**:
  - Secure terminals or kiosks where clipboard functionality is disabled.

## Command-Line Delay Feature

You can provide an optional delay (in seconds) as a command-line argument. This is useful if you want to give yourself time to focus the target window before KeyPaste starts typing.

**Example:**


keypaste.exe 10


This will wait 10 seconds before pasting the clipboard content.



## Requirements

- Windows operating system

## Building the Application

To build KeyPaste, use the following command in your project directory:

```
g++ -static -o keypaste.exe keypaste.cpp -luser32 -mwindows
```

## Download EXE

You can download the latest release of KeyPaste.exe from the following link:

<span style="font-size: 16px;">**[💾 Download the Latest Release](https://github.com/CurveZ/KeyPaste/releases/latest)**</span>

Simply download the `keypaste.exe` file and run it—no installation required!


<h3 style="color: red;">⚠️ Warning</h3>

Once KeyPaste starts simulating keystrokes, it will continue until all clipboard content has been typed out. Be cautious when pasting large amounts of text, as it may cause unexpected behavior in some applications or windows. For example, typing hundreds of characters rapidly could lead to unusual results or even temporary unresponsiveness in certain programs.

**Use responsibly and ¡ensure the target application is ready to receive the input!**


## More Information

For more details, updates, and support, visit the official KeyPaste website:  
[https://kervels.net/keypaste/](https://kervels.net/keypaste/)

Happy pasting!
