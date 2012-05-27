#ifndef CONVERTEDTEST_H
#define CONVERTEDTEST_H

#include "Test.h"
#include "ImageDiff.h"

#include <Image.h>
#include <GenericAlgorithm.h>
#include <AlgorithmException.h>
#include <Converter.h>

template<typename ImageType>
class ConvertedTest : public Test {
  public:
    typedef ImageType::depth depth;

    ConvertedTest(std::string name, imagein::SpecificAlgorithm<ImageType> *algo, const std::vector<std::string>& input, const std::string& output, ImageDiff<D> maxDiff)
        : Test(name), _algo(algo), _inputStr(input), _outputStr(output), _maxDiff(maxDiff) {}

    ConvertedTest(std::string name, imagein::SpecificAlgorithm<ImageType> *algo, const std::string& input, const std::string& output, ImageDiff<D> maxDiff)
        : Test(name), _algo(algo), _outputStr(output), _maxDiff(maxDiff) {
        _inputStr.push_back(input);
    }
    
    bool init() {
        for(std::vector<std::string>::const_iterator it = _inputStr.begin(); it < _inputStr.end(); ++it) {
            Image<depth> image = new Image<depth>(*it);
            ImageType convertedImage = Converter<ImageType>::convert(image);
            _inputImg.push_back(convertedImage);
        }
        _outputImg = new ImageTypeFile(_outputStr);
        return true;
    }
    
    bool test() {
        Image<depth>* algoImg = (*_algo)(_inputImg);

        _diff = new ImageDiff<D>(*algoImg, *_outputImg);
        return *_diff <= _maxDiff;
    }
    
    bool cleanup() {
        for(typename std::vector<const imagein::Image_t<D>*>::iterator it = _inputImg.begin(); it < _inputImg.end(); ++it) {
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
    imagein::SpecificAlgorithm<ImageType> *_algo;
    std::vector<const imagein::Image_t<D>*> _inputImg;
    imagein::Image_t<D>* _outputImg;
    std::vector<std::string> _inputStr;
    std::string _outputStr;
    ImageDiff<D>* _diff;
    ImageDiff<D> _maxDiff;

};

#endif //!ALGORITHM_TEST_H
