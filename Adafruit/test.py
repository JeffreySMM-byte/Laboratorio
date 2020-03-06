from Adafruit_IO import RequestError, Client, Feed

ADAFRUIT_IO_USERNAME = 'JSMM'
ADAFRUIT_IO_KEY = 'aio_VZpp31HB6hfilyplS2rj1zre0wST'

aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

try:
    test = aio.feeds('test')
except RequestError:
    test_feed = Feed(name = 'test')
    test_feed = aio.create_feed(test_feed)

aio.send_data(test.key, 43)
