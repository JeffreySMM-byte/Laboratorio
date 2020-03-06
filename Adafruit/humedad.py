from Adafruit_IO import RequestError, Client, Feed

ADAFRUIT_IO_USERNAME = "JSMM"
ADAFRUIT_IO_KEY = "aio_VZpp31HB6hfilyplS2rj1zre0wST"

aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

hum = aio.feeds('hum')

aio.send_data(hum.key, 78)
