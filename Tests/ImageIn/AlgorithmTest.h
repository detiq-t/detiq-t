/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ALGORITHM_TEST_H
#define ALGORITHM_TEST_H

#include "Test.h"
#include "ImageDiff.h"

#include <Image.h>
#include <GenericAlgorithm.h>
#include <AlgorithmException.h>


template<typename D, unsigned int A = 1>
class AlgorithmTest : public Test {
  public:

    AlgorithmTest(std::string name, imagein::GenericAlgorithm_t<D, A> *algo, const std::vector<std::string>& input, const std::string& output, ImageDiff<D> maxDiff)
        : Test(name), _algo(algo), _inputStr(input), _outputStr(output), _maxDiff(maxDiff) {}

    AlgorithmTest(std::string name, imagein::GenericAlgorithm_t<D, 1> *algo, const std::string& input, const std::string& output, ImageDiff<D> maxDiff)
        : Test(name), _algo(algo), _outputStr(output), _maxDiff(maxDiff) {
        _inputStr.push_back(input);
    }
    
    AlgorithmTest(std::string name, imagein::GenericAlgorithm_t<D, 2> *algo, const std::string& input1, const std::string input2, const std::string& output, ImageDiff<D> maxDiff)
        : Test(name), _algo(algo), _outputStr(output), _maxDiff(maxDiff) {
        _inputStr.push_back(input1);
        _inputStr.push_back(input2);
    }
    
    bool init() {
        for(std::vector<std::string>::const_iterator it = _inputStr.begin(); it < _inputStr.end(); ++it) {
            _inputImg.push_back(new imagein::Image_t<D>(*it));
        }
        _outputImg = new imagein::Image_t<D>(_outputStr);
        return true;
    }
    
    bool test() {
        imagein::Image_t<D>* algoImg = (*_algo)(_inputImg);

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
    imagein::GenericAlgorithm_t<D, A> *_algo;
    std::vector<const imagein::Image_t<D>*> _inputImg;
    imagein::Image_t<D>* _outputImg;
    std::vector<std::string> _inputStr;
    std::string _outputStr;
    ImageDiff<D>* _diff;
    ImageDiff<D> _maxDiff;

};

#endif //!ALGORITHM_TEST_H
