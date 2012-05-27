

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
