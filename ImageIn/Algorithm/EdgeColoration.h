#ifndef ALGORITHM_EDGECOLORATION_H
#define ALGORITHM_EDGECOLORATION_H

#include <cstdlib>
#include <cmath>

namespace imagein {
  namespace algorithm {
    
    template <class I, unsigned int A>
    class EdgeColoration_t : public Algorithm_t<I, A>
    {
    public:
      EdgeColoration_t() {
        generateColors();
      }

    private:
      typedef typename I::depth_t D;

      void generateColors()
      {
        for (int i = 0; i < 2 * 3 * A; i += 3) {
          _colors[i] = rand() % 255;
          _colors[i + 1] = rand() % 255;
          _colors[i + 2] = rand() % 255;

          std::cout << _colors[i] << "," << _colors[i + 1] << "," << _colors[i+2] << std::endl;
        }
      }
      
      int _colors[6 * A];

    protected:
      I* algorithm(const std::vector<const I*>& imgs)
      {
        I* result = new I(imgs[0]->getWidth(), imgs[0]->getHeight(), 3);

        for(int j = 0; j < imgs[0]->getHeight(); j++) {
          for(int i = 0; i < imgs[0]->getWidth(); i++) {
            D r, g, b;
            int max(0);
            int max_val(0);
            bool neg(false);
            
            for(int n = 0; n < imgs.size(); n++) {
              D v = imgs[n]->getPixel(i, j, 0);
              if (max_val < std::fabs(v)) {
                max = n;
                max_val = std::fabs(v);
                if (v < 0)
                  neg = true;
                else
                  neg = false;
              }
            }

            int nb = (2 * max + (neg ? 1 : 0));

            std::cout << nb << std::endl;

            r = _colors[3 * nb]     * ((double)max_val / 255.0);
            g = _colors[3 * nb + 1] * ((double)max_val / 255.0);
            b = _colors[3 * nb + 2] * ((double)max_val / 255.0);

            result->setPixel(i, j, 0, r);
            result->setPixel(i, j, 1, g);
            result->setPixel(i, j, 2, b);
          }
        }

        return result;
      }
    };
  }

}

#endif
