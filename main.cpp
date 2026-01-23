//Esteban Mora, group w/ Garret & Carlos
//1/22/2026
//CPSC-25-12703

#include <iostream>
#include <fstream>

// Adding colors
const int PALETTE_SIZE = 6;

int red[PALETTE_SIZE]   = { 54, 25, 90, 10, 5, 36 };
int green[PALETTE_SIZE] = { 24, 70, 10, 10, 25, 80 };
int blue[PALETTE_SIZE]  = { 10, 10, 92, 15, 20, 10 };


int main() {

    // image dimensions
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int MAX_ITER = 300;

    // make and open the HTML file
    std::ofstream out("mandelbrot.html");
    if (!out) {
        std::cerr << "Error opening HTML output file\n";
        return 1;
    }

    // Write the HTML and JavaScript code to generate the Mandelbrot set
    out << "<!DOCTYPE html>\n<html>\n<body>\n";
    out << "<canvas id='c' width='" << WIDTH << "' height='" << HEIGHT << "'></canvas>\n";
    out << "<script>\n";
    out << "const canvas = document.getElementById('c');\n";
    out << "const ctx = canvas.getContext('2d');\n";
    out << "const img = ctx.createImageData(" << WIDTH << ", " << HEIGHT << ");\n";
    // Push Mandelbrot data into JS arrays
    out << "let data = img.data;\n";

    out << "const PALETTE_SIZE = " << PALETTE_SIZE << ";\n";
   
    // Define color arrays in JS
    out << "const red = [";
    for (int i = 0; i < PALETTE_SIZE; i++) 
    out << red[i] << (i < PALETTE_SIZE - 1 ? ", " : "");
    out << "];\n";

    out << "const green = [";
    for (int i = 0; i < PALETTE_SIZE; i++) 
    out << green[i] << (i < PALETTE_SIZE - 1 ? ", " : "");
    out << "];\n";

    out << "const blue = [";
    for (int i = 0; i < PALETTE_SIZE; i++) 
    out << blue[i] << (i < PALETTE_SIZE - 1 ? ", " : "");
    out << "];\n";

    // Mandelbrot calculation and pixel coloring
    out << "let i = 0;\n";
    out << "for (let y = 0; y < " << HEIGHT << "; y++) {\n";
    out << "  for (let x = 0; x < " << WIDTH << "; x++) {\n";
    out << "    let zx = 0, zy = 0;\n";
    out << "    let cX = (x - " << WIDTH / 2 << ") / 150;\n";
    out << "    let cY = (y - " << HEIGHT / 2 << ") / 150;\n";
    out << "    let iter = " << MAX_ITER << ";\n";
    out << "    while (zx*zx + zy*zy < 4 && iter > 0) {\n";
    out << "      let tmp = zx*zx - zy*zy + cX;\n";
    out << "      zy = 2*zx*zy + cY;\n";
    out << "      zx = tmp;\n";
    out << "      iter--;\n";
    out << "    }\n";

    // option A
    // Color based on iteration count
    out << "    if (iter === 0) {\n";
    out << "      data[i++] = 0;\n";
    out << "      data[i++] = 0;\n";
    out << "      data[i++] = 0;\n";
    out << "      data[i++] = 255;\n"; // alpha
    out << "      continue;\n";
    out << "    } else {\n";
    out << "      let used = " << MAX_ITER << " - iter;\n";
    out << "      iter = (used % PALETTE_SIZE);\n";
    out << "      data[i++] = red[iter];\n";
    out << "      data[i++] = green[iter];\n";
    out << "      data[i++] = blue[iter];\n";
    out << "      data[i++] = 255;\n"; // alpha
    out << "    }\n";

    out << "  }\n";
    out << "}\n";

    // Draw the image on the canvas
    out << "ctx.putImageData(img, 0, 0);\n";
    out << "</script>\n</body>\n</html>\n";

    out.close();
    std::cout << "mandelbrot.html generated — open it in your cloud IDE's browser preview.\n";
    return 0;
}