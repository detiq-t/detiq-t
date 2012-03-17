

template <typename D, unsigned int A>
imagein::Image_t<D>* imagein::GenericAlgorithm_t<D,A>::operator() (const std::vector<const imagein::Image_t<D>*>& imgs) const {
    if(imgs.size()!=A) {
        throw NotEnoughImageException(__LINE__, __FILE__);
    }
    return algo(imgs);
}
