#ifndef FILTERING_TEST_H
#define FILTERING_TEST_H

#include "Test.h"
#include "ImageDiff.h"

#include <Image.h>
#include <GenericAlgorithm.h>
#include <AlgorithmException.h>
#include <Algorithm/Filtering.h>

template<typename D>
class FilteringTest : public Test {
  public:

    FilteringTest(std::string name, imagein::GenericAlgorithm_t<int>* algo, const std::string& input, const std::string& output, ImageDiff<D> maxDiff)
        : Test(name), _algo(algo), _outputStr(output), _maxDiff(maxDiff) {
        _inputStr.push_back(input);
    }
    
    bool init() {
        for(std::vector<std::string>::const_iterator it = _inputStr.begin(); it < _inputStr.end(); ++it) {
            imagein::Image_t<D>* img = new imagein::Image_t<D>(*it);
            imagein::Image_t<int>* intImg = Converter<Image_t<D> >::convertToInt(*img);
            _inputImg.push_back(intImg);
        }
        _outputImg = new imagein::Image_t<D>(_outputStr);
        return true;
    }
    
    bool test() {
        imagein::Image_t<int>* algoImg = _algo->operator()(_inputImg);
        imagein::Image_t<D> *img = Converter<Image_t<D> >::makeDisplayable(*algoImg);
        _diff = new ImageDiff<D>(*img, *_outputImg);
        delete img;
        return *_diff <= _maxDiff;
    }
    
    bool cleanup() {
        for(typename std::vector<const imagein::Image_t<int>*>::iterator it = _inputImg.begin(); it < _inputImg.end(); ++it) {
            delete *it;
        }
        delete _outputImg;
        return true;
    }

    std::string info() {
        if(_diff==NULL) return "";
        return _diff->toString();
    }

    ImageDiff<D>* getDiff() { return _diff; }
  
  private:
    imagein::GenericAlgorithm_t<int> *_algo;
    std::vector<const imagein::Image_t<int>* > _inputImg;
    imagein::Image_t<D>* _outputImg;
    std::vector<std::string> _inputStr;
    std::string _outputStr;
    ImageDiff<D>* _diff;
    ImageDiff<D> _maxDiff;

};

#endif //!ALGORITHM_TEST_H
