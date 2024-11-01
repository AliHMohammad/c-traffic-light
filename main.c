#define MY_PORT_B *(unsigned char*)0x25
#define MY_PORT_B_DDR *(unsigned char*)0x24

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
	MY_PORT_B_DDR |= (1 << 5); // Plus 32, 1 shiftet 5 gange = 32
	MY_PORT_B_DDR |= (1 << 4); // Plus 16, 1 shiftet 4 gange = 16
	MY_PORT_B_DDR |= (1 << 3); // Plus 8, 1 shiftet 3 gange = 8
}

void loop() {
	//TODO: Skriv 32 til 0x25, tænder PB5
	//unsigned char* ptr_til_port_b = 0x25;
	// volatile så den ikke bliver filtreret fra i -Os flag under compile 
	volatile long pause = 0;

	// Rødt lys
	MY_PORT_B |= (1 << 5); // plus 32, 1 shiftet 5 gange = 32

	for (pause = 0; pause < 100000; pause++) {
		pause = pause;
	}
	
	MY_PORT_B &= ~(1 << 5); // = 0, 1 shiftet 5 gange = 32 men NOT (~) 
	
	for (pause = 0; pause < 100000; pause++) {
		pause = pause;
	}


	// Gult lys
	MY_PORT_B |= (1 << 4); // plus 32, 1 shiftet 4 gange = 16

	for (pause = 0; pause < 100000; pause++) {
		pause = pause;
	}
	
	MY_PORT_B &= ~(1 << 4); // = 0, 1 shiftet 4 gange = 16 men NOT (~) 
	
	for (pause = 0; pause < 100000; pause++) {
		pause = pause;
	}



	// Grønt lys
	MY_PORT_B |= (1 << 3); // plus 8, 1 shiftet 3 gange = 8

	for (pause = 0; pause < 100000; pause++) {
		pause = pause;
	}
	
	MY_PORT_B &= ~(1 << 3); // = 0, 1 shiftet 3 gange = 8 men NOT (~) 
	
	for (pause = 0; pause < 100000; pause++) {
		pause = pause;
	}
}
