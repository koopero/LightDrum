#include "FastLED.h"
#include "LightDrum.h"

#define STRIP_TYPE NEOPIXEL
#define STRIP_FORMAT GRB
#define STRIP_LENGTH 144
#define STRIP_PIN 3
#define STRIP_CIRCLE 79

#define SENSOR0_PIN 0
#define SENSOR1_PIN 1

#define SENSOR_FLOOR 200
#define SENSOR_CEIL 700

#define COLOUR_V 255

#define SPIN 500


CRGB leds[STRIP_LENGTH];

smoothVal sensor[2];

long phase = 0;



void setup() {
	FastLED.addLeds<STRIP_TYPE, STRIP_PIN, STRIP_FORMAT>( leds, STRIP_LENGTH);
}

void loop() {
  // put your main code here, to run repeatedly:
	sensor[0].iterate( max( 0, analogRead( SENSOR0_PIN ) - SENSOR_FLOOR ) );
	sensor[1].iterate( max( 0, analogRead( SENSOR1_PIN ) - SENSOR_FLOOR ) );


	phase += map( sensor[0].value, 0, SENSOR_CEIL, 0, -SPIN ) + map( sensor[1].value, 0, SENSOR_CEIL, 0, -SPIN );
	int sparkle = map( max( sensor[1].value, sensor[0].value ) , 0, SENSOR_CEIL, 0, 300 );

	for ( int x = 0; x < STRIP_LENGTH; x ++ ) {
		CHSV pixel;

		pixel.h = map( x, 0, STRIP_CIRCLE, 0, 255 ) + ( phase >> 4 );
		pixel.s = 255;
		pixel.v = random( 255 ) < sparkle ?  COLOUR_V : 0;

		hsv2rgb_rainbow( pixel, leds[x] );
	}

	FastLED.show();

}
