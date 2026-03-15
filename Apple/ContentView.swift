import SwiftUI

struct ContentView: View {
    var body: some View {
        WebView(htmlFileName: "index")
            .ignoresSafeArea()
    }
}

#Preview {
    ContentView()
}
