#pragma once

/**
 * Start the web server: the dashboard page at http://<pin's IP>/ and the data
 * interface it uses (/api/...). Call once Wi-Fi is set up; it serves whenever
 * the pin is connected.
 */
void web_start(void);
