# Breeding-chicken

Das Programm kontrolliert und reguliert Luftfeuchtigkeit und Temperatur in einer DIY Brutkiste (Styroporbox mit Heizfolie,Nebler und Motor). Die Messdaten der Sensoren werden auf einem OLED 124x64 0,96" angezeigt.

Es wird an den esp8266 nodemcu folgendes angeschlossen:

Schwimmerschalter an D0
OLED Display an D1 und D2
DHT11 an D3
Pumpe an D4
Nebler an D5
Heizfolie an D6
Wender an D7
Wender an D8
Modusschalter an GPIO 10
NTC auf A0

Teiweise werden Relais/Transistoren verwendet.

Wird ein DHT22 verwendet, ist kein NTC nötig.
