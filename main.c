#define MY_PORT_B *(unsigned char*)0x25
#define MY_PORT_B_DDR *(unsigned char*)0x24

#define NS_GREEN (1 << 5)
#define NS_YELLOW (1 << 4)
#define NS_RED (1 << 3)

#define EW_GREEN (1 << 2)
#define EW_YELLOW (1 << 1)
#define EW_RED (1 << 0)

void setup();
void loop();

int main() {
	setup();
	while(1) {
		loop();
	}

	return 0;
}

void setup() {
	MY_PORT_B_DDR |= NS_GREEN; // Plus 32, 1 shiftet 5 gange = 32
	MY_PORT_B_DDR |= NS_YELLOW; // Plus 16, 1 shiftet 4 gange = 16
	MY_PORT_B_DDR |= NS_RED; // Plus 8, 1 shiftet 3 gange = 8
	MY_PORT_B_DDR |= EW_GREEN; // Plus 8, 1 shiftet 2 gange = 4
	MY_PORT_B_DDR |= EW_YELLOW; // Plus 8, 1 shiftet 1 gange = 2
	MY_PORT_B_DDR |= EW_RED; // Plus 8, 1 shiftet 0 gange = 1
} 

void loop() {
	// volatile så loops IKKE bliver filtreret fra i -Os flag under compile 
	volatile long pause = 0;

	// Rødt lys Tænd
	MY_PORT_B |= NS_RED; // plus 8, 1 shiftet 3 gange = 8
	MY_PORT_B |= EW_RED; // plus 1, 1 shiftet 0 gange = 1
	for (pause = 0; pause < 1500000; pause++) {
		pause = pause;
	}

	// Gult lys Tænd
	MY_PORT_B |= NS_YELLOW; // plus 32, 1 shiftet 4 gange = 16
	for (pause = 0; pause < 500000; pause++) {
		pause = pause;
	}
	
	// Rødt lys sluk
	MY_PORT_B &= ~NS_RED; // = 0, 1 shiftet 3 gange = 8 men NOT (~) 
	// Gult lys sluk
	MY_PORT_B &= ~NS_YELLOW; // = 0, 1 shiftet 4 gange = 16 men NOT (~) 
	// Grønt lys Tænd
	MY_PORT_B |= NS_GREEN; // plus 32, 1 shiftet 5 gange = 32
	for (pause = 0; pause < 2000000; pause++) {
		pause = pause;
	}

	// Grønt lys Sluk
	MY_PORT_B &= ~NS_GREEN; // = 0, 1 shiftet 5 gange = 32 men NOT (~) 
	// Gult lys Tænd
	MY_PORT_B |= NS_YELLOW; // plus 32, 1 shiftet 4 gange = 16
	for (pause = 0; pause < 1000000; pause++) {
		pause = pause;
	}

	// Gult lys sluk
	MY_PORT_B &= ~NS_YELLOW; // = 0, 1 shiftet 4 gange = 16 men NOT (~)
	// Rødt lys tænd
	MY_PORT_B |= NS_RED; // plus 8, 1 shiftet 3 gange = 8
	for (pause = 0; pause < 1000000; pause++) {
		pause = pause;
	}


	// ===============================================================

	// Gult lys Tænd
	MY_PORT_B |= EW_YELLOW; // plus 2, 1 shiftet 1 gang = 2
	for (pause = 0; pause < 500000; pause++) {
		pause = pause;
	}

	// Rødt lys sluk
	MY_PORT_B &= ~EW_RED; // = 0, 1 shiftet 0 gange = 1 men NOT (~) 
	// Gult lys sluk
	MY_PORT_B &= ~EW_YELLOW; // = 0, 1 shiftet 1 gang = 2 men NOT (~) 
	// Grønt lys Tænd
	MY_PORT_B |= EW_GREEN; // plus 4, 1 shiftet 2 gange = 4
	for (pause = 0; pause < 2000000; pause++) {
		pause = pause;
	}

	// Grønt lys Sluk
	MY_PORT_B &= ~EW_GREEN; // = 0, 1 shiftet 2 gange = 4 men NOT (~) 
	// Gult lys Tænd
	MY_PORT_B |= EW_YELLOW; // plus 2, 1 shiftet 1 gang = 2
	for (pause = 0; pause < 1000000; pause++) {
		pause = pause;
	}

	// Gult lys sluk
	MY_PORT_B &= ~EW_YELLOW; // = 0, 1 shiftet 1 gang = 2 men NOT (~)
}
