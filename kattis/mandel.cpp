// problem: https://open.kattis.com/problems/mandelbrot

#include<bits/stdc++.h>
using namespace std;

class Complex {
  public:
    double real;
    double comp;
    Complex(double x, double y) {
      real = x;
      comp = y;
    }

    string print() {
      return to_string(real) + ", " + to_string(comp);
    }
};

double norm(Complex c) {
  return sqrt(c.real*c.real + c.comp*c.comp);
}

bool diverges(Complex z, Complex c, int iter) {
  if (norm(z) > 2) return true;
    
  if (iter > 0) {
    // newZ = z^2 + c
    double r = z.real;
    double cp = z.comp;
    // square
    z.real = (r*r - cp*cp);
    z.comp = (2*r*cp);
    // add
    z.real += c.real;
    z.comp += c.comp;
    // old z didnt converge, so if it didnt change...
    if (z.real == r && z.comp == cp) return false;
    return diverges(z, c, iter-1);
  }
  return false;
}

int main() {
  
  string line;
  stringstream ss;
  double x, y;
  int r;
  int i =0 ;
  while ((cin >> x >> y >> r)) {
    Complex zero = Complex(0, 0);
    Complex c = Complex(x, y);
    cout << "Case " << ++i << ": " << 
      (diverges(zero, c, r) ? "OUT" : "IN" ) << endl;
  }

  return 0;
}

