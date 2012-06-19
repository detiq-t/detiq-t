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


    
template <class I>
I* Algorithm_t<I,1>::operator() (const imagein::Image_t<typename I::depth_t>* img) {
    std::vector<const imagein::Image_t<typename I::depth_t>*> imgs;
    imgs.push_back(img);
    return this->algorithm(imgs);
}

template <class I>
I* Algorithm_t<I,2>::operator() (const imagein::Image_t<typename I::depth_t>* img, const imagein::Image_t<typename I::depth_t>* img2) {
    std::vector<const imagein::Image_t<typename I::depth_t>*> imgs;
    imgs.push_back(img);
    imgs.push_back(img2);
    return this->algorithm(imgs);
}

template <class I>
I* Algorithm_t<I,3>::operator() (const imagein::Image_t<typename I::depth_t>* img, const imagein::Image_t<typename I::depth_t>* img2, const imagein::Image_t<typename I::depth_t>* img3) { 
    std::vector<const imagein::Image_t<typename I::depth_t>*> imgs;
    imgs.push_back(img);
    imgs.push_back(img2);
    imgs.push_back(img3);
    return this->algorithm(imgs);
}
