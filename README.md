# Apple

An iOS app built with **Swift** and **SwiftUI** that uses an **HTML file as its UI source code**.

## How it works

Instead of building the interface with SwiftUI views or UIKit controls, the app renders an `index.html` file inside a `WKWebView`. Swift acts as the host layer that loads and displays the HTML/CSS content.

```
Apple/
├── Apple.xcodeproj/          # Xcode project
│   └── project.pbxproj
└── Apple/
    ├── AppleApp.swift        # @main SwiftUI entry point
    ├── ContentView.swift     # Root view – hosts the WebView
    ├── WebView.swift         # UIViewRepresentable wrapper for WKWebView
    ├── index.html            # HTML source code that defines the UI
    ├── Info.plist            # App configuration
    └── Assets.xcassets/      # App icons and accent colour
```

## Requirements

| Tool  | Version   |
|-------|-----------|
| Xcode | 15.0 +    |
| iOS   | 16.0 +    |
| Swift | 5.9 +     |

## Getting started

1. Open `Apple.xcodeproj` in Xcode.
2. Select an iPhone simulator or device.
3. Press **⌘ R** to build and run.

The app will launch and display the contents of `index.html` full-screen. Edit `Apple/index.html` to change the UI – no Swift code changes needed.