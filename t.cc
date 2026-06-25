#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <unistd.h>
void delay_ms(long ms) {
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000; 
	nanosleep(&ts, NULL);
}
#pragma pack(push, 1) 
struct pixel {
	uint8_t r, g, b;
};
#pragma pack(pop) 
void ppm(const char* name, const std::vector<pixel>& pixels, int lon, int on) {
	std::ofstream fp(name, std::ios::binary);
	fp << "P6\n" << lon << " " <<on << "\n255\n";
	fp.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(pixel));
}

void pintar_pixel_completo(pixel& pixeel, uint8_t cor) {
	pixeel.r = cor;
	pixeel.g = cor;
	pixeel.b = cor;
}


int main(void) {
	int32_t wit = 16384;
	int32_t hig = 16384; 
	int cx = wit / 2;
	int cy = hig / 2;
	int r = 16384 / 2;

	size_t total_pixels = (size_t)wit * (size_t)hig;
	std::vector<pixel> data(total_pixels, pixel{0, 0, 0}); 
	for (size_t i = 0; i < total_pixels; i++) {
		int x = i % wit;
		int y = i / wit;
		int dx = x - cx;
		int dy = y - cy;
		if ((dx * dx + dy * dy) <= (r * r)) {
			pintar_pixel_completo(data[i], 255);
		} else {
			pintar_pixel_completo(data[i], 0);
		}
	}
	ppm("image.ppm", data, wit, hig);
	return 0;
}
