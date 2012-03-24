
template < class I, unsigned int A>
I* SpecificAlgorithm_t<I,A>::operator() (const std::vector<const imagein::Image_t<typename I::depth_t>*>& imgs) {
    if(imgs.size()!=A) {
        throw NotEnoughImageException(__LINE__, __FILE__);
    }
    return algorithm(imgs);
}
