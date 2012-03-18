
template < typename D, template <typename D> class I, unsigned int A>
I<D>* SpecificAlgorithm_t<D,I,A>::operator() (const std::vector<const imagein::Image_t<D>*>& imgs) const {
    if(imgs.size()!=A) {
        throw NotEnoughImageException(__LINE__, __FILE__);
    }
    return algorithm(imgs);
}
