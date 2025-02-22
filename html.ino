void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 LED Control</title>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<div class=\"container\">";
  html += "<h1>ESP32 LED Control</h1>";
  html += "<a href=\"/LED=ALL\"><button>All LED </button></a><br>";
  html += "<a href=\"/LED=32415\"><button>Sigle LED </button></a><br>";
  html += "<a href=\"/LED=12345\"><button>3,2&4.1&5</button></a>";
  html += "</div></body></html>";

  server.send(200, "text/html", html);
}