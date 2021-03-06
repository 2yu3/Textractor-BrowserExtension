# Textractor Browser Extension

Simple extension for Textractor that creates WebSocket server and sends sentencies to clients.
Extensions creates server at 0.0.0.0:1234

The purpose of this extension is to give an ability to use all browser plugins that help reading Japanese.

[There is](https://github.com/2yu3/Textractor-BrowserExtension-WebUI/) a simple WebUI.
![screenshot](https://github.com/2yu3/Textractor-BrowserExtension/raw/master/screenshot.png)

## Installation

1. Download the latest versions of [Textractor](https://github.com/Artikash/Textractor/releases/latest) and this [extension](https://github.com/2yu3/Textractor-BrowserExtension/releases/latest)
2. Extract dlls to the same directory where `Textractor.exe` is
3. Download [webui](https://github.com/2yu3/Textractor-BrowserExtension-WebUI/releases/latest)
4. Add extension to Textractor via clicking "Extensions" button and drag&drop `BrowserWebSocket.dll`
5. Open `index.html` from webui
6. Press connect button. If everything is ok, you should see "Hello from Textractor" message.
