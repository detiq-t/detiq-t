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



template <typename D, unsigned int A>
imagein::Image_t<D>* imagein::GenericAlgorithm_t<D,A>::operator() (const std::vector<const imagein::Image_t<D>*>& imgs) {
    if(imgs.size()!=A) {
        throw NotEnoughImageException(__LINE__, __FILE__);
    }
    return this->algorithm(imgs);
}

template <typename D>
imagein::Image_t<D>* imagein::GenericAlgorithm_t<D,1>::operator() (const std::vector<const imagein::Image_t<D>*>& imgs) {
    if(imgs.size()!=1) {
        throw NotEnoughImageException(__LINE__, __FILE__);
    }
    return this->algorithm(imgs);
}

template <typename D>
imagein::Image_t<D>* imagein::GenericAlgorithm_t<D,1>::operator() (const imagein::Image_t<D>* img) {
    std::vector<const imagein::Image_t<D>*> imgs;
    imgs.push_back(img);
    return this->algorithm(imgs);
}
