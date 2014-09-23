#define clamp(v) ((v)>255?255:(v)<0?0:(v))

class smoothVal {
public:
	short value = 0;
	short rise = 40;
	short fall = 2;

	short iterate ( short wantVal ) {
		if ( wantVal > value ) {
			value = min( wantVal, value + rise );
		} else if ( wantVal < value ) {
			value = max( wantVal, value - fall );
		}

		return value;
	};
};


int grad8Clamp ( const int * gradient, long l ) {
    
    l = clamp(l);
    l = l * 7 / 8;
   
    long a = gradient[(l>>5)+0];
    long b = gradient[(l>>5)+1];
    short c = l & 31;
    short ic = ( 31 - c );

    return (( a * ic ) + ( b * c ) ) >> 5;

}